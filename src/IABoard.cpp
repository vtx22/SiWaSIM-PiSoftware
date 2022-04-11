#include "IABoard.hpp"

IABoard::IABoard()
{
   _i2c = new I2C("/dev/i2c-1", 0x50);
}

IABoard::~IABoard()
{
   delete _i2c;
}

bool IABoard::detectBoard()
{
   _i2c->writeData(0x78);
   if (_i2c->readData() == 0x01)
   {
      printf("IA-Board: Board detected!\n");
      return true;
   }

   printf("IA-Board ERROR: No Board detected!\n");
   return false;
}

uint8_t IABoard::digitalRead()
{
   _i2c->writeData(0x03);
   return _i2c->readData();
}

bool IABoard::digitalRead(uint8_t channel)
{
   if (channel > 4 || channel < 1)
   {
      printf("IA-Board ERROR: Channel out of range! Allowed: 1 - 4\n");
      return false;
   }

   uint8_t data = digitalRead();

   return (data & channel);
}
// 1=0x6A 2=0x6C 3=0x6E 4=0x70
uint16_t IABoard::readTransistions(uint8_t channel)
{
   if (channel > 4 || channel < 1)
   {
      printf("IA-Board ERROR: Channel out of range! Allowed: 1 - 4\n");
      return 0;
   }

   _i2c->writeData(0x6A + 2 * (channel - 1));
   uint8_t data[2] = {0x00, 0x00};
   _i2c->readData(data, 2);

   uint16_t counts = data[0] + (data[1] << 8);
}