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

flutter_reactive_ble is best supported https://www.linkedin.com/pulse/which-flutter-bluetooth-low-energy-library-choose-reinhold-quillen/ while old enough that copilot knows how to use it





NEvermind, below doesn't do shit

Avoid flutter_reactive_ble like the plague - even their example app doesn't work

https://medium.com/@danielwolf.dev/get-started-with-bluetooth-low-energy-using-flutter-arduino-bdf5d790edc

https://pub.dev/packages/flutter_reactive_ble





package com.example.led_zeppelin_app

import io.flutter.embedding.android.FlutterActivity
import io.flutter.embedding.engine.FlutterEngine
import io.reactivex.exceptions.UndeliverableException
import io.reactivex.plugins.RxJavaPlugins
import com.polidea.rxandroidble2.exceptions.BleException

class MainActivity: FlutterActivity() {
    override fun configureFlutterEngine(flutterEngine: FlutterEngine) {
        super.configureFlutterEngine(flutterEngine)
        RxJavaPlugins.setErrorHandler { throwable: Throwable ->
            if (throwable is UndeliverableException && throwable.cause is BleException) {
                println("""Suppressed UndeliverableException: $throwable""")
                return@setErrorHandler   // ignore BleExceptions as they were surely delivered at least once
            }
            throw RuntimeException("Unexpected Throwable in RxJavaPlugins error handler", throwable)
        }
    }
}




https://stackoverflow.com/questions/67578189/pub-failed-to-delete-entry-because-it-was-in-use-by-another-process


re-advertise in the loop to stay discoverable
https://forum.arduino.cc/t/unable-to-reconnect-to-ble-after-disconnection-when-working-with-one-central-and-multiple-peripherals/1127844/4


Tanh managed to extract the solution from ChatGPT, which gave it using the deprecated Flutter Blue but I managed to migrate it to flutter blue plus and it worked


Increased size and complexity of code led to 

A fatal error occurred: No serial data received.
*** [upload] Error 2


https://github.com/nkolban/ESP32_BLE_Arduino/blob/master/examples/BLE_notify/BLE_notify.ino

