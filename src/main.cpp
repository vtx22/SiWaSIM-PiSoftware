#include <iostream>
#include <string>

#include "I2C.hpp"
#include "UART.hpp"

int main()
{
   //I2C test("/dev/ttyAMA0", 0x50);
   UART test2("/dev/ttyS0");
   //test.begin();

   uint8_t message[5] = {0xFF, 0xFF, 0xFF, 0xAA, 0xAB};
   //test2.transmitMSG(message, 5);
}