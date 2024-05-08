---
author: "Miro Keimiöniemi"
title: "Input Devices"
date: "2024-04-27"
description: "Week 12"
tags: 
  - "electronics"
  - "microcontroller"
  - "circuit board"
  - "PCB"
  - "input"
  - "input devices"
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
image: "qtouch-board.webp"
---

## Assignments

**Group assignment**
1. Join one of the introduction sessions on Mon, Tue or Wed and document the probing of several different input devices.
2. Pick a group leader who has to create and populate the group assignment page. 

**Individual assignment**
1. Link to the group assignment page and describe what you learned from the group assignment.
2. Add a sensor to a microcontroller board that you have designed and read it.

## Probing input devices

Our this week's group assignment was to probe several different input devices, which was documented by Vytautas Bikauska [here](https://public-df.gitlab.io/shared-documentation/inputdevices.html). We tested both one and three axis hall effect sensors as well as a [time of flight distance sensor](https://www.sparkfun.com/products/14722) and due to the latter being a [SparkFun](https://www.sparkfun.com/) breakout board, the I2C communication protocol as well as [Qwiic](https://www.sparkfun.com/qwiic) connectors became topics of conversation as well.

The distance sensor was particularly interesting, providing millimeter resolution up to 4 meters away, enabling all kinds of potentially interesting ideas. Seeing the logic analyzer at work again with multiple simultaneous channels and an analog input as well was quite fascinating too, although I hope I will not have to use it much personally. 

