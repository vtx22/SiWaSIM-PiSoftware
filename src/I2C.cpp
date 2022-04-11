#include "I2C.hpp"

I2C::I2C(std::string dev, uint16_t address) : _dev(dev), _address(address)
{
   begin();
}

I2C::~I2C()
{
   close(i2c0);
}

bool I2C::begin()
{
   i2c0 = open(_dev.c_str(), O_RDWR);

   if (i2c0 < 0)
   {
      printf("I2C ERROR: Cannot open device!\n");
      return false;
   }

   if (ioctl(i2c0, I2C_SLAVE, _address) < 0)
   {
      printf("I2C ERROR: Device Error!\n");
      return false;
   }

   return true;
}

bool I2C::writeData(uint16_t register, uint8_t *data, uint8_t length)
{
   if (write(i2c0, data, length) != length)
   {
      printf("I2C ERROR: Could not transmit data!\n");
   }

   return true;
}