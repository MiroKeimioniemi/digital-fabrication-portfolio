// Code for the XIAO SAMD21 handling the gesture detection of the "LED Zeppelin" gesture controlled lamp

// Include the necessary libraries (Arduino framwork must be explicitly included in PlatformIO)
#include <Arduino.h>
#include <Wire.h>
#include <deque>
#include <numeric>
#include "Adafruit_FreeTouch.h"

// Initialize the capacitive Qtouch sensors (1 & 2 not in use due to broken connections)

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

// Boolean flags for detecting gestures and a deque to maintain a rolling average of the previously activated pin for smoothing out readings
bool slide = false;
bool tap = false;
std::deque<short> previous_max_indices(70, 0);

// Relevant lamp state variables and their defaults
bool power_on = true;
const char BRIGHTNESS_INCREMENT = 47;
char brightness = BRIGHTNESS_INCREMENT * 2;

// Utility function declarations
void receiveEvent(int howMany);
void requestEvent();
int roundedAverage(const std::deque<short>& data);

void setup() {
  // Initialize serial communication 
  Serial.begin(115200);

  // Initialize the internal indicator LED pins (for debugging)
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

  // Calibrate the sensors on startup by measuring the maximum baseline values for each pin
  for (int i = 0; i < 100; i++) {
      // qt1_baseline = max(qt1_baseline, qt_1.measure());
      // qt2_baseline = max(qt2_baseline, qt_2.measure());
      qt3_baseline = max(qt3_baseline, qt_3.measure());
      qt4_baseline = max(qt4_baseline, qt_4.measure());
      qt5_baseline = max(qt5_baseline, qt_5.measure());
      qt6_baseline = max(qt6_baseline, qt_6.measure());
      qt7_baseline = max(qt7_baseline, qt_7.measure());
    }

  // Initialize the I2C communication in slave mode with address 8
  Wire.begin(8);         
  Wire.onReceive(receiveEvent);      
  Wire.onRequest(requestEvent);
}

short qt_threshold = 17;      // Define the threshold for increase over baseline values for detecting touch
short max_index = 4;          // Define the index of the currently activated pin
unsigned long tap_start = 0;  // Create a variable for holding the timestamp of the start of a tap gesture

void loop() {
  // Reset the current sensor readings to 0
  // short qt1 = 0;
  // short qt2 = 0;
  short qt3 = 0;
  short qt4 = 0;
  short qt5 = 0;
  short qt6 = 0;
  short qt7 = 0;

  // Turn off the indicator LEDs (HIGH = off for internal LEDs on XIAOs)
  digitalWrite(PIN_LED_RXL, HIGH);
  digitalWrite(PIN_LED_TXL, HIGH);

  // Measure the current capacitance values of each sensor
  // qt1 = qt_1.measure();
  // qt2 = qt_2.measure();
  qt3 = qt_3.measure();
  qt4 = qt_4.measure();
  qt5 = qt_5.measure();
  qt6 = qt_6.measure();
  qt7 = qt_7.measure();

  // Store the differences between the current readings and their baseline values for each sensor from 1 to 7
  // short qts[] = {qt_threshold, qt1 - qt1_baseline, qt2 - qt2_baseline, qt3 - qt3_baseline, qt4 - qt4_baseline, qt5 - qt5_baseline, qt6 - qt6_baseline, qt7 - qt7_baseline};
  // Less pins because I broke the board connections and wonky order because I connected them funnily in the lamp
  short qts[] = {qt_threshold, qt6 - qt6_baseline, qt4 - qt4_baseline, qt3 - qt3_baseline, qt5 - qt5_baseline, qt7 - qt7_baseline};
  short previous_max_index = max_index;
  // Maintain a rolling average using the previous max indices
  previous_max_indices.pop_front();
  previous_max_indices.push_back(previous_max_index);
  max_index = 0;

  // Find the sensor with the highest difference from its baseline value
  // max_index = 0 means that none of the sensors is being touched
  for (int i = 0; i <= 5; i++) {
      if (qts[i] > qts[max_index]) {
          max_index = i;
      }
  }

  Serial.print("max_index: ");
  Serial.println(max_index);
  
  // Detect a slide gesture if the sensor touched changes without loss of contact
  if (previous_max_index != 0 && max_index != 0 && previous_max_index != max_index) {
    slide = true;
    tap_start = 0;
  }

  Serial.print(roundedAverage(previous_max_indices));

  // Assume a tap gesture if the sensor touched changes from 0 to a non-zero value
  if (roundedAverage(previous_max_indices) == 0 && max_index != 0) {
    tap_start = millis();
  }
  // Detect a tap gesture if no slide gesture is detected but the touch contact ends or exceeds a certain duration
  if (tap_start != 0 && ((max_index == 0 && ((millis() - tap_start) > 50)) || ((millis() - tap_start) > 500))) {
    tap = true;
    tap_start = 0;
  }

  // Toggle the lamp power state upon a tap gesture
  if (tap && power_on) {
    digitalWrite(LED_BUILTIN, HIGH);
    power_on = false;
    tap = false;
  } else if ((tap || slide) && !power_on) {
    digitalWrite(LED_BUILTIN, LOW);
    power_on = true;
    tap = false;
  }

  // Adjust the brightness of the lamp upon a slide gesture
  if (slide) {
    if (max_index != 0) {
      brightness = max_index * BRIGHTNESS_INCREMENT;
    }
    slide = false;
  }

  delay(1);
}

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

// A function to calculate the rolling average rounded to the nearest integer
int roundedAverage(const std::deque<short>& data) {
    return round(std::accumulate(data.begin(), data.end(), 0.0) / data.size());
}