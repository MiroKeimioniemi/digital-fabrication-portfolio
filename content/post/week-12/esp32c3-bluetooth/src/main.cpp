// Include the necessary libraries
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
CRGB veryLongLEDs1[NUM_LEDS_1 + NUM_LEDS_2];
CRGB shortLEDs1[NUM_LEDS_2];
// CRGB shortLEDs2[NUM_LEDS_2];

// Define lamp state variables
int isOn = true;
int brightness = 100;
CRGB color = CRGB::White;
int animation = 1;
time_t nextAlarm;
time_t currentTime;

int animationStep = 0;
unsigned long lastAdvertisingTime = 0; // Keep track of the last time we started advertising
bool deviceConnected = false;
bool oldDeviceConnected = false;

bool fromApp = false;
bool fromDevice = false;

bool brightening(int i);

// Define the callback classes for the BLE characteristics

// Callback class for the color characteristic
class ColorCallback: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    uint8_t* data = pCharacteristic->getData(); // Get the data as a byte array
    int length = pCharacteristic->getValue().length(); // Get the length of the data

    if (length == 4) { // Check if the length of the data is 4 (length of a 32-bit integer)
      uint32_t value = *((uint32_t*)data); // Interpret the data as a 32-bit integer
      color = CRGB((value >> 16) & 0xFF, (value >> 8) & 0xFF, value & 0xFF); // Create a CRGB color from the integer
    }
  }
};

class NumberCallback: public BLECharacteristicCallbacks {
  int *number;

  public:
    NumberCallback(int *number): number(number) {}

    void onRead(BLECharacteristic *pCharacteristic) {
      pCharacteristic->setValue(*number);

      fromApp = true;
    }

    void onWrite(BLECharacteristic *pCharacteristic) {
      uint8_t* data = pCharacteristic->getData(); // Get the data as a byte array
      int length = pCharacteristic->getValue().length(); // Get the length of the data

      if (length == 1) { // Check if the length of the data is 1 (length of an 8-bit integer)
        *number = *data; // Interpret the data as an 8-bit integer

        Wire.beginTransmission(8);
        Wire.write(isOn);
        Wire.write(brightness);
        Wire.endTransmission();

        fromApp = true;
      }
    }
};

time_t toLittleEndian(uint8_t* data) {
    // Assuming time_t is 4 bytes (32 bits)
    time_t result = 0;
    for (int i = 0; i < 4; i++) {
        result |= ((time_t)data[i] << (8 * i));
    }
    return result;
}

class TimeCallback: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        uint8_t* data = pCharacteristic->getData(); // Get the data as a byte array
        int length = pCharacteristic->getValue().length(); // Get the length of the data

        if (length == 5) { // Check if the length of the data is 5 (1 byte for the flag + 4 bytes for the timestamp)
            uint8_t flag = data[0]; // The first byte is the flag
            time_t value = toLittleEndian(data + 1); // The rest of the data is the timestamp

            if (flag == 1) {
                nextAlarm = value;
            } else if (flag == 0) {
                currentTime = value;
            }
        }
    }
};

class ServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  }

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
  }
};

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

  // Initialize the serial communication
  Serial.begin(115200);

  Wire.begin();

  // Initialize the BLE server
  BLEDevice::init("LED Zeppelin");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks());

  // Create the service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create the characteristics
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

  // Set the callbacks for the characteristics
  pOnCharacteristic->setCallbacks(new NumberCallback(&isOn));
  pBrightnessCharacteristic->setCallbacks(new NumberCallback(&brightness));
  pColorCharacteristic->setCallbacks(new ColorCallback());
  pAnimationCharacteristic->setCallbacks(new NumberCallback(&animation));
  pNextAlarmCharacteristic->setCallbacks(new TimeCallback());

  // Add user descriptions
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

  // Start advertising
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  BLEDevice::startAdvertising();
  pAdvertising->start();
}

unsigned long lastSync = 0; // Keep track of the last  sync

void loop() {
  unsigned long currentTimeElapsed = millis(); // Get the current time

  // Check if it's been 5 seconds since we last started advertising
  if (currentTimeElapsed - lastAdvertisingTime >= 5000) {
    // Restart advertising
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();

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

  if (Wire.requestFrom(8, 2) == 2) {

  while (Wire.available()) {
    int newIsOn = Wire.read();
    int newBrightness = Wire.read();

    // Sync values 
    if (newIsOn != isOn) {
      isOn = newIsOn;

      Wire.beginTransmission(8);
      Wire.write(isOn);
      Wire.write(brightness);
      Wire.endTransmission();

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
  if (currentTimeElapsed - lastSync > 1000) {
    fromApp = false;
    lastSync = currentTimeElapsed;
  }
  
  // disconnecting
  if (!deviceConnected && oldDeviceConnected) {
      pServer->startAdvertising(); // restart advertising
      Serial.println("start advertising");
      oldDeviceConnected = deviceConnected;
  }

  if (isOn == 0) {
    animationStep = 0;
    FastLED.clear();
    FastLED.show();
  } else {
    
    if (animation == 3) {
      brightening(animationStep) ? animationStep = 0 : animationStep++;
    } else {

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
