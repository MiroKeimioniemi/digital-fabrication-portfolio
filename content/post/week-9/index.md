---
author: "Miro Keimiöniemi"
title: "Output Devices"
date: "2024-04-09"
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
  - "output"
  - "Output devices"
  - "speaker"
  - "audio"
  - "neopixel"
  - "LED"
  - "WS2812B"
categories: 
  - "Electronics"
  - "Milling"
  - "CAD"
series: 
  - "Weekly Assignments"
image: "output-board.jpg"
---

This week I faced my old nemesis once again; the NeoPixel LED strip. Nothing in electronics has caused me nearly as much headache as them. When creating the [networking bracelet prototypes](https://www.linkedin.com/posts/miro-keimi%C3%B6niemi_now-that-school-is-over-for-the-year-ill-activity-7143994838173089792-r3KP?utm_source=share&utm_medium=member_desktop), we could not find a single small development board in the entire [Aalto school of electrical engineering](https://www.aalto.fi/en/school-of-electrical-engineering) that would support both FastLED or NeoPixel arduino libraries and bluetooth communications. Both Arduino Nano 33 BLE and Nano 33 IoT lacked the former whereas we apparently had the only esp32s (ESP 32-S2) that lacked the latter, forcing us eventually to opt for an Arduino Micro with a separate, external Bluetooth module. 

As recently as just last week I had opted out of using them in favor of standard LEDs due to unnecessary complexity where each NeoPixel would have needed its own capacitor and my first attempt at wiring all of it got very nasty. However, I could no longer run but had to finally confront it head first due to their central importance for my final project. I had gotten away with powering them directly with 3.3V from the Arduino Micro with the networking bracelet prototype due to how few we needed to use but I could not risk operating even slightly outside of specification when I would need probably closer to a hundred instead of only few and so I spent the  vast majority of output week wrestling with how to drive 5V CMOS LED strips with 3.3V logic, all of which will be delved into and explained more deeply below.

## Assignments

- Add an output device to a microcontroller board you've designed, and program it to do something. 
- If you have not produced and tested a board in the Electronics Design week yet, you can improve its design to include an output device and produce one working board for both of the weeks (Electronics Design and Output Devices).
- Include a hero shot and source files of your board in your documentation (such as KiCad project and Arduino test code).

## Outputting audio

On the surface, my final project is a gesture controlled lamp, which sounds interesting and somewhat unique in its particular form but also relatively simple to make, but my true underlying motivation was to create a wake-up lamp capable of simulating a sunrise and with a unique spin to it. However, I am a very heavy sleeper and need something in addition to just light, even if it is shining straight at my face from up close. My idea is therefore to also have a speaker inside that plays, for example, nature noises and gets louder at the same rate as the sunrise gets brighter and whiter for a gradual, gentle wakeup.

I thus started by trying out a small speaker, which was delightfully straigthforward to use in comparison to the NeoPixel LEDs. I took one which already had an adapter and just plugged it to a laptop to hear what it would sound like. It was very quiet but reproduced the desired sound well. I then tried driving it using a microcontroller according to [documentation](https://github.com/kr15h/i2s_xiao-esp32c3) by our instructor.

![Small speaker back](small-speaker-back.webp)
![Small speaker front](small-speaker-front.webp)

I have now learned to always go with the exact parts discussed if they are available as hardware compatibility issues get a lot nastier and more annoying than software ones, where there usually exists workarounds. Therefore, I grabbed the [XIAO ESP32C3](https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/), which I found to potentially be quite optimal as the main microcontroller of my entire final project upon further research for reasons further explained below. I then paired it with the [Adafruit MAX98357 I2S Class-D Mono Amp](https://learn.adafruit.com/adafruit-max98357-i2s-class-d-mono-amp/raspberry-pi-wiring) with a [2-pin screw terminal block](https://www.adafruit.com/product/724) soldered on it and a couple wires.

Before designing and soldering anyhting, I wanted to make sure that the documentation delivered on its promises and that all the components certainly worked. I connected the pins [as specified](https://github.com/kr15h/i2s_xiao-esp32c3) with the left side representing the XIAO ESP32C3 and the right the amplifier:

- GND -> GND
- 5V -> VIN
- D7 (GPIO20) -> LRC
- D6 (GPIO21) -> BCLK
- D5 (GPIO7) -> DIN

I connected the XIAO to my laptop and uploaded the [`SimpleTone.ino` example code](https://github.com/kr15h/i2s_xiao-esp32c3/blob/main/SimpleTone.ino) playin a consistent 440Hz. Even though the test setup was fiddly and fragile with wires pushed through holes and diagonally against their walls, the experiment was successful as can be heard below:

{{< video src="initial-speaker-test.mp4" loop="true" muted="true" >}}

Since the last time I had edited a video for documentation, Microsoft had made it mandatory to register to [Clipchamp](https://clipchamp.com/en/) and so the above video was edited with [kdenlive](https://kdenlive.org/en/), which is an open-source video editing application that Neil Gershenfeld had recommended on the very first lecture if I remember correctly. The very basic operations and navigation felt pleasantly similar to [Adobe Premiere Pro](https://www.adobe.com/products/premiere.html), with which I am already intimately familiar with, although exporting was found under "Project" > "Render..." which caught me a bit off guard. Overall, however, I am much happier with it than Clipchamp. The tone produced by the contraption depicted above was again very quiet and hence I increased the gain of the audio in the clip to 1000%.

## Design

XIAO ESP32 board



Started with esp32 and audio




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

hole clearance issue was ignored with no problem




