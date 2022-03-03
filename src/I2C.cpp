#include <I2C.hpp>

I2C::I2C(std::string dev, uint16_t address) : _dev(dev), _address(address)
{
}

bool I2C::begin()
{
   _file = open(_dev, O_RDWR);
   if (file < 0)
   {
      printf("I2C ERROR: Cannot open device!");
      return false;
   }
   ioctl(_file, I2C_SLAVE, _address);
}