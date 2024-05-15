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