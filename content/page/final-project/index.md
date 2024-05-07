---
title: Final Project
description: Gesture controlled sunrise alarm clock lamp - LED Zeppelin
date: '2024-02-01'
image: 'led-zeppelin-render.webp'
aliases:
  - project
lastmod: '2024-04-11'
menu:
    main: 
        weight: -99
        params:
            icon: bulb
links:
  - title: My Website
    description: See my portfolio on my personal website.
    website: https://mirokeimioniemi.com/
    image: /favicon.ico
  - title: GitHub
    description: See my public software projects on GitHub.
    website: https://github.com/MiroKeimioniemi
    image: https://github.githubassets.com/images/modules/logos_page/GitHub-Mark.png
---

The LED Zeppelin is a custom gesture controlled sunrise alarm clock lamp, where all the electronics are contained within the ellipsoid diffuser, that can be placed on or inside various different kinds of separate stands. It works as a regular lamp by tapping it to turn it on or off and swiping towards either end to adjust its brightness either up or down. The alarm clock functionality works via a mobile app where you can choose an animation including a sound that will start and reach its peak at the times set. The app can also be used to change the color as well as fine tune the brightness.

{{< 3DModel "lamp-render.glb" >}}

**TODO:**

| Task | Status | Deadline |
|----------|----------|----------|
| 1. Design the lamp and a stand  | [1st iteration complete]({{< relref "post/week-2/index.md" >}})  | 9.2.2024 |
| 2. Design touch detection circuit  | [Done]({{< relref "post/week-10/index.md" >}})  | 10.4.2024  |
| 3. Program touch detection circuit  | [Done]({{< relref "post/week-10/index.md" >}})  | 27.4.2024  |
| 4. Implement gesture detection  | [Done]({{< relref "post/week-10/index.md" >}})  | 27.4.2024  |
| 5. Design output circuit  | [1st iteration complete]({{< relref "post/week-9/index.md" >}}), 2nd needed  | 19.5.2024  |
| 6. Program light animations  | To be done  | 31.5.2024  |
| 7. Program ambient sound output  | To be done  | 21.5.2024  |
| 8. Program intra-board communication  | To be done  | 8.5.2024  |
| 9. Design power delivery circuit  | [1st iteration complete]({{< relref "post/week-9/index.md" >}}), 2nd needed  | 19.5.2024  |
| 10. Combine circuits and produce the result  | To be done  | 20.5.2024  |
| 11. Design mobile app  | To be done  | 8.5.2024  |
| 12. Implement mobile app with Flutter  | To be done  | 17.5.2024  |
| 13. Program wireless networking with mobile app  | To be done  | 17.5.2024  |
| 14. Design the internals and the ellipsoid lamp cover  | To be done  | 10.5.2024  |
| 15. Produce the lamp cover  | To be done  | 31.5.2024  |
| 16. Assemble the lamp  | To be done  | 31.5.2024  |
| 17. Produce the stand  | To be done  | 1.6.2024  |
| (18.) Design and produce an alternative stand  | Optional  | -  |
| (19.) Add long touch and double tap gestures  | Optional  | -  |
| (20.) Give the lamp a personality  | Optional  | -  |
| (21.) Proximity detection using e.g. Bluetooth  | Optional  | -  |
| 22. Make a presentation page and video  | To be done  | 7.6.2024  |

**Notes:**

<ol>
  <li value="5">Output circuit must be redesigned using level shifters in order to use 5V power for NeoPixels with 3.3V logic. 3.5mm audio socket pins must also be routed correctly. NeoPixels and level shifters are both already procured and available at the FabLab. </li>
  <br>
  <li value="6">Light animations can be programmed among the last tasks when the lamp is already assembled so that they look as intended.</li>
  <br>
  <li value="9">Likely need to purchase a 5V power source capable of 9A as I could not find one at the lab.</li>
  <br>
  <li value="15">3/4D mill a sikablock to produce half an ellipsoid diffuser by vacuum forming 3mm transparent (or white) acrylic already available at the lab. 
  
  Using Roland Modela MDX-40 might require a more elaborate design, where the piece to be vacuum formed might have to be produced in several layers. It, however, might not have sufficient length dimension either so 3D-axis milling with the larger CNC might be the best idea. It is a good idea to account for the fillet at the base of the mold by making it a bit higher than what the vacuum formed product should be. Remember to measure the height possible for a 3D-milled ellipsoid.
  </li>
  <br>
  <li value="14">Design a separate 3D-printable framework that safely suspends the circuit in the middle of the lamp from supports whose lengths correspond to the exact radius of the ellipsoid at the given positions. The circuit board can be fastened to it with screws and it can be fastened to the lamp cover with some kind of adhesive. With good design and little transportation, it might not have to be fastened at all. It is also obviously highly important to leave a hole for the power cable.</li>
  <br>
  <li value="16">Flexible copper strips soldered to jumper cables can be attached to the underside of the diffuser from their adhesive sides as seven looped stripes around the long axis. The internal frame can be fastened to one half with a strong adhesive and to the other with a slow one upon closing the ellipsoid. Alternatively, it does not have to be fastened to the other side at all. In this case, I could make the cover openable with some sort of a snapping mechanism, which is likely much harder to make but would make the lamp easily repairable.</li>
  <br>
  <li value="20">Make it behave like a luminous pet or a spren (from The Stormlight Archive) that turns on dimly when detecting proximity and might occasionally want attention, which it communicates by changing its hue until acknowledged with, for example, a long touch to which it might respond with some different light pattern. It could be made to track, for example, a habit or whether one had a good day. It could also be linked with another similar lamp such that if it is being touched for long, the other lamp lights up the area that is being touched and one can thus, for example, say a personal good night with it. In the long run it could even be made to talk and listen with additional hardware capabilities but those are definitely beyonf the current scope.</li>
