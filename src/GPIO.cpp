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
      float highttime = period * dutyCycle;
   }

   if ((int)frequency == 995)
   {
      frequency--;
   }
   if ((int)frequency == 996)
   {
      frequency++;
   }

   if (gpioHardwarePWM(pin, frequency, 1e6 * dutyCycle) < 0)
   {
      printf("GPIO ERROR: PWM Error\n");
   }
}

void GPIO::setPinMode(uint8_t pin, uint8_t mode)
{
   if (gpioSetMode(pin, mode) != 0)
   {
      printf("GPIO ERROR: Error setting pin mode! PIN: %d\n", pin);
   }
}

void GPIO::writePin(uint8_t pin, bool state)
{
   if (gpioWrite(pin, state) != 0)
   {
      printf("GPIO ERROR: Error writing to pin %d!\n", pin);
   }
}

bool GPIO::readPin(uint8_t pin)
{
   int value = gpioRead(pin);
   if (value != 0 && value != 1)
   {
      printf("GPIO ERROR: Error reading from pin %d!\n", pin);
      return 0;
   }

   return value;
}
