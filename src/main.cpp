#include <iostream>
#include <string>

#include "I2C.hpp"
#include "UART.hpp"

int main()
{
   //I2C test("/dev/ttyAMA0", 0x50);
   UART com("/dev/ttyUSB0");
   //test.begin();

   //uint8_t message[10] = {0xFF, 0xFF, 0xFF, 0xAA, 0xAB};
   //com.transmitMSG(message, 10);
}