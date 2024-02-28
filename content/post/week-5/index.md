---
author: "Miro Keimiöniemi"
title: "3D Printing & Scanning"
date: "2024-02-27"
description: "Week 7"
tags: 
  - "CAD"
  - "software"
  - "3D modeling"
  - "Blender"
categories: 
  - "CAD"
  - "3D Printing"
  - "3D Scanning"
series: 
  - "Weekly Assignments"
image:
---

Easily the hardest part of this course is to come up with the ideas for each week's project. Not because of my lack of ideas or creativity in general but because of my desire to make something useful or meaningful for each project with limited time in the lab because of its opening hours, the number of other students on the course whose machine time I do not want to encroach upon, and because I am taking three other courses at the same time with this, those being [Statistical Inference](https://www.aalto.fi/en/open-university-course-list/statistical-inference), [Theory of Computation](https://courses.aalto.fi/s/course/a053X000012R0qeQAC/theory-of-computation?language=en_US) and [Artificial Intelligence D](https://courses.aalto.fi/s/course/a053X000012QzrRQAS/artificial-intelligence-d?language=en_US). Additionally, I just joined a startup called [Miitti App](https://www.miitti.app/) and am still in the process of finding a paying summer job in the software industry too. 

All of that put together adds up to quite a bit of intellectual work, on top of which I still have to figure out what I would 1. want to and 2. be realistically able to make each week. Sometimes the constraints in our assignment guide and help in this and other times, such as this week, they make it all the more difficult. See the assignments below, particularly the "What to design?" section.

## Assignments

**Basics**

- Do NOT use Formlabs printers. This assignment is only FDM.
- Join one of the scheduled introduction / TA sessions to complete the group assignment and get booking access to printers.
- The FDM 3D printers are booked for you until end of next week.

**Group assignment**

- Join FDM 3D Printing introduction session and document as you go.
- After the introduction session each of you should print one design rule test file (angle, free, bridging, combined) using any of the FDM 3D printers.
- Look at the prints together and discuss what can you learn from them in terms of design rules.
- Each group has a group leader who is responsible for creating the group assignment page.
- Each participant from the group should link to that page from their individual documentation.

**Individual assignment**

- Design an object (a small one, few cm3) that CAN NOT be made using subtractive manufacturing.
- 3D print the object you designed using an FDM printer, such as Ultimaker, Prusa MK4 or Prusa MINI.
- 3D scan anything with one of our Creality Ferret 3D Scanners.
- Document your process on a new page on your documentation website.

**What to design?**

According to ChatGPT, subtractive manufacturing involves removing material from a larger block or piece of material to create the desired object. However, there are certain objects that cannot be made using this method. Here are some examples:

1. Hollow objects
2. Objects with complex internal structures
3. Objects with fine details
4. Objects made of certain materials
5. Irregularly shaped objects

## Designs

As already mentioned, this week's project was particularly difficult to come up with due to the strictness of the requirements, those being the small size and something that cannot be created using subtractive manufacturing. To achieve the desired scale, my ideas initially fell into two categories: characters and cable holders, preferably fusing them into one somehow to have both a design challenge as well as something somewhat functional. However, the limitation of it having to be something that cannot be manufactured subtractively proved to be very challenging for my skillset

I could only come up with two kinds 



wanted to create some kind of a character 


Adding a loopcut to the center and deleting the vertices on one side made it so that the object scales only in the remaining direction as the centerpoint was now in the corner.

Scale 1 is good, rotated 180deg over y-axis and 45 over z-axis and then additionally 4.5 in both over x and y

Added a mirror modifier over all X, Y and Z

Remember to apply modifiers, weird shit happens if you don't

1.6cm

https://www.creality.com/pages/download-cr-scan-ferret

Make sure modifiers are the right way around

Exporting .stl also exports invisible items

To clean up in blender Edit > X-ray > Lasso Select > Delete


## 3D Printing

{{< 3DModel "tesseract-keychain.glb" >}}
{{< 3DModel "cable-holder.glb" >}}

Remember to apply modifiers to be displayed in .glb

[Group documentation](https://zinaaaa.gitlab.io/digital-fabrication/week6_docu.html)

## 3D Scanning

{{< 3DModel "wooden-hammer.glb" >}}
{{< 3DModel "black-panther.glb" >}}

Only kept .glb files in the repo (others are saved locally) because they contain textures and everything as jpgs get converted to webps by my scripts. also to save space

Added the following shortcode for displaying the models using [modelviewer](https://modelviewer.dev/):

```html
<script type="module" src="https://unpkg.com/@google/model-viewer/dist/model-viewer.min.js"></script>

<model-viewer style="width: 100%; height: 400px;" src="{{ .Get 0 }}" alt="3D model" auto-rotate camera-controls></model-viewer>
```

Tesseract key chain and basic cable holder, three branches keychain, sword keychain?

x-ray mode and lasso to delete entire parts

Hammer face count went from 853476 to 213369 only because the texture was very intricate and this was passable in that only very slight distortion was introduced




Paddington or another non-descript bear with a hat and a raincoat if there is a copyright issue. Should not be, however, as this material is purely for educational purposes.

Tesseract

select face in edit mode and move up along Z-axis
