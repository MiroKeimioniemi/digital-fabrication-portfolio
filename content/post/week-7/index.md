---
author: "Miro Keimiöniemi"
title: "Computer-Controlled Machining"
date: "2024-04-09"
description: "Week 9"
tags: 
  - "CAD"
  - "2D modeling"
  - "parametric"
  - "3D modeling"
  - "vector"
  - "Inkscape"
  - "SVG"
  - "Ondsel"
  - "FreeCAD"
  - "Fusion 360"
  - "CNC"
  - "Recontech1312"
  - "wood"
  - "plywood"
  - "woodworking"
categories: 
  - "CAD"
  - "Parametric Modeling"
  - "Machining"
series: 
  - "Weekly Assignments"
image: "installed-shelves.webp"
---

I feel that this week had the highest stakes thus far. Not only could the machine actually kill you, for which there is actual [precedent](https://www.nytimes.com/2011/04/14/nyregion/yale-student-dies-in-machine-shop-accident.html), we were also given a strictly limited 120cm x 120cm x 1.5cm sheet of plywood and our assignment was to create something large, meaning that it could not be easily hidden. This meant that the project had to be large and complex enough to pass the assignment criteria but also something that we genuinely needed and wanted to have in our apartment.

## Assignments

- Document the safety introduction details and general flow of using the machine.
- Make (design+mill+assemble) something big using a 15 mm thick and 120x120 cm big soft plywood sheet.
- Do a fitting test with a simple design first so that your parts are snug fit when assembling them and to avoid spoiling material. You will get one plywood sheet.
- Make sure you choose the right depth of cut (1/2 diameter of tool is safe) and calculate the feed rate (FR = SS * CL * NF) accordingly to avoid breaking the tool.
- Document your process in a new page on your website.

## Design

As the assignment was to make something big at approximately meter-scale as specified on the [Fab Academy page](https://academy.cba.mit.edu/classes/computer_machining/index.html), I had to immediately discard many ideas such as organizer boxes and a stand for our [portable projector](https://us.xgimi.com/products/halo-plus) to mount it on the bedhead. I had to think bigger, which naturally led to seats, tables and bookcases but our apartment was already filled with those. Something which we had talked about for a while now, however, was to get shelves for a corner of our kitchen - shown below - where we could put jars of dried goods in order to gain more storage space and add a bit of color.

![Kitchen corner before shelves](before-shelves.webp)

The jars were placed on the counter for reference. The idea would be to have two shelves on top of each other so that the lower one fits the larger jars (height: ~31cm, diameter: ~9.2-11cm) on the left and the upper one would fit the smaller jars (height: ~24-28cm, diameter: ~6.5-10.5cm) on the right. The wall area is approximately 69.4cm wide and 78cm tall. Given a thickness of 15mm for the plywood, the height would theoretically not be an issue with a naive approach of simply summing up all heights. However, a shelf obviously needs some sort of a support structure that can either be internal, such as in the case of thicker floating shelves, or external, which is necessary for such thin material as this. 

In fact, the carrying capacity was my priority concern as the full glass jars were rather heavy and the 15mm thickness did not feel like much. Given enough time I would definitely have conducted a stress test but I started designing over the weekend and there were various difficulties (to be discussed furhter below) due to which I only finished my design by Tuesday morning, just before my machining time slot. My design was thus informed to a great extent by tryinf to attain a level of foolproofness, which I had to balance with the limited space. 

![Measuring the objects to be shelved](measuring.webp)
![Plywood sheet thickness with index finger for reference](plywood-sheets.webp)

The most obvious way in which the conflict and tradeoff between robustness and height constraints manifested was trying to figure out the height of the supports. I wanted to use triangular ones due to their stability and [superior load bearing capability](https://letstalkscience.ca/educational-resources/backgrounders/why-a-triangle-a-strong-shape) and I wanted to make them as large as possible to reinforce this but was quickly confronted with the height limits. I cannot count how many times I walked back and forth between my desk and the kitchen corner to measure something but eventually I ended up deciding that the height of the supports should be prioritized and as the wall area could accomodate a maximum of six large jars next to each other, I measured the top diameters of the jars and ended up placing the supports very carefully exactly so that between the edges and three supports it would fit precisely 1-2-2-1 jars (where a number indicates the number of jars on a segment and "-" indivates a support). The support width would be the 15mm and this was more or less exactly how much space there would be between the tops of the side-by-side jars.

The limited space and (literally) heavy requirements did certainly provide its own design challenge but I wanted something to explore the capabilities and limits of the CNC machine as well. Below is a snapshot of the design process put on "paper", which may look like a bunch of incoherent scribbles - because it is - but it has all the information necessary for me to remember all alternative models, ensure adherence to material bounds and to sufficiently visualize some alternatives to make a decision on which one to pursue more seriously.  

![Shelf sketches](sketches.webp)

After consulting with my partner to get her opinion on what she would be willing to look at in the kitchen for the rest of our stay in the apartment, we mutually decided to go with the city backdrop design. As for the cities themselves, we chose Tampere and Munich as we are both originally from the former and she has lived a year in the latter as well. I could have made something abstract too but for something that is already custom in the first place it makes more sense to go all the way. Thinking of another alternative, it would be pretty cool to make silhouttes of one's favorite fictional cities too.

### Vectors

I then proceeded to browse skyline silhouttes of both Tampere and Munich with searches like "Tampere/Munich skyline silhouette vector" and found the following [this one](https://sndp.mediadelivery.fi/img/468/200572301.png) for Tampere and [this one](https://image.shutterstock.com/image-vector/munich-skyline-silhouette-black-city-260nw-1890802744.jpg) for Munich. I also used [this](https://media.licdn.com/dms/image/C4D16AQHuzMTjrQYcfw/profile-displaybackgroundimage-shrink_200_800/0/1592293143501?e=2147483647&v=beta&t=ZKE729V-MwQuIzHG-s6nCrEIPGbMoybx5kuUVhBlo34) as another reference for Tampere. 

As the Tampere image was not a vector and it did not contain everything I wanted, I created my own silhouette based on it. I imported it to Inkscape, traced the outline using "Path" > "Trace Bitmap" with rather extreme settings (Threshold: 0.881 and Optimize: 5.000) and deleted the unwanted nodes such as the clouds and the fish. I then added a grid overlay with 1mm spacing in the "Document Properties" > "Grids" to aid with precision editing of individual nodes. With it enabled, I proceeded to fix the trace by making everything symmetrical that should be so and adjusting the spacing between the buildings. I also merged the different components of [Näsinneula](https://fi.wikipedia.org/wiki/N%C3%A4sinneula) (the highest tower) by positioning them so that they overlap slightly and clicking "Path" > "Union". 

![Trace bitmap on reference image](trace-bitmap.webp)
![Traced vector](clean-vector.webp)
![Symmetric, merged Näsinneula with grid](fixing-vector.webp)

I then proceeded to remodel most of the buildings node by node with extra care put into the iconic, even emblematic Näsinneula, while removing many and drawing additional ones such as the [Nokia Arena](https://fi.wikipedia.org/wiki/Tampereen_Kannen_areena) and [Hotel Torni](https://fi.wikipedia.org/wiki/Hotelli_Torni_Tampere). I also overhauled the [haulitorni](https://fi.wikipedia.org/wiki/Pispalan_Haulitehdas) entirely to be machinable with a 6mm milling bit. I made sure that all the spaces to be milled were at minimum 6mm thick and I made all relevant outer corners so that they could be milled sharply. The rest I was curious to observe and willing to accept however they would turn out. For the haulitorni this meant small rounded triangles cut out using "Path" > "Difference" to symbolize the staircase lattice framework. To make absolutely sure I had the dimensions right, I drew it as a triangle with stroke width of 6mm and then traced it into a new filled vector.

![Path difference operation to create rounded triangle lattice](difference-vector.webp)
![Redrawn Tampere skyline over the inspiration image](vector-comparison.webp)

The final result with dimensions of 690mm x 250mm (reduced for the webpage) can be seen below.

<svg width="100%" height="100%" viewBox="0 0 690 250" xml:space="preserve" xmlns="http://www.w3.org/2000/svg"><g style="display:inline"><path style="fill:var(--pre-text-color)" d="M148 0v20l-11 1-2 6.73L125 29v6l5 10 11 2v6l-6 1v6h6l-2 127c-2.212.18-4.425 0-6.643 0L130 180h-20v-75h2V95h3l-10-10H95L85 95h3v10h2v71h-8v-6h2l-8.864-7h-8L58 170h2c.062 4.354.104 8.648 0 13H50l-5 17H25v-70h-7v-4.239H7V130H-.237v120H690v-60h-6v-10l-1.163-15-1.837-3-3-11c-.973-6.29-2-14.288-2-17.32v-5.941l-4-6-4.153 6-.01 6c0 6-.837 13.261-1.837 17.261-.457 1.827-2 7.61-3 11l-2 3-1.006 15-.157 10H648l5.99-29.527s8.734-20.28 1.01-20.473h-10l-37 2.502v-66l-35 30v38l-5.874.498V55.099l-2.258-1.874-2.258-1.874-10.354-.95-10.354-.948-1.01-1.62-1.01-1.62-8.101-.5-8.1-.5-1.84 1.168L520 47.55V205h-13v-20l-7-5.092V140c-1.026-5.21-2.93-10.081-4.855-15L490 77h-3c-1.48 13.259-4.601 34.631-5 48-2.101 4.863-3.537 9.915-4.96 15v39.43L453 150l-20.806 28.989-.916-28.989-7.254-29.084L417.032 150c-.383 7.702-1.048 47.357-2.032 55h-14l-5-145h-10l-5 120h-6v-50h-8.041L364 120h-63l-3 10h-8v20h-15v-45l-10-30-30 10 .242 60-.242 35h-25v-10.057L198 170v3h-6v-3l-12-.057V162h-18.702L159 60h6v-6l-6-1v-6l11-2 5-10v-6l-10-1.492L163 21l-11-1V0Zm-48 112.957c1.97 0 3.94.095 4.346.282a2.94 2.94 0 0 1 1.463 1.514c.336.805.299 7.849-.046 8.593-.673 1.454-2.592 2.117-4.091 1.414-.736-.344-7.202-6.85-7.482-7.526-.622-1.505.051-3.34 1.466-3.995.405-.188 2.375-.282 4.345-.282m-2.849 16.003c.401.013.802.104 1.177.28.736.344 7.202 6.85 7.482 7.526.622 1.505-.052 3.34-1.466 3.995-.81.375-7.879.375-8.69 0a2.94 2.94 0 0 1-1.463-1.514c-.336-.805-.298-7.849.046-8.593.505-1.09 1.71-1.736 2.914-1.694m2.85 17.997c1.97 0 3.94.095 4.345.282a2.94 2.94 0 0 1 1.463 1.514c.336.805.299 7.849-.046 8.593-.673 1.454-2.592 2.117-4.091 1.414-.736-.344-7.202-6.85-7.482-7.526-.622-1.505.051-3.34 1.466-3.995.405-.188 2.375-.282 4.345-.282m-2.85 16.003c.401.013.802.104 1.177.28.736.344 7.202 6.85 7.482 7.526.622 1.505-.052 3.34-1.466 3.995-.81.375-7.879.375-8.69 0a2.94 2.94 0 0 1-1.463-1.514c-.336-.805-.298-7.849.046-8.593.505-1.09 1.71-1.736 2.914-1.694" transform="translate(.237)"/></g></svg>

I did the same for Munich but with much smaller modifications, only making sure that it was well machinable, as the reference image I found from Google Images on a site called "Free Vector Art & Graphics" was, in my opinion, better already and I was not as familiar with Munich in general despite [my brief visit last summer](https://www.instagram.com/p/CvNqD60N_Bb/?utm_source=ig_web_copy_link&igsh=MzRlODBiNWFlZA==) when we had to purchase an additional suitcase to carry back all the books we bought.

![Reference image for Munich skyline](munich-image.webp)

Below is the resulting, refined 690mm x 230mm (reduced for the webpage) vector.

<svg width="100%" height="100%" viewBox="0 0 690 230" xml:space="preserve" xmlns="http://www.w3.org/2000/svg"><path style="display:inline;fill:var(--pre-text-color)" d="m629 3-1 22-1 20-2 10v5h-2c-.957.028-2 1.043-2 2 .028 1.042 1.043 1.972 2 2h2v6l-6 2v10l6 2v6h-6v2c2 0 2 3 2 3s0 3-2 3v2c2 0 2 3 2 3s0 3-2 3v2h6l-1 32h-7v28c0 6 6 14 13 14h-22.913v-42L599 136l8.181-4L607 85h-12l-.096-15H587c0 6.927-7 5-7 5V63h-10v2h-6v-2h-11v2h-6v-2h-10v12s-7.08 1.85-7-5h-8l-.009 14.78H510V132l8 4-8 4v7h-41v-20h-6V85l-4-15h-3V60h-2l-1-18s-.885-4.54-2 0l-1 18h-2v10h-3l-4 15v42h-6v20h-37v-3s-2-.199-2-4h-1l-2-20s-.462-2.31-1 0l-2 20h-1c-.084 4.055-2 4-2 4v8h-1s-1 .014-1 1v2c.056 1.042.977 1 .977 1H387v7h-1s-.972.014-1 1v3c.028.986.92 1 .92 1H387v6.915L375 175v-60l-1-40 1-9.81s.013-7.5-5-7.613L366 57l-.744-7s-.094-.215-.224-.241c-.079-.016-.17.035-.262.241l-.77 7-4 .55c-5.012 0-5 7.45-5 7.45-.043 4.01 1.015 6.036 1 10-.046 12.483-.908 27.729-1 40-.033 5.333 0 4.667 0 10h-20v-10l-1-40 1-9.81s.012-7.5-5-7.613L326 57l-.744-7s-.24-.55-.487 0l-.77 7-3.999.55c-5.012 0-5 7.45-5 7.45-.044 4.011 1.015 6.036 1 10-.05 13.5-1.046 26.722-1 40 .068 19.804.077 39.623 0 60h-10v-35c-1.294-1.71 0-3-5.052-5.008L300 135s1.274-2.492 0-5c0 0-1-1-3-1-.415 0-1.056-7.307-2-9-.688-1.233-1.379-1.2-2 0-.282.542-1.472 8.978-2 9-2.552.104-3 1-3 1-.896 1.75-.036 4.726 0 5-1 0-8 0-8-5v-30l-5-.04c-1.952 0-2-4.96-2-4.96V85s-2.043-2.972-5-3V71c-3.363-6.77-2.696-6.564-6 0v11c-2.985.028-5 3-5 3v10s.03 5-2 5h-5c-.006 2.504 0 18.908 0 30 0 5-7 5-8 5 0 0 1.275-2.491 0-5 0 0-1-1-3-1-.415 0-1.056-7.307-2-9-.687-1.232-1.378-1.2-2 0-.281.542-1.472 8.978-2 9-2.552.104-3 1-3 1-1.24 2.421 0 5 0 5-4.956 2.056-5 5-5 5 .048 11.14.225 22.283 0 33.422h-7.096L217 22c.04-1.951-2-2-2-2l-43 .003s-2.04-.034-2 1.997l-.054 146h-7l.054-44h-5v-4h-5v3.783h-5.922L147 77h-9v5h-13V70h-12l-.086 116H106v-11h-4v-27l-3-18-3 18v5.92h-6.033L90 148h-2v-3h-2v-3h-2v-3h-2v-3h-2v-3h-2v-3h-2v-3h-2l-3-33h-1l-3 33h-2l.05 3H63v3h-2v3h-2v3h-2v3h-2v3h-2v3h-2v6h-6v-6l-3-18-3 18v27h-7l.002-43-2.497-9L27 132h-5v-19l1-4-7-22-7 22 1 4v19H5l-2.493-9L0 132v98h690v-40h-19.636v-7.284C680 182 687 175 690 168v-23h-35v-5h-19l-1-32h6v-2c-2-.01-2-3-2-3s0-3.035 2-3.035V98c-2-.019-2-3-2-3s0-3 2-3v-2h-6v-6l6-2V72l-6-2v-6h2c.975 0 2.093-1.025 2.093-2 0-1.042-1-2-2-2H635v-5l-2-10-1-20-1-22c-1-6.743-2 0-2 0"/></svg>

### 3D modeling

I then attempted to use Ondsel for designing the actual shelf by importing the SVG, extruding it and adding joints to it. The importing was pleasantly straightforward with correct scaling as well but I found it rather peculiar that the SVG was not similarly straight across the "Part Design" and " Draft" workbenches. I wet to adjust the grid size in order to envelope the entire shape and tried to troubleshoot it but later I realized that the bottom and side nodes had not perfectly snapped to the grid in Inkscape. I had practically fully designed the first verion of the shelf when Ondsel betrayed me and all 18 backups of the project that I had spent the entirety of Sunday exploratorily making were corrupted. I suspect this might have something to do with the fact that I edited the city vector as a sketch and forgot to use the lock constraint on the non-adjusting parts but that should still not happen. I lost practically all my work and so Ondsel/FreeCAD lost me as a user, at least for the rest of the course and complex projects.

![Import SVG to Ondsel](import-ondsel.webp)
![Pad SVG](pad-ondsel.webp)
![Cut SVG](cut-ondsel.webp)
![Grid settings](grid-ondsel.webp)
![Edit SVG as sketch in Ondsel](edit-sketch-ondsel.webp)

I decided to then start over in Fusion 360, with which I was more comfortable already anyway and which I knew to be significantly more stable and reliable. It did have a weird quirk though, of which Ondsel did not suffer: the vector was not correctly scaled upon importing the SVG file via "Insert" > "Insert SVG". I had to scale it by an arbitrary factor to match the original width, which was exactly 3.778233 for Tampere and 3.7795275 for Munich, even though they were the same width (different heights by 2cm difference though). The way by which I found the factor was to define a width parameter in "Modify" > "Change Parameters" and assign it to the horizontal edge of a rectangle and then trying out different scaling factors by increasing any decimal part until the vector width exceeded the rectangle, backtracking by one and adding a new number until I ran out of zoom to determine any substantial difference.

![Scaling the imported vector](import-svg-fusion.webp)

The shelf design using the below parameters is relatively simple. It contains the city background board, which was created in Inkscape, imported to Fusion 360 and scaled and then added to with the regular sketching tools such as lines and rectangles, the shelf component itself and triangular supports as well as a long rectangular one. The values below are relatively straightforward with `thickness` referring to the plywood material's thickness, `depth` to how far the shelf reaches from the wall, `height` to the size of the triangle supports as opposed to the entire thing, `load_diameter` to the top diameter of the jars to be placed on the shelf and `snugness` to how much room would be cut for joints.

| Name      | Value |
|-----------|-------|
| thickness | 15mm  |
| Width     | 690mm |
| dedpth    | 160mm |
| height    | 110mm |
| load_diameter | 106mm |
| snuggness | 0.1mm |

![City background sketch](city-background-sketch.webp)
![Shelf sketch](shelf-sketch.webp)
![Triangle support sketch](triangle-support-sketch.webp)

The green highlight of the city signifies that the city is fully but non-parametrically constrained (meaning it cannot be adjusted with the below values). The black part, however, signifies a regular fully constrained sketch that is attached to it. The idea for the three T-slits is to accomodate the joints connecting the shelf and supports to the back board. Why the board stretches beyond them is for easy installation to the wall, where it should be sufficient to drill screws through the extension part, hiding most of them from direct line of sight when viewed from above and making the installation process easier. The shelf connects to the background via three joints and the triangle connects to both the background as well as to the support bar, which rests on them.

To align the components properly in the assembly phase as well as to make them fit tighter, I added a pocket for the supports by creating a new sketch, which I extruded into the shelf by approximately 2mm (`thickness / 8`). The final support bar is significanttly wider than that depicted in the screenshot below.

![Support pocket](inset.webp)

I then assembled the parts into the first shelf, duplicated it, replaced the Tampere background with Munich and proceeded onto experimenting with the measure tool to make sure they would fit properly and leave enough space for the jars in all directions.

![Creating rigid joints in Fusion 360](joint.webp)
![Stacked Tampere and Munich shelves](ready-shelves.webp)

Out of curiosity, I also tested the Fusion 360 render workbench, which was very streamlined and straightforward so that creating a render was very quick and easy but there are not many options for adjusting it. I chose "Oak" as the material from "Appearance" > "Library" > "Wood" and applied it to all the bodies. I then locally rendered the image below with "Render Quality" of 75 and dimensions of 4000px x 4000px as for some reason it added a lot of white space around it. Cropping the image to around 1200px x 1200px then produced the below image.

![Fusion 360 render workbench](render-fusion360.webp)
![Shelves rendered in Fusion 360](city-skyline-shelf-fusion360-render.webp)

I wanted to again display it as a 3D model using modelviewer as well but no `.glb` export option was available and when exporting as `.obj` from Fusion 360, the texture was not included. I thus searched for a plywood texture on the internet and found one [here](https://polyhaven.com/a/plywood). I opened the example project that came with it and replaced the sphere in it with the `.obj` of the shelves using X- and Y-scaling of 0.01 for the texture in the shading view. I then exported it as `.glb` and displayed it below using my custom `3DModel` Hugo shortcode.

![Applying texture in blender](fusion360-render.webp)

{{< 3DModel "textured-city-skyline-shelves.glb" >}}

## CNC Milling

Our lab had the [Recontech 1312](https://www.cnc.fi/recontech-1312.html) CNC machine, which I used to mill the parts. We each had 2-hour slots for machining, which barely got me started - likely because I was the very first one who had booked a slot and the process might not have been established and streamlined properly yet. Additionally, we managed to bump into many software issues that even the instructors had not previously encountered. I will document my particular process below but once more [Aalto FabLab Wiki](https://wiki.aalto.fi/display/AF/Aalto+Fablab+Home?src=sidebar) has great documentation for [2D milling with recontech 1312](https://wiki.aalto.fi/display/AF/2D+Milling+with+Recontech+1312) in addition to which there is an 80-minute video for an even more exhaustive overview of the entire process [here](https://www.youtube.com/watch?v=mRKgx9oFAFw).

![Recontech 1312 CNC milling machine](fully-cut.webp)

### Safety

Use of gloves is recommended with materials that might splinter but explicitly not when using the machine, as they might get tangled up and pulled in. The large, red emergency stop can be found in the control box in the top left corner of the control unit below. The vacuum bed is very loud and thus ear protection is also highly recommended. Additionally, there is a first aid kit in the workshop in the lower, grey cabinet with sliding doors next to the blue cabinet by the second entrance if needed. Make sure to have long hair tied up and avoid loose clothing and only run the machine from outside of the room but monitor it through the window in the door. Calculating an appropriate feed rate and being aware of the cut area if using clamps is also crucial.

![Recontech 1312 control unit](control.webp)
![CNC room through door](cnc-room.webp)

### Creating toolpaths

I exported the sketches in `.dxf` format by individually selecting them from the tree view in Fusion 360 one by one and choosing "Save As DXF" from the context menu brought up by a right-click, which, however, is not necessarily the smartest way as discussed in the reflections at the bottom of the page. Those can be found in the repository [here](https://gitlab.com/miro.keimioniemi/digital-fabrication-portfolio/-/tree/main/content/post/week-7). I then uploaded them onto a USB stick and carried that over to the computer used with the machine. I imported the `.dxf` files into [VCarve Pro](https://www.vectric.com/products/vcarve-pro) and discovered some difficulties with that. The exported `.dxf` files included the sketch guidelines in addition to which they had accumulated some duplicate lines other than those too. This then resulted in various different types of unintended behavior such as a warning in creating the toolpaths in the milder end and setting the toolpaths on the inside even when outside was selected in the more baffling, annoying end.

![Warning about open contours upon trying to create toolpaths](open-contours.webp)

This could be solved by using the "Interactive Trim" tool to cut out the undesirable guidelines as well as the intersecting and overlapping lines. In theory this is as simple as just clicking on the lines to be deleted and merged but in reality it sometimes felt like the computer bits had to be flipped just right by sunrays penetrating and hitting them at a particular angle because of how fiddly deleting particularly the overlapping lines was. I did manage eventually, after which I could then join the vectors using "Join" once all overlapping lines were certainly deleted. One way to detect them was to ungroup the vectors and then just select each of the faces if the entire thing did not get highlighted when doing so. A successful join operation can be inferred from the number of open vectors being 0 after the operation.

![DXF imported to VCarve](import-dxf-vcarve.webp)
![Trimmed lines](join-vectors.webp)
![Join vectors](join-triangle.webp)

I created a "2D Profile Toolpath", set the cut depth to 15.4mm, which was recommended to us by our instructor, given that we had a sacrificial layer beneath the material, and input the below tool settings: 

- Diameter: 6mm
- No. Fluters: 2
- Pass Depth: 3 mm
- Stepover: 2.4 mm 40%
- Spindle Speed: 16000 r.p.m
- Feed Rate: 2100 mm/min
- Plunge Rate: 500 mm/min

Most of settings were set correctly by default and only needed verifying, which could be done by referring to the Aalto FabLab wiki entry on [2D milling with recontech 1312](https://wiki.aalto.fi/display/AF/2D+Milling+with+Recontech+1312). Due to the limited time slot, the milling bit was pre-installed for us but it can be changed by moving the vacuum tube to the side and changing both the collet and the bit as shown [here](https://www.youtube.com/watch?v=mRKgx9oFAFw). The particular tool we were using had 2 flutes (the cutting edges) and a diameter of 6 mm. We were told that the optimal pass depth would be equal to the radius of the tool and a stepover of 2.4 mm made it fast to move the tool around when not milling with enough of a margin of safety. The Recontech 1312 is rated for a spindle speed of upto 20 000 revolutions per minute but we were instructed to use 16 000 r.p.m with a plunge rate of 500 mm/min for safety. The feed rate could be calculated using the following formula:

```Feedrate (mm/sec) = Number of Flutes X Tooth feed (mm) X RPM (mm/s)```

Tooth feed for the above equation is dependent on the cutter diameter and the type of material to be milled. A lookup table can be found [here](https://www.sorotec.de/webshop/Datenblaetter/fraeser/schnittwerte_en.pdf), which gives a value of 0.060 for 6 mm and soft wood. This results in 1920, which we initially rounded down to 1900. After my time was starting to run out, [Solomon Embafrash](https://fabacademy.org/2018/labs/fablabaalto/students/solomon-embafrash/index.html), Aalto FabLab's manager told me it was fine to increase it to 2100 mm/min due to how soft the plywood was and most of my parts were milled with that setting with a decent outcome.

![Tool settings](tool-settings.webp)

I then added 10 mm wide and 2 mm thick tabs to the nearest straight paths at regular intervals and close to critical points to keep the milled part in contact with the rest of the sheet to avoid vibration, which might cause splintering and non-optimal cutting.

![Adding tabs](tabs.webp)

I then added a pocket 1.875mm (thickness / 8) deep to correctly align the components under the shelf using the "Pocket Toolpath".

![Creating a pocket toolpath](pocket.webp)

I had forgotten to add "Dog-Bone" fillets for the first test city background slits to compensate for the mill bit's roundness when trying to fit the components together. Having realized this, I did remember to add them to the rest of the parts by navigating to "Fillet", choosing "'Dog-Bone' Fillet" and clicking the corners I wanted one to be added for. Removing them was also simple by clicking the arcs if one were misplaced.

![Fillet tool](fillet.webp)
![Creating "Dog-Bone" fillets](dog-bone.webp)

The paths could then be previewed by selecting the desired ones and clicking usually "Reset Preview" first and then "Preview Visible Toolpaths" to show the updated ones. Here it is good to check for everything necessary getting cut or engraved and that the tabs are created correctly.

To save the toolpaths, navigate to "Save Toolpaths" and save them at any location. For a single path, the saving mode does not matter but for multiple paths one must be very careful. The checkmark in the box next to the toolpaths in the lower right corner means that they are visible, whereas the blue overlay of the text indicates selection, of which there can only be one. If one wants save multiple but not all toolpaths, make all visible by ensuring they have checkmarks next to them and choose "Visible toolpaths to one file" and then save with machine set to "Recontech 1312" and post processor to "Mach2/3 Arcs (mm) (*.txt)". Neither I nor Solomon realized to do this for the second city background and thus only the outlines were milled. I decided that it was easier just to re-mill it using the correct toolpaths as I still had material left.

![Save toolpaths](cut-preview.webp)

### Milling

Turn on the machine by rotating the black main switch to "ON" position and pressing the red "Power On" button on the control unit. To use the entire vacuum bed, make sure that both handles in the front controlling their respective sides of the machine are pointing down. To turn it on, press the white button in the upper right corner of the control panel. You can tell if it worked by the noise but you can wait until you have finished the entire setup before you turn it on.

![Recontech 1312 control unit](control.webp)
![Recontech 1312 CNC machine](recontech-1312.webp)

The saved toolpath file could then be opened in the very retro-looking [Mach3](https://www.machsupport.com/software/mach3/) software via "Load G-Code". Every time you open the software, make sure to begin by clicking "Reset" as the very first thing you do. Then, enable "Soft Limits" to enable software limits to make sure that you are notified if the toolpath exceeds the milling area. Finally, click "Ref All Home" to bring the tool to the origin in the front left corner. The tool can be moved manually using the arrow keys on the keyboards of both the computers inside and outside the room. You can then open the `.txt` toolpath file using the "Load G-Code" button.

![Mach3 CNC software](cnc-software.webp)

You can change the tool by first un-attaching the red dust shoe at the mouth of the large tube by loosening its two locking screws while holding it and swivelling it around the toolholder to get some space. Place the cushion found in the cabin immediately to the right of the door - where also the tools and collets are - under the toolholder to protect the tool in case it falls and change the collet by unscrewing the nut from the toolholder and screwing in another that is of appropriate size for the tool to be used. Insert the milling bit about 2cm in and tighten it by simultaneously using a spanner on the top of the shaft and a key wrench inserted from the bottom of the toolholder, bring back the dust shoe and remove the cushion.

![Collets and tools](tools.webp)
![Fixtures](fixtures.webp)

To load the material, prepare the vacuum bed by unplugging the vacuum holes under the area to be covered and set rubber strips underneath to prevent the air from escaping. Place the sacrificial, breathable MDF layer on top and blow off potential dust with the air compressor on the left wall. If using the whole bed, open both vacuum valves and then place your material on top of the sacrificial layer. Turn on the vacuum and check that the suction is adequate by trying to push the corners of the materials and checking that the pressure gauge is on the green zone. If the suction is inadequate or the material has a risk of warping or vibrating or you just want to be sure otherwise, you can additionally fixture the material using clamps in the cabin that attach to the rails or by using screws/nails, glue/tape, weights or encapsulation depending on the material and your needs. Make sure, however, that these do not intersect the toolpath on any of the X-, Y- or Z-axis to not damage the tool.

To calibrate X, Y and Z, turn on the vacuum bed to suck in the material for an accurate height measurement and place the yellow, conical Z-axis calibrator magnetically attached to the left side of the machine on the sheet of material. Move the machining bit over it and click the "Terän mittaus" button in the Mach3 software, which slowly lowers the bit on it until it barely touches it and so automatically sets the Z-axis. Then move the toolhead into the desired XY position, which defines the bottom leftmost corner of the milling area, and click both "Zero X" and "Zero Y".

Once the tool and vacuum bed are set and tested and the material is loaded along with the sacrificial layer, you can step out of the room, close the door, load the G-code if you had not yet done so on the laptop outside next to the door, preview the toolpaths in the top right corner of the Mach3 software and press the green button next to the door to launch the process. The green light signifies that the spindle is not spinning whereas the red light warns of a spinning spindle. Opening the door causes the milling to immediately stop so do not ever do so without stopping it first or waiting for it to finish. Do, however, monitor the cutting outside. Wait for the milling to finish, clean up after yourself by performing the steps in reverse, always leaving the room better than you found it and take your freshly milled pieces with you.

![CNC cutting](cnc-cutting.webp)

## Processing and assembly 

I carried the cut sheet of material to the woodworking space and used a chisel and a hammer to remove the tabs keeping the cut pieces attached to the sheet and the outcome was quite satisfying, even though particularly Tampere had some chipped details in Näsinneula and haulitorni. 

![Freshly milled sheet of material](chisel.webp)
![Separated city backboard](separated.webp)

As mentioned above already, I forgot the dog-bones from the Munich joints and the first version of Tampere missed the center one entirely and I had to re-mill it. The Munich joints would have to be processed a bit more but hurry from various sources forced me to wrap up my work for a while before I got the time to return to it. Below are the products of the day of milling.

![Milled parts](all-parts.webp)

After a couple of weeks I finally got the time to go back and assemble the parts. I took Rosa with me as she was the one who wanted two and so we assembled one each with a bit of cooperation in drilling. I did Tampere and she did Munich. We sanded the parts to get rid of splinters, smoothen all corners and make them fit nice and tight.

![Sanding the parts](sanding.webp)

As already mentioned above, I forgot to add the dog-bones to the Munich background and thus the shelf part would not fit to it. We thus used the [Dremel 4000](https://www.dremel.com/fi/fi/p/dremel-4000-f0134000ja) rotary-tool to add them afterwards. We changed the tool to the smallest sanding one available, although this was still quite a bit larger than the pre-existing dog-bones in the other parts. The tool could be changed by pressing the lock button and loosening the collet as shown below on the left. 

Using it was then as straightforward as plugging the power cable in, selecting the rotation speed from the bottom and pushing the blue switch up. Props to the designers for color-coordinating all controls blue nicely! The speed had to be set high enough so that the tool would not bounce and then I just gently pushed it into the corners where I wanted to create the dog-bones. The result can be seen in the rightmost image below, where the ones created with the Dremel are above and the pre-existing ones of the second Tampere background are on the bottom.

![Changing the dremel tool](dremel-tool.webp)
![Using the dremel to add dog-bones](dremel.webp)
![Additional dog-bones in the top corners, CNC ones in all the lower corners](added-dog-bones.webp)

Rosa was actually faster than I, even though she had to make more additional dog-bones than I, and while I still sanded my pieces, she had gotten hers to fit already and was hammering them into place with the rubber mallet. The fit was really snug but she faced another issue, which was that the shelf part did not go all the way in, even with the hammering and there remained a small gap between the joints of the background and the shelf as the shelf part did not have dog-bones either, which we had overlooked. We tried further sanding it a tiny bit and then just pounding it in as far as it goes as it was so tightly and deeply in already that pulling it out would have been very difficult and likely loosened the fit for the next time and the result can be seen below on the right. It's not perfect but close enough, particularly for the upper, less load-bearing shelf.

![Hammering the parts together using a rubber mallet](bang-into-place.webp)
![Gaps between background and shelf part](gaps.webp)

Trying to learn from this, I made sure to try and sand the corners of the shelf part so that they make true 90° angles. I tried to avoid creating dog-bones by only using sandpaper and the block as I wanted the fit to look perfect but in retrospective, it would have been easier to just create those as the gaps were not still quite perfectly closed although a bit better than without.

![Sanding the shelf joint with a sanding block](sanding-block.webp)
![Sanding the shelf jount with sanding paper](sanding-paper.webp)
![Assembled Tampere shelf](assembled-tampere-shelf.webp)
![Gaps in Tampere shelf](gaps-2.webp)

My parts slipped right in and while snuggish, not nearly as tight as Rosa's. This meant that they were easier to work with but perhaps slightly less reliable in terms of staying together. To play it safe with both shelves, we decided to still tighten the shelve parts to the backboards with some screws, which provide just a bit of additional support and ensure that the parts cannot be pulled apart. The thin screws, chosen to avoid splintering, sunk in like butter to the very soft wood and could be nicely hidden on the backside.
 
![Fastening screws](drilling.webp)
![Ready Munich shelf from behind](screwed.webp)
![Ready Munich shelf from the front](ready-munich-shelf.webp)

Below is a visualization of what the shelves would look like on the wall. I placed the lower Tampere shelf on top of the metal trim of the kitchen backsplash for a bit more of additional support as the contents of the shelf were to be quite heavy. I aligned the visible ends to be parallel to the edges of the wall and placed the shelves quite far apart to make sure there would be space for the tall containers on the lower shelf, although when actually fastening them, I brought the upper one lower. 

![Visualizing the end result](eyeballing-layout.webp)

To then install the shelves, I marked spots for pre-drilling holes into the backboards of the shelves for the screws used to fasten the shelf with excess plates from assembling IKEA furniture - of which there were precisely the right amount. The backboard was made to be elongated precisely so that most screws could be "hidden" under it but for extra stability and safety, I added ones above as well, centering them on the buildings closest to the edges high enough to significantly increase stability but low enough not to look too out of place. 

I measured them carefully and did the same for the ones under the shelf as well until I realized that it was a lot simpler and faster just to set the drill perpendicularly against the backboard as close to the underside of the shelf and its supports as allowed by the drill's shape and just drill straight through with a thin drill bit. Here it was important to be as close as possible to the shelf and support components to impart as little stress on the wood as possible from future loads but this was limited by the drill's shape and size.

![Positioning screw plates](support-plates.webp)
![Marking drill holes](marking-holes.webp)
![Drilling by eyeballing / feel](drilling.webp)

The wall where the shelves were to be installed was drywall and thus required drywall anchors for safety and stability.
Rosa held up the first shelf while I marked the spots for the centers of the anchors by drawing through the holes with a 0.5 pencil lead as they were the only things slim enough to fit through. It worked neatly after cleaning the splinters on the backside and I then installed the drywall anchors by first hammering them in a bit and then tightening with a basic screwdriver. Many anchors broke inside the wall so that their tips had to be carved out with a smaller flat-tipped screwdriver before inserting a new one in their place and continuing from where they were left off but we had enough for this to not be a major issue.

![Marking the spots through the holes (the scratch on my hand is from bouldering and thus unrelated)](mark-holes-on-wall.webp)
![Hammering the drywall anchors into place](hammering-drywall.webp)
![Drywall anchors for the first shelf](drywall-screws.webp)

We then drilled the screws in with the backplates, which went surprisingly smoothly without any major trouble. To position the second shelf above the first one, I placed the tallest container that the lower one was meant to carry on it and left a couple of centimeters of space between its top and the bottom of the next shelf. Simultaneously we had a leveler on the second shelf and once it was both at the right height and perfectly level, we drew a long line under the backboard to mark this and then Rosa marked the holes while I held the shelf still. Having been careful in the design phase paid off as the tip of Näsinneula avoided a collision with the support of the upper shelf nicely.

Drilling the second shelf to the wall was a lot scarier as we could not properly tell whether the holes were exactly on top of the anchors but we figured out that we could stick thin hammering nails through both the holes in the shelf as well as the anchors on the wall. We stuck ones through every hole we were not currently drilling in and so ensured that the shelf stayed level and in place while drilling. Starting from the far ends and moving towards the center, we soon had both shelves installed.

![Drilling the shelf to the wall](drilling-to-wall.webp)
![Leveling the shelf](leveler.webp)
![Pinning the shelf to the wall with nails](pinning-to-wall.webp)

Below are the shelves in everyday usage. Not much of the city backgrounds can actually be seen outside of a tea ceremony when all our tea varieties and Rosa's self-painted teapot + mug combination are offloaded from the shelf but they fulfill their functional purpose perfectly and presented a nice challenge in making them. I was very relieved after they easily carried all the weight of the full large containers.

![Fully loaded lower shelf](loaded-shelf.webp)
![Both shelves fully loaded](fully-loaded-shelves.webp)

## Reflections

This was an intense week during which I learned not to trust Ondsel with vectors but also how to create more complex parametric designs, mill them and how to save as much headache as possible in the post-processing and assembly phase.

Firstly, one must be very deliberate with their choice of parameters and their relationships. It would be a good idea to note the possible ranges where the parameters can lie or to define only a very small number of base parameters from which all others are derived in a way so that they can range from 0 to infinity without interfering with the others. Intuitively, the maximum number of such parameters would be 3 for width, height and depth. If there are any more, they will by necessity break down eventually, which might also be desired such as in this case with a fixed thickness, but this should be noted. 

Once the design is made, there exists far smarter ways of exporting than exporting the dxfs individually. Next time, I would most likely create the toolpaths in Fusion 360 too or, at the very least, create a sketch of the surface of the material sheet with fixed dimensions and all the components laid out on it. I could then export this as a singular `.dfx` file, which would save all the headache in VCarve Pro, including both overlapping lines and accidentally not exporting inner paths.

Finally, the importance of Dog-Bones cannot be overestimated. Adding them to all the relevant corners upon creating the toolpaths saves a ton of effort from the post-processing and assembly phase. Also, be prepared for splinters, particularly with thin parts of the design and cheap wood.

Overall, however, I am proud of the result, which still holds its load well after a couple of weeks!





