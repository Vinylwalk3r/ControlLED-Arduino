# ControlLED (Arduino Part)

### !!!This is a WIP (Work in Progress). 
Im updating as im going along. also, nothing is tested yet, so if you would make something like this, and use my code, I dont promis anything at the moment. Until the testing rig is finished, I'll just say, this is WIP and anything and nothing can work!

- [What is This?](#what-is-this?)
- [Features](#features)
- [Effects List](#effects)
- [Latest Update](#latest-update)
- [Example](#example)


## What Is This?
If you want to have custom DIY lighting in your speakers, controlled by an Arduino, this project might be worth a look. This code will allow you to control your speaker RGB LEDs over Bluetooth, and get some nice effect for them.


## Features

- Multiple effects to choose from
- Fans controlled by temperature readings
- Manual control over the fans
- Autoswitching between manual / auto fan control
### Bluetooth Required
- Individually select different LED colors
- Switching between effects via either bluetooth or manual

The Fans are controlled via PWM. 

## Effects
The effects are hardcoded into the arduino, and are the following
- Spin
- Flash to music
- Random

Got an idea for a new effect, or have a question? Just ask me at johannesw4@gmail.com

## Latest Update

### [07-110918](https://github.com/Vinylwalk3r/ControlLED-Arduino/blob/master/changelog.md#07-110918)

Added

- This Changelog
- Table of content and updated readme A LOT

Changed

- Changed RGB selection from 0 (Red), 127 (Green) and 256 (Blue) to 0,1,2 (Red, Green, Blue)
- Changed if's to switch cases in light and effect selection
- Reorganized Everything
- Changed many bytes names to complete lowercase names
- Changing if's to switch cases
- Fixed minor issues
- Cleaned code

## Example
Below is a example of how it's going to look when finished. All the white boxes are components located under the floor.

![Sorry, this image cant be viewed :/](https://github.com/Vinylwalk3r/ControlLED-Arduino/blob/master/image/ExampleSetup.JPG)

A more detailed diagram of how to wire this thing up will come when it is released.
