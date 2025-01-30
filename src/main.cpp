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
