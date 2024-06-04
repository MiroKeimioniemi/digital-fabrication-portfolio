// Include the necessary libraries
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <FastLED.h>
#include <Wire.h>

// Define the UUIDs for the Bluetooth Low Energy (BLE) peripheral service and its characteristics
#define SERVICE_UUID        "6932598e-c4fe-4855-9701-240a78abc000"
#define ON_CHARACTERISTIC_UUID "dfc1a400-3523-4626-bd77-3469dbed8b74"
#define BRIGHTNESS_CHARACTERISTIC_UUID "05f52bf8-4823-42c6-8647-dc89b76ad4e4"
#define COLOR_CHARACTERISTIC_UUID "b2516e35-6917-43b7-8cad-c7065a9e0033"
#define ANIMATION_CHARACTERISTIC_UUID "0d72cbb7-742f-4030-b4ec-3aefb8c1eb1a"

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
// int nextAlarm = 0;
// int time = 0;
int animationStep = 0;

bool brightening(int i);

// Define the callback classes for the BLE characteristics

// Callback class for the color characteristic
class ColorCallback: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value.length() == 6) { // Check if the length of the value is 6 (length of a hex color code without '#')
        long number = strtol(value.c_str(), NULL, 16); // Convert the hex color code to a long integer
        color = CRGB((number >> 16) & 0xFF, (number >> 8) & 0xFF, number & 0xFF); // Create a CRGB color from the hex color code
      }
    }
};

// Callback class for the number characteristics
class NumberCallback: public BLECharacteristicCallbacks {
    int *number;

    public:
      NumberCallback(int *number): number(number) {}

      void onRead(BLECharacteristic *pCharacteristic) {
        pCharacteristic->setValue(std::to_string(*number));
      }

      void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        *number = std::stoi(value);

        Wire.beginTransmission(8);
        Wire.write(isOn);
        Wire.write(brightness);
        Wire.endTransmission();
      }
};

// class TimeCallback: public BLECharacteristicCallbacks {

// }

void setup() {
  // Initialize the LED strips
  FastLED.addLeds<NEOPIXEL, DATA_PIN_1>(shortLEDs1, NUM_LEDS_2);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_2>(longLEDs1, NUM_LEDS_1);
  // FastLED.addLeds<NEOPIXEL, DATA_PIN_3>(longLEDs2, NUM_LEDS_1);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_4>(veryLongLEDs1, (NUM_LEDS_1 + NUM_LEDS_2));
  FastLED.setBrightness(brightness);

  // Initialize the serial communication
  Serial.begin(115200);

  Wire.begin();

  // Initialize the BLE server
  BLEDevice::init("LED Zeppelin");
  BLEServer *pServer = BLEDevice::createServer();

  // Create the service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create the characteristics
  BLECharacteristic *pOnCharacteristic = pService->createCharacteristic(
                                          ON_CHARACTERISTIC_UUID,
                                          BLECharacteristic::PROPERTY_READ |
                                          BLECharacteristic::PROPERTY_WRITE
                                        );
  BLECharacteristic *pBrightnessCharacteristic = pService->createCharacteristic(
                                          BRIGHTNESS_CHARACTERISTIC_UUID,
                                          BLECharacteristic::PROPERTY_READ |
                                          BLECharacteristic::PROPERTY_WRITE
                                        );
  BLECharacteristic *pColorCharacteristic = pService->createCharacteristic(
                                          COLOR_CHARACTERISTIC_UUID,
                                          BLECharacteristic::PROPERTY_READ |
                                          BLECharacteristic::PROPERTY_WRITE
                                        );
  BLECharacteristic *pAnimationCharacteristic = pService->createCharacteristic(
                                          ANIMATION_CHARACTERISTIC_UUID,
                                          BLECharacteristic::PROPERTY_READ |
                                          BLECharacteristic::PROPERTY_WRITE
                                        );

  // Set the callbacks for the characteristics
  pOnCharacteristic->setCallbacks(new NumberCallback(&isOn));
  pBrightnessCharacteristic->setCallbacks(new NumberCallback(&brightness));
  pColorCharacteristic->setCallbacks(new ColorCallback());
  pAnimationCharacteristic->setCallbacks(new NumberCallback(&animation));

  // Add user descriptions.
  BLEDescriptor *pOnDescriptor = new BLEDescriptor(BLEUUID((uint16_t)0x2901));
  pOnDescriptor->setValue("On Characteristic");
  pOnCharacteristic->addDescriptor(pOnDescriptor);

  BLEDescriptor *pBrightnessDescriptor = new BLEDescriptor(BLEUUID((uint16_t)0x2901));
  pBrightnessDescriptor->setValue("Brightness Characteristic");
  pBrightnessCharacteristic->addDescriptor(pBrightnessDescriptor);

  BLEDescriptor *pColorDescriptor = new BLEDescriptor(BLEUUID((uint16_t)0x2901));
  pColorDescriptor->setValue("Color Characteristic");
  pColorCharacteristic->addDescriptor(pColorDescriptor);

  BLEDescriptor *pAnimationDescriptor = new BLEDescriptor(BLEUUID((uint16_t)0x2901));
  pAnimationDescriptor->setValue("Animation Characteristic");
  pAnimationCharacteristic->addDescriptor(pAnimationDescriptor);

  // Set the initial values for the characteristics
  pOnCharacteristic->setValue("1");
  pBrightnessCharacteristic->setValue("100");
  pColorCharacteristic->setValue("FFFFFF");
  pAnimationCharacteristic->setValue("0");

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void loop() {

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
    }

    if (newBrightness != brightness) {
      brightness = newBrightness;

      Wire.beginTransmission(8);
      Wire.write(isOn);
      Wire.write(brightness);
      Wire.endTransmission();
    }
  }

  }

  if (isOn == 0) {
    FastLED.clear();
    FastLED.show();
  } else {
    
    if (animation == 1) {
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

  Serial.println("On:");
  Serial.println(isOn);
  Serial.println("Brightness:");
  Serial.println(brightness);
  Serial.println("Animation:");
  Serial.println(animation);
}

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
    delay(100);
    
    return (i >= 240) ? true : false;
  }

