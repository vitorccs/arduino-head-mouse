# Arduino Head Mouse
A USB mouse controlled by both head movement and voice, for disability-aid or fun purposes.

![Image](https://github.com/user-attachments/assets/c18d263a-5e33-46e4-bc62-8dd1bcd8d360)

## Recording
https://github.com/user-attachments/assets/e7d2481a-8fa1-44dd-9bdf-6bea67ef0fe4

## Description
![Image](https://github.com/user-attachments/assets/e63b57fd-b76c-400c-9920-b03a0221d645)

The mouse cursor is controlled by head movement while any sound made in the microphone fires the left mouse click.
There is also a potentiometer to adjust the microphone sensibility per your environment noise level.
Additionally, there is a button to perform a left click and another button to reset the mouse cursor to center position.

## Components
* 01 - Arduino Pro Micro 5v (Atmega32u4, 16 Mhz)
* 01 - MPU6050 (accelerometer/gyroscope)
* 01 - SparkFun Electret Microphone Breakout ([ref1](https://www.sparkfun.com/sparkfun-electret-microphone-breakout.html), [ref2](https://www.robocore.net/sensor-ambiente/sensor-de-som-microfone))
* 01 - 500Ω Potentiometer
* 02 - Leds
* 01 - 150 - 470Ω Resistor 
* 02 - Push buttons
* 02 - Terminal connectors (KF301 5.0 3P)
* 01 - Optionally, a (cheap) Headset to serve as a case for your project

<img src="https://github.com/user-attachments/assets/762ec68a-59fc-4484-9efc-677a596a5ec5" width="320">


## About PlatformIO IDE
Platform IO is a plugin for Microsoft Virtual Studio Code. It is a more robust IDE compared to official Arduino IDE. It also allows us to easily create our own private libraries and use a more object oriented code.

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

#define DEBUG true
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
noDelay soundTimer;

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

  soundTimer.setdelay(20);
}

void loop()
{
  if (!soundTimer.update())
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
The eletronic schematic was created in the [Fritzing](https://fritzing.org/) software and can be downloaded at
* [arduino-head-mouse.zip](https://github.com/user-attachments/files/18549015/arduino-head-mouse.zip)

## Sources
* https://github.com/tix-life/Colibrino
* https://www.instructables.com/Head-Mouse-With-MPU6050-and-Arduino-Micro/
* https://www.instructables.com/Head-Mouse-Game-controller-or-disability-aid/
