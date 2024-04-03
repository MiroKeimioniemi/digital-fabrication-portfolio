#include <Arduino.h>
#include "Adafruit_FreeTouch.h"

Adafruit_FreeTouch qt_1 = Adafruit_FreeTouch(A0, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_2 = Adafruit_FreeTouch(A1, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_3 = Adafruit_FreeTouch(A6, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_4 = Adafruit_FreeTouch(A7, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_5 = Adafruit_FreeTouch(A8, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_6 = Adafruit_FreeTouch(A9, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_7 = Adafruit_FreeTouch(A10, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);

void setup() {
  Serial.begin(115200);
  Serial.println("FreeTouch test");
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  pinMode(PIN_LED, OUTPUT);

  digitalWrite(PIN_LED, HIGH);
  digitalWrite(PIN_LED2, HIGH);
  digitalWrite(PIN_LED3, HIGH);

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
}

int qt_Threshold = 850;

void loop() {
  int qt1 = 0;
  int qt2 = 0;
  int qt3 = 0;
  int qt4 = 0;
  int qt5 = 0;
  int qt6 = 0;
  int qt7 = 0;

  qt1 = qt_1.measure();
  Serial.println();
  Serial.print(qt1);
  

  qt2 = qt_2.measure();
  Serial.println();
  Serial.print(qt2);
  

  qt3 = qt_3.measure();
  Serial.println();
  Serial.print(qt3);
  

  qt4 = qt_4.measure();
  Serial.println();
  Serial.print(qt4);
  

  qt5 = qt_5.measure();
  Serial.println();
  Serial.print(qt5);
  

  qt6 = qt_6.measure();
  Serial.println();
  Serial.print(qt6);
  

  qt7 = qt_7.measure();
  Serial.println();
  Serial.print(qt7);
  


  if (qt1 >= qt_Threshold) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (qt2 >= qt_Threshold) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (qt3 >= qt_Threshold) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (qt4 >= qt_Threshold) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (qt5 >= qt_Threshold) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (qt6 >= qt_Threshold) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (qt7 >= qt_Threshold) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}


void setup() {
  Serial.begin(115200);
  Serial.println("Hello, world!");
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}