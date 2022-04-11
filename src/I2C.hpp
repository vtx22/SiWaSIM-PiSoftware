#pragma once
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

class I2C
{
public:
   I2C(std::string dev, uint16_t address);
   ~I2C();
   bool begin();
   bool writeData(uint16_t register, uint8_t *data, uint8_t length);
   bool readData();

private:
   std::string _dev;
   uint16_t _address;
   int i2c0 = -1;
};