---
author: "Miro Keimiöniemi"
title: "3-Axis Milling & Vacuum Forming (Wildcard)"
date: "2024-06-17"
description: "Week 16"
tags: 
  - "3-axis milling"
  - "vacuum forming"
  - "acrylic"
  - "sikablock"
  - "diffuser"
  - "lamp cover"
  - "stand"
  - "Recontech 1312"
  - "system"
  - "integration"
categories: 
  - "CAD"
  - "3-Axis Milling"
  - "Vacuum Forming"
series: 
  - "Weekly Assignments"
image: "lamp-externals.webp"
---

Wildcard week! This is one of the freest weeks as we got to pick one out of three manufacturing processes: waterjet, 3/4-axis milling or ultrasonic welding for producing inflatables, with which we could do an entirely free-form project. For me, this meant exploring the processes for building my lamp physically. The trickiest part of that had always been the large ellipsoid diffuser. The intuitively interesting processes for it at our lab were molding and casting, 3D-printing and vacuum forming. 

Molding and casting would have required a massive two-part mold and we did not have too much of the materials left - and those that we did have had way too short curing times and undesirable textures in being either entirely opaque or an ugly brownish transparent. 3D-printing had the same textural issues and was also constrained by the too-small print area, which would have required a vertical seam instead of the horizontal one that I much preferred. Once I found out about the large sheets of 3mm thick translucent acrylic and heard that they could be vacuum formed, I had made my decision on what I was to do. 

