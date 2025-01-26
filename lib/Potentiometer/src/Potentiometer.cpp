#include <Arduino.h>
#include <Potentiometer.h>

Potentiometer::Potentiometer(uint8_t pin, uint16_t max)
{
  this->pin = pin;
  this->max = max;
  pinMode(pin, INPUT);
}

uint16_t Potentiometer::getReading()
{
  uint16_t reading = analogRead(this->pin);

  return map(reading, 0, 1023, 0, this->max); 
}