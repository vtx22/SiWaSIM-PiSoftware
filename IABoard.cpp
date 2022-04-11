#include "IABoard.hpp"

IABoard::IABoard()
{
   _i2c = new I2C("/dev/i2c-1", 0x50);
}

IABoard::~IABoard()
{
   delete _i2c;
}

void IABoard::detectBoard()
{
   _i2c.writeData(0x78);
   if (_i2c.readData() == 0x01)
   {
      printf("IA-Board: Board detected!\n");
      return;
   }

   printf("IA-Board ERROR: No Board detected!\n");
}