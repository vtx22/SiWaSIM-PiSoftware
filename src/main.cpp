#include <iostream>
#include <string>
#include <signal.h>
#include <pigpio.h>
#include <stdio.h>
#include <stdlib.h>

#include "I2C.hpp"
#include "UART.hpp"

int main()
{
   //I2C test("/dev/ttyAMA0", 0x50);
   //UART com();
   //test.begin();

   //uint8_t message[10] = {0xFF, 0xFF, 0xFF, 0xAA, 0xAB};
   //com.transmitMSG(message, 10);

   if (gpioInitialise() < 0)
   {
      printf("Error!!\n");
      return 0;
   }
   while (true)
   {
      if (gpioHardwarePWM(18, 10000, 50) != 0)
      {
         printf("PWM Error\n");
      }
      time_sleep(1);
   }
}