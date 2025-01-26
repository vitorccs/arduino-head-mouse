#ifndef MIC_SENSOR_H
#define MIC_SENSOR_H
#include <Arduino.h>

class MicSensor
{
public:
  MicSensor(uint8_t pin, uint16_t max = 100);
  uint16_t readNoise();

private:
  uint8_t pin;
  uint16_t max;
};

#endif