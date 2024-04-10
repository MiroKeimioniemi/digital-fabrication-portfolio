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
image: "output-board.webp"
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

## Testing the LEDs

I tried testing the LED strip similarly for probably hours without result. I could not fathom what could possibly be wrong until I did some further research and discovered that, according to their [datasheet](https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf), the input voltage level to a WS2812B strip has to be 0.7 times the power voltage in order to be registered as a 1 bit. As they are rated for 3.5V - 5.3V, I tried to power them with 5V but controlling them with 3.3V logic did not work because it is less than 0.7 * 5V = 3.5V and so the NeoPixels could not resolve the peaks of the PWM signal from the valleys, resulting in them not responding. 

I used two different kinds of LEDs, one of which was a NeoPixel [strip](https://www.adafruit.com/product/1138) and the other a [stick](https://www.adafruit.com/product/1426). My first goal was to try and test whether the NeoPixels work in the first place - and I had a heavy suspicion that at least one of them should as I tried out a few. As none of them lit up, however, I got to my abovementioned research. 

![Unresponsive LED strip](unresponsive-leds.webp)

After discovering the difference between the [CMOS](https://en.wikipedia.org/wiki/CMOS) and [TTL](https://en.wikipedia.org/wiki/Transistor%E2%80%93transistor_logic) logic families, those being from the casual user's perspective mainly their input voltage requirements, I managed to diagnose the issue. With a great degree of simplification, the concept of a logic family relates to how logic gates are built physically in the circuit. What is interesting in terms of everyday usage, however, is that TTL (transistor-transistor logic) accepts "absolute" voltages such that the logic voltages are independent of the power voltage of a component, so that both 5V and 3.3V components recognize 2V logic, whereas CMOS (complementary metal-oxide-semiconductor) only accepts "relative" logic voltages, which must be at the least 0.7 times the power voltage of a component, meaning that a 3.3V device requires 2.31V logic input and a 5V device needs 3.5V logic input.

Herein lies the problem. I was initially trying to power them on with 5V and control them with 3.3V, which did not and - discovered with my newly found understanding - should not work. Even though, the strips are rated for 3.5V - 5.3V, I remembered successfully using them with 3.3V with the networking bracelet prototypes and so I tried it just to check that they were actually working. As can be seen below, this lit up the LED as expected.

![Lighting up a single LED](lit-led.webp)

Using a lower voltage seemed to work but this felt wrong. One would imagine that RGB LEDs are still one of the simplest output devices out there. Why should you have to drive them out of spec on so many microcontrollers? There had to be a better way. The question was then: how to step up the input voltage?

### Level shifting exploration

After extensive search, which started from this [Arduino forum post](https://forum.arduino.cc/t/neopixels-will-not-work-on-xiao-esp32c3-but-will-on-uno/1137392), I found a couple possible solutions: using components called 74HCT125, 74HC14 or 74HCT04, none of which we had at our lab, or creating a custom circuit using MOSFETs. The closest to the beforementioned components, at least in name, was the [74HC164D,653 8-bit serial-in/parallel-out shift register](https://assets.nexperia.com/documents/data-sheet/74HC_HCT164.pdf) but it did not sound like the right thing and I could not figure out if it could do the job or no due to my utter lack of all electronic circuits intuition and poor understanding of datasheets. I cannot even figure out all the components and connections of most example circuits with familiar sounding labels but incomprehensible and unexplained subscripts.

You cannot build circuits with components you do not have and thus I dove head-first into the MOSFET route. MOSFETs (Metal-Oxide-Semiconductor Field-Effect Transistor) are a type of [transistor](https://en.wikipedia.org/wiki/Transistor#:~:text=A%20transistor%20is%20a%20semiconductor,connection%20to%20an%20electronic%20circuit.) analogous to variable resistors. Unlike current controlled "regular" BJT transistors, MOSFETs are voltage controlled. There are three pins: drain (D), gate (G) and source (S). When voltage is applied to gate (G), current flows from the drain (D) to the source (S). They can thus be used as programmable switches or amplifiers by connecting the drain (D) to a voltage source and the source (S) to ground. If the voltage source is larger than the voltage applied to the gate (G) pin, the MOSFET acts effectively as an amplifier, outputting higher voltage signal than the logic input, which was exactly what I was looking for. 

![MOSFETs soldered on a board](mosfets.webp)

[Here](https://www.youtube.com/watch?v=J4oO7PT_nzQ) is a [great video about transistors in general](https://www.youtube.com/watch?v=J4oO7PT_nzQ) and [here](https://www.youtube.com/watch?v=GrvvkYTW_0k) is a shorter, simpler explanation on [N-channel MOSFETs](https://www.youtube.com/watch?v=GrvvkYTW_0k) specifically, which are the most common type. The datasheet for the N-channel logic level MOSFETs can be found [here](https://www.onsemi.com/pdf/datasheet/nds355an-d.pdf).

While a relatively simple component, their actual usage was not quite as obvious. I searched for model circuits and found a wide range of variants. [Many](https://forum.arduino.cc/t/neopixels-will-not-work-on-xiao-esp32c3-but-will-on-uno/1137392) [have](https://forums.adafruit.com/viewtopic.php?t=166684) [had](https://forum.arduino.cc/t/shift-register-output-voltage/65511) [similar issues](https://www.reddit.com/r/arduino/comments/4wxz05/neopixel_on_33v_arduino_help/) to mine but none were definitively solved outside the [recommendation to use a 74AHCT125 level shifter](https://electronics.stackexchange.com/questions/593193/high-frequency-voltage-conversion-3-3v-control-of-neopixels), which I did not have access to during the few days I had. Another option would have been to step down the power voltage to the NeoPixels but this felt like giving up (something).

I jumped from [one](https://forum.arduino.cc/t/level-shifting-3-3v-to-12v-without-inversion/916694) [forum](https://forum.arduino.cc/t/solved-how-to-build-level-shifter-3-3v-to-24v/345469) [post](https://forum.arduino.cc/t/3-3v-to-5v-logic-level-shifter-using-transistors/117723) to the [next](https://electronics.stackexchange.com/questions/82104/single-transistor-level-up-shifter) trying to look for the one definitive answer to how to level-shift 3.3V logic to 5V for use with a NeoPixel strip but could not find one. I did finally discover a reasonable seeming logic level shifter circuit by "penguintutor" [here](https://www.penguintutor.com/electronics/mosfet-levelshift), but they said that the circuit is inverting but that it could be compensated for in software - but they never explained how. Not even on the program code page. 

!["Logic level shift for a NeoPixel" from penguintutor.com](logic-level-shifter.webp)

I was confused as to how that would happen as according to my understanding, the amplified current was supposed to flow when a voltage was applied to the gate. Now that I look at it afterwards, it might be because the output is connected on the side of the voltage source and therefore, if the output is connected to something that is later connected to ground, the current flows by default. With this explanation, however, I do not see how opening another path to ground would then turn it off either... It would feel a lot more logical to have the output be connected to the ground end so that current flows through it only when voltage is applied to the gate. I also do not see how this alternative would be inverting. I continued searching for explanations and alternative circuits and stumbled upon the following pages:

- [https://hackaday.com/2016/12/05/taking-it-to-another-level-making-3-3v-and-5v-logic-communicate-with-level-shifters/](https://hackaday.com/2016/12/05/taking-it-to-another-level-making-3-3v-and-5v-logic-communicate-with-level-shifters/) 
  I originally learned about CMOS and TTL here and while it mentions a few types of level shifter circuits, they are really not explained at all.

- [https://www.newark.com/pdfs/techarticles/microchip/3_3vto5vAnalogTipsnTricksBrchr.pdf](https://www.newark.com/pdfs/techarticles/microchip/3_3vto5vAnalogTipsnTricksBrchr.pdf) This is where the 3.3V to 5V MOSFET circuit presented in the above link originates from but although important parameters for selecting the resistor's resistance, such as the switching speed of the input and the current consumption through the resistor, are considered, the actual functioning of the circuit is not explained and nothing is mentioned about inversion.

- [https://hackaday.com/2017/01/20/cheating-at-5v-ws2812-control-to-use-a-3-3v-data-line/](https://hackaday.com/2017/01/20/cheating-at-5v-ws2812-control-to-use-a-3-3v-data-line/)
  Here is some kind of a hack for creating a level shifter out of a "sacrificial" NeoPixel but I do not quite understand how exactly it works and it would probably not have been too pretty integration-wise. It is applied [here](https://todbot.com/blog/2017/01/12/crashspace-bigbutton-w-esp8266/).

- [https://electronics.stackexchange.com/questions/82104/single-transistor-level-up-shifter](https://electronics.stackexchange.com/questions/82104/single-transistor-level-up-shifter) Here is discussion about the simplest possible single-directional level shifter but the example was made with a BJT transistor and the discussion moved to impedances of devices on certain sides and I was lost.

- [https://forum.arduino.cc/t/3-3v-to-5v-logic-level-shifter-using-transistors/117723](https://forum.arduino.cc/t/3-3v-to-5v-logic-level-shifter-using-transistors/117723) Here I was introduced to the idea of chaining two NPN transistors one after another, allegedly inverting the signal twice (still don't know where the inversions come from) to output an amplified, non-inverted signal.

- [https://maker.pro/custom/tutorial/how-to-use-a-logic-level-shifter-circuit-for-components-with-different-voltages](https://maker.pro/custom/tutorial/how-to-use-a-logic-level-shifter-circuit-for-components-with-different-voltages) Here is an even more complicated version of the above using two different types of transistors.

- [https://learn.sparkfun.com/tutorials/bi-directional-logic-level-converter-hookup-guide/all#board-overview](https://learn.sparkfun.com/tutorials/bi-directional-logic-level-converter-hookup-guide/all#board-overview) Here is Sparkfun's Bi-Directional logiv level converter circuit.

- [https://forum.arduino.cc/t/solved-how-to-build-level-shifter-3-3v-to-24v/345469](https://forum.arduino.cc/t/solved-how-to-build-level-shifter-3-3v-to-24v/345469) Here is some of the most extensive discussion I found on the topic amd some of the best circuit diagrams, one of which I ended up using. A lot of the discussion I cannot follow, however, as a lot of background knowledge is assumed, which I simply do not have.

- [https://forum.arduino.cc/t/level-shifting-3-3v-to-12v-without-inversion/916694/5](https://forum.arduino.cc/t/level-shifting-3-3v-to-12v-without-inversion/916694/5) Here is some additional discussion on the topic still.

Below are some of the circuit diagrams found on these pages:

![Level shifter circuit 1](shifter-3.webp)
![Level shifter circuit 2](shifter-6.webp)
![Level shifter circuit 3](shifter-1.webp)
![Level shifter circuit 4](shifter-2.webp)
![Level shifter circuit 5](shifter-5.webp)
![Bi-Directional converter](bi-directional-converter.webp)
![Level shifter circuit 6](shifter-4.webp)

They certainly do seem to share a common theme but no two were quite the same. Simplicity would obviously be preferred and so I tried to look into the possiblity of inverting the signal in software too but this was quickly shot down on the [FastLED forums](https://www.reddit.com/r/FastLED/comments/suwld0/how_can_i_invert_my_signal/). Furthermore, a [general sentiment](https://www.reddit.com/r/FastLED/comments/cdkkwe/possibly_to_invert_the_output/) seemed to be that no level-shifting should usually even be necessary. Even [Adafruit's NeoPixel Überguide](https://learn.adafruit.com/adafruit-neopixel-uberguide/logic-level) mirrored this sentiment but it appears that my components were then really at the very opposite ends of the tolerances as they would not play ball - just my luck. On [espressif forums](https://www.esp32.com/viewtopic.php?t=9041) there was a suggestion to invert the output on the GPIO pin definition level but this did not work at least quickly either.



## Board design

As already mentioned above, this week I used the [XIAO ESP32C3](https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/) board due to it being used in the audio output example but also because of its future-proof networking capabilities. Some of its most important specs are listed below.

[Seeed Studio XIAO ESP32C3](https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/)

- ESP32-C3 32-bit RISC-V singlecore processor running at up to 160MH
- 4MB of onboard flash memory
- 400KB of SRAM
- 11 digital (PWM) I/O pins, 4 of which also analog (working voltage 3.3V)
- 1 I2C interface
- 1 SPI interface
- 2 UART interfaces
- Complete Wi-Fi subsystem complying with IEEE 802.11b/g/n protocol supporting Station, SoftAP and promiscuous modes, with first two simultaneously too
- Cryptographic hardware accelerators supporting AES-128/256, Hash, RSA, HMAC, digital signature and secure boot
- Bluetooth LE subsystem supporting Bluetooth 5 and mesh
- Type-C power supply and downloading interface
- 3.3V/5V DC power
- 5V output pin supports also input with a diode

![XIAO ESP32C3 pinout](xiao-esp32c3-pinout.webp)




initially with power supply but left it out

Started with esp32 and audio


SLEEVE & TIP for 3.5mm jack - NOT SLEEVE AND RING



Create a XIAO breakout board with a I2C connection to communicate with another board, an integrated speaker connection and connectors for LEDs

Capacitors, diode, voltage regulator, 


https://www.temposlighting.com/guides/how-to-add-custom-leds-to-any-project

Running with 3.3V works!!!

https://learn.adafruit.com/adafruit-neopixel-uberguide/best-practices




Two inverters in series?


Shortcircuiting esp32 caused an emp that knocked out my bluetooth devices? Even my glucose sensor connected to my phone

https://www.multi-circuit-boards.eu/en/pcb-design-aid/surface/conductor-ampacity.html

push the flux pen

Resistor markings: 4990 means 499 and 0 zeros

Struggled even more here than last week with my arch nemesis: NeoPixel LED strips

104 capacitor refers to 0.1uF

hole clearance issue was ignored with no problem






