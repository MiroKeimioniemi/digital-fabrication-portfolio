---
author: "Miro Keimiöniemi"
title: "Computer-Aided Design"
date: "2024-02-02"
description: "Week 4"
tags: 
  - "CAD"
categories: 
  - "CAD"
series: 
  - "Weekly Assignments"
image: 
---

## Assignments

- Pick a simple object and design it using vector drawing software such as InkScape, Illustrator or Boxy SVG. The object could be something as simple as a nail, a hinge or a bolt or anything related to your final project. It could be a logo of a product that you are about to prototype.
- Use a raster graphics software of your choice, such as Gimp, Photoshop or Photopea, to edit, crop, resize and optimize an image of your choice.
- Explore a few 3D modelling tools (e.g. Blender, FreeCAD (Onsdel ES), SolveSpace, Fusion 360, Solidworks, Rhino) and pick one to make something for your final project.
- Create page containing the assignment documentation on your website.
- Document your process with screenshots and descriptions.
- Submit a link to that page here.

## 2D Modelling

### Vector - Inkscape

### Raster - Gimp

I have done most of my image processing with [Photoshop](https://www.adobe.com/products/photoshop.html) back in the day when I still had a license. At one point I could no longer justify the costs of a Creative Cloud subscription as I did not have much time to play around with it anymore and basic editing could be done on the phone or on the web with apps such as [Figma](https://www.figma.com/), [Canva](https://www.canva.com/), [Pixlr](https://pixlr.com/), [Adobe Express](https://www.adobe.com/express/feature/image/editor) and many others. Still, I found [Gimp](https://www.gimp.org/) installed on my laptop too so I will have to assume that I might have either edited a photo or intended to do so in the past but I have no recollection of this, as could be seen from my non-existent command of the software.

My first (second?) impressions are that on the surface it looks and seems like Photoshop, but immediately it can be seen - and especially felt - that the usabilty is quite different. I try to change the selected tool or hit `Ctrl + T` to enter transform mode and nothing happens. Scaling down a layer actually scales it down such that if it is scaled back up, it looks blurry. Coming from Photoshop, nothing works quite like you would expect it to and everything feels just a little bit clunkier and less streamlined. However, I must admit that I did not spend very long on this as I wanted to get to 3D as fast as possible and it might just be a configuration issue or not being used to it.

Last year, around this time, I started my journey developing a [probabilistic strategy game](https://github.com/MiroKeimioniemi/probabilistic-strategy-game) from scratch, for which I had long had the idea. I finished it as a semi-polished local 2-player conquest game, where each player assigns primary moves to all their units during their turn, which get executed based on the probability of success. If the primary move, such as "move a wide and heavy tank to a thick forest square" fails, a secondary move is attempted, which can be anything from retrying to engaging in a battle with the enemy at optimal or subotimal range, depending on the distance in between. Each unit type and territory have different attributes resulting in strengths and weaknesses for different kinds of positions, which can also change by, for example, a tank blasting a mountain range into flat gravel. 

The prototype of the ambitious game was finished slightly after Wappu (1.5.) after six days with a total of 8 hours of sleep but I am quite proud for the solo effort, building it from scratch using [Scala](https://www.scala-lang.org/) and [ScalaFX](https://www.scalafx.org/). However, it is not very approachable for the average person who might not have the correct [JVM](https://en.wikipedia.org/wiki/Java_virtual_machine) environment installed and configured and so I am planning to package it into some kind of an executable and for that purpose, I wanted an icon for the application. Something simple but distinct. 

I figured this would be the perfect opportunity and so, after studying the [how to make windows icons](https://learn.microsoft.com/en-us/windows/win32/uxguide/vis-icons), I fired up Gimp and created a new 256x256 (maximum size for `.ico`) project with x- and y resolution of 72. I dragged and dropped in some of the crude custom assets I had made for the game using [Pixilart](https://www.pixilart.com/) and played around with potential arrangements a little until I ended up with placing the contrasting enemy tanks on contrasting terrain tiles in a logo that appears decent looking and recognizable in a very small form factor too. I scaled down the assets to 150px and 128px with `Shift + S` and rotated the blue one 180 degrees with `Shift + R`. I merged the layers by right clicking the top one and pressing "Merge Down" until they were all merged, which was faster that figuring out how to select multiple layers, as for some reason holding control or shift and clicking did not work. I then duplicated the layer and scaled it into different sizes: 256, 128, 96, 64, 48, 32, 24 and 16, which was what the 2021 updated [windows guide](https://learn.microsoft.com/en-us/windows/win32/uxguide/vis-icons) recommended on the topic. I then exported them as `.ico`, which automatically recognized each layer as corresponding to a variant in the icon file. I selected compress for all of them to make it 33% smaller still and then I was done.

![New Gimp project](gimp-new-project.webp)
![Gimp project](gimp-project.webp)
![Gimp export ico](gimp-export.webp)
![Probabilistic strategy game icon](probabilistic-strategy-game-icon.webp)

## 3D Modelling

## Reflections
