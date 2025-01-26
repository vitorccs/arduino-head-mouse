#ifndef MOUSE_HANDLER_H
#define MOUSE_HANDLER_H
#include <Arduino.h>
#include <MouseHandler.h>
#include <PushButton.h>
#include <DigitalLed.h>
#include <MicSensor.h>
#include <MPU6050.h>
#include <Potentiometer.h>

class MouseHandler
{
public:
    MouseHandler(MPU6050 &mpu,
                 DigitalLed &clickLed,
                 DigitalLed &resetLed,
                 MicSensor &micSensor,
                 Potentiometer &sensibilityPot,
                 bool vxInvert,
                 bool vyInvert);
    void enableDebug(bool enable);
    void leftClick();
    void reset();
    void setCalibration();
    void setMicSensibility(uint8_t sensibility);
    void handle();

private:
    int16_t ax, ay, az, gx, gy, gz;
    int vx, vy, vx_prec, vy_prec;
    MPU6050 &_mpu;
    DigitalLed &_clickLed;
    DigitalLed &_resetLed;
    MicSensor &_micSensor;
    Potentiometer &_sensibilityPot;
    bool _vxInvert;
    bool _vyInvert;
    bool _debug = false;
};

#endif