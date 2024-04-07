---
author: "Miro Keimiöniemi"
title: "Output Devices"
date: "2024-04-07"
description: "Week 11"
tags: 
  - "electronics"
  - "design"
  - "KiCad"
  - "microcontroller"
  - "circuit board"
  - "milling"
  - "PCB"
  - "Roland Modela MDX-40"
  - "CopperCAM"
  - "Roland VPanel"
  - "soldering"
categories: 
  - "Electronics"
  - "Milling"
  - "CAD"
series: 
  - "Weekly Assignments"
image:
---

Speaker can be integrated very directly by just using an amp with breakout board according to this example: https://github.com/kr15h/i2s_xiao-esp32c3

Create a XIAO breakout board with a I2C connection to communicate with another board, an integrated speaker connection and connectors for LEDs

Capacitors, diode, voltage regulator, 


https://www.temposlighting.com/guides/how-to-add-custom-leds-to-any-project

Running with 3.3V works!!!
https://hackaday.com/2017/01/20/cheating-at-5v-ws2812-control-to-use-a-3-3v-data-line/
https://hackaday.com/2016/12/05/taking-it-to-another-level-making-3-3v-and-5v-logic-communicate-with-level-shifters/

https://learn.adafruit.com/adafruit-neopixel-uberguide/best-practices

CMOS vs TTL

https://www.penguintutor.com/electronics/mosfet-levelshift
https://www.esp32.com/viewtopic.php?t=9041

inverted mosfet thingy problematic due to code

https://forum.arduino.cc/t/3-3v-to-5v-logic-level-shifter-using-transistors/117723/3

Two inverters in series?

https://maker.pro/custom/tutorial/how-to-use-a-logic-level-shifter-circuit-for-components-with-different-voltages

Shortcircuiting esp32 caused an emp that knocked out my bluetooth devices? Even my glucose sensor connected to my phone

https://www.multi-circuit-boards.eu/en/pcb-design-aid/surface/conductor-ampacity.html

push the flux pen

Resistor markings: 4990 means 499 and 0 zeros

Struggled even more here than last week with my arch nemesis: NeoPixel LED strips

104 capacitor refers to 0.1uF



