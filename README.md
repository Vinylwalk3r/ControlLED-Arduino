# ControlLED (Arduino Part)

# !!!This is a WIP (Work in Progress). 
Im updating as im going along. also, nothing is tested yet, so if you would make something like this, and use my code, I dont promis anything at the moment. Until the testing rig is finished, I'll just say, this is WIP and anything and nothing can work!

- [Introduction](#whatisit?)
- [Features](#features)
- [Effects](#effects)
- [Example](#example)


## What is It?
If you want to have custom DIY lighting in your speakers, controlled by an Arduino, this project might be worth a look. This code will allow you to control your speaker RGB LEDs over Bluetooth, and get some nice effect for them.


## Features

- Individually select different LED colors
- Multiple effects to choose from
- Switching between effects via both bluetooth and manual
- Manual control over the fans
- Fans controlled by temperature readings
- Autoswitching between manual / auto

The Fans are controlled via PWM. 

## Effects
The effects are hardcoded into the arduino, and are the following
- Spin
- Flash to music
- Random

## Example
Below is a example of how it's going to look when finished. All the white boxes are components located under the floor.

![ScreenShot](https://github.com/Vinylwalk3r/ControlLED-Arduino/blob/master/image/ExampleSetup.JPG)

A more detailed diagram of how to wire this thing up will come when it is released.
