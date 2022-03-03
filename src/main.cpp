#include <iostream>
#include <string>

#include "I2C.hpp"

int main()
{
   std::string dev = "/dev/i2c-1";
   I2C test(dev, 0x50);
   test.begin();
}