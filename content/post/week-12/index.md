---
author: "Miro Keimiöniemi"
title: "Networking and Communications"
date: "2024-05-07"
description: "Week 14"
tags: 
  - "electronics"
  - "microcontroller"
  - "circuit board"
  - "PCB"
  - "networking"
  - "QTouch"
  - "capacitance"
  - "sensor"
  - "LED"
  - "XIAO"
  - "SAMD21"
  - "debugging"
categories: 
  - "Electronics"
  - "Programming"
series: 
  - "Weekly Assignments"
image: "interboard-communication-attempt.webp"
---

https://docs.arduino.cc/learn/communication/wire/

https://www.arduino.cc/reference/en/language/functions/communication/wire/

```C
#include <Arduino.h>
#include <Wire.h>
#include <FastLED.h>

#define NUM_LEDS 120
#define DATA_PIN D8

CRGB leds[NUM_LEDS];

bool boolValue;
int intValue;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(5);

  Wire.begin();
  Serial.begin(115200);
}

void loop() {
  Wire.requestFrom(8, 2);

  while (Wire.available()) {
    leds[0] = CRGB::Black;
    leds[1] = CRGB::Black;
    leds[2] = CRGB::Black;
    leds[3] = CRGB::Black;
    leds[4] = CRGB::Black;
    leds[5] = CRGB::Black;
    FastLED.show();

    boolValue = Wire.read();
    Serial.print("Boolean value: ");
    Serial.println(boolValue);

    intValue = Wire.read();
    Serial.print("Integer value: ");
    Serial.println(intValue);
  }

  if (boolValue)
  {
    leds[intValue] = CRGB::Red;
    FastLED.show();
  }
  
  delay(500);
}

```

-

```C
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_FreeTouch.h"

Adafruit_FreeTouch qt_1 = Adafruit_FreeTouch(A0, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_2 = Adafruit_FreeTouch(A1, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_3 = Adafruit_FreeTouch(A6, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_4 = Adafruit_FreeTouch(A7, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_5 = Adafruit_FreeTouch(A8, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_6 = Adafruit_FreeTouch(A9, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_7 = Adafruit_FreeTouch(A10, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);

short qt1_baseline = 0;
short qt2_baseline = 0;
short qt3_baseline = 0;
short qt4_baseline = 0;
short qt5_baseline = 0;
short qt6_baseline = 0;
short qt7_baseline = 0;

bool power_on = true;
bool slide = false;
bool tap = false;

char brightness_level = 4;

void requestEvent();

void setup() {
  Serial.begin(115200);
  Serial.println("FreeTouch test");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_LED_RXL, OUTPUT);
  pinMode(PIN_LED_TXL, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(PIN_LED_RXL, HIGH);
  digitalWrite(PIN_LED_TXL, HIGH);

  if (! qt_1.begin())
    Serial.println("Failed to begin qt");
  if (! qt_2.begin())
    Serial.println("Failed to begin qt");
  if (! qt_3.begin())
    Serial.println("Failed to begin qt");
  if (! qt_4.begin())
    Serial.println("Failed to begin qt");
  if (! qt_5.begin())
    Serial.println("Failed to begin qt");
  if (! qt_6.begin())
    Serial.println("Failed to begin qt");
  if (! qt_7.begin())
    Serial.println("Failed to begin qt");

  for (int i = 0; i < 100; i++) {
      qt1_baseline = max(qt1_baseline, qt_1.measure());
      qt2_baseline = max(qt2_baseline, qt_2.measure());
      qt3_baseline = max(qt3_baseline, qt_3.measure());
      qt4_baseline = max(qt4_baseline, qt_4.measure());
      qt5_baseline = max(qt5_baseline, qt_5.measure());
      qt6_baseline = max(qt6_baseline, qt_6.measure());
      qt7_baseline = max(qt7_baseline, qt_7.measure());
    }

  Wire.begin(8);               
  Wire.onRequest(requestEvent);
}

short qt_threshold = 20;
short max_index = 4;
unsigned long tap_start = 0;

void loop() {

  short qt1 = 0;
  short qt2 = 0;
  short qt3 = 0;
  short qt4 = 0;
  short qt5 = 0;
  short qt6 = 0;
  short qt7 = 0;

  digitalWrite(PIN_LED_RXL, HIGH);
  digitalWrite(PIN_LED_TXL, HIGH);

  qt1 = qt_1.measure();
  qt2 = qt_2.measure();
  qt3 = qt_3.measure();
  qt4 = qt_4.measure();
  qt5 = qt_5.measure();
  qt6 = qt_6.measure();
  qt7 = qt_7.measure();

  short qts[] = {qt_threshold, qt1 - qt1_baseline, qt2 - qt2_baseline, qt3 - qt3_baseline, qt4 - qt4_baseline, qt5 - qt5_baseline, qt6 - qt6_baseline, qt7 - qt7_baseline};
  short previous_max_index = max_index;
  max_index = 0;

  for (int i = 0; i <= 7; i++) {
      if (qts[i] > qts[max_index]) {
          max_index = i;
      }
  }

  Serial.print("max_index: ");
  Serial.println(max_index);
  
  // Detect a slide gesture
  if (previous_max_index != 0 && max_index != 0 && previous_max_index != max_index) {
    slide = true;
    tap_start = 0;
  }

  // Detect a tap gesture
  if (previous_max_index == 0 && max_index != 0) {
    tap_start = millis();
  }
  if (tap_start != 0 && ( max_index == 0 || ((millis() - tap_start) > 500))) {
    tap = true;
    tap_start = 0;
  }

  if (tap && power_on) {
    digitalWrite(LED_BUILTIN, HIGH);
    power_on = false;
    tap = false;
  } else if ((tap || slide) && !power_on) {
    digitalWrite(LED_BUILTIN, LOW);
    power_on = true;
    tap = false;
  }

  if (slide) {
    if (max_index != 0) {
      brightness_level = max_index;
    }
    slide = false;
  }

  delay(10);
}

void requestEvent() {
  Wire.write((uint8_t)power_on);
  Wire.write((uint8_t)brightness_level);
}
```

