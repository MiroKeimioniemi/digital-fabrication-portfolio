#include <Arduino.h>
#include "Adafruit_FreeTouch.h"

Adafruit_FreeTouch qt_1 = Adafruit_FreeTouch(A0, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_2 = Adafruit_FreeTouch(A1, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_3 = Adafruit_FreeTouch(A6, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_4 = Adafruit_FreeTouch(A7, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_5 = Adafruit_FreeTouch(A8, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_6 = Adafruit_FreeTouch(A9, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_7 = Adafruit_FreeTouch(A10, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);

int qt1_baseline = 0;
int qt2_baseline = 0;
int qt3_baseline = 0;
int qt4_baseline = 0;
int qt5_baseline = 0;
int qt6_baseline = 0;
int qt7_baseline = 0;

int powerOn = true;
bool slide = false;
bool tap = false;

int brightness = 0;

void lightLED(int led);

void setup() {
  Serial.begin(115200);
  Serial.println("FreeTouch test");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_LED_RXL, OUTPUT);
  pinMode(PIN_LED_TXL, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(PIN_LED_RXL, HIGH);
  digitalWrite(PIN_LED_TXL, HIGH);

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);

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
}

int qt_threshold = 8;
int maxIndex = 4;
unsigned long tapStart = 0;

void loop() {

  int qt1 = 0;
  int qt2 = 0;
  int qt3 = 0;
  int qt4 = 0;
  int qt5 = 0;
  int qt6 = 0;
  int qt7 = 0;

  digitalWrite(PIN_LED_RXL, HIGH);
  digitalWrite(PIN_LED_TXL, HIGH);

  qt1 = qt_1.measure();
  Serial.print("qt1: ");
  Serial.println(qt1);

  qt2 = qt_2.measure();
  Serial.print("qt2: ");
  Serial.println(qt2);

  qt3 = qt_3.measure();
  Serial.print("qt3: ");
  Serial.println(qt3);

  qt4 = qt_4.measure();
  Serial.print("qt4: ");
  Serial.println(qt4);
  
  qt5 = qt_5.measure();
  Serial.print("qt5: ");
  Serial.println(qt5);
  
  qt6 = qt_6.measure();
  Serial.print("qt6: ");
  Serial.println(qt6);
  
  qt7 = qt_7.measure();
  Serial.print("qt7: ");
  Serial.println(qt7);


  int qts[] = {qt_threshold, qt1 - qt1_baseline, qt2 - qt2_baseline, qt3 - qt3_baseline, qt4 - qt4_baseline, qt5 - qt5_baseline, qt6 - qt6_baseline, qt7 - qt7_baseline};
  int previousMaxIndex = maxIndex;
  maxIndex = 0;

  for (int i = 0; i <= 7; i++) {
      if (qts[i] > qts[maxIndex]) {
          maxIndex = i;
      }
  }

  Serial.print("maxIndex: ");
  Serial.println(maxIndex);
  
  // Detect a slide gesture
  if (previousMaxIndex != 0 && maxIndex != 0 && previousMaxIndex != maxIndex) {
    slide = true;
    tapStart = 0;
  }

  // Detect a tap gesture
  if (previousMaxIndex == 0 && maxIndex != 0) {
    tapStart = millis();
  }
  if (tapStart != 0 && ( maxIndex == 0 || ((millis() - tapStart) > 500))) {
    tap = true;
    tapStart = 0;
  }

  if (tap && powerOn) {
    digitalWrite(LED_BUILTIN, HIGH);
    powerOn = false;
    tap = false;
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(5, LOW);
  } else if ((tap || slide) && !powerOn) {
    digitalWrite(LED_BUILTIN, LOW);
    powerOn = true;
    tap = false;
    lightLED(brightness);
  }

  if (slide) {
    if (maxIndex != 0) {
      lightLED(maxIndex);
    } else {
      lightLED(brightness);
    }
    slide = false;
  }

  delay(10);
}

void lightLED(int led) {
  switch (led) {
    case 1:
      brightness = 1;
      pinMode(2, OUTPUT);
      pinMode(3, OUTPUT);
      pinMode(4, INPUT);
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(5, LOW);
      break;
    case 2:
      brightness = 2;
      pinMode(2, OUTPUT);
      pinMode(3, OUTPUT);
      pinMode(4, INPUT);
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);
      break;
    case 3:
      brightness = 3;
      pinMode(2, INPUT);
      pinMode(3, OUTPUT);
      pinMode(4, OUTPUT);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      break;
    case 4:
      brightness = 4;
      pinMode(2, INPUT);
      pinMode(3, OUTPUT);
      pinMode(4, OUTPUT);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      break;
    case 5:
      brightness = 5;
      pinMode(2, OUTPUT);
      pinMode(3, INPUT);
      pinMode(4, OUTPUT);
      digitalWrite(2, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      break;
    case 6:
      brightness = 6;
      pinMode(2, OUTPUT);
      pinMode(3, INPUT);
      pinMode(4, OUTPUT);
      digitalWrite(2, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      break;
    case 7:
      brightness = 7;
      pinMode(2, INPUT);
      pinMode(3, INPUT);
      pinMode(4, INPUT);
      digitalWrite(5, HIGH);
      break;
  }
}