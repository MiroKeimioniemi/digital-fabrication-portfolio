---
author: "Miro Keimiöniemi"
title: "Computer-Aided Design"
date: "2024-02-09"
description: "Week 4"
tags: 
  - "CAD"
  - "2D modeling"
  - "3D modeling"
  - "vector"
  - "raster"
  - "rendering"
  - "Inkscape"
  - "Gimp"
  - "Ondsel"
  - "FreeCAD"
  - "Blender"
  - "SVG"
  - "parametric"
  - "render"
categories: 
  - "CAD"
  - "Parametric Modeling"
  - "Final Project"
  - "Rendering"
series: 
  - "Weekly Assignments"
image: "led-zeppelin-render.webp"
---

## Assignments

- Pick a simple object and design it using vector drawing software such as InkScape, Illustrator or Boxy SVG. The object could be something as simple as a nail, a hinge or a bolt or anything related to your final project. It could be a logo of a product that you are about to prototype.
- Use a raster graphics software of your choice, such as Gimp, Photoshop or Photopea, to edit, crop, resize and optimize an image of your choice.
- Explore a few 3D modelling tools (e.g. Blender, FreeCAD (Onsdel ES), SolveSpace, Fusion 360, Solidworks, Rhino) and pick one to make something for your final project.
- Create a page containing the assignment documentation on your website.
- Document your process with screenshots and descriptions.

## 2D Modeling

### Vector - Inkscape