Vacuum forming seemed a reasonably easy and straightforward process, but it required a mold over which to form the vacuum and which to push through the material to be formed. Hence, out of the three options, 3-axis milling seemed the most reasonable, particularly in the context of the [Fab Academy](https://fabacademy.org/), where historically the mold for [molding and casting]({{< relref "post/week-11/index.md" >}}) was already produced with the process in order to achieve as smooth of a surface finish as possible, which was required for smooth results from vacuum forming as I gathered from following [Vytautas Bikauskas' process](https://timeritualslabour.gitlab.io/digital-fabrication/week14.html) just before me. I figured I would not have to be quite as exact due to vacuum forming a larger piece of much thicker translucent material compared to his thin piece of transparent acrylic, but 3-axis milling seemed highly appropriate nevertheless as it could easily be applied to [SikaBlock](https://automotive.sika.com/en/solution-products/advanced-resins/sikablock.html), which could withstand the high temperatures of the acrylic when vacuum formed. Furthermore, it could be used for producing the stand as well.

## Assignments

Design and produce something with a digital process (incorporating computer-aided design and manufacturing) not covered in another assignment, documenting the requirements that your assignment meets, and including everything necessary to reproduce it.

- Choose one of the proposed digital manufacturing technologies.
- Create a digital design to be manufactured with the technology/machine of your choice.
- Work together with the workshop master and document the process.
- Publish the documentation on your course documentation page.
- Submit a link to your documentation page here.

## 3-axis milling

Both the larger [Recontech 1312](https://www.cnc.fi/recontech-1312.html) CNC machine and the [Roland Modela MDX-40](https://www.rolanddga.com/support/products/milling/modela-mdx-40-3d-milling-machine) milling machine are capable of 3-axis milling, with the latter supporting even 4-axis milling, where the tool can rotate around the object to be milled. As the design for my lamp diffuser was quite large at 36cm long, I had to use the Recontech 1312, the general usage of which is already documented in [Computer-Controlled Machining]({{< relref "post/week-7/index.md" >}}). To determine the [semi-minor axis](https://en.wikipedia.org/wiki/Semi-major_and_semi-minor_axes), i.e. the maximum vertical radius of a horizontally lying ellipsoid (not a mathematically rigorous definition), I searched for the longest milling bits and defined it accordingly.

Our lab's CNC expert Jonas Tjepkema recommended that I should use 12mm thick milling bits as I did not need to do anything detailed. I thus measured the semi-minor axis accordingly and we prepared the tool paths with them before we were alerted by Aalto Fablab Manager Solomon about the 12mm collet being somehow unreliable and potentially wobbly. I had chosen the semi-minor axis to be 8cm based on the the 12mm milling bits but luckily found 6mm milling bits that were 8cm and 10cm long, both of which were fine as even though a couple centimeters had to be reserved for the collet, the shape of the ellipsoid is quite forgiving. 

### Preparing the SikaBlock

The heat-resistant SikaBlock came in large slabs with a thickness of 5cm, which meant that they had to be cut with a circular saw and glued together in order to make a thicker block from which to mill the model. To give a bit of a safety margin, we tried to cut the pieces to be approximately 40cm long and 17cm wide but as can be seen further below, they were not perfectly exact, airing on the side of rather a tiny bit too much than too little.

![Cutting the SikaBlock slab with a circular saw](cut-sikablock.webp)

The [Prolab Glue](https://www.materialshop.fi/Prolab-Glue-levyliima) for gluing together the pieces of SikaBlock turned out to have a curing time of 5h, delaying the CNCing originally planned for Tuesday all the way to Friday when the next slot was available. It also turned out to be expired 6 months ago and its datasheet was no longer available anywhere on the internet due to its manufacturing having been stopped. Regardless, the chocolate pudding looking mixture that resulted from thoroughly mixing twice as much of component A to component B in a mixing ratio of 2A:1B by weight, turned out to hold perfectly well, especially when it had multiple days instead of that five hours due to the availability of the CNC machine.

![Chocolate vanilla pudding](prolab-glue.webp)
![Delicious looking pseudo chocolate cake](chocolate-cake.webp)

![Gluing the pieces of SikaBlock together](making-a-monolith.webp)
![Letting the glue set under pressure](glue-setting.webp)

### Tool configurations

3D-toolpaths can be generated in [VCarve Pro](https://www.vectric.com/products/vcarve/) analogously to 2D-toolpaths as documented in [Computer-Controlled Machining]({{< relref "post/week-7/index.md" >}}) but this time I wanted to try [Fusion 360](https://www.autodesk.com/products/fusion-360/overview) as Jonas had mentioned it to be a lot more powerful. This, of course, required manually defining the tools to be used, which could be done by opening "Tool Library" on the "Manufacture" toolbench as shown below.

![Open tool library from the manufacture toolbench](open-tool-library.webp)

I created a new folder under `Local` called `Aalto Fablab`, where I created a new library for `Sikablock`, which contains both the 12mm and 6mm tool configurations in the below image. Later I also created another library called `Hard wood` for configuring the same 6mm end mills for milling the stand out of hard wood. The dimensions in both configurations are obviously the same but the feedrates differ as can be seen further below. 

![Fusion 360 local tool library](tool-library.webp)

The relevant tabs for configuring the tools are "General" where the tool can be named, "Cutter" where the tool dimensions can be configured as shown below, and Cutting data where the feedrates are adjusted. Most of the fields in "Cutter" are quite self evident: "Type" refers usually to the shape of the mill, the most common of which are "Flat end mill" for rough cutting and "Ball end mill" for finishing passes. "Unit" is wise to have be the same as on your measuring tool and "Clockwise spindle rotation" is usually correct when left checked. "Number of flutes" is the number of the twisting cutting edges of the tool - particularly easy to count as the distinct protrusions from the end of the flat end mill. "Material" I don't see having much of an effect on anyhting so that was left as the default "HSS" as well. 

"Diameter" refers to the maximum diameter of the cutting end of the tool where the flutes are, i.e. the distance from one cutting edge to another on the opposite side. "Shaft diameter" refers to the diameter of the end from which the tool is held in the collet. Overall length is the total length of the tool from end to end. "Length below holder" refers to how much of the tool comes out from the collet, such that the difference between it and the overall length of the tool is the part within the collet. It is generally a good practice to budget between 15mm to 25mm for this, with more being likely better up to that point for secure fastening of the tool. "Shoulder length" refers to that part of the tool which has a diameter corresponding to "Diameter", i.e. the length below holder that has a diameter different from "Shaft diameter". "Flute length", on the other hand, corresponds to the length of the cutting part that has sharp edges. It is thus usually a little bit less than the length of the overall spiral. 

![Measuring the overall length of the 6mm flat end mill with a caliper](measuring-milling-bit.webp)
![Configuring Cutter parameters (dimensions) of the 6mm flat end mill](flat-6mm-cutter-parameters.webp)

The "Cutting data" parameters are set similarly to how it was done in the 2D case in [Computer-Controlled Machining]({{< relref "post/week-7/index.md" >}}) by using [this reference](https://www.sorotec.de/webshop/Datenblaetter/fraeser/schnittwerte_en.pdf). In Fusion 360, the principles are the same. All the fields with fx next to them below are automatically computed from those without. Thus, the only really modifiable parameters are "Spindle speed", which is how fast the tool rotates and is recommended to be set at 16 000 for our machine and "Cutting feedrate", which determines the "Feed per tooth", which could be targeted to be quite high at 0.0875 for SikaBlock from Jonas' experience and around 0.055 for hard wood. "Ramp feedrate" and "Plunge feedrate" can be set to be equal usually at approximately one fifth (1/5) of the "Cutting feedrate" as a conservative rule of thumb. 

![Physical tool vs virtual tool](milling-bit.webp)
![Configuring Cutting data of the 6mm flat end mill](flat-6mm-cutting-data.webp)

Then press "Accept" to add the tool configuration to the library and repeat the process for all tools to be used in the process. Below are the configurations used first for the 6mm flat end mill and then the 6mm ball end mill with cutting data first for SikaBlock and then for hard wood. No other tabs were touched so that they are all defaults.

![6mm flat end mill general data](flat-6mm-general.webp)
![6mm flat end mill dimensions](flat-6mm-cutter-parameters.webp)
![6mm flat end mill cutting data for SikaBlock](flat-6mm-cutting-data.webp)
![6mm flat end mill cutting data for hard wood](flat-6mm-hard-cutting-data.webp)

![6mm flat end mill general data](ball-6mm-general.webp)
![6mm flat end mill dimensions](ball-6mm-cutter-parameters.webp)
![6mm flat end mill cutting data for SikaBlock](ball-6mm-cutting-data.webp)
![6mm flat end mill cutting data for hard wood](ball-6mm-hard-cutting-data.webp)

### Creating toolpaths

The logic for creating the toolpaths is largely the same as with 2D-toolpaths, which were documented using VCarve Pro in [Computer-Controlled Machining]({{< relref "post/week-7/index.md" >}}). To create 3D-toolpaths in Fusion 360, navigate to the "Manufacture" workbench from the top left corner and click on "Setup" to set up the material as shown below. Here all the options are pretty much self-explanatory and the visual preview shows the effect of each parameter. It is important to set the origin ("Stock Point") identically in both Fusion and the CNC machine controller (In this case [Mach3](https://www.machsupport.com/software/mach3/)) so do pay particular attention to that. Then I just set the dimensions of the stock to match the cut pieces, which had a couple of centimeters of margin and clicked "OK" without touching the "Post Process" tab. 

![Setting up the stock configuration for the toolpath](toolpath-setup.webp)
![Stock dimensions](toolpath-stock-dimensions.webp)

For the roughing pass, I used the adaptive clearing roughing strategy with the below settings. As the tools were already configured, I could simply select the 6mm flat end mill from the "Sikablock" library and proceed to the next parts of the setup, which was much more extensive and customizable than that of VCarve Pro.

![Creating a toolpath using adaptive clearing](adaptive-clearing.webp)

In the "Geometry" tab you can define the "Machining Boundary", which defines the horizontal software limits for how far the toolpath can go. "Stock Definition" intelligently looks at previous operations to determine how much of the stock is left to avoid excess work. I left these to defaults if I remember correctly. "Heights" defines the vertical software limits for the toolpath whereas "Passes" allows for finer control of the parameters of the toolpath and the tool while cutting. For most operations it suffices to leave these to their defaults as well. "Maximum Roughing Stepdown" is usually good to be kept to half of the diameter of the tool and climb "Direction" usually provides desired results. "Stock to Leave" does what it says. "Linking" I also left in its default state.

![Toolpath geometry](geometry.webp)
![Toolpath heights](heights.webp)
![Toolpath passes](passes.webp)
![Toolpath linking](linking.webp)

Now clicking "OK" generates the toolpaths as seen below. On the left is the generated toolpath and on the right is a visualization of the result after running it. 

![6mm adaptive clearing toolpath](6mm-rough-toolpath.webp)
![6mm adaptive clearing result preview](6mm-rough-result.webp)

As the roughing toolpath leaves a bit of material, I added a "2D Contour" to cut the model shape out entirely. I left everything else as default except that I chose the contour to be the outline of the remaining model. 

![2D Contour to cut out the model from the remaining stock](2d-contour.webp)

Finally, I added a finishing toolpath using "Scallop" where most of the settings were again either the same or left as defaults.

![Finishing pass with Scallop](scallop.webp)

For the stand, I went through the same exact steps with the only differences being the different tool configurations and a "Parallel" finishing toolpath instead of "Scallop". The stand was redesigned to be more sturdy and stable but primarily so that it would be easily producible via 3-axis milling. More about this in [system integration]({{< relref "post/week-15/index.md" >}}).

![Finishing pass with Parallel](parallel.webp)

### Exporting toolpaths

Exporting the toolpaths was initially the most confusing part. To export toolpaths, generate an "NC Program", which represents a single "job" to be run on the target machine, by clicking the button next to "Setup". The confusing part was then trying to figure out what "Post" under "Machine and post" means. Eventually, we figured out that I should select "Artsoft"'s "Mach3Mill" from the "Post Library" that can be opened by clicking the folder icon next to the "Post" field. Everything else can be left as default, although it is a good idea to specify a filename and make sure where to find the output. Then, in the "Operations" tab, select the toolpaths that share the same tool and post them. The resulting files correspond to those generated in [Computer-Controlled Machining]({{< relref "post/week-7/index.md" >}}) but have the file extension `.tap` instead of `.txt`.

![NC Program settings](image-2.webp)
![NC Program post library](image-1.webp)
![NC Program operations](image.webp)

### CNC milling result

I first tested the toolpath with some foam as I was a bit anxious about only having 60mm of the tool showing out of the collet for an 80mm tall model but I could soon see that the curvature mitigated this problem entirely. I then taped the SikaBlock onto the sacrificial layer, placed it carefully so that the tool could run directly parallel to its edge and then executed the `.tap` toolpaths as already documented in [Computer-Controlled Machining]({{< relref "post/week-7/index.md" >}}), producing the below results.

![CNC milling foam](milled-foam.webp)
![Fastening SikaBlock](fastening-sikablock.webp)
![CNC milling SikaBlock](milling-sikablock.webp)
![Freshly milled SikaBlock](milled-sikablock.webp)


The 12mm toolpaths would have only taken a bit less than an hour combined but the 6mm tool took almost three hours for the roughing alone, even though I increased the feedrate slightly from Mach3 as it was running too. However, it was late on a Friday and I wagered that the result was already smooth enough for my purposes, thus deciding to forego the finishing pass entirely and only sand and coat it instead to make it smooth enough. As can be seen below, however, taping it to the sacrificial layer might have been a mistake after all as it was very difficult to separate. 

![](sanding-sikablock.webp)
![](removing-1.webp)
![](removing-2.webp)
![](removing-3.webp)
![](removing-4.webp)

I wiped the sanded model with wet paper after air gunning it to really make sure that all of the dust was gone. Then, following in [Vytautas' footsteps](https://timeritualslabour.gitlab.io/digital-fabrication/week14.html), I coated it with a spraykit made for smoothening models and then sanded it once more to obtain the very smooth but still not quite perfect model below on the right. I figured it should be sufficient for my thick translucent acrylic though as I doubted that the details would propagate onto the surface - which turned out to be correct.

![](removed.webp)
![](wet-paper.webp)
![](spraykit.webp)
![](sprayed.webp)

Later I also 3D-milled the newly designed stand, which required a lot less post processing. I noticedd only after it was ready, that for some reason the finishing pass had only touched the inside of the stand but I decided that it merely added an intriguing detail, sanded the outside a little bit and left it be as it was.

![3D-milled redesigned stand](stand.webp)

![](preparing-model.webp)
![](first-vacuum-attempt.webp)
![](second-attempt.webp)
![](fourth-attempt.webp)
![](thin-acrylic.webp)

![](sawing-acrylic.webp)
![](sanding-acrylic.webp)
![](loaded-material.webp)

![](first-success.webp)
![](heat-gunning.webp)
![](acute-processing.webp)
![](blowing-air.webp)
![](first-success-out.webp)

![](bigger-setup.webp)
![](big-success.webp)
![](small-success.webp)
![](great-fillets.webp)

transparent stuff started boiling around 720 seconds.

![](heat-monitor.webp)
![](risky-margin.webp)
![](vacuum-former-settings.webp)

![](evolution-of-vacuum-pressed.webp)








Vacuum forming difficulties: 

The covering tape would not come off fully - put it in there anyway

The acrylic would get pulled out from underneath the frame so that the vacuum breaks and it forms into a dent instead of the shape



Toolpaths for stand as well










