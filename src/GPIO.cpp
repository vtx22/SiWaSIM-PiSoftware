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
   if (frequency < 1)
   {
      float period = 1 / frequency;
      float highttime = period * dutyCycle / 100.f;
   }

   if ((int)frequency == 995)
   {
      frequency--;
   }
   if ((int)frequency == 996)
   {
      frequency++;
   }

   if (gpioHardwarePWM(pin, frequency, 1e6 * dutyCycle / 100.f) < 0)
   {
      printf("PWM Error\n");
   }
}
