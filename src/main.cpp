#include <iostream>
#include <string>

#include "I2C.hpp"
#include "UART.hpp"

int main()
{
   I2C test("/dev/ttyAMA0", 0x50);
   UART test2("/dev/ttyS0");
   test.begin();
}