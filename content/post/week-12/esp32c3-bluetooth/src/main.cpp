// Code for the XIAO ESP32C3 handling the LED output and BLE communication of the "LED Zeppelin" gesture controlled lamp

// Include the necessary libraries (Arduino framwork must be explicitly included in PlatformIO)
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <FastLED.h>
#include <Wire.h>
#include <BLE2902.h>

// Define the UUIDs for the Bluetooth Low Energy (BLE) peripheral service and its characteristics
#define SERVICE_UUID        "6932598e-c4fe-4855-9701-240a78abc000"
#define ON_CHARACTERISTIC_UUID "dfc1a400-3523-4626-bd77-3469dbed8b74"
#define BRIGHTNESS_CHARACTERISTIC_UUID "05f52bf8-4823-42c6-8647-dc89b76ad4e4"
#define COLOR_CHARACTERISTIC_UUID "b2516e35-6917-43b7-8cad-c7065a9e0033"
#define ANIMATION_CHARACTERISTIC_UUID "0d72cbb7-742f-4030-b4ec-3aefb8c1eb1a"
#define NEXT_ALARM_CHARACTERISTIC_UUID "2b3e71d1-4c3e-418e-942b-67f28951c2d3"

// Define the LED strips and the data pins used to control them
#define NUM_LEDS_1 38
#define NUM_LEDS_2 17
#define DATA_PIN_1 D0
#define DATA_PIN_2 D1
#define DATA_PIN_3 D2 
#define DATA_PIN_4 D8

CRGB longLEDs1[NUM_LEDS_1];
// CRGB longLEDs2[NUM_LEDS_1];
CRGB veryLongLEDs1[NUM_LEDS_1 + NUM_LEDS_2];  // There are only two different lengths of LED strips but the third and fourth had to be soldered together due to a fault in the hardware
CRGB shortLEDs1[NUM_LEDS_2];
// CRGB shortLEDs2[NUM_LEDS_2];

// Define lamp state variables and set defaults
int isOn = true;            // Boolean flag to indicate whether the LEDs should be on or off
int brightness = 100;       // Brightness level of the LEDs (0-255)
CRGB color = CRGB::White;   // Color of the LEDs as red, green and blue components (0-255)
int animation = 1;          // Animation mode for the LEDs (0-3) 0 = static, 1 = breathing, 2 = rainbow, 3 = brightening
time_t nextAlarm;           // Time for when to trigger the next alarm (in seconds since the Unix epoch)
time_t currentTime;         // Current time (in seconds since the Unix epoch)

// Define helper variables
int animationStep = 0;                  // Step counter to enable non-blocking animations
unsigned long lastAdvertisingTime = 0;  // Keep track of the last time the bluetooth service was advertised
bool deviceConnected = false;           // Boolean flag to indicate whether a device is currently connected
bool oldDeviceConnected = false;        // Boolean flag to indicate whether a device was previously connected
bool fromApp = false;                   // Boolean flag to indicate whether the value was set from the app via BLE
bool fromDevice = false;                // Boolean flag to indicate whether the value was set from the device via I2C

bool brightening(int i);    // Function declaration for an animation uniformly brightening the LEDs


// Define the callback classes for the BLE characteristics

class ColorCallback: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {    // Callback function for when the characteristic is written to

    uint8_t* data = pCharacteristic->getData();         // Get the data as a byte array
    int length = pCharacteristic->getValue().length();  // Get the length of the data

    if (length == 4) {  // Check if the data is a 32-bit integer (4 bytes)
      uint32_t value = *((uint32_t*)data);  // Interpret the data as a 32-bit integer
      color = CRGB((value >> 16) & 0xFF, (value >> 8) & 0xFF, value & 0xFF);  // Create a CRGB color from the integer and set it as the new color
    }
  }
};

class NumberCallback: public BLECharacteristicCallbacks {
  int *number;  // Pointer to the integer value that the characteristic represents

  public:
    NumberCallback(int *number): number(number) {}    // Constructor to set the pointer to the integer value

    void onRead(BLECharacteristic *pCharacteristic) { // Callback function for when the characteristic is read
      pCharacteristic->setValue(*number);             // Set the value of the characteristic to the integer value
      fromApp = true;
    }