What we most laughed about, however, was the absurd number of different voltage acronyms with almost every circuit using a new one. Some of the most common ones are VCC, VDD, VSS, VEE, Vin and Vout, which, according to [this site](https://reversepcb.com/vcc-vdd-vee-vss-gnd/) roughly correspond to, analog (circuit) power supply, digital (chip) power supply, digital ground, negative power supply, voltage in and voltage out. 

## QTouch sensors

The [Seeed Studio XIAO SAMD21](https://wiki.seeedstudio.com/Seeeduino-XIAO/) features 7 QTouch pins, which can be read using the [Adafruit_FreeTouch library](https://github.com/adafruit/Adafruit_FreeTouch). They can be used to detect changes in capacitance, which occurs, for example, upon touching them with a finger. I made the board depicted below to test them during the [electronics design week]({{< relref "post/week-8/index.md" >}}) but the code only tests whether the board functions or not, and cannot be used for the final project as is just yet.

![XIAO SAMD21 QTouch controller](qtouch-board.webp)

As I already pretty much built my input board during the [electronics design week]({{< relref "post/week-8/index.md" >}}), I decided to dedicate this input week to adapting it for my final project. The QTouch pads registered a change in capacitance exactly like I wanted, even through some thin materials, and all the charlieplexed indicator lights light up to correctly designate the pad that is being touched. However, the capacitance readings are different and the changes are smaller with a material on top. Hence, my goal for this week was to program a solution for correctly detecting touch through (bent) acrylic.  

### Testing input

I first tested the QTouch sensors by adding a 500ms delay to the [electronics design week code](https://gitlab.com/miro.keimioniemi/digital-fabrication-portfolio/-/blob/main/content/post/week-8/qtouch-test-code/qtouch-test-code/src/main.cpp) in order to be able to read the input values. When just resting on the table without being touched, the values measured by the individual QTouch pins ranged roughly from 430 to 680. The values measured by each pin, named in an increasing order from left to right, can be seen in the image of the serial output terminal below.

![Default serial terminal output](serial-output.webp)
![Serial output when touching pad 5](serial-output-touched.webp)

Interestingly, there seems to be a slight pattern. The pin connected to the leftmost pad, qt1, reads the highest value and the reading decreases until the lowest one read by qt3 after which they again mostly increase. Correspondingly, qt3 has by far the shortest path from pad to pin and the path lengths keep on increasing from qt4 up to qt7, although not proportionally as much as from qt2 to qt1. It is a bit peculiar that qt1 and qt2 measure the highest capacitances when it seems to be loosely correlated with the length of the path but they are not as long as the ones from the pads on the right. This might of course all be due to their internal routing or other differences between the pins themselves, but in terms of the PCB architecture, the only feature that would make those two stand out especially is that they feature the closest and longest zigzag patterns with themselves. 

The values tended to vary usually by approximately 1 and at most 2, except for qt2, which sometimes climbed from 606 all the way to 611 but only for single readings at a time. When touching a corresponding pad, the value ranged from 1014 to 1016 as seen above. One could thus set a threshold above the highest reading, say at 850, and thus the currently touched pad could be identified as the one exceeding it. However, if one touches a pad with something in between, such as in the image below where the pin recognizes a touch through over 4mm of layered acrylic with the code discussed below, the changes in the values are naturally much smaller. 

![Tocuhing a pad through two 2mm sheets of acrylic](touch-through-acrylic.webp)
![Serial output when touching pad 5 through one 2mm sheet of acrylic](serial-output-acrylic-in-between.webp)

With a single 2mm sheet of acrylic in between, the baseline values increase approximately by 10 to 20 and the increases upon touch are significantly smaller at around 48 - 56 instead of hundreds up until the maximum readings. For two 2mm acrylic sheets, the increases are around 10 to 15. As can be seen in the serial output above, qt5 is correctly registered by the code to be discussed below, but it can no longer be distinguished as simply the largest value over some thershold. Instead, I had to first establish baseline values for the pins and then compare the changes to a change threshold that is low enough to detect touches through various materials but high enough not to be triggered the by random variation. Below is the modified code for doing so.

### Threshold code

```C
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

void setup() {
  Serial.begin(115200);
  Serial.println("FreeTouch test");

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

int qt_Threshold = 5;

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


  int qts[] = {qt_Threshold, qt1 - qt1_baseline, qt2 - qt2_baseline, qt3 - qt3_baseline, qt4 - qt4_baseline, qt5 - qt5_baseline, qt6 - qt6_baseline, qt7 - qt7_baseline};
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
      digitalWrite(5, LOW);
      break;
    case 2:
      pinMode(2, OUTPUT);
      pinMode(3, OUTPUT);
      pinMode(4, INPUT);
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);
      break;
    case 3:
      pinMode(2, INPUT);
      pinMode(3, OUTPUT);
      pinMode(4, OUTPUT);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      break;
    case 4:
      pinMode(2, INPUT);
      pinMode(3, OUTPUT);
      pinMode(4, OUTPUT);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      break;
    case 5:
      pinMode(2, OUTPUT);
      pinMode(3, INPUT);
      pinMode(4, OUTPUT);
      digitalWrite(2, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      break;
    case 6:
      pinMode(2, OUTPUT);
      pinMode(3, INPUT);
      pinMode(4, OUTPUT);
      digitalWrite(2, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      break;
    case 7:
      pinMode(2, INPUT);
      pinMode(3, INPUT);
      pinMode(4, INPUT);
      digitalWrite(5, HIGH);
      break;
  }
}
```

Much of the general structure of the code is explained in the [electronics design week](https://digital-fabrication-portfolio-miro-keimioniemi-a2f2c11a6e705b8f.gitlab.io/p/electronics-design/#testing-the-board) documentation but in summary, it first initializes both the QTouch pins and the charlieplexed LED pins and then enters the main loop where each QTouch pin's value is printed. Then all of them are iterated through to determine if any of them are touched, which then determines which LED is turned on. 

The finished code differs from the original test code by introducing new baseline variables for each reading that are initialized by taking the maximum of a hundred samples for each in the setup phase every time the board is powered up in order to minimize the natural variablity. The loop is then made to iterate over a list of differences between the current readings of each pin and their established baselines and a lower difference threshold leading to the base case where none of the QTouch pins are touched. The qt_Threshold was set to 5 as it is significantly larger than the standard deviation of the measurements so that false activations due to random variation are avoided but is also low enough so that the pins remain highly sensitive, even with something in between. I also modified the switch statement to make sure that only one LED is ever on at once and deleted everything related to the onboard indicator LED to clean it up a bit.

{{< video src="sensitivity-tests.mp4" loop="true" muted="true" >}}

### Gestures code

```C
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

int qt_Threshold = 8;
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


  int qts[] = {qt_Threshold, qt1 - qt1_baseline, qt2 - qt2_baseline, qt3 - qt3_baseline, qt4 - qt4_baseline, qt5 - qt5_baseline, qt6 - qt6_baseline, qt7 - qt7_baseline};
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
```

{{< video src="gestures-test.mp4" loop="true" muted="true" >}}

![](paper-thickness.webp)





