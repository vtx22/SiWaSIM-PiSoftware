#include <iostream>
#include <string>

#include "I2C.hpp"
#include "UART.hpp"

int main()
{
   I2C test("/dev/i2c-1", 0x50);
   test.begin();
}