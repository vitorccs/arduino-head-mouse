#include <Arduino.h>
#include <MouseHandler.h>
#include <PushButton.h>
#include <DigitalLed.h>
#include <MicSensor.h>
#include <MPU6050.h>
#include <Mouse.h>
#include <Potentiometer.h>
#include <avr/wdt.h>

MouseHandler::MouseHandler(MPU6050 &mpu,
                           DigitalLed &clickLed,
                           DigitalLed &resetLed,
                           MicSensor &micSensor,
                           Potentiometer &sensibilityPot,
                           bool vxInvert,
                           bool vyInvert) : _mpu(mpu),
                                            _clickLed(clickLed),
                                            _resetLed(resetLed),
                                            _micSensor(micSensor),
                                            _sensibilityPot(sensibilityPot)
{
    _mpu = mpu;
    _clickLed = clickLed;
    _resetLed = resetLed;
    _micSensor = micSensor;
    _sensibilityPot = sensibilityPot;
    _vxInvert = vxInvert;
    _vyInvert = vyInvert;
}

void MouseHandler::enableDebug(bool enable)
{
    _debug = enable;
}

void MouseHandler::leftClick()
{
    Mouse.press(MOUSE_LEFT);
    _clickLed.turnOn();
    delay(200);
    Mouse.release(MOUSE_LEFT);
    delay(200);
    _clickLed.turnOff();
}

void MouseHandler::reset()
{
    _resetLed.turnOn();
    wdt_disable();
    wdt_enable(WDTO_120MS);
    while (1) {}
}

void MouseHandler::setCalibration()
{
    _mpu.setXAccelOffset(-1738);
    _mpu.setYAccelOffset(-796);
    _mpu.setZAccelOffset(617);
    _mpu.setXGyroOffset(32);
    _mpu.setYGyroOffset(-36);
    _mpu.setZGyroOffset(-5);
}

void MouseHandler::handle()
{
    _mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // fix gyroscope static state
    vx = gx / 200;
    vy = -gz / 200;

    if (_vxInvert)
    {
        vx = vx * -1;
    }

    if (_vyInvert)
    {
        vy = vy * -1;
    }

    uint16_t sensibility = _sensibilityPot.getReading();
    uint16_t noise = _micSensor.readNoise();

    Mouse.move(vx, vy);

    if (_debug)
    {
        Serial.print("noise: ");
        Serial.print(noise);
        Serial.print(", sensibility: ");
        Serial.print(sensibility);
        Serial.print(", vx:");
        Serial.print(vx);
        Serial.print(", vy: ");
        Serial.println(vy);
    }

    if (noise > sensibility)
    {
        leftClick();
    }
}
