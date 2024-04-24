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
  pinMode(PIN_LED_RXL, OUTPUT);
  pinMode(PIN_LED_TXL, OUTPUT);

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


  if (qt1 >= qt_Threshold) {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (qt2 >= qt_Threshold) {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (qt3 >= qt_Threshold) {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (qt4 >= qt_Threshold) {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (qt5 >= qt_Threshold) {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (qt6 >= qt_Threshold) {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (qt7 >= qt_Threshold) {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else {
    digitalWrite(LED_BUILTIN, HIGH);
  }


  int qts[] = {qt_Threshold, qt1, qt2, qt3, qt4, qt5, qt6, qt7};
  int maxIndex = 0;

  for (int i = 0; i <= 7; i++) {
      if (qts[i] > qts[maxIndex]) {
          maxIndex = i;
      }
  }

  Serial.print("maxIndex: ");
  Serial.println(maxIndex);


  switch(maxIndex) {
    case 0:
      pinMode(2, INPUT);
      pinMode(3, INPUT);
      pinMode(4, INPUT);
      digitalWrite(5, LOW);
      break;
    case 1:
      pinMode(2, OUTPUT);
      pinMode(3, OUTPUT);
      pinMode(4, INPUT);
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      break;
    case 2:
      pinMode(2, OUTPUT);
      pinMode(3, OUTPUT);
      pinMode(4, INPUT);
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      break;
    case 3:
      pinMode(2, INPUT);
      pinMode(3, OUTPUT);
      pinMode(4, OUTPUT);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      break;
    case 4:
      pinMode(2, INPUT);
      pinMode(3, OUTPUT);
      pinMode(4, OUTPUT);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      break;
    case 5:
      pinMode(2, OUTPUT);
      pinMode(3, INPUT);
      pinMode(4, OUTPUT);
      digitalWrite(2, LOW);
      digitalWrite(4, HIGH);
      break;
    case 6:
      pinMode(2, OUTPUT);
      pinMode(3, INPUT);
      pinMode(4, OUTPUT);
      digitalWrite(2, HIGH);
      digitalWrite(4, LOW);
      break;
    case 7:
      digitalWrite(5, HIGH);
  }
}