#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H
#include <Arduino.h>

class Potentiometer
{
public:
  Potentiometer(uint8_t pin, uint16_t max = 100);
  uint16_t getReading();

private:
  uint8_t pin;
  uint16_t max;
};

#endif