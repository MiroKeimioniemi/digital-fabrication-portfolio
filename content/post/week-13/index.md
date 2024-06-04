---
author: "Miro Keimiöniemi"
title: "Interface and Application Programming"
date: "2024-05-08"
description: "Week 15"
tags: 
  - "programming"
  - "software"
  - "UI/UX"
categories: 
  - "Programming"
series: 
  - "Weekly Assignments"
image: "cover.webp"
---

![Figma UI draft](figma-ui-draft.webp)

Sun/Moon shows the current color of the lamp. The brightness slider adjusts the lamps brightness, while illustrating this by the sun/moon either rising or lowering and the lighting of the scene adapting by becoming more or less bright. Initially the idea was for the moon and sun to swap places as the slider is being moved but now I am thinking that I might want to have it be either one based on the time of day and have it be draggable in the vertical axis for another way of adjusting the brightness.

Next to the brightness slider is a color picker icon, the tapping of which brings out the color wheel that allows the user to change the color of the lamp. The chosen color along with current brightness fully determines the colors of all visual elements of the UI. Swiping down, left or right or tapping the icon again hides the color wheel. Below them is the animation menu, where the highlighted selection indicates which animation will be played with the next alarm. The user can browse them in place and change the animation of the next alarm regardless of what its animation has been set in the alarms section.

The alarms section can be accessed by tapping the displayed time or the pen icon next to it. It has seven slots, one for each weekday, which allows the user to set automatically recurring alarms at any time. Tapping the time in this view opens a time picker, whereas tapping the animation next to it opens the animations view, where the user can select the desired animation.

https://rydmike.com/flexcolorpicker/




Make sure which widget's parameters are needed

CTRL + SHIFT + P brings out all useful commands:
- Toggle Debug Painting is highly useful
- Get packages if they are not recognized even when imported ( https://stackoverflow.com/questions/44909653/visual-studio-code-target-of-uri-doesnt-exist-packageflutter-material-dart )
- Select device

SHIFT + ALT + F automatically formats the document nicely


SVG viewbox has nothing to do with the actual size of the svg, it is merely a coordinate system


CTRL + . to wrap with widget (1000x faster than without)

Gradient appeared grey but it seems that debug painting added other overlay stuff too

https://greymag.medium.com/flutter-orientation-lock-portrait-only-c98910ebd769