</ol>

## Ideation

Having to come up with a final project idea as pretty much the first thing without knowing how everything works caught me a bit off guard but it does make sense in the context of the course as it is so intense, fast-paced and and packed with both information and assignments. Having a final project thought out in the very beginning helps you orient your approach to each week and know what you most need to focus on. For example, as a result of the below brainstorming and committing to an idea, I knew that I needed to focus especially on LEDs and speakers on the [output week]({{< relref "post/week-9/index.md" >}}). It was a long road to arrive at the idea, however, and what follows is a dump of some of the ideas I got, considered and eventually discarded.

The ideation phase is often very long for me as I always want to create something somehow meaningful, whether that is in a local or global context. For this project, it seems to make more sense to go local as that is, according to my understanding, in some sense the very ethos of the fab movement. I had a cool idea for remote chess boards but am a couple of years late, because those have already been producticed and commercialized by, for example, [ChessUp](https://playchessup.com/en-eu) (although I think I could make them nicer looking), which was both cool and a bit of a bummer. Maybe I will make them nicer looking and/or cheaper and compete that way one day.

After discovering this, I lost my appetite for the idea and tried turning to solving some personal problems instead. The only issue is that I currently cannot come up with too many problems I would have - how incredible is it to live in Finland and be in a modestly decent fiscal situation for a student? - so there were no obvious project ideas for this particular scope. I still do have many ideas but many of them were not directly suitable for this course. I kept on wondering about another remotely playable board game but after extensive research, I could not come up with any other the playing experience of which would be significantly improved over just a digital version. I would then have to create a new game myself, which I opened as a background tab in my mind and still keep there. However, here are the results of my further brainstorming within the bounds of the course:

- Luminous remote chess
- Remotely playable board game
- Connected, re-arrangeable statues that mirror each other's shapes. For example, a rigid string that can be folded to a shape, causing the other to take the same shape
- Remote drawing / writing inspired by The Way of Kings spanreeds
- 3D printer that scans the item put inside it and then replicates it
- Luminous remote chess
- Box that opens only when a task is completed (can be used for locking away one's phone or to keep a reward)
- Physical wave synthesizer that produces sound corresponding to the shape of a string (sine, saw, square etc.)
- Midi controller
- Mood lamp
- Wall clock
- Bright light alarm clock
- Something for a bookcase (physical reading challenge / art?)
- Weasley clock
- Lightsaber laser pointer
- Perpetual motion machine

Most interesting avenues:

- Action at a distance / "Magical items”
    - Remotely playable board game
    - Kinetic statues
    - Weasley clock
    - Spanreed
    - Lightsaber laser pointer
- Productivity boosters
    - Innovative alarm clock
    - Phone / reward locker
    - Year progress bar
    - Task / mortality visualization
- Midi controller / instrument / player

I ended up leaning toward creating some kind of an alarm clock / light that would wake me up to a simulated sunset. Many exist already, but they are kind of expensive and boring looking so the point here would prehaps be either the design or adding some cool feature that they do not have, at least in lower pricing points. With my non-existent drawing skills, I sketched a few ideas on Samsung Notes with my tablet. They look pretty horrendous due to being incredibly quick, not being drawn in an app made for it and being drawn by me, but perhaps they might still be somewhat representative of the general thought process.

![](sketch-1.webp)
![](sketch-2.webp)
![](sketch-3.webp)
![](sketch-4.webp)
![](sketch-5.webp)
![](sketch-6.webp)

I grew very interested towards the last one "Oval blimp thingy" that I then renamed to "gesture controlled bright alarm lamp", which Rosa suggested should be called the "LED Zeppelin" due to its resemblance to a zeppelin and the resulting pun. It was actually a real shower thought stumbled upon when pondering possible interesting shapes for a sunrise alarm clock. I think I was drawn to it for its elegance, where the oval is the perfect shape for simulating sunrises and sunsets. All electronics would be packed inside of it so that the stands could be changeable and thus a bit more of a design elemnt that can go anywhere from minimalist to elaborate. 

It also provides the perfect range of scaling challenge. Its primary function would be to function as an alarm clock that simulates a sunrise with independently controllable LEDs inside. The alarm would be set in a simple app that communicates with the lamp over Bluetooth to set the times for the alarm (integration with native clock apps is also an interesting potential avenue for exploration). A built-in speaker could also play some noise that increases in volume with the brightness. The secondary functions would be gesture controls, where a whole palm touch would turn it on and off and sliding one's hand over it would increase brightness in one way and reduce it in the other. The tertiary function would be to control the colors from the app in some unified way and make the brightness control dynamic such that lower brightness levels are warmer and higher are cooler.

An interesting addition would also be habit tracking, where, for example, a one fingered tap is a positive note, to which the lamp would react by a brief, gentle green blink and catalogue that in the app, where it could possibly be elaborated upon or just left as a positive mark. The ranking is based on which functionalities I would most need but it might be that 1 and 2 change places too. Achieving all of these would be perfect but there are also further expansion possibilites such as adding more long-distance proximity detection, adding mood lamp and connectivity functionality between other similar lamps, so that if two are connected and one is being touched, that is signaled to the other too. Also orientation detection for optimizing the light patterns based for each stand could be interesting. The possibilities are almost endless and the end product might be something like an expressive companion that would be similar to, for example, Alexa, but with light instead of voice.

Potential components:

- TTP223 capacitive sensor (30 for $8.59 on [Amazon](https://www.amazon.com/ALAMSCN-TTP223-Capacitive-Locking-Arduino/dp/B0BJDJP1ZR?th=1) or 100 for $10.99)
- RCWL-9196 microwave radar sensor (10 for 3-4€ on [AliExpress](https://www.aliexpress.com/item/1005004991510841.html?spm=a2g0o.detail.pcDetailTopMoreOtherSeller.2.293ey2yqy2yqlE&gps-id=pcDetailTopMoreOtherSeller&scm=1007.40050.354490.0&scm_id=1007.40050.354490.0&scm-url=1007.40050.354490.0&pvid=dc574ca4-b32f-4aac-8885-e2c47e0f1d27&_t=gps-id:pcDetailTopMoreOtherSeller,scm-url:1007.40050.354490.0,pvid:dc574ca4-b32f-4aac-8885-e2c47e0f1d27,tpp_buckets:668%232846%238114%231999&pdp_npi=4%40dis%21EUR%210.36%210.28%21%21%210.38%210.30%21%40210318c317070893569726894eab04%2112000031266085716%21rec%21FI%21%21AB&utparam-url=scene%3ApcDetailTopMoreOtherSeller%7Cquery_from%3A))
- XIAO SAMD21 (QTouch)

Notes:

Potential processes for making the cover:
- Vacuum forming is the most promising
  - possible materials:
    - Polystyrene (+sikablock)
    - Acrylic (pmma translucent acrylic)
- 3D printing
- Molding & casting (3D-printed mold?)


## Plan, progress and timeline

I have utilized the electronics design week and output devices week for getting acquinted with the [XIAO SAMD21](https://wiki.seeedstudio.com/Seeeduino-XIAO/) and [XIAO ESP32C3](https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/) boards that I can use for gesture input and wireless communication respectively, although the latter capabilities I have not yet further explored. Below are the two boards I have designed thus far and used for testing the input and output capabilities:

![XIAO SAMD21 QTouch controller board](xiao-samd21-qtouch-board.webp)

Upon quick testing, the QTouch sensors resolve touch nicely and they do register a slight change in capacitance under a 2mm sheet of acrylic as well. I will still have to conduct more testing by connecting different capacitive materials to the board and I am planning to take the programming much further as my main mission for input devices week. Thus far I have only checked that input is received and the readings change even with material in between but I will have to figure out how to detect the small changes. They also did not seem uniform across sessions, so absolute thresholds might not work for multiple reasons. One possible approach to solving this would be to initialize the capacitance readings during the first second of turning on and then detecting sufficiently large changes (e.g. > 5) so that it does not pick up on noise but works through most materials.

![XIAO ESP32C3 output board](output-board.webp)

For the output board I tested four different ways of controlling WS2812B strips but only two of them lit the LEDs up in the first place but none displayed the right colors, likely because the strip was not what I thought it was. I have not resolved the issue yet but this is obviously of key importance and high on the priority list. I could not make it work with 5V power input directly nor with using MOSFETSs to try to step up the logic voltage and we have no level shifters in the lab. Therefore, for powering on the LEDs on the final board, I will likely use the voltage divider to reduce the voltage from 5V to around 4.5V so that it is well within the spec but can also be reliably controlled with 3.3V logic. The board also has audio output but it was miswired such that the 3.5mm jack ground connection and right channel were the wrong way around. 

During the [input week]({{< relref "post/week-10/index.md" >}}), I programmed the touch and gesture detection components so that the SAMD21 receives clear input signals upon touch and can differentiate between taps and swipes for turning on and off and adjusting the level of brightness respectively.


Use vacuum forming to create the cover from acrylic
Use XIAO ESP32C3 as the main controller board for driving WS2812B strips and communicating wirelessly and (XIAO) SAMD21 as the secondary one to detect touch input
--> Order WS2812B strips and 74AHCT125 level converter(s)?
