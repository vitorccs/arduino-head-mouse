# Arduino Head Mouse
USB mouse with cursor controlled by head movement and click made by sound/noise in a microphone - a project intended for disability-aid or fun purposes.

![Image](https://github.com/user-attachments/assets/b4f5f402-cdca-41a1-a580-e5c3fc2f3980)

This project was also published in this Autodesk Instructable article:

https://www.instructables.com/Arduino-Head-Mouse-With-Click-Controlled-by-Sound/


## Possible use
| Alternative Communication Board |
| -- |
| <img src="https://github.com/user-attachments/assets/78531ada-6acd-46df-ba9c-3d172aaa7b74" width="600"> |
| https://www.cboard.io |

| Simple writing communication |
| -- |
|<img src="https://github.com/user-attachments/assets/c6fa1262-8d97-4d36-b806-e4416cdd2d64" width="600"> |
| (Notepad + Virtual Keyboard)

| Entertainment (point & click games) |
| -- |
| <img src="https://github.com/user-attachments/assets/fc564a63-64a6-4212-8c1b-81166d585eb9" width="600"> |
| https://store.steampowered.com/app/2377970/Cats_Hidden_Around_the_World/ |

## Recordings
Note: enable the sound by clicking on the speaker icon from the video toolbar

https://github.com/user-attachments/assets/613e4d65-5710-4287-ade9-1d59fe7d8d9c

https://github.com/user-attachments/assets/5b56a279-1681-46fb-a604-73bcdcfd5af5

https://github.com/user-attachments/assets/e7d2481a-8fa1-44dd-9bdf-6bea67ef0fe4


## Description

![Image](https://github.com/user-attachments/assets/aa2313ef-4b64-403a-be62-0686b8329115)

+ The mouse cursor is controlled by head movement while any sound detected in the microphone makes the left mouse click.
+ The potentiometer adjust the microphone sensibility per your environment noise level
+ [Optional] the left button performs a left click (useful for assisting somebody)
+ [Optional] The right button briefly interrupts the board (useful for fixing your head position)

## Components
* 01 - Arduino Pro Micro 5v (Atmega32u4, 16 Mhz)
* 01 - MPU6050 (accelerometer/gyroscope)
* 01 - SparkFun Electret Microphone Breakout ([ref1](https://www.sparkfun.com/sparkfun-electret-microphone-breakout.html), [ref2](https://www.robocore.net/sensor-ambiente/sensor-de-som-microfone))
* 01 - 500Ω Potentiometer
* 02 - Leds
* 01 - 150 - 470Ω Resistor 
* 02 - Push buttons
* 02 - Terminal connectors (KF301 5.0 3P)
* 01 - 22 AWG 6 Pairs Cable ([ref](https://www.amazon.com/FiveStarCable-Conductors-Alarm-Security-22-6/dp/B009PPKBKA?th=1))
* 01 - Optionally, a (cheap) Headset to serve as a case for your project

## Mounting pictures
Prototype board

<img src="https://github.com/user-attachments/assets/ef08598f-56f1-4311-abb4-088d5b643873" width="320">

Position of accelerometer

<img src="https://github.com/user-attachments/assets/08244144-f4fb-4dc9-874a-e39fc02a2c14" width="320">

The Headset

<img src="https://github.com/user-attachments/assets/9e040b8a-bcad-4712-9e2e-57550a50cafa" width="320">


## About PlatformIO IDE
Platform IO is a plugin for Microsoft Visual Studio Code. It is a more robust IDE compared to the official Arduino IDE. It also allows us to easily create our own private libraries and use a more object oriented code.

## About the code
The PINs can be customized in the `main.cpp` 
```c++
#include <Arduino.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Mouse.h>
#include <PushButton.h>
#include <MicSensor.h>
#include <DigitalLed.h>
#include <NoDelay.h>
#include <MouseHandler.h>
#include <Potentiometer.h>

#define DEBUG false
#define MIC_PIN A1
#define LED_CLICK_PIN 5
#define LED_RESET_PIN 6
#define BTN_CLICK_PIN 7
#define BTN_RESET_PIN 8
#define SENS_POT_PIN 9
#define VX_INVERT false
#define VY_INVERT false

MPU6050 mpu;
DigitalLed clickLed(LED_CLICK_PIN);
DigitalLed resetLed(LED_RESET_PIN);
MicSensor micSensor(MIC_PIN);
Potentiometer sensibilityPot(SENS_POT_PIN);
MouseHandler mouseHandler(mpu, clickLed, resetLed, micSensor, sensibilityPot, VX_INVERT, VY_INVERT);
PushButton leftClickBtn(BTN_CLICK_PIN);
PushButton resetBtn(BTN_RESET_PIN);
noDelay loopTimer;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection())
  {
    while (1);
  }

  mouseHandler.setCalibration();
  mouseHandler.enableDebug(DEBUG);

  loopTimer.setdelay(20);
}

void loop()
{
  if (!loopTimer.update())
  {
    return;
  }

  if (leftClickBtn.isPushed())
  {
    mouseHandler.leftClick();
  }

  if (resetBtn.isPushed())
  {
    mouseHandler.reset();
  }

  mouseHandler.handle();
}
```

## Fritzing file
The electronic schematic was created in the [Fritzing](https://fritzing.org/) software and can be downloaded at
* [arduino-head-mouse.zip](https://github.com/user-attachments/files/18631044/arduino-head-mouse.zip)

## Sources
* https://github.com/tix-life/Colibrino
* https://www.instructables.com/Head-Mouse-With-MPU6050-and-Arduino-Micro/
* https://www.instructables.com/Head-Mouse-Game-controller-or-disability-aid/
