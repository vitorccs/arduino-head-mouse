#include <Arduino.h>
#include <PushButton.h>

PushButton::PushButton(uint8_t pin)
{
  this->pin = pin;
  pinMode(pin, INPUT_PULLUP);
}

bool PushButton::isPushed()
{
  return digitalRead(this->pin) == LOW;
}