-

```
[1147793][E][Wire.cpp:513] requestFrom(): i2cRead returned Error 263
```

{{< video src="i2c-demo.mp4" loop="true" muted="true" >}}

The demo is not too impressive in terms of accuracy both because of haphazard, quick random wiring and a lot of noise due to long wires and no calibration of sensitivity etc. but the demo clearly demonstrates the LED strip, which is connected to the XIAO ESP32C3 reacting to touch input from the XIAO SAMD21 which communicates with the ESP32C3 in real time over I2C.

![](interboard-communication-attempt.webp)


Initialize wire as the last thing in setup!

lightLED seems to be the issue?


TIMING ISSUE!! Not calling lightLED works for a moment but then starts returning -1

Cleaning code helped





https://docs.arduino.cc/learn/communication/wire/

https://www.arduino.cc/reference/en/language/functions/communication/wire/

https://www.arduino.cc/reference/en/language/functions/communication/wire/setclock/

https://www.arduino.cc/reference/en/language/functions/communication/wire/write/



https://playground.arduino.cc/Code/Time/


WiFi and REST API was not a good fit in the end as it could not be configured flexibly enough with various routers and networks in various places. Bluetooth, however, enables direct connection with less energy consumption, making it significantly more sensible for this.

https://stackoverflow.com/questions/2397822/what-is-the-best-practice-for-dealing-with-passwords-in-git-repositories

As an extension, Bluetooth could be used to setup wifi for further range and larger data throughput but is beyond this project

Flutter installation: https://docs.flutter.dev/get-started/install/windows/mobile

I remember there being some issues when I orginally did it, but it has been a few months and therefore I cannot recall them. The instructions are quite comprehensive however.

Need VS code extensions: https://docs.flutter.dev/get-started/test-drive


Plug-and-play working solution: https://wiki.seeedstudio.com/XIAO_ESP32C3_Bluetooth_Usage/  


## Bluetooth Low Energy

```C
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
    leds[15] = color;
    leds[16] = color;
    leds[17] = color;
    leds[18] = color;
    leds[19] = color;
    leds[20] = color;
    leds[21] = color;
    leds[22] = color;
    leds[23] = color;
    leds[24] = color;
    leds[25] = color;
    leds[26] = color;
    leds[27] = color;
    leds[28] = color;
    leds[29] = color;
    leds[30] = color;
    leds[31] = color;
    leds[32] = color;
    leds[33] = color;
    leds[34] = color;
    leds[35] = color;
    leds[36] = color;

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
```

{{< video src="bluetooth-demo.mp4" loop="true" muted="true" >}}

https://wiki.seeedstudio.com/XIAO_ESP32C3_Bluetooth_Usage/






