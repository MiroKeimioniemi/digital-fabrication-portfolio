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
image: "final-pcb.webp"
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

Even though it was warned about that the [ESPAsyncWebServer library's](https://github.com/lacamera/ESPAsyncWebServer/) source code might have to be modified due to some minor errors in it to run the example properly, this seemed to have been fixed when I ran it as for me it worked immediately with no problem whatsoever. 

I did not bother to learn the example too thoroughly because I knew I would not be implementing the wireless connectivity via Wi-Fi for my project due to it not being a good fit due to its inflexibility when changing places, routers and networks. It would either limit the usage of the lamp into a single network and therefore space, or the connected device's internet access unless I wanted to first configure it via Bluetooth and then use the Wi-Fi, which made no sense as I had to only sync a few small values for which Bluetooth Low Energy (BLE) was specifically made. 

## Bluetooth Low Energy

[Bluetooth Low Energy](https://www.bluetooth.com/learn-about-bluetooth/tech-overview/) (BLE) is a modern wireless personal area network technology that utilizes 40 channels of the 2.4GHz [ISM Band](https://en.wikipedia.org/wiki/ISM_radio_band) to communicate with devices in close proximity, which in this case is usually less than or equal to about 10 meters. 

Even though it uses the same radio frequencies, Bluetooth Low Energy is entirely distinct from classic Bluetooth, which works more like a wireless serial port. Instead, Bluetooth LE works by peripheral devices creating and advertising one or multiple different services with characteristics, such as the lamp state variables, which can be accessed by the central device by connecting to the services and reading, writing or subscribing to certain characteristics in the service(s). One can use it so that the peripheral services work mostly as notification boards and the central device just reads them when necessary, or the central device can subscribe to some of the characteristics so that it is notified any time they change so that this is the only time data transfer occurs. 

This is highly energy efficient, making both devices consume very little energy, while also enabling them to stay connected to multiple devices at once. This, combined with relatively simple use makes it in every way superior to Wi-Fi for this use case, and is thus my choice for wireless connectivity for the project.

### XIAO ESP32C3

Below is a walkthrough of the parts of the final code running on the XIAO SAMD21 that are relevant to creating a Bluetooth Low Energy (BLE) service with the state variables as characteristics on the peripheral device. The full code can be found from the repository [here](https://gitlab.com/miro.keimioniemi/digital-fabrication-portfolio/-/blob/main/content/post/week-12/esp32c3-bluetooth/src/main.cpp?ref_type=heads).

Though relatively simple on a very high conceptual level, there is quite a bit of boilerplate that must be written, even when using the ESP32 compatible BLE libraries, documentation for which can be found [here](https://github.com/nkolban/esp32-snippets/blob/master/Documentation/BLE%20C%2B%2B%20Guide.pdf). Following [this](https://wiki.seeedstudio.com/XIAO_ESP32C3_Bluetooth_Usage/) tutorial to use the XIAO ESP32C3 as a Bluetooth server, include the following libraries:

```C
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
```

Define the Universally Unique Identifiers (UUID) for each service and characteristic using an online UUID generator such as [uuidgenerator.net](https://www.uuidgenerator.net/).

```C
// Define the UUIDs for the Bluetooth Low Energy (BLE) peripheral service and its characteristics
#define SERVICE_UUID        "6932598e-c4fe-4855-9701-240a78abc000"
#define ON_CHARACTERISTIC_UUID "dfc1a400-3523-4626-bd77-3469dbed8b74"
#define BRIGHTNESS_CHARACTERISTIC_UUID "05f52bf8-4823-42c6-8647-dc89b76ad4e4"
#define COLOR_CHARACTERISTIC_UUID "b2516e35-6917-43b7-8cad-c7065a9e0033"
#define ANIMATION_CHARACTERISTIC_UUID "0d72cbb7-742f-4030-b4ec-3aefb8c1eb1a"
#define NEXT_ALARM_CHARACTERISTIC_UUID "2b3e71d1-4c3e-418e-942b-67f28951c2d3"
```

Define the state variables to hold the values transmitted over BLE. 

```C
// Define lamp state variables and set defaults
int isOn = true;            // Boolean flag to indicate whether the LEDs should be on or off
int brightness = 100;       // Brightness level of the LEDs (0-255)
CRGB color = CRGB::White;   // Color of the LEDs as red, green and blue components (0-255)
int animation = 1;          // Animation mode for the LEDs (0-3) 0 = static, 1 = breathing, 2 = rainbow, 3 = brightening
time_t nextAlarm;           // Time for when to trigger the next alarm (in seconds since the Unix epoch)
time_t currentTime;         // Current time (in seconds since the Unix epoch)
```

Define callback classes for the BLE characteristics, which handle responses to reads and writes of the characteristic by the central device in an appropriate manner for the given data type. The data is sent over as a byte array and must therefore be interpreted the correct way, with which GitHub Copilot was quite helpful due to the operations being quite simple but a bit tedious to think through when sleep deprived. 

All integers received via `NumberCallback` are mapped betwen 0 and 255 so that they can be interpreted as standalone 8-bit (= 1-byte) integers, whereas color is sent and received as a little-endian 32-bit unsigned integer, where the 8 most significant bits are unused, while the remaining 24 bits represent the red, green and blue components in 8-bit increments respectively. `TimeCallback` can receive both the current time for syncing purposes as well as the next alarm depending on the 1-byte flag in front of the 32-bit integer timestamp representing the number of seconds since the "[Unix epoch](https://en.wikipedia.org/wiki/Unix_time)" 1970-01-01T00:00:00Z (UTC). Below, under the Flutter section, it can be seen how the data is sent from the app side.

```C
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
```

Define a server callback for tracking when the central device is connected.

```C
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
```

As the final step before setup, initialize the pointers to the characteristics and the server as null pointers outside the arduino functions, so that they are accessible in both the setup as well as the loop so that they can be updated at all times.

```C
// Initialize the BLE server and characteristics outside the setup to be globally accessible in the loop
BLEServer *pServer = nullptr;
BLECharacteristic *pOnCharacteristic = nullptr;
BLECharacteristic *pBrightnessCharacteristic = nullptr;
BLECharacteristic *pColorCharacteristic = nullptr;
BLECharacteristic *pAnimationCharacteristic = nullptr;
BLECharacteristic *pNextAlarmCharacteristic = nullptr;
```

In the Arduino setup function, initialize and name the device and create the server with its callbacks. Use the above pointers to create the service and characteristics with the desired properties, which allow the central device to read, write and subscribe to the characteristics. Set callbacks, initial values and descriptors for each, which enables the use of notifications so that the central device does not have to periodically read the characteristics but instead gets the latest updates in real time. Finally, start advertising the service so that it can be found by the central device.

```C
void setup() {
  
  ...

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
```

In the loop, it is important to start readvertising the service if the device gets disconnected as this is what enables the device to be found again. Otherwise, it can only be connected to once until the whole device is restarted. The lamp state can change from both the app, which is handled by the callbacks set in the setup already, as well as from the I2C communication, which updates them according to the gestures detected. 

If they change via callbacks, they can simply be read in the loop. If they change via the wire input, they must be explicitly updated via `pCharacteristic->setValue(pointer_to_data, size_of_data_in_bytes)` inside the loop with `pCharacteristic->notify()`, which notifies the central device about a change in the variable. Initially, I had a bit of issues with getting the notifications to work, but [this example](https://github.com/nkolban/ESP32_BLE_Arduino/blob/master/examples/BLE_notify/BLE_notify.ino) and [this video](https://www.youtube.com/watch?v=oCMOYS71NIU) helped with understanding the logic behind using the BLE2902 library necessary for it. 

```C
unsigned long lastSync = 0; // Initialize a variable to keep track of the last time the values were synced

void loop() {
  unsigned long currentTimeElapsed = millis();  // Get the current time

  // Restart advertising every 5 seconds so that the device stays discoverable after being disconnected
  if (currentTimeElapsed - lastAdvertisingTime >= 5000) {
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();
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
  
  // Restart advertising if a device was connected and then disconnected
  if (!deviceConnected && oldDeviceConnected) {
      pServer->startAdvertising();
      Serial.println("start advertising");
      oldDeviceConnected = deviceConnected;
  }

  ...

}
```

There is a bit of redundancy with the periodical readvertising and doing so upon disconnecting the device and some other old code too, but as they say: "Don't touch it if it works" and hence they are still in there after the fully sleepless nigth, after which I did not touch the code anymore at all the moment after it finally worked. 

Below is a demo video of connecting to the XIAO ESP32C3 via the [LightBlue app](https://play.google.com/store/apps/details?id=com.punchthrough.lightblueexplorer&hl=en&pli=1) and using it to control the lamp's on/off state, brightness and color. 

{{< video src="bluetooth-demo.mp4" loop="true" muted="true" >}}

### Flutter

For the lamp to be controllable from an app, it obviously does not suffice that the BLE capability is only implemented in one end. The functionalities of the central device thus have to be programmed in [Flutter](https://flutter.dev/) as well, which is Google's open source cross-platform framework for building applications on all devices from Android and iOS to Windows, macOS and the web, and my choice of framework for my Android application. More about flutter in the [Interface and Application Programming]({{< relref "post/week-13/index.md" >}}) documentation.

Below is a walkthrough of the parts of the final code running on my Pixel 6 that are relevant to interacting with the Bluetooth Low Energy (BLE) service using the central device. The full code can be found from the repository [here](https://gitlab.com/miro-keimioniemi/led-zeppelin-app).

Because I practically had only a single night to implement the Bluetooth functionality on the app end, I had to rely quite heavily on GitHub Copilot and ChatGPT but both have knowledge cutoffs around 2023, which is quite difficult for such rapidly evolving frameworks. Hence, based on [this blog post](https://www.linkedin.com/pulse/which-flutter-bluetooth-low-energy-library-choose-reinhold-quillen/) and the original publication dates of the potential BLE libraries, those being [FlutterBlue](https://pub.dev/packages/flutter_blue) (deprecated), [FlutterBluePlus](https://pub.dev/packages/flutter_blue_plus) (last year) and [Flutter reactive BLE](https://pub.dev/packages/flutter_reactive_ble) (a few years old), I chose Flutter reactive BLE as it was still recently maintained but old enough that the LLMs should know its basic functionality. However, even after hours of tired trial and error, I did not manage to get it work, even when using [their own example](https://github.com/PhilipsHue/flutter_reactive_ble/tree/master/example/lib/src). 

I switched to [FlutterBluePlus](https://pub.dev/packages/flutter_blue_plus) and tried my best to learn and apply it while heavily sleep deprived but I was still missing something. Eventually, [Thanh](https://0nitfans.com/) who also stayed up at the lab the whole night tried to help me in my frustration and managed to formulate the problem for ChatGPT in a way that I clearly had not been able to so that it came up with a working solution - well, almost. It seems that it wrote it using the no longer supported FlutterBlue library, but it was close enough such that I could migrate it to the well-supported FlutterBluePlus with the help of their [migration guide](https://github.com/boskokg/flutter_blue_plus/blob/master/MIGRATION.md). With that help at the very last moment when I was just about to give up, I managed to finally gain back momentum and implement the BLE functionality to the LampState class as follows.







See demo on [YouTube](https://www.youtube.com/watch?v=ouhtvRlAQOE).
