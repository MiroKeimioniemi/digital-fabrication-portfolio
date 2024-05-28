// Include the necessary libraries
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <FastLED.h>

// Define the UUIDs for the Bluetooth Low Energy (BLE) peripheral service and its characteristics
#define SERVICE_UUID        "6932598e-c4fe-4855-9701-240a78abc000"
#define CHARACTERISTIC_UUID "b2516e35-6917-43b7-8cad-c7065a9e0033"

// Define the LED strips and the data pins used to control them
#define NUM_LEDS 120
#define DATA_PIN D8

CRGB leds[NUM_LEDS];

// Lamp state variables
bool isOn = true;
char brightness = 250;
CRGB color = CRGB::Black;
char animation = 0;
int nextAlarm = 0;
int time = 0;

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value.length() == 6) { // Check if the length of the value is 6 (length of a hex color code without '#')
        long number = strtol(value.c_str(), NULL, 16); // Convert the hex color code to a long integer
        color = CRGB((number >> 16) & 0xFF, (number >> 8) & 0xFF, number & 0xFF); // Create a CRGB color from the hex color code

        Serial.println("*********");
        Serial.print("New color: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);

        Serial.println();
        Serial.println("*********");
      }
    }
};

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(250);

  Serial.begin(115200);

  BLEDevice::init("MyESP32");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("Hello World");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void loop() {
  // put your main code here, to run repeatedly:
  leds[3] = color;
  leds[4] = color;
  leds[5] = color;
  leds[6] = color;
  leds[7] = color;
  leds[8] = color;
  leds[9] = color;
  leds[10] = color;
  leds[11] = color;
  leds[12] = color;
  leds[13] = color;
  leds[14] = color;
  FastLED.show();
  delay(200);
}