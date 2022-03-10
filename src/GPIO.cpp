#include "GPIO.hpp"

GPIO::GPIO()
{
   if (gpioInitialise() < 0)
   {
      printf("GPIO ERROR: GPIO initialization failed!\n");
   }
}

GPIO::~GPIO()
{
   gpioTerminate();
}

void GPIO::setPWM(int pin, float dutyCycle, float frequency)
{
   if (gpioHardwarePWM(pin, frequency, 1e6 * dutyCycle / 100.f) < 0)
   {
      printf("PWM Error\n");
   }
}
