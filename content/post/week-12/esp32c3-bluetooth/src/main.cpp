// Include the necessary libraries
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <FastLED.h>

// Define the UUIDs for the Bluetooth Low Energy (BLE) peripheral service and its characteristics
#define SERVICE_UUID        "6932598e-c4fe-4855-9701-240a78abc000"
#define ON_CHARACTERISTIC_UUID "dfc1a400-3523-4626-bd77-3469dbed8b74"
#define BRIGHTNESS_CHARACTERISTIC_UUID "05f52bf8-4823-42c6-8647-dc89b76ad4e4"
#define COLOR_CHARACTERISTIC_UUID "b2516e35-6917-43b7-8cad-c7065a9e0033"
#define ANIMATION_CHARACTERISTIC_UUID "0d72cbb7-742f-4030-b4ec-3aefb8c1eb1a"

// Define the LED strips and the data pins used to control them
#define NUM_LEDS 120
#define DATA_PIN D8

CRGB leds[NUM_LEDS];

// Define lamp state variables
int isOn = true;
int brightness = 100;
CRGB color = CRGB::White;
int animation = 0;
// int nextAlarm = 0;
// int time = 0;

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

      void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        *number = std::stoi(value);
      }
};

// class TimeCallback: public BLECharacteristicCallbacks {

// }

void setup() {
  // Initialize the LED strip
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(250);

  // Initialize the serial communication
  Serial.begin(115200);

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

  if (isOn == 0) {
    FastLED.clear();
    FastLED.show();
  } else {
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

    FastLED.setBrightness(brightness);
    FastLED.show();
  }

  Serial.println("On:");
  Serial.println(isOn);
  Serial.println("Brightness:");
  Serial.println(brightness);
  Serial.println("Animation:");
  Serial.println(animation);

  delay(1000);
}