[I have been making music](https://mirokeimioniemi.com/portfolio/music.html) for a whole decade now. It started from playing around with [Magix Music Maker](https://www.magix.com/us/music-editing/music-maker/) disguised as "Asus Music Maker" on my cousin's family's computer. I fell in love immediately, even though initally we were just dragging around loops. I eventually leapt to the much more powerful and advanced [FL Studio](https://www.image-line.com/), with which I produced everything from progressive house and dubstep to orchestral and soundtrack music, which has been used in multiple projects, the most notable being a [Sorin Sirkus](https://www.sorinsirkus.fi/) show. I have published and since retracted many songs under a couple of different names but my latest project that is still very much in the works will be called "marou", derived from how different English speakers might prononunce my name "Miro". The most frequent variants are approximately "Mairou" and "Mirou", from which I derived "marou" either by dropping the "i" or changing it to an "a" depending on the perspective. Anyway, the purpose of this prologue was to give context to what I would draw, which is a logo for this new project.

I am quite familiar with vector graphics, having drawn them in [Adobe Illustrator](https://www.adobe.com/products/illustrator.html), [Figma](https://www.figma.com/) and various other software, as well as directly written SVGs in code. I had not, however, used [Inkscape](https://inkscape.org/) yet. My first impressions are that it seems to be a very capable alternative for Illustrator. In fact, it has been a while since I last used but I cannot quickly think of any reasong to go back, especially considering the rather drastic price difference between 0 and whatever Illustrator currently happens to cost. Opening Inkscape feels very familiar and it is easy to start drawing immediately with whatever tools one is most comfortable. Disregarding a bit of panel hunting, everything works exactly as expected. I particularly like the right panel, where you can have tabs for whatever you most need or drag them out of there onto their own, separate windows, which really helps working with multiple screens.

![Inkscape](inkscape.webp)

To start sketching the logo, I first navigated to "Document Properties > Grids" and then created a new rectangular grid. I toggled on "Snapping" from the upper right corner and started sketching with the "Pen Tool" in BSpline mode, which is my favorite as the path always goes through whichever points I want it to go through and rounds corners just as I would expect. However, I did have to have to adjust the "Fill and Stroke" properties to remove automatic filling and modify the stroke style and color. The causes and effects of the properties remained a bit unclear to me as, for example, the strokes were of variable widths at one point and I managed to even crash the program, which happened a couple of times.

![Inkscape crash report](inkscape-crash.webp)

Eventually, however, the settings got applied just as I wanted to and I could start sketching. I played around with some shapes derived from the letter "m", creating the above McDonald's looking thing among them. I decided to go with just the full name but in a custom font. I wanted to create something very simple that almost borderlines on nondescript but is elegant nevertheless. I was inspired by the [Dune Rise](https://fontswan.com/dune-font/) font, which in turn was inspired by the fantastic 2021 [Dune movie](https://www.imdb.com/title/tt1160419/). My font - with currently only five letters in it - could then be characterized as an exploration into what the Dune Rise font would look like in lowercase and bold. After some time, I had created the illustration below, where the lines drawn by me are highlighted in faint purple and the points clicked are represented by the squares in all orientations. The equally tall "m", "r", "u" and "a"'s spine are created using the "Pen Tool" and the "o" as well as the "a"'s body were created using the rectangle tool with smoothened corners. Inkscape's "Node Tool", which provides the below blueprint is delightfully easy and straightforward to use too.

![marou font blueprint](marou-font-original.webp)

I created a few variants by copy-pasting the original sketch onto a new layer, where I rounded its corners from the "Fill and Stroke > Stroke style" panel by changing the "Cap" from "Butt cap" to "Round cap". I also copied both of these and squished them down along the y-axis to see if that would look better. I batch exported the four different layers by selecting them from the panel behind "Export > Batch Export" and exporting them as plain `.svg` files. The resulting svg code for the above version is as depicted below. I chose the stroke color to be var(--pre-text-color) as it contrasts with the background as  white or black in full opacity depending on which mode the visitor has enabled such that it is clearly visible in both modes.

```svg
<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<!-- Created with Inkscape (http://www.inkscape.org/) -->

<svg
   width="100%"
   height="100%"
   viewBox="0 0 701.70694 151.58676"
   version="1.1"
   id="svg1"
   xmlns="http://www.w3.org/2000/svg"
   xmlns:svg="http://www.w3.org/2000/svg">
  <defs
     id="defs1" />
  <g
     id="layer4"
     style="display:inline"
     transform="translate(-198.42441,-113.0722)">
    <path
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:square;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 37.795276,670.88517 c 0.0019,-22.27682 0.0038,-44.55298 0.0038,-66.71815 1.7e-5,-22.16516 -0.0019,-44.8194 12.707959,-56.14675 12.709859,-11.32734 37.681429,-11.32734 50.280108,-1.95078 12.59867,9.37657 12.59867,28.12858 12.59867,50.10382 0,21.97525 0,47.1711 0,49.13335 0,1.96224 0,-19.30979 0,-41.28482 0,-21.97503 0,-44.6513 12.59868,-55.9901 12.59867,-11.33881 37.79452,-11.33881 50.39319,-10e-6 12.59868,11.33881 12.59868,34.01553 12.59868,56.36553 0,22.35001 0,44.37197 0,66.39437"
       id="path30-2"
       transform="translate(170.07874,-415.74804)" />
    <path
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:square;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 283.46462,254.83894 c -2e-5,-9.35576 -3e-5,-18.71151 -5e-5,-28.06728"
       id="path31-6" />
    <path
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8471;stroke-linecap:square;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 339.29821,539.4203 c 0,0.93013 0,1.86025 0,23.77678 0,21.91653 0,64.81946 0,107.7224"
       id="path33-5"
       transform="matrix(0.99981188,0,0,1.0055598,168.06597,-419.66768)" />
    <path
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8471;stroke-linecap:square;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 339.29821,539.4203 c 0,43.83306 0,87.66611 0,131.49918"
       id="path33-4-4"
       transform="matrix(0.99981188,0,0,1.0055598,218.11114,-419.46664)" />
    <rect
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       id="rect34-0"
       width="100.51688"
       height="131.729"
       x="405.34225"
       y="122.87004"
       ry="45.62513"
       rx="50.258442" />
    <rect
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       id="rect34-2-9"
       width="100.51688"
       height="131.729"
       x="642.76373"
       y="123.25511"
       ry="45.62513"
       rx="50.258442" />
    <path
       style="display:inline;fill:none;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:square;stroke-dasharray:none;stroke-opacity:1"
       d="m 444.49513,538.78197 c -18.95715,0 -37.91429,0 -47.45235,11.00588 -9.53805,11.00588 -9.65702,33.01675 -9.77599,55.02806"
       id="path1-0"
       transform="translate(170.07874,-415.74804)" />
    <path
       style="display:inline;fill:none;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:square;stroke-dasharray:none;stroke-opacity:1"
       d="m 617.34929,544.78718 c 0,19.97908 0,39.95777 0,62.54619 0,22.58842 0,47.78427 16.79383,60.38295 16.79383,12.59868 50.38014,12.59868 67.17363,0 16.7935,-12.59868 16.7935,-37.79504 16.7935,-60.37593 0,-22.5809 -10e-6,-42.54505 -10e-6,-62.5096"
       id="path2-3"
       transform="translate(172.57198,-422.26618)" />
  </g>
</svg>
```

This code can then be embedded onto the site by merely pasting it to the markdown file at the cost of its consciseness. They could be embedded as images too, but then their color would not change dynamically with the mode. Below are the four different variants I made.

<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<!-- Created with Inkscape (http://www.inkscape.org/) -->

<svg
   width="100%"
   height="100%"
   viewBox="0 0 701.70694 151.58676"
   version="1.1"
   id="svg1"
   xmlns="http://www.w3.org/2000/svg"
   xmlns:svg="http://www.w3.org/2000/svg">
  <defs
     id="defs1" />
  <g
     id="layer4"
     style="display:inline"
     transform="translate(-198.42441,-113.0722)">
    <path
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:square;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 37.795276,670.88517 c 0.0019,-22.27682 0.0038,-44.55298 0.0038,-66.71815 1.7e-5,-22.16516 -0.0019,-44.8194 12.707959,-56.14675 12.709859,-11.32734 37.681429,-11.32734 50.280108,-1.95078 12.59867,9.37657 12.59867,28.12858 12.59867,50.10382 0,21.97525 0,47.1711 0,49.13335 0,1.96224 0,-19.30979 0,-41.28482 0,-21.97503 0,-44.6513 12.59868,-55.9901 12.59867,-11.33881 37.79452,-11.33881 50.39319,-10e-6 12.59868,11.33881 12.59868,34.01553 12.59868,56.36553 0,22.35001 0,44.37197 0,66.39437"
       id="path30-2"
       transform="translate(170.07874,-415.74804)" />
    <path
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:square;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 283.46462,254.83894 c -2e-5,-9.35576 -3e-5,-18.71151 -5e-5,-28.06728"
       id="path31-6" />
    <path
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8471;stroke-linecap:square;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 339.29821,539.4203 c 0,0.93013 0,1.86025 0,23.77678 0,21.91653 0,64.81946 0,107.7224"
       id="path33-5"
       transform="matrix(0.99981188,0,0,1.0055598,168.06597,-419.66768)" />
    <path
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8471;stroke-linecap:square;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 339.29821,539.4203 c 0,43.83306 0,87.66611 0,131.49918"
       id="path33-4-4"
       transform="matrix(0.99981188,0,0,1.0055598,218.11114,-419.46664)" />
    <rect
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       id="rect34-0"
       width="100.51688"
       height="131.729"
       x="405.34225"
       y="122.87004"
       ry="45.62513"
       rx="50.258442" />
    <rect
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       id="rect34-2-9"
       width="100.51688"
       height="131.729"
       x="642.76373"
       y="123.25511"
       ry="45.62513"
       rx="50.258442" />
    <path
       style="display:inline;fill:none;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:square;stroke-dasharray:none;stroke-opacity:1"
       d="m 444.49513,538.78197 c -18.95715,0 -37.91429,0 -47.45235,11.00588 -9.53805,11.00588 -9.65702,33.01675 -9.77599,55.02806"
       id="path1-0"
       transform="translate(170.07874,-415.74804)" />
    <path
       style="display:inline;fill:none;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:square;stroke-dasharray:none;stroke-opacity:1"
       d="m 617.34929,544.78718 c 0,19.97908 0,39.95777 0,62.54619 0,22.58842 0,47.78427 16.79383,60.38295 16.79383,12.59868 50.38014,12.59868 67.17363,0 16.7935,-12.59868 16.7935,-37.79504 16.7935,-60.37593 0,-22.5809 -10e-6,-42.54505 -10e-6,-62.5096"
       id="path2-3"
       transform="translate(172.57198,-422.26618)" />
  </g>
</svg>

<br />

<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<!-- Created with Inkscape (http://www.inkscape.org/) -->

<svg
   width="100%"
   height="100%"
   viewBox="0 0 701.70613 152.11424"
   version="1.1"
   id="svg1"
   xmlns="http://www.w3.org/2000/svg"
   xmlns:svg="http://www.w3.org/2000/svg">
  <defs
     id="defs1" />
  <g
     id="layer5"
     style="display:inline"
     transform="translate(-198.42522,-303.10811)">
    <path
       style="display:inline;opacity:1;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:round;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 37.795276,670.88517 c 0.0019,-22.27682 0.0038,-44.55298 0.0038,-66.97794 1.7e-5,-22.42495 -0.0019,-45.6129 12.707959,-57.20711 12.709859,-11.5942 37.681429,-11.5942 50.280108,-1.95313 12.59867,9.64107 12.59867,28.92207 12.59867,51.16182 0,22.23975 0,47.4356 0,49.39785 0,1.96224 0,-19.30979 0,-41.54933 0,-22.23953 0,-45.44478 12.59868,-57.04809 12.59867,-11.60332 37.79452,-11.60332 50.39319,0 12.59868,11.60331 12.59868,34.80902 12.59868,57.42352 0,22.61451 0,44.63647 0,66.65887"
       id="path30"
       transform="translate(170.07874,-225.18465)" />
    <path
       style="display:inline;opacity:1;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:round;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 283.46462,445.40234 c -2e-5,-9.35576 -3e-5,-18.71151 -5e-5,-28.06728"
       id="path31" />
    <path
       style="display:inline;opacity:1;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8471;stroke-linecap:round;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 339.29821,539.4203 c 0,43.83306 0,87.66611 0,131.49918"
       id="path33"
       transform="matrix(0.99981188,0,0,1.0055598,168.06596,-229.1043)" />
    <path
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8471;stroke-linecap:round;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 339.29821,539.4203 c 0,43.83306 0,87.66611 0,131.49918"
       id="path33-4"
       transform="matrix(0.99981188,0,0,1.0055598,218.11114,-228.90325)" />
    <rect
       style="display:inline;opacity:1;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       id="rect34"
       width="100.51688"
       height="131.729"
       x="405.34225"
       y="313.43344"
       ry="45.62513"
       rx="50.258442" />
    <rect
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       id="rect34-2"
       width="100.51688"
       height="131.729"
       x="642.76379"
       y="313.81851"
       ry="45.62513"
       rx="50.258442" />
    <path
       style="display:inline;fill:none;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:round;stroke-dasharray:none;stroke-opacity:1"
       d="m 444.49513,538.78197 c -18.95715,0 -37.91429,0 -47.45235,14.13222 -9.53805,14.13222 -9.65702,42.39552 -9.77599,70.65939"
       id="path1"
       transform="translate(170.07874,-225.18465)" />
    <path
       style="display:inline;fill:none;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:round;stroke-dasharray:none;stroke-opacity:1"
       d="m 617.34929,544.78718 c 0,19.97908 0,39.95777 0,62.54619 0,22.58842 0,47.78427 16.79383,60.38295 16.79383,12.59868 50.38014,12.59868 67.17363,0 16.7935,-12.59868 16.7935,-37.79504 16.7935,-60.37593 0,-22.5809 -10e-6,-42.54505 -10e-6,-62.5096"
       id="path2"
       transform="translate(172.57197,-231.57311)" />
  </g>
</svg>

<br />

<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<!-- Created with Inkscape (http://www.inkscape.org/) -->

<svg
   width="100%"
   height="100%"
   viewBox="0 0 702.71405 117.32545"
   version="1.1"
   id="svg1"
   xmlns="http://www.w3.org/2000/svg"
   xmlns:svg="http://www.w3.org/2000/svg">
  <defs
     id="defs1" />
  <g
     id="layer6"
     style="display:inline"
     transform="translate(-200.97416,-489.51572)">
    <path
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:square;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 37.795276,670.88517 c 0.0019,-22.27682 0.0038,-44.55298 0.0038,-66.97306 1.7e-5,-22.42007 -0.0019,-45.598 12.707959,-57.1872 12.709859,-11.58919 37.681429,-11.58919 50.280108,-1.95308 12.59867,9.6361 12.59867,28.90716 12.59867,51.14194 0,22.23479 0,47.43064 0,49.39288 0,1.96225 0,-19.30978 0,-41.54435 0,-22.23457 0,-45.42988 12.59868,-57.02823 12.59867,-11.59835 37.79452,-11.59835 50.39319,0 12.59868,11.59835 12.59868,34.79412 12.59868,57.40366 0,22.60954 0,44.6315 0,66.6539"
       id="path30-2-6"
       transform="matrix(1.0014352,0,0,0.76302498,172.58781,86.796212)" />
    <path
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:square;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 286.13603,596.61886 c -2e-5,-7.13868 3.6e-4,-12.42538 3.4e-4,-19.56406"
       id="path31-6-9" />
    <path
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8471;stroke-linecap:square;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 339.29821,539.4203 c 0,0.93013 0,1.86025 0,23.77678 0,21.91653 0,64.81946 0,107.7224"
       id="path33-5-3"
       transform="matrix(1.0012468,0,0,0.76726725,170.57216,83.805435)" />
    <path
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8471;stroke-linecap:square;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 339.29821,539.4203 c 0,43.83306 0,87.66611 0,131.49918"
       id="path33-4-4-0"
       transform="matrix(1.0012468,0,0,0.76726725,220.68914,83.958825)" />
    <rect
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:16.5191;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       id="rect34-0-0"
       width="100.66113"
       height="100.51252"
       x="408.189"
       y="497.77527"
       ry="34.813114"
       rx="50.33057" />
    <rect
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:16.5191;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       id="rect34-2-9-7"
       width="100.66113"
       height="100.51252"
       x="645.95117"
       y="498.06909"
       ry="34.813114"
       rx="50.33057" />
    <path
       style="display:inline;fill:none;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:square;stroke-dasharray:none;stroke-opacity:1"
       d="m 444.49513,538.78197 c -18.95715,0 -37.91429,0 -47.45235,11.00588 -9.53805,11.00588 -9.65702,33.01675 -9.77599,55.02806"
       id="path1-0-2"
       transform="matrix(1.0014352,0,0,0.76302498,172.58781,86.796212)" />
    <path
       style="display:inline;fill:none;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:square;stroke-dasharray:none;stroke-opacity:1"
       d="m 617.34929,544.78718 c 0,19.97908 0,39.95777 0,62.54619 0,22.58842 0,47.78427 16.79383,60.38295 16.79383,12.59868 50.38014,12.59868 67.17363,0 16.7935,-12.59868 16.7935,-37.79504 16.7935,-60.37593 0,-22.5809 -10e-6,-42.54505 -10e-6,-62.5096"
       id="path2-3-1"
       transform="matrix(1.0014352,0,0,0.76302498,175.08463,81.822705)" />
  </g>
</svg>

<br />

<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<!-- Created with Inkscape (http://www.inkscape.org/) -->

<svg
   width="100%"
   height="100%"
   viewBox="0 0 702.71324 118.66858"
   version="1.1"
   id="svg1"
   xmlns="http://www.w3.org/2000/svg"
   xmlns:svg="http://www.w3.org/2000/svg">
  <defs
     id="defs1" />
  <g
     id="layer1"
     style="display:inline"
     transform="translate(-197.89593,-641.17655)">
    <path
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:round;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 37.795276,670.88517 c 0.0019,-22.27682 0.0038,-44.55298 0.05265,-67.36413 0.04885,-22.81115 0.147261,-46.79251 12.907285,-58.78342 12.760023,-11.99092 37.731593,-11.99092 50.280547,-1.95664 12.54895,10.03428 12.44951,30.10166 12.39979,52.73462 -0.0497,22.63296 -0.0497,47.82881 -0.0497,49.79106 0,1.96224 0,-19.30979 0.0497,-41.94253 0.0497,-22.63275 0.14916,-46.62438 12.79755,-58.62091 12.6484,-11.99652 37.84425,-11.99652 50.3932,0 12.54896,11.99653 12.44952,35.98863 12.3998,58.99634 -0.0497,23.00771 -0.0497,45.02967 -0.0497,67.05207"
       id="path30-2-6-5"
       transform="matrix(1.0014352,0,0,0.763025,169.50877,239.80019)" />
    <path
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:round;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 283.05699,749.62285 c -2e-5,-7.13868 3.6e-4,-12.42538 3.4e-4,-19.56406"
       id="path31-6-9-0" />
    <path
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8471;stroke-linecap:round;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 339.29821,539.4203 c 0,0.93013 0,1.86025 0,23.77678 0,21.91653 0,64.81946 0,107.7224"
       id="path33-5-3-5"
       transform="matrix(1.0012468,0,0,0.76726727,167.49312,236.80941)" />
    <path
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:18.8471;stroke-linecap:round;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       d="m 339.29821,539.4203 c 0,43.83306 0,87.66611 0,131.49918"
       id="path33-4-4-0-6"
       transform="matrix(1.0012468,0,0,0.76726727,217.61011,236.9628)" />
    <rect
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:16.5191;stroke-linecap:round;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       id="rect34-0-0-7"
       width="100.66113"
       height="100.51252"
       x="405.10995"
       y="650.77924"
       ry="34.813114"
       rx="50.33057" />
    <rect
       style="display:inline;fill:none;fill-opacity:1;fill-rule:evenodd;stroke:var(--pre-text-color);stroke-width:16.5191;stroke-linecap:round;stroke-dasharray:none;stroke-opacity:1;paint-order:markers fill stroke"
       id="rect34-2-9-7-3"
       width="100.66113"
       height="100.51252"
       x="642.87213"
       y="651.07306"
       ry="34.813114"
       rx="50.33057" />
    <path
       style="display:inline;fill:none;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:round;stroke-dasharray:none;stroke-opacity:1"
       d="m 444.49513,538.78197 c -18.95715,0 -37.91429,0 -47.45235,11.00588 -9.53805,11.00588 -9.65702,33.01675 -9.77599,55.02806"
       id="path1-0-2-8"
       transform="matrix(1.0014352,0,0,0.763025,169.50877,239.80019)" />
    <path
       style="display:inline;fill:none;stroke:var(--pre-text-color);stroke-width:18.8976;stroke-linecap:round;stroke-dasharray:none;stroke-opacity:1"
       d="m 617.34929,544.78718 c 0,19.97908 0,39.95777 0,62.54619 0,22.58842 0,47.78427 16.79383,60.38295 16.79383,12.59868 50.38014,12.59868 67.17363,0 16.7935,-12.59868 16.7935,-37.79504 16.7935,-60.37593 0,-22.5809 -10e-6,-42.54505 -10e-6,-62.5096"
       id="path2-3-1-5"
       transform="matrix(1.0014352,0,0,0.763025,172.00559,234.82668)" />
  </g>
</svg>

### Raster - Gimp

I have done most of my image processing with [Photoshop](https://www.adobe.com/products/photoshop.html) back in the day when I still had a license. At one point I could no longer justify the costs of a Creative Cloud subscription as I did not have much time to play around with it anymore and basic editing could be done on the phone or on the web with apps such as [Figma](https://www.figma.com/), [Canva](https://www.canva.com/), [Pixlr](https://pixlr.com/), [Adobe Express](https://www.adobe.com/express/feature/image/editor) and many others. Still, I found [Gimp](https://www.gimp.org/) installed on my laptop too so I will have to assume that I might have either edited a photo or intended to do so in the past but I have no recollection of this, as could be seen from my non-existent command of the software.

My first (second?) impressions are that on the surface it looks and seems like Photoshop, but immediately it can be seen - and especially felt - that the usabilty is quite different. I try to change the selected tool or hit `Ctrl + T` to enter transform mode and nothing happens. Scaling down a layer actually scales it down such that if it is scaled back up, it looks blurry. Coming from Photoshop, nothing works quite like you would expect it to and everything feels just a little bit clunkier and less streamlined. However, I must admit that I did not spend very long on this as I wanted to get to 3D as fast as possible and it might just be a configuration issue or not being used to it.

![Gimp project](gimp-project.webp)

Last year, around this time, I started my journey developing a [probabilistic strategy game](https://github.com/MiroKeimioniemi/probabilistic-strategy-game) from scratch, for which I had long had the idea. I finished it as a semi-polished local 2-player conquest game, where each player assigns primary moves to all their units during their turn, which get executed based on the probability of success. If the primary move, such as "move a wide and heavy tank to a thick forest square" fails, a secondary move is attempted, which can be anything from retrying to engaging in a battle with the enemy at optimal or subotimal range, depending on the distance in between. Each unit type and territory have different attributes resulting in strengths and weaknesses for different kinds of positions, which can also change by, for example, a tank blasting a mountain range into flat gravel. 

The prototype of the ambitious game was finished slightly after Wappu (1.5.) after six days with a total of 8 hours of sleep but I am quite proud for the solo effort, building it from scratch using [Scala](https://www.scala-lang.org/) and [ScalaFX](https://www.scalafx.org/). However, it is not very approachable for the average person who might not have the correct [JVM](https://en.wikipedia.org/wiki/Java_virtual_machine) environment installed and configured and so I am planning to package it into some kind of an executable and for that purpose, I wanted an icon for the application. Something simple but distinct. 

I figured this would be the perfect opportunity and so, after studying the [how to make Windows icons](https://learn.microsoft.com/en-us/windows/win32/uxguide/vis-icons), I fired up Gimp and created a new 256x256 (maximum size for `.ico`) project with x- and y resolution of 72. I dragged and dropped in some of the crude custom assets I had made for the game using [Pixilart](https://www.pixilart.com/) and played around with potential arrangements a little until I ended up with placing the contrasting enemy tanks on contrasting terrain tiles in a logo that appears decent looking and recognizable in a very small form factor too. Gimp showing the current image in the taskbar is actually a super cool feature as it worked as a preview for exactly what I wanted to do here, even though it did have a small overlay. 

I scaled down the assets to 150px and 128px with `Shift + S` and rotated the blue one 180 degrees with `Shift + R`. I merged the layers by right clicking the top one and pressing "Merge Down" until they were all merged, which was faster that figuring out how to select multiple layers, as for some reason holding control or shift and clicking did not work. I then duplicated the layer and scaled it into different sizes: 256, 128, 96, 64, 48, 32, 24 and 16, which was what the 2021 updated [Windows guide](https://learn.microsoft.com/en-us/windows/win32/uxguide/vis-icons) recommended on the topic. I then exported them as `.ico`, which automatically recognized each layer as corresponding to a variant in the icon file. I selected compress for all of them to make it 33% smaller still and then I was done.

![New Gimp project](gimp-new-project.webp)
![Gimp export ico](gimp-export.webp)
![Probabilistic strategy game icon](probabilistic-strategy-game-icon.webp)

## 3D Modeling

I got my first experience with 3D modeling just last autumn on the [Design Thinking and Electronic Prototyping](https://courses.aalto.fi/s/course/a053X000012QyDfQAK/design-thinking-and-electronic-prototyping?language=en_US) course, where we got a similar task to design and 3D-print something. I decided to create a magnetic tray for our whiteboard as we had meant to get one for a while but had not found a suitable one. For this, I used Fusion 360 as Aalto students have a license for it and it seemed good to know in the industry. I largely liked it, although it fell severly short in one aspect: it did not have a dark theme. For a [Dark Reader](https://darkreader.org/) user like me, this rendered the application practically unusable. I must admit that my inexperience with general 3D modeling workflows might have contributed to that initially but it is a major shortcoming anyway. 

Below are my 3D model of the tray as well as the physical, printed version, which unfortunately did not reach its full potential as the filament ran out during the printing and thus the pocket never actually connected. Nevertheless, it was just tall enough to fit the magnets perfectly and although having them on the storage side does not look quite as elegant, it still works, even though the tray wall is twice the thickness of the outer pocket wall. 

![3D model of a whiteboard tray with a magnet pocket created using Fusion 360](magnetic-tray-model.webp)
![3D-printed magnetic tray](3d-printed-magnetic-tray.webp)

I did enjoy using Fusion 360, although there would still be a lot to learn for me. However, we were supposed to try something new and as I would lose my licenses after graduating, I decided to learn to use free, open-source software instead.

### Ondsel

We were instructed to experiment with something new, so I chose [Ondsel ES](https://ondsel.com/) out of the free options listed as examples for us as it seemed to be the most advanced CAD program out of them due to being built on top of [FreeCAD](https://www.freecad.org/) but with additional features and UI/UX improvements, which I always really appreciate. It even came with a default dark theme! FreeCAD on the other hand looked more sophisticated, widely used and better documented than [SolveSpace](https://solvespace.com/index.pl) so this was a natural progression. By learning the basics of free, open-source software I could continue using them after university too when I have lost my student licenses.

#### Installation

The Ondsel installation really tripped me up. [Their site](https://ondsel.com/) had a big, orange download button, the clicking of which led to a page with the only download option for Windows being `x86_64.7z`, which already threw me off a little. I expected the zip file to contain the usual installer but was surprised to fnd no such thing after extracting the files using Windows 11's built-in "Extract all" function. There were no installation instructions on the website nor a README.md nor any text files with any instructions or guides on its usage either and so I was baffled as to how exactly would I run the program. 

![Ondsel downloads](ondsel-download-page.webp)

I wasted over an hour trying to find such instructions. In fact, I was still a bit confused as to what exactly I had downloaded. Digging through the folder, I found a `FirstRun.py` python script which imported FreeCAD and I had read somewhere that Ondsel had or was an add-on, which got me thinking that I would have to download FreeCAD and then add it there somehow, even though that made no sense as this was suppposed to be a FreeCAD fork.

![Contents of the downloaded zip file](ondsel-download-content.webp)

Visiting [FreeCAD's downloads page](https://www.freecad.org/downloads.php) was enlightening nevertheless, as there the `.7z` format was described as a "64-bit **_portable_**" for Windows, which gave me the crucial keyword to find the answers to my search. [Portable applications](https://en.wikipedia.org/wiki/Portable_application) are self-contained, standalone applications that do not always have to be installed in the same way as most applications are. I had to venture all the way out to [Reddit](https://www.reddit.com/r/software/comments/ce0aqu/portable_vs_installation/) to learn this. All of their files are stored and modified in a single directory and so they can be installed on, for example, usb sticks, which one to use the exact same piece of software on multiple devices, with all kinds of additional benefits but also some drawbacks as discussed [here](https://www.reddit.com/r/software/comments/ce0aqu/portable_vs_installation/). The takeaway was, however, that an `.exe` file should exists somewhere and so I kept on digging until I finally found it in the `Ondsel_ES_2024.1.0.35694-Windows-x86_64\bin` directory. For further confusion, there were multiple `.exe` files and none of them were named "Ondsel", but I deduced that it must be the `freecad.exe` as it was the one with the right logo along with `freecadcmd.exe`, which would be the command line version.

![FreeCAD downloads](freecad-downloads.webp)
![Correct executable located](ondsel-executable.webp)

I created a shortcut to it by selecting it and then right-clicking on it, choosing "Show more options" (windows 11) and then choosing "create shortcut". I dragged the shortcut onto my desktop, double-clicked it to open the application and then opened the AssemblyExample.FCStd from the start page to capture the below screenshot (with navigation cube made movable and dragged to the upper right corner).

![Ondsel Assembly Example](ondsel-assembly-example.webp)

#### Usage

I started a new project by clicking "Empty File" from the start page and changed to the "Part Design" mode via View > Workbench > Part Design. Following the example of [this video](https://www.youtube.com/watch?v=V1P4bhulIaU), I created a spreadsheet with the following values for length, largest diameter, thickness and stand height based on my night stand and window stool dimensions, and saved the project as `lamp.FCStd` to this repository us.

| Dimensions       | Values|
|------------------|-------|
| Length           | 400 mm|
| Largest Diameter | 140 mm|
| Thickness        | 2 mm  |
| Stand Height     | 30 mm |

My currently strongest idea for the final project is to create a gesture controlled bright alarm lamp, more about which can be read [here]({{< relref "page/final-project/index.md" >}}). Its design is very simple, as it takes the form of an ellipsoid, which can then be placed on different more or less elaborate stands.

I was already familiar with the revolution method from previous projects, in which a cross-section is first sketched and then rotated around the chosen axis to create the solid 3D object. I figured that this would be the easiest way to create the ellipsoid and to carefully control its outline.

I started out by clicking "Create sketch" and choosing the XZ-plane, where I sketched a B-spline with 3 knots (a bit similar in look and feel to Bézier curves for those familiar with, for example, [After Effects](https://www.adobe.com/products/aftereffects.html) but still different according to [Wikipedia](https://en.wikipedia.org/wiki/B-spline)), with the ends being level and the middle one being horizontally centered but vertically off. When I created the solid of revolution by selecting the current sketch and then "Revolution" with "Axis: Horizontal sketch axis" and "Angle: 360°", the result turned out almost comically pointy at the ends. 

I then started over with a 5-knot B-spline, which offered me more flexibility over the shape. I set the constraints using the values I defined in the spreadsheet by clicking the bluish icon in the "Length" field, which opens another dialogue, which allows mathematical expressions using variables as input. The values defined in the spreadsheet can be accessed by `{spreadsheet-name}.{value/cell-alias}`. After fully constraining the first B-spline, I drew another, which I constrained to be the distance specified by `Spreadsheet.thickness` inwards from the outer B-spline, whose lowest point was vertically constrained to the origin by `Spreadsheet.largest_diameter / 2` and whose ends were horizontally constrained with the origin by `Spreadsheet.length / 2`. 

![Set constraints with spreadsheet variables](constraints-from-spreadsheet-variables.webp)
![Lamp cover sketch](lamp-cover-sketch.webp)
![Lamp cover as a solid of revolution 3D object](lamp-cover-model.webp)

I made the cover more rounded by further adjusting the constraints and then hid it from view by selecting it from the tree view on the left and pressing `space`. I then clicked "Create body" and with it selected, "Create sketch", where I drew a center-constrained rectangle with side lengths `Spreadsheet.length / 2` and `Spreadsheet.largest_diameter * 0.8` and extruded it with the "Pad" tool, where I input `Spreadsheet.largest_diameter / 2 + Spreadsheet.stand_height` as the padding length and applied it in reverse. This made it reach up to the widest part of the lamp while simultaneoustly lifting it off the ground by `stand_height`, which was initially set to be 30mm.

![Padded rectangle](padded-rectangle.webp)

Now I had a cuboid that was partially inside and partially outside the lamp cover. In order to shape it to be compatible with the lamp, I tried to copy the the lamp body, which initially did not work because I had not yet exited the padding operation by pressing "OK". After I did and retried, it prompted the following dialogue:


![Copying an object](copy-object.webp)

Initially I had all automatically selected and I just pressed "OK", after which I pasted it with `Ctrl + V`. This, however, also copied the spreadsheet as `Spreasheet001` as can be seen in the picture below. This aroused suspicion in me and so I opened `Sketch002` under `Body002` to inspect its constrains, which validated my suspicion. The constraints were now linked to `Spreadsheet001`, which meant that the values in the orginal spreadsheet no longer affected them. This allows for entirely indpendent modification of the body but was undesirable to me as it meant that the stand created with a cut boolean operation would not automatically adjust to the dimensions. Thus, I deleted the object and copied the original again with the above settings. I unselected "Auto select depending objects" and "Spreadsheet", which gave me a new copy that was still dependent on the original spreadheet as it should be.

I then selected the cuboid and the copied lamp cover and attempted to cut the latter from the former using the "Boolean operation", but I got the following error: `Boolean: Result has multiple solids: that is not currently supported.` This occurred because should the boolean cut operation have been successfully executed, the body would have been split into two such that it would have contained two disjoint objects, which is not allowed as explained in [this useful video](https://youtu.be/StQlYt2HY_k?si=euU7TYR30mPhNzFz) covering some of the basic rules and logic of using FreeCAD.

I thus edited the sketch of the copied object to produce a solid ellipsoid instead of a hollow one by deleting the inner B-spline and replacing it with a straight line between the ends of the remaining B-spline. For some reason it complained about not being fully constrained, but then I realized I was accidentally drawing reference lines instead of construction geometry. The fix was as simple as pressing "Toggle construction geometry" but the lesson was forever important: always pay close attention to the state of the program, whether that is the settings of the tools currently in use or the entire workbench.

After modifying the copied lamp cover to be solid, it was easy to cut it from the stand by selecting both (latter first), selecting "Cut" from the resulting dialogue and pressing "OK", which created the simple stand below.

![Boolean cut stand](boolean-cut.webp)

I then applied the "Fillet" tool to all the edges, which turned out to be an order-sensitive operation, where I had to first apply it to the longer edges before the shorter ones to accomodate them all. I then toggled the visibility of the lamp cover back on by selecting it from the tree on the left and pressing `space` to end up with the simple parametric 3D model below, which can easily be resized in all the dimensions defined in the spreadsheet by simply changing their values.

![Lamp with simple stand](lamp-with-stand.webp)

To create a bit more interesting stand next, I hid the simple stand and started exploring ways to create rounded cylinders as quickly and easily as possible. I first started a new sketch and drew a slot, which seemed like exactly what I was looking for. However, the constraints were difficult to figure out and I could not make out how to rotate it after drawing it.

![Slot sketch](slot-sketch.webp)

 In fact, the search for the most convenient way to rotate objects turned out to be incredibly frustrating. The "Rotate" tool in "Draft" workbench would only rotate whatever was selected along the XY-plane or crash the entire program with the below error message incrementing the counter with every click on anything if I had, for example, "Revolution" selected inside a body instead of the body itself, which often occurred due to Ondsel autoselecting that instead of the body. 

![GUI Error upon rotating "Revolution"](gui-error.webp)

An even more surefire way to crash the program entire was to use the "Ruler" tool. I would get the reading once, yes, but if I tried to do anything afterwards, such as right- or left-click anywhere on the application window, it would dependably go white and eventually display the "not responding" dialogue. Luckily their recovery feature works impressively well though! 

![Ruler crashes the program](crash.webp)

It can thus be said that I am not particulary impressed by the "Draft" workbench. I did eventually find a somewhat satisfying way to rotate and move the bodies in the form of the "Transform" tool, found by selecting a body, right-clicking and choosing "Transform", which brings about the below arrows and curves that enable easy moving and rotating. 

![Select body > right-click > transform](transform.webp)


 In terms of creating a cylinder, what I was looking for was so simple that I thought that there must be a faster way to prototype something so simple. I discovered that you can add ready-made shapes in the "Part" workbench, where I then created a cylinder and experimented with the values, eventually arriving at the ones presented below. What was especially convenient was that the angles could be input into it upon creation.

![Cylinder](cylinder.webp)

The above cylinder was still not quite what I was looking for, however, as setting the angles only conserned its body, not the top and bottom faces. The bottom face was fine as I wanted it flat against the XY-plane anyway, but the top I wanted to round off. I tried some extreme fillet values and thought about extruding or insetting it somehow but could not come up with a way how. The only way I could come up with was the "Boolean cut" operation, which was a major hassle to set up. I created a sphere an lined it up with the cylinder with some careful camera work. I then duplicated it, decreased its radius and moved it more towards the cylinder by subtracting an equal amount from all of its coordinates. I then cut it from the bigger sphere using "Boolean cut", after which I carefully positioned the result to optimally cover the tip as shown below, and then cut that from the cylinder, using the same "Boolean cut" method.

![An unorthodox rounding method](unorthodox-rounding.webp)

I then mirrored the resulting cylinder first in the XZ-plane and then the result of that in the YZ-plane to produce the four
legs (or arms in this case?) of the slighlty less simple stand, which I bundled up into a part container by clicking "Create part" and dragging and dropping all parts of the stand to it. I boolean cut another copy of the lamp cover of the original cylinder, which propagated the cut to the three others upon refresh (`Ctrl + R`), and added a rectangle to connect them on the bottom and to act as a stable surface. It required a bit of fiddling with the numbers as well but inputting the same radius as on the cylinders made it nicely as round as them at the ends. Below are the resulting stand as well as the lamp, which my girlfriend coined "LED Zeppelin" and which I might now roll with, along with the treeview of all the tasks performed to arrive at it.

![A sligthly less simple stand](less-simple-stand.webp)
![LED Zeppelin 3D model](led-zeppelin-cad.webp)

Ondsel does not yet have extensive documentation, but as it is a FreeCAD fork, almost everything one can do in FreeCAD applies to Ondsel as well - although I do wonder where the "Draft" workbench issues originate from. Only the tasks window is on the right and the UI does not feel quite as boxed in. Here are some very useful FreeCAD resources for learning the very basics of both FreeCAD and Ondsel:

- [FreeCAD Tutorial for Beginners 2024](https://youtu.be/t8nPF-qWyfE?si=q6U-c51pNgZR4zcp)
- [FreeCAD Basic Rules](https://youtu.be/StQlYt2HY_k?si=euU7TYR30mPhNzFz)
- [Design for CNC with FreeCAD](https://www.youtube.com/watch?v=V1P4bhulIaU)

### Blender

I was really excited to finally have a great excuse for playing with Blender. I have long been fascinated by visual effects, animation and 3D rendering, as is evident from my YouTube history being full of [Corridor Crew](https://www.youtube.com/channel/UCSpFnDQr88xCZ80N-X7t0nQ)'s [VFX Artists React](https://www.youtube.com/watch?v=_4WrKeoeZhk&list=PLwVUbPpIRn1QspuvMVVfQvO7RPWnMJ1aA&pp=iAQB) and [RocketJump](https://www.youtube.com/@rocketjump) who created one of my favorite internet shows [Video Game High School](https://www.youtube.com/watch?v=1JqR3GVqib4&list=PLsMtUWKCmBPRFzqglpk4YQlNFy8wzSXBN&pp=iAQB), which I last rewatched a couple of years ago and still found highly entertaining! I searched for some quick overviews for absolute beginners and stumbled upon the goldmine of content that is the [Blender Fast Track](https://www.youtube.com/watch?v=98qKfdJRzr0&list=PL8eKBkZzqDiV2xca_7QVNdG8LGBfZBCkI&pp=iAQB) series, which was 4.5h of extensive, in depth scene building in [Blender 4.0 ](https://www.blender.org/download/releases/4-0/) that I accidentally drank up at 2x speed during a single sitting.

To render the lamp, I exported the model as a Wavefront OBJ - Arch module (*.obj) from Ondsel and imported it to Blender via "File > Import > Wavefront (.obj)". Now, the first thing that I immediately noticed was how much more responsive it is as compared to Ondsel/FreeCAD. Navigation is immediate and rotating and moving the view is very pleasant thanks to the automatic lock on origin, in addition to which, Blender's corresponding ruler "Measure" does not crash the application! I now had successfully imported `lamp.obj` but the scaling was off. This could, however, be adjusted in the right panel under Scene > Units by inputting 0.001 to "Unit Scale" to correspond to millimeters instead of meters. 

![lamp.obj imported to Blender](blender.webp)

I headed over to the shading tab and experimented with the default Principled BSDF settings, but noticed something quite peculiar when turning "Metallic" to 1.000 and "Roughness" to 0.000. Observation #1 was that the surfaces were not smooth and observation #2 was that, for some reason, the orginial - non-mirrored - leg of the stand got the same shading. 

![Initial shading](initial-shading.webp)

Problem #2 was easy to fix by clicking the dropdown with the sphere icon in the image and selecting the same material as the other parts of the stand. Somehow Blender had recognized that the lamp cover should be a different material from the stand but it had accidentally included one leg. Problem #1 was similarly easy to solve by selecting "Object > Shade Smooth".

![Shade smooth](shade-smooth.webp)

I smoothened both the lamp as well as the stand. Then I headed back to the shading tab, where I set the "Emission Strength" to 6.900 instead of 0.000 and added a little bit of coating, by increasing "Coat Weight" from 0.000 to 0.343 and "Roughness from 0.040 to 0.066. This, in combination with enabling "Bloom" from the "Scene" settings on the right tab and decreasing the "Radius" a bit, created the look of controlled glowing light. I then followed [this tutorial](https://www.youtube.com/watch?v=Egd_BNAT3l8) to create a quick procedural wood texture for the stand. The video was a couple of years old and thus the "Principled BSDF" node looked a bit different but the following routing produced similar effects. The values of the parameters on the video were entirely different and these required a lot of tweaking, but even though it still looks a bit plasticy in these light conditions, it might just pass for lacquered wood in certain light. I also enabled "Ambient Occlusion" and changed the "Factor" from 1.00 to 2.00 to make it look a little more dramatic.

![Lamp emitting light](light-emitting.webp)
![Shaded LED Zeppelin](shaded.webp)

Now that the shading was done, I tried to figure out how to render an image of the lamp. I tried to position the camera for a good shot but there was only grey. I tried to mess with all possible settings and positions but nothing changed. I then just deleted the camera and created a new one from "Add > Camera", which worked perfectly out of the box. Then the question was, why does the point light not do anything? The answer was that for some reason, likely due to changing the "Unit Scale" from metres to millimeters, the default settings of the lights were negligibly low. 

![Point light default settings](point-light.webp)

I added a point light with more reasonable settings and realized that the scene is quite empty. I added a planar mesh with the intention to add a backdrop too. I tested what rendering would produce for this most simple case and the result was pretty horrible as can be seen below:

![First render with one point light source](ugly-render.webp)

At that point it was already super late and I did not feel too enthusiastic about having create, construct and light the scene. I revisited the shading tab in between, which looked quite good with its global illumination and decided that it would do for now. I researched how to render that and found a solution in the form of "View > Viewport Render Image", which is supposed to render more or less what was currently on my screen. However, when I first rendered with it, in addition to the unnecessary overlay, the ambient occlusion that makes the lamp sit in the scene more nicely was missing. 

After a lot research and trial and error as this did not seem to be a common problem (or goal, which would explain the problem not arising for many), I found that toggling the overlays off somehow mysteriously brought back the ambient occlusion as well as got rid of the sphere as an added bonus. However, the image was more dimmer and more washed out so that the light did not clearly pop out of the background, which was baffling because it looked just perfect in the "Shading" view. As I did not have the time to build a proper scene nor conduct more troubleshooting and the quick renders fell short, I resorted to a good old screenshot with the overlays turned off and it clearly looks the best, which is kind of ironic for rendering software. This is most likely due to my settings, configurations etc. but I will dig into them more when I have time for a proper scene too!

![Viewport Render Image with Overlays on](viewport-render-with-overlays.webp)
![Viewport Render Image with Overlays off](viewport-render-without-overlays.webp)
![Screenshot through camera in Shading view](led-zeppelin-render.webp)

With more shaders and lights stacking up, I could feel my laptop with integrated AMD Radeon graphics starting to be pushed outside of its comfort zone by the sound of the fans and the increased latency in moving around. Rotating the scene around immediately pushes the integrated GPU to 100% usage from which it then returns to idle 4-7% when staying still. I gotta say that the software is pretty well optimized considering the lack of graphical power in my machine, but this is definitely tempting me to grab one of those [RTX 4080s](https://www.nvidia.com/fi-fi/geforce/graphics-cards/40-series/rtx-4080-family/) that I have been eyeing for a while now. Perhaps this would finally be the viable excuse to do so...

## Reflections

Quite a packed week. I definitely learned a lot about 3D-modeling and rendering in particular. Additionally, I learned about what knowledge one can reasonably expect to transfer over to different programs in the same niche. This can vary anywhere from absolutely nothing to delightfully much. Ondsel/FreeCAD and, to an extent, Gimp occasionally felt like playing on an inverted piano; the music theory remains the same but you have to change the roles of the hands and play in different directions, whereas with Inkscape I felt quite pleasantly at home from the get go. Blender was a bit overwhelming with its multiplicity of tabs, modifiers, nodes, panels and views but that is likely just a symptom of great depth and I feel quite confident that I largely understood the basics even though I will still have study the rendering pipeline and configurations so that there will not be any unwanted surprises.

In terms of specifics, I learned not to use default parts in Ondsel/FreeCAD. They are annoying to deal with and difficult to customize especially with respect to parameters. I also learned to go far around the "Draft" workbench where next to nothing seemed to work. I also learned what portable software is and how to run it on Windows. I got a lot more experience with various workflows in 3D and learned that if I want to do it on any more serious level, I might want to invest in a proper PC with a powerful graphics card, which is something I have been looking for a good excuse for for long now. Every other part I could justify as an investment as producing music is one of the most CPU and RAM intensive tasks out there but a graphics card I could not justify as an investment, even though it might really be for the games... Too bad [Cyberpunk 2077](https://www.cyberpunk.net/) is one of my favorite franchises out there... But now this might be a convenient excuse. And it is only a small leap from Blender to [Unreal Engine](https://www.unrealengine.com/en-US), where I could make my more complex game ideas come to life, now with assets and renders I can make myself.

In conclusion, the two most important takeaways for this week were, however, that I can easily crash any program and that free, open-source software is pretty damn advanced and cool in 2024! The barrier to entry in almost anything that can be done digitally seems to nowadays only be the learning curve for [FOSS](ttps://en.wikipedia.org/wiki/Free_and_open-source_software). In fact, [Fab Academy's](https://fabacademy.org/) most valuable resource might just be the [exhaustive list of software and hardware](https://fabacademy.org/2024/schedule.html) for each of the weekly topics that Neil Gershenfeld walks us through every Wednesday on the global lectures.







































































