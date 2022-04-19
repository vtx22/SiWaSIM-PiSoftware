#pragma once
#include <signal.h>
#include <pigpio.h>
#include <stdint.h>
#include <cstdio>

class GPIO
{
public:
   GPIO();
   ~GPIO();
   void setPWM(int pin, float dutyCycle, float frequency);

   void setPinMode(uint8_t pin, uint8_t mode);

   void writePin(uint8_t pin, bool state);
   bool readPin(uint8_t pin);

private:
};