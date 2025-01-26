#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H
#include <Arduino.h>

class PushButton
{
public:
  PushButton(uint8_t pin);
  bool isPushed();

private:
  uint8_t pin;
};

#endif