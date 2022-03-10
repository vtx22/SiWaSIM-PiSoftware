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
   GPIO gpio = GPIO();
   //gpio.setPWM(13, 50, 1000);
   while (true)
   {
      time_sleep(1);
   }
}