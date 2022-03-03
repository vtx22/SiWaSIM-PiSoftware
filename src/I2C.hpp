#pragma once
#include <string>
#include <stdint>
//#include <i2c/smbus.h>
//#include <linux/i2c-dev.h>

class I2C
{
public:
   I2C(std::string dev);
   bool begin();

private:
   std::string _dev;
   uint16_t _address;
   int _file;
};