    void onWrite(BLECharacteristic *pCharacteristic) {
      uint8_t* data = pCharacteristic->getData();
      int length = pCharacteristic->getValue().length();

      if (length == 1) {  // Check if the data is an 8-bit integer (1 byte)
        *number = *data;  // Interpret the data as an 8-bit integer

        Wire.beginTransmission(8);  // Begin the I2C transmission to the device with address 8
        Wire.write(isOn);           // Write the isOn value to the connected device
        Wire.write(brightness);     // Write the brightness value to the connected device
        Wire.endTransmission();     // End the I2C transmission

        fromApp = true;
      }
    }
};

// A helper function to convert a 4-byte data array to a 32-bit integer in little-endian order
time_t toLittleEndian(uint8_t* data) {
    time_t result = 0;
    for (int i = 0; i < 4; i++) {
        result |= ((time_t)data[i] << (8 * i));
    }
    return result;
};

class TimeCallback: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        uint8_t* data = pCharacteristic->getData();
        int length = pCharacteristic->getValue().length();

        if (length == 5) {                            // Check if the length of the data is 5 (1 byte for the flag + 4 bytes for the timestamp)
            uint8_t flag = data[0];                   // Interpret the first byte as a flag
            time_t value = toLittleEndian(data + 1);  // Interpret the remaining 4 bytes as a 32-bit timestamp in little-endian order

            // Set the appropriate time variable based on the flag
            if (flag == 1) {
                nextAlarm = value;
            } else if (flag == 0) {
                currentTime = value;
            }
        }
    }
};

class ServerCallbacks: public BLEServerCallbacks {
  // Set the deviceConnected flag to true when a device connects to the server
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  }
  // Set the deviceConnected flag to false when a device disconnects from the server
  void onDisconnect(BLEServer* pServer) {  
    deviceConnected = false;
  }
};

// Initialize the BLE server and characteristics outside the setup to be globally accessible in the loop
BLEServer *pServer = nullptr;
BLECharacteristic *pOnCharacteristic = nullptr;
BLECharacteristic *pBrightnessCharacteristic = nullptr;
BLECharacteristic *pColorCharacteristic = nullptr;
BLECharacteristic *pAnimationCharacteristic = nullptr;
BLECharacteristic *pNextAlarmCharacteristic = nullptr;

