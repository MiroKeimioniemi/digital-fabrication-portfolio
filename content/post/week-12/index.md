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
  - "I2C"
  - "ESP32C"
  - "Wi-Fi"
  - "Bluetooth Low Energy"
  - "BLE"
  - "Ccmmunication"
  - "debugging"
categories: 
  - "Electronics"
  - "Programming"
series: 
  - "Weekly Assignments"
image: "final-pcb.jpg"
---

This and much of the documentation of the following weeks apart from system integration, is written retroactively after the major crunch necessary to finish the final project in time. As a result, the extensiveness, detailedness and particularly the story beats relating to the details of the ups and downs might be a bit lacking in terms of detail in comparison to previous weeks. 

As can be seen below, our assignment was to specifically explore the Wi-Fi capabilities of the XIAO ESP32C3 board, which I had already chosen to be the main microcontroller of my final project. I explored the Wi-Fi route for a moment but quickly determined that it would not be optimal for the wireless communication necessary for the [final project]({{< relref "page/final-project/index.md" >}}) due to how it would either limit its usage into a single network and therefore space, or the connected device's internet access without significantly increasing the project's complexity. Instead, Bluetooth Low Energy was practically perfect for intermittently sending a few integers back and forth, which is why I chose that as the primary wireless communication protocol. 

I used the XIAO SAMD21 for detecting touch and recognizing gestures and hence I had to sync the internal state of the lamp between the two microcontrollers. This I chose to do via I2C mostly because of the pin configurations of the XIAOs but also due to its simplicity of use. 

## Assignments

**Group assignment**

- Join an introduction session to get an overview of networking possibilities with XIAO ESP32
- Pick a group leader who is going to populate the group assignment page
  
**Individual assignment**

- Link to the group assignment page and describe what did you learn individually.
- Explore the WiFi capabilities of the XIAO ESP32C3 board.
- Plug it into one of the boards you produced earlier.
- Program the XIAO board to spawn an Access Point and create a simple REST API.
- The REST API should have endpoints for controlling output device(s) of your board as well as reading input.
- Document as you go and publish content on a page on your documentation website.

## Inter-Integrated Circuit (I2C)

