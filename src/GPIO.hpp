#pragma once
#include <signal.h>
#include <pigpio.h>
#include <stdint.h>
#include <cstdio.h>

class GPIO
{
public:
   GPIO();
   ~GPIO();
   void setPWM(int pin, float dutyCycle, float frequency);

private:
};