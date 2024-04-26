---
author: "Miro Keimiöniemi"
title: "Molding & Casting"
date: "2024-04-25"
description: "Week 13"
tags: 
  - "CAD"
  - "software"
  - "3D modeling"
  - "Fusion 360"
  - "Blender"
  - "Ultimaker"
categories: 
  - "CAD"
  - "Molding"
  - "Casting"
series: 
  - "Weekly Assignments"
image: "dg-lightsaber-render-horizontal.png"
---

The last official entirely creative week! What I mean by this is that this was likely the last entirely self-contained project week - independent of the final project and not contributing to it - where I had to first learn a new process, then come up with an idea for what to do with it, design the project and use the process to create it - all within a single week. It's almost making me kind of nostalgic already but it is also a major relief as now I get to focus my efforts on the final project without having to be so all over the place. This is further helped by the fact that instead of having three other different courses in parallel, now I only have [linear algebra](https://www.aalto.fi/fi/avoimen-yliopiston-kurssit/linear-algebra). Being the last full project week puts a lot of pressure on keeping up the track record, however, and so I could not make just anything. Luckily, yet another shower thought struct and allowed me to do three things at once; make something cool for our absolutely amazing [Data Guild](https://dataguild.fi/), make something cool for this week and have it take the form of a lightsaber hilt, which I have wanted to design for ages.

## Assignments

- Review the safety data sheets for at least two of labs molding and casting materials.
- Make and compare test casts with each of them.
- Design a 3D mold around the stock and tooling that you'll be using.
- 3D print it using FDM printers
- Use it to cast parts.
- Include a hero shot and source files of your design in your documentation.

## Design

As already established, I would generally want everything I create to serve some kind of purpose in terms of being useful and preferably necessary or at least somewhat meaningful. Luckily we humans are great at ascribing meaning to anything and everything so the latter criteria is usally much easier to fulfill. I still found it difficult, however, as in terms of small plastic objects, I had already made a keychain and a cable holder during the [3D printing & scanning week]({{< relref "post/week-5/index.md" >}}) and I could not figure out what else I would want to create at that scale.

Apparently one can mold and cast almost any types of material and of the rarer varieties, chocolate was mentioned as one of the explicit examples on the [global lecture](https://www.youtube.com/watch?v=ohZDPuDLI-c). I first considered making some funny shaped chocolate but I could not match my coursemate [Vytautas Bikauskas'](https://timeritualslabour.gitlab.io/digital-fabrication/week11.html) mean bar and austerity chocolate calendar, which I found hilarious! If you are reading this and want to ever commercialize it, hit me up! I can help with designing and making websites, doing market and customer research, pitching and branding as well as especially creating marketing and sales strategies ;D

I could not compete with that in the time I had and the process seemed a bit involved with special types of chocolates and warming it up etc. In order to catch up by next week, I have to do three weeks worth of work in one and thus I decided to follow the process as presented. This left me with plastic as the material. I considered creating a mold from the panther I 3D scanned in [week 5]({{< relref "post/week-5/index.md" >}}) or making custom Chess pieces, which inspired me to think more about board games. This, on the other hand, led me to [Jungle Speed](https://en.wikipedia.org/wiki/Jungle_Speed), which became an enormous hit in our guild last autumn as we introduced it with Aawez and caused severe sleep deprivation to many due to multiple very long nights of continuous playing. 

It is a reflex-based pattern matching game where every time two or more people play the same shape, they must fight over a totem and the loser(s) who did not get it has to take their and the opponent's cards. First one to get rid of their cards wins and the game can be continued to arrive at a ranking. The totem is exactly in the right order of magnitude in terms of size and we just got a new guild room, which gives a great excuse for gifting DG a nice symbol capturing the spirit of this academic year - and it can be used for playing too, although you have to be more careful not to poke anyone in the eye with it than with the more rounded standard totem. Furthermore, we have been planning to have a Jungle Speed tournament for long and it might serve as a trophy for that too. Below is an image featuring some of the cards, the totem and its very approximate digital twin. 

![Jungle Speed cards and totem with an approximate digital twin](jungle-speed.webp)

I started by opening Fusion 360 and creating a new component for the totem, under which I created a closed sketch and made a body out of it using the "Revolve" operation around the Z-axis with the sketch selected as the profile. A 360° revolution around the Z-axis produced the above and below digital twin totem. This was very easy to edit with the points movable even in the 3D view with the correct component selected - allowing live sculpting. Another heavily utilized tool was the "Circular Pattern" tool, which duplicated objects symmetrically along the arc of a circle. These two in combination were everything extra one needs to create circular objects in addition to the basics tools discussed in [Computer-Aided Design]({{< relref "post/week-2/index.md" >}}) in the context of Ondsel, which I was no longer confident using due to an incident in [week 9, Computer-Controlled Machining]({{< relref "post/week-7/index.md" >}}).

![Sketch of revolve profile](twin-sketch.webp)
![Revolve tool](revolve.webp)
![Circular pattern tool](circular-pattern-tool.webp)
![Circular pattern](circular-pattern.webp)

I experimented with different side profiles and the idea of making it difficult to grab due to a weird, irregular shape or even spikes to make playing with it more interesting. Then I remembered that I had had a [lightsaber](https://en.wikipedia.org/wiki/Lightsaber) as a project idea for long. This was highly appropriate not only because I personally am a massive [Star Wars](https://en.wikipedia.org/wiki/Star_Wars) fan but because the majority of our guild is as well. In fact, our fuksi captain Pranav owns his own collection, one of which has been used as a prop and even a beacon in many events for this year's fuksis. Below are images of the final design in the design view and the render view. The coloring of the components is just a cool looking suggestion.

![Custom Data Guild lightsaber Jungle Speed totem](dg-lightsaber.webp)
![Custom Data Guild lightsaber Jungle Speed totem render](dg-lightsaber-render.webp)

The design files can be found from the repository [here](https://gitlab.com/miro.keimioniemi/digital-fabrication-portfolio/-/tree/main/content/post/week-11) under [`content/post/week-11`](https://gitlab.com/miro.keimioniemi/digital-fabrication-portfolio/-/tree/main/content/post/week-11). Below is the 3D model of the custom Data Guild lightsaber Jungle Speed totem:

{{< 3DModel "dg-lightsaber.glb" >}}

Story of the particular design

Did not use many constraints

## Making the mold

### 3D modeling

{{< 3DModel "dg-lightsaber-super-mold.glb" >}}

### 3D printing

20 hours with ultimaker, 9 with prusa

I like Prusa more

### Molding

## Casting


