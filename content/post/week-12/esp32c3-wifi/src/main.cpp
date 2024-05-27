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

  // Print the available endpoints
  Serial.println("Toggle state ON/OFF");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/toggle");
  Serial.println();

  Serial.println("Switch ON");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/on");
  Serial.println();

  Serial.println("Switch OFF");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/off");
  Serial.println();

  Serial.println("Control with JSON");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/json?data={'state':'on'}");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/json?data={'state':'off'}");
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
