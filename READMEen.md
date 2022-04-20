# SWController
 
![IMG](./ReadMe.png "SWC")

[RU](./README.md)/[EN](./READMEen.md)

> Spot welding machine control system

## Functions

At the moment, this code for controlling the spot welding machine can:
+ Enable welding for a specified time

Development is underway:
+ Profiles for metal depending on their thickness

## Required modules

Required for assembly:
+ Arduino Uno (Nano)
+ LCD1602 Screen (Blue)
+ Encoder
+ Relay
+ Potentiometer (To adjust the contrast of the display)
+ Button (If the encoder is without a button)

## Installation

First, install the libraries:
+ [EncButton](https://github.com/GyverLibs/EncButton)
+ [microWire](https://github.com/GyverLibs/microWire)
+ [LiquidCrystal](https://github.com/arduino-libraries/LiquidCrystal)
+ SimpleMenu16PIN ([MeatBallDev/SimpleMenu16PIN](https://github.com/MeatBallDev/SimpleMenu16PIN))

Next, download the required firmware version, then flash the Arduino.  
If everything is connected according to the scheme below, then nothing needs to be changed in the code.

## Connection

The encoder is connected as follows: **CLK** - **D8**, **DT** - **D9**, **SW** - **D10**. If the control is reversed, then it is necessary to change the locations of the 8th and 9th pins.
> If the encoder is without a button, then it is connected according to the same scheme, but a button is connected in **D10** instead of **DT **.

The display is connected according to this scheme - [scheme](./DispConnect.jpg)  
The signal pin of the relay is connected to **D11**

## Management

Turning the encoder to the right is the next item/value,  
Turning the encoder to the left - previous point/value,  
Pressing the encoder/button - selection,  
Holding the encoder/button - exit backwards.

## Usage

After the launch, the main screen will appear. Please press the encoder/button 1 time.  
After that, you will have a menu with the following items:
+ Run
+ M. run
+ Profiles
+ Min. time
+ Max. time
+ Info
+ Reset EEPROM

Let's go through the functional points :)

### Run
*** W.I.P.*** Start welding using one of the work profiles.

### M. Run
Start welding for the specified time. (Within the minimum/maximum)

### Profiles
***W.I.P.*** Create/edit job profiles.

### Min. time
The minimum possible welding time is indicated here. (For profiles and manual welding)

### Max. time
The maximum possible welding time is indicated here. (For manual welding)

### Reset EEPROM
Resetting the non-volatile EEPROM memory if it is necessary to clear all stored data, or it was occupied by past Arduino firmware.  
To start the NC, you need to press the encoder button and hold it down to scroll it in any direction.  
***ATTENTION!*** This action resets all saved data.

## Future plans

Some plans for this project \m/
- [ ] Add icons for simplified use.
- [ ] Make a 3D model of a universal housing.
- [ ] Automatic selection of welding time after specifying the type of metal and its thickness.

## Feedback

If you have ideas for new features, questions, etc. write to the topic "questions" or to me in the social network. I will definitely answer you ;)
+ [VK (Maxivimax)](https://vk.com/maxivimax)
+ [Telegram (Maxivimax)](https://t.me/maxivimax)