void setup() {
  // Initialize the LED strips
  FastLED.addLeds<NEOPIXEL, DATA_PIN_1>(shortLEDs1, NUM_LEDS_2);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_2>(longLEDs1, NUM_LEDS_1);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_4>(veryLongLEDs1, (NUM_LEDS_1 + NUM_LEDS_2));
  FastLED.setBrightness(brightness);

  // Initialize serial communication
  Serial.begin(115200);

  // Initialize I2C communication in master mode
  Wire.begin();

  // Initialize the BLE server and name the device
  BLEDevice::init("LED Zeppelin");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks());

  // Create the BLE service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create the BLE characteristics for the service with read, write, notify and indicate properties
  pOnCharacteristic = pService->createCharacteristic(
                                          ON_CHARACTERISTIC_UUID,
                                          BLECharacteristic::PROPERTY_READ |
                                          BLECharacteristic::PROPERTY_WRITE |
                                          BLECharacteristic::PROPERTY_NOTIFY |
                                          BLECharacteristic::PROPERTY_INDICATE
                                        );
  pBrightnessCharacteristic = pService->createCharacteristic(
                                          BRIGHTNESS_CHARACTERISTIC_UUID,
                                          BLECharacteristic::PROPERTY_READ |
                                          BLECharacteristic::PROPERTY_WRITE |
                                          BLECharacteristic::PROPERTY_NOTIFY |
                                          BLECharacteristic::PROPERTY_INDICATE
                                        );
  pColorCharacteristic = pService->createCharacteristic(
                                          COLOR_CHARACTERISTIC_UUID,
                                          BLECharacteristic::PROPERTY_READ |
                                          BLECharacteristic::PROPERTY_WRITE |
                                          BLECharacteristic::PROPERTY_NOTIFY |
                                          BLECharacteristic::PROPERTY_INDICATE
                                        );
  pAnimationCharacteristic = pService->createCharacteristic(
                                          ANIMATION_CHARACTERISTIC_UUID,
                                          BLECharacteristic::PROPERTY_READ |
                                          BLECharacteristic::PROPERTY_WRITE |
                                          BLECharacteristic::PROPERTY_NOTIFY |
                                          BLECharacteristic::PROPERTY_INDICATE
                                        );
  pNextAlarmCharacteristic = pService->createCharacteristic(
                                          NEXT_ALARM_CHARACTERISTIC_UUID,
                                          BLECharacteristic::PROPERTY_READ |
                                          BLECharacteristic::PROPERTY_WRITE |
                                          BLECharacteristic::PROPERTY_NOTIFY |
                                          BLECharacteristic::PROPERTY_INDICATE
                                        );

  // Set the callbacks (event/request handlers) for the characteristics
  pOnCharacteristic->setCallbacks(new NumberCallback(&isOn));
  pBrightnessCharacteristic->setCallbacks(new NumberCallback(&brightness));
  pColorCharacteristic->setCallbacks(new ColorCallback());
  pAnimationCharacteristic->setCallbacks(new NumberCallback(&animation));
  pNextAlarmCharacteristic->setCallbacks(new TimeCallback());

  // Add BLE descriptors to the characteristics to enable notifications
  BLE2902 *pOnDescriptor = new BLE2902();
  // pOnDescriptor->setValue("On Characteristic");
  pOnCharacteristic->addDescriptor(pOnDescriptor);
  pOnDescriptor->setNotifications(true);

  BLE2902 *pBrightnessDescriptor = new BLE2902();
  // pBrightnessDescriptor->setValue("Brightness Characteristic");
  pBrightnessCharacteristic->addDescriptor(pBrightnessDescriptor);
 pBrightnessDescriptor->setNotifications(true);

  BLE2902 *pColorDescriptor = new BLE2902();
  // pColorDescriptor->setValue("Color Characteristic");
  pColorCharacteristic->addDescriptor(pColorDescriptor);
  pColorCharacteristic->setNotifyProperty(true);

  BLE2902 *pAnimationDescriptor = new BLE2902();
  // pAnimationDescriptor->setValue("Animation Characteristic");
  pAnimationCharacteristic->addDescriptor(pAnimationDescriptor);
  pAnimationCharacteristic->setNotifyProperty(true);

  BLE2902 *pNextAlarmDescriptor = new BLE2902();
  // pNextAlarmDescriptor->setValue("Next Alarm Characteristic");
  pNextAlarmCharacteristic->addDescriptor(pNextAlarmDescriptor);
  pNextAlarmCharacteristic->setNotifyProperty(true);

  // Set the initial values for the characteristics
  pOnCharacteristic->setValue((uint8_t*)&isOn, 1);
  pBrightnessCharacteristic->setValue((uint8_t*)&brightness, 1);
  pColorCharacteristic->setValue((uint8_t*)&color, 4);
  pAnimationCharacteristic->setValue((uint8_t*)&animation, 1);
  pNextAlarmCharacteristic->setValue((uint8_t*)&nextAlarm, 4);

  // Start the service
  pService->start();

  // Start advertising the server
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  BLEDevice::startAdvertising();
  pAdvertising->start();
}

unsigned long lastSync = 0; // Initialize a variable to keep track of the last time the values were synced