I started, in order of importance, with the Inter-Integrated Circuit (I2C) protocol to make the microcontrollers communicate with each other locally using the [Arduino Wire library](https://www.arduino.cc/reference/en/language/functions/communication/wire/). To begin, I studied the I2C protocol and its concrete implementation from [this article](https://docs.arduino.cc/learn/communication/wire/). In short, it is a relatively simple protocol for transferring data over short distances between microcontrollers and sensors on the same board or closely connected to it using only two pins: the serial clock pin (SCL) and the serial data pin (SDA). The SCL provides a steady clock signal by pulsing at a regular interval so that the data pin can be used to transmit data both ways and to multiple peripherals with different addresses. Therefore, multiple devices can be connected to a bus and they can all individually send and receive data from the master.

To implement I2C in practice, make sure that all devices share common ground and connect the SDA pin of the master to the SDA pins of the slaves and likewise the SCL pins to SCL pins. Between boards, this is typically done via [Qwiic](https://www.sparkfun.com/qwiic), [STEMMA QT](https://learn.adafruit.com/introducing-adafruit-stemma-qt/what-is-stemma-qt) or [Grove](https://wiki.seeedstudio.com/Grove_System/) connectors but as, for my final board, I had all the components on the same board, it sufficed to connect the XIAOs SDA to SDA and SCL to SCL via traces on the board as the whole board shared the same ground anyway.

The [example code](https://docs.arduino.cc/learn/communication/wire/#examples) in the article is very simple and worked immediately as expected. Adapting it for my code was not immediately successful, however, as I continued to bump into the following error message on the master device on my first attempt:

```
[1147793][E][Wire.cpp:513] requestFrom(): i2cRead returned Error 263
```

![I2C request error](interboard-communication-attempt.webp)

I never quite figured out what exactly the issue was as sit might have something to do with the poor connection due to our lab not having the correct 4-pin JST connectors and me imporvising with regular jumper cables in the too tight connector as shown above. It was unfortunate that the testing did not work but I proceeded to creating the final board anyway, on which it worked after a bit of adjusting.

{{< video src="i2c-demo.mp4" loop="true" muted="true" >}}

The demo is not too impressive in terms of accuracy both because of the haphazard, quick random wiring and a lot of noise due to long wires and no calibration of sensitivity etc. but it clearly demonstrates the LED strip, which is connected to the XIAO ESP32C3 reacting to touch input from the XIAO SAMD21 which communicates with the ESP32C3 in real time over I2C.

This was accomplished after a while of debugging, during which I discovered a timing issue with the I2C Wire communication. Originally, the LEDs were being lit with a separate lightLED function iterating through the entire strip and turning on the LEDs with the given brightness and color. This contributed to the issue in a major way, likely due to blocking the loop during its execution but even when not calling it, the wire communication only worked for a while, until it started returning -1 for the rest of the time after a while. I then refactored and cleaned the code on both devices and initialized wire as the last thing in both setups, which got rid of the issue. 

### XIAO SAMD21

Below is a walkthrough of the parts of the final code running on the XIAO SAMD21 that are relevant to the I2C communication for a slave. The full code can be found from the repository [here](https://gitlab.com/miro.keimioniemi/digital-fabrication-portfolio/-/blob/main/content/post/week-12/samd21-i2c/src/main.cpp?ref_type=heads).

I2C communication can be handled seamlessly via the built-in [Arduino Wire library](https://www.arduino.cc/reference/en/language/functions/communication/wire/), which provides useful functions to begin and end communication and transmissions, read and write data and to control timeouts and the clock.

```C
#include <Wire.h>
```

In C, functions must be declared before use even if they are not defined as the files are compiled from top to bottom. 

```C
// Utility function declarations
void receiveEvent(int howMany);
void requestEvent();
```

Initialize the Wire class in slave mode by giving an address as an argument as the last task in setup and set the functions to handle data sent and requests made by the master device, which is the connected XIAO ESP32C3 in this case.

```C
void setup() {
  
  ...

  // Initialize the I2C communication in slave mode with address 8
  Wire.begin(8);         
  Wire.onReceive(receiveEvent);      
  Wire.onRequest(requestEvent);
}
```

Define the functions that handle incoming and outgoing data. Upon a request by the master device, write the values of the `power_on` and `brightness` variables to the I2C channel as unsigned 8-bit integers. `power_on` is of type `bool` ranging from 0 to 1 and `brightness` is of type `char` but only ranges betwen 0 and 255. Upon a transmission, read the new values to them sent by the master device while data is available in the channel. 

```C
// A function to send the power_on and brightness values via I2C upon request
void requestEvent() {
  Wire.write((uint8_t)power_on);
  Wire.write((uint8_t)brightness);
}

// A function to receive the power_on and brightness values via I2C
void receiveEvent(int howMany) {
  while (Wire.available()) { 
    power_on = Wire.read();
    brightness = Wire.read();
  }
}
```

This is all that is necessary for the peripheral device in slave configuration. Nothing needs to be written in the loop, because the Wire library automatically handles incoming data and requests according to the specifications above.

### XIAO ESP32C3

Below is a walkthrough of the parts of the final code running on the XIAO ESP32C3 that are relevant to the I2C communication for the master. The full code can be found from the repository [here](https://gitlab.com/miro.keimioniemi/digital-fabrication-portfolio/-/blob/main/content/post/week-12/esp32c3-bluetooth/src/main.cpp?ref_type=heads).

The [Arduino Wire](https://www.arduino.cc/reference/en/language/functions/communication/wire/) library must again be included. It handles both the master and slave roles.

```C
#include <Wire.h>
```

Initialize the Wire class in master mode by giving no arguments to the begin function. 

```C
void setup() {

  ...

  // Initialize I2C communication in master mode
  Wire.begin();

  ...

}
```

During each loop, request the latest values of the SAMD21 state variables and sync them with those of the ESP32C3 if they have changed. The `requestFrom()` function takes as parameters the address of the peripheral of interest and the number of bytes to be requested and returns the number of bytes returned from the peripheral device. `beginTransmission(address)` and `endTransmission()` signify the beginning and end of transmissions with, in this case, writes in between to send data to the peripheral device. 

```C
void loop() {

  ...

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

        ...

        }

      if (newBrightness != brightness) {
        brightness = newBrightness;

        Wire.beginTransmission(8);
        Wire.write(isOn);
        Wire.write(brightness);
        Wire.endTransmission();

        ...

      }
    }
  }

  ...

}
```

## Wi-Fi & REST API

To explore the ESP32C3's Wi-Fi capabilities, I adapted [this example](https://gitlab.com/kriwkrow/networking-with-xiao-esp32-demo) simply by including the [FastLED library](https://fastled.io/) and defining the LED strip with some state variables to replace the previous ones. I then modified the loop to turn the LEDs on and off depending on the HTTP request made as shown below:

```C
// REST API with JSON Example (WiFi client version)
// Created 2024-04-24 by Krisjanis Rijnieks

// Include libraries used
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <FastLED.h>
#include <ESPAsyncWebServer.h>
#include "ArduinoJson.h"

// Define the number of LEDs and the data pin and instantiate the LED array
#define NUM_LEDS 120
#define DATA_PIN D8
CRGB leds[NUM_LEDS];

// Define the WiFi SSID and password
const char* ssid = "ssid";
const char* password = "password";

// Define the state variables as server objects
bool powerOn = false;
char brightness = 10;
CRGB color = CRGB(255, 255, 255);
int nextAlarm = 11;
int currentTime = 10;
char selectedAnimation = 1;

// Initialize the server
AsyncWebServer server(80);

void setup() {
  // Initialize the LED strip
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(10);

  // Initialize the serial communication
  Serial.begin(115200);

  // Initialize the WiFi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi\n");
  
  // Print the IP address of the server
  Serial.println("Access REST API: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Define the server endpoints
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(
      200, "text/plain", 
      "Welcome to the LED Zeppelin REST API!\n\nAvailable endpoints are\n/toggle\n/on\n/off\n/json?data={\"state\":\"on|off\"}"
    );
  });

  server.on("/toggle", HTTP_GET, [](AsyncWebServerRequest *request) {
    powerOn = !powerOn;
    request->send(200, "application/json", "OK");
  });
  
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    powerOn = true;
    request->send(200, "application/json", "OK");
  });

  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    powerOn = false;
    request->send(200, "application/json", "OK");
  });

  server.on("/json", HTTP_GET, [](AsyncWebServerRequest *request) 
  {
    if(request->hasParam("data")){
      String jsonInString = request->getParam("data")->value();
      Serial.print("Reveived data: ");
      Serial.println(jsonInString);

      char jsonInChar[jsonInString.length() + 1];
      jsonInString.toCharArray(jsonInChar, sizeof(jsonInChar));
      char* jsonInCharPtr = jsonInChar;
      
      JsonDocument jsonIn;
      deserializeJson(jsonIn, jsonInCharPtr);
      const char* state = jsonIn["state"];
      Serial.print("state: ");
      Serial.println(state);

      if (jsonIn["state"] == "on") {
        powerOn = true;
      } else if (jsonIn["state"] == "off") {
        powerOn = false;
      }
    }

    JsonDocument jsonOut;
    jsonOut["status"] = "OK";
    
    String jsonOutString;
    serializeJson(jsonOut, jsonOutString);
 
    request->send(200, "application/json", jsonOutString);
  });

  // Start the server
  server.begin();
}

void loop() {
  if (powerOn) {
    for (int i = 0; i < 10; i++) {
      leds[i] = CRGB::White;
    }
  } else {
    for (int i = 0; i < 10; i++) {
      leds[i] = CRGB::Black;
    }
  }
  FastLED.show();

  delay(1000);
}
```

Even though it was warned about that the [ESPAsyncWebServer library's](https://github.com/lacamera/ESPAsyncWebServer/) source code might have to be modified due to some minor errors in it to run the example properly, this seemed to have been fixed when I ran it as for me it worked immediately. 

I did not bother to learn the example too thoroughly because I knew I would not be implementing the wireless connectivity via Wi-Fi for my project due to it not being a good fit due to its inflexibility when changing places, routers and networks. It would either limit the usage of the lamp into a single network and therefore space, or the connected device's internet access unless I wanted to first configure it via Bluetooth and then use the Wi-Fi, which made no sense as I had to only sync a few small values for which Bluetooth Low Energy (BLE) was specifically made. 

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




WiFi and REST API was not a good fit in the end as it could not be configured flexibly enough with various routers and networks in various places. Bluetooth, however, enables direct connection with less energy consumption, making it significantly more sensible for this.

https://stackoverflow.com/questions/2397822/what-is-the-best-practice-for-dealing-with-passwords-in-git-repositories

As an extension, Bluetooth could be used to setup wifi for further range and larger data throughput but is beyond this project

Flutter installation: https://docs.flutter.dev/get-started/install/windows/mobile

I remember there being some issues when I orginally did it, but it has been a few months and therefore I cannot recall them. The instructions are quite comprehensive however.

Need VS code extensions: https://docs.flutter.dev/get-started/test-drive


Plug-and-play working solution: https://wiki.seeedstudio.com/XIAO_ESP32C3_Bluetooth_Usage/  







