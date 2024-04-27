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
image:
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

As I already pretty much built my input board during the [electronics design week]({{< relref "post/week-8/index.md" >}}), I decided to dedicate this input week to adapting it for my final project. The QTouch pads registered a change in capacitance exactly like I wanted, even through some thin materials, and all the charlieplexed indicator lights light up to correctly designate the pad that is being touched. However, the capacitance reading are different and the changes are smaller with a material on top. Hence, my goal for this week was to program a solution for correctly detecting touch through (bent) acrylic.  
