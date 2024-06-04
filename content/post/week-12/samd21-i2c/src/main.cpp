#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_FreeTouch.h"

// Adafruit_FreeTouch qt_1 = Adafruit_FreeTouch(A0, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
// Adafruit_FreeTouch qt_2 = Adafruit_FreeTouch(A1, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_3 = Adafruit_FreeTouch(A6, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_4 = Adafruit_FreeTouch(A7, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_5 = Adafruit_FreeTouch(A8, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_6 = Adafruit_FreeTouch(A9, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_7 = Adafruit_FreeTouch(A10, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);

// short qt1_baseline = 0;
// short qt2_baseline = 0;
short qt3_baseline = 0;
short qt4_baseline = 0;
short qt5_baseline = 0;
short qt6_baseline = 0;
short qt7_baseline = 0;

bool slide = false;
bool tap = false;

bool power_on = true;
const char BRIGHTNESS_INCREMENT = 47;
char brightness = BRIGHTNESS_INCREMENT * 2;

void receiveEvent(int howMany);
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

  // if (! qt_1.begin())
  //   Serial.println("Failed to begin qt");
  // if (! qt_2.begin())
  //   Serial.println("Failed to begin qt");
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
      // qt1_baseline = max(qt1_baseline, qt_1.measure());
      // qt2_baseline = max(qt2_baseline, qt_2.measure());
      qt3_baseline = max(qt3_baseline, qt_3.measure());
      qt4_baseline = max(qt4_baseline, qt_4.measure());
      qt5_baseline = max(qt5_baseline, qt_5.measure());
      qt6_baseline = max(qt6_baseline, qt_6.measure());
      qt7_baseline = max(qt7_baseline, qt_7.measure());
    }

  Wire.begin(8);         
  Wire.onReceive(receiveEvent);      
  Wire.onRequest(requestEvent);
}

short qt_threshold = 10;
short max_index = 4;
unsigned long tap_start = 0;

void loop() {

  // short qt1 = 0;
  // short qt2 = 0;
  short qt3 = 0;
  short qt4 = 0;
  short qt5 = 0;
  short qt6 = 0;
  short qt7 = 0;

  digitalWrite(PIN_LED_RXL, HIGH);
  digitalWrite(PIN_LED_TXL, HIGH);

  // qt1 = qt_1.measure();
  // qt2 = qt_2.measure();
  qt3 = qt_3.measure();
  qt4 = qt_4.measure();
  qt5 = qt_5.measure();
  qt6 = qt_6.measure();
  qt7 = qt_7.measure();

  // short qts[] = {qt_threshold, qt1 - qt1_baseline, qt2 - qt2_baseline, qt3 - qt3_baseline, qt4 - qt4_baseline, qt5 - qt5_baseline, qt6 - qt6_baseline, qt7 - qt7_baseline};
  // Less pins because I broke the board connections and wonky order because I connected them in a weird order
  short qts[] = {qt_threshold, qt6 - qt6_baseline, qt4 - qt4_baseline, qt3 - qt3_baseline, qt5 - qt5_baseline, qt7 - qt7_baseline};
  short previous_max_index = max_index;
  max_index = 0;

  for (int i = 0; i <= 5; i++) {
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
      brightness = max_index * BRIGHTNESS_INCREMENT;
    }
    slide = false;
  }

  delay(16);
}

void requestEvent() {
  Wire.write((uint8_t)power_on);
  Wire.write((uint8_t)brightness);
}

void receiveEvent(int howMany) {
  while (Wire.available()) { 
    power_on = Wire.read();
    brightness = Wire.read();
  }
}