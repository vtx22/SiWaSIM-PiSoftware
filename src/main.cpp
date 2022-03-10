#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "I2C.hpp"
#include "UART.hpp"
#include "GPIO.hpp"

int main()
{
   //I2C test("/dev/ttyAMA0", 0x50);
   //UART com();
   //test.begin();

   //uint8_t message[10] = {0xFF, 0xFF, 0xFF, 0xAA, 0xAB};
   //com.transmitMSG(message, 10);
   GPIO gpio;
   int scale = 300;
   for (int i = 0; i < scale; i++)
   {
      int freq = 1000 - scale / 2.f + i;
      gpio.setPWM(13, 50, freq);
      printf("PWM FREQ: %d\n", freq);
      time_sleep(0.1);
   }
}