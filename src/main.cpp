#include <iostream>
#include <string>

#include "I2C.hpp"

int main()
{
   I2C test = new I2C("/dev/i2c-1", 0x50);
   test.begin();
}