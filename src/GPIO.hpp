#pragma once
#include <signal.h>
#include <pigpio.h>

class GPIO
{
public:
   GPIO();
   ~GPIO();
   void setPWM(int pin, float dutyCycle, float frequency);

private:
};