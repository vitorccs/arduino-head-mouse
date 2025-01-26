#include <Arduino.h>
#include <PushButton.h>
#include <MicSensor.h>

MicSensor::MicSensor(uint8_t pin, uint16_t max)
{
  this->pin = pin;
  this->max = max;
  pinMode(pin, INPUT);
}

uint16_t MicSensor::readNoise()
{
  uint16_t reading = analogRead(this->pin);

  return map(reading, 0, 1023, 0, this->max); 
}