void loop() {
  unsigned long currentTimeElapsed = millis();  // Get the current time

  // Restart advertising every 5 seconds so that the device stays discoverable after being disconnected
  if (currentTimeElapsed - lastAdvertisingTime >= 5000) {
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();

    // Send the current values of the other characteristics to the connected device over BLE

    // // Create a 32-bit color value in ARGB format
    // uint32_t colorValue = 0xFF000000 | ((color.r & 0xFF) << 16) | ((color.g & 0xFF) << 8) | (color.blue & 0xFF);

    // // Convert the color value to a 4-byte array in little-endian order
    // uint8_t colorArray[4];
    // colorArray[0] = colorValue & 0xFF;
    // colorArray[1] = (colorValue >> 8) & 0xFF;
    // colorArray[2] = (colorValue >> 16) & 0xFF;
    // colorArray[3] = (colorValue >> 24) & 0xFF;

    // // Set the characteristic value and send the notification
    // pColorCharacteristic->setValue(colorArray, 4);
    // pColorCharacteristic->notify();

    // uint8_t animationValue = (uint8_t)animation;
    // pAnimationCharacteristic->setValue(&animationValue, 1);
    // pAnimationCharacteristic->notify();

    // uint8_t nextAlarmValue = (uint8_t)nextAlarm;
    // pNextAlarmCharacteristic->setValue(&nextAlarmValue, 1);
    // pNextAlarmCharacteristic->notify();

    // // Update the last advertising time
    // lastAdvertisingTime = currentTimeElapsed;
  }

  // Check if there is data available on the I2C bus
  if (Wire.requestFrom(8, 2) == 2) {

    // Sync values from the conductance sensor via I2C
    while (Wire.available()) {
      int newIsOn = Wire.read();
      int newBrightness = Wire.read();

      // Update the values only if they have changed
      if (newIsOn != isOn) {
        isOn = newIsOn;

        Wire.beginTransmission(8);
        Wire.write(isOn);
        Wire.write(brightness);
        Wire.endTransmission();

        // Rewrite and notify of the BLE characteristic change if the value was set based on the conductivity sensor
        if (deviceConnected && !fromApp) {
          uint8_t isOnValue = (uint8_t)isOn;
          pOnCharacteristic->setValue(&isOnValue, 1);
          pOnCharacteristic->notify();
        }
      }

      if (newBrightness != brightness) {
        brightness = newBrightness;

        Wire.beginTransmission(8);
        Wire.write(isOn);
        Wire.write(brightness);
        Wire.endTransmission();

        if (deviceConnected && !fromApp) {
        uint8_t brightnessValue = (uint8_t)brightness;
          pBrightnessCharacteristic->setValue(&brightnessValue, 1);
          pBrightnessCharacteristic->notify();
        }
      }
    }
  }

  // Reset the app signifier flags periodically
  if (currentTimeElapsed - lastSync > 1000) {
    fromApp = false;
    lastSync = currentTimeElapsed;
  }
  
  // Restart advertising if a device was connected and then disconnected
  if (!deviceConnected && oldDeviceConnected) {
      pServer->startAdvertising();
      Serial.println("start advertising");
      oldDeviceConnected = deviceConnected;
  }

  if (isOn == 0) {      // If the lamp is off, turn off the LEDs and reset the animation
    animation = 0;
    animationStep = 0;
    FastLED.clear();
    FastLED.show();
  } else {              
    
    if (animation == 3) {  // If the lamp is on and the animation mode is set to brightening, advance the animation by one step or restart it if it has reached the end
      brightening(animationStep) ? animationStep = 0 : animationStep++;
    } else {               // If the lamp is on and the animation mode is not set to brightening, set the LEDs to the current color and brightness

      for(int i = 0; i < NUM_LEDS_1; i++) {
        longLEDs1[i] = color;
        // longLEDs2[i] = color;
      }
      for(int i = 0; i < NUM_LEDS_2; i++) {
        shortLEDs1[i] = color;
        // shortLEDs2[i] = color;
      }
      for(int i = 0; i < (NUM_LEDS_1 + NUM_LEDS_2); i++) {
        veryLongLEDs1[i] = color;
      }

      FastLED.setBrightness(brightness);
      FastLED.show();
    }
  }

  // Serial.println("On:");
  // Serial.println(isOn);
  // Serial.println("Brightness:");
  // Serial.println(brightness);
  // Serial.println("Animation:");
  // Serial.println(animation);
  // Serial.println(ctime(&nextAlarm));
  // Serial.println(ctime(&currentTime));
};

// Function to uniformly brighten the LEDs
bool brightening(int i) {
    for(int j = 0; j < NUM_LEDS_1; j++) {
      longLEDs1[j] = CRGB(i, i, i);
      // longLEDs2[j] = CRGB(i, i, i);
    }
    for(int j = 0; j < NUM_LEDS_2; j++) {
      shortLEDs1[j] = CRGB(i, i, i);
      // shortLEDs2[j] = CRGB(i, i, i);
    }
    for(int j = 0; j < (NUM_LEDS_1 + NUM_LEDS_2); j++) {
      veryLongLEDs1[j] = CRGB(i, i, i);
    }
    FastLED.show();
    delay(50);
    
    return (i >= 240) ? true : false;
}
