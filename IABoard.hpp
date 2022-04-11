#pragma once
#include "I2C.hpp"

class IABoard
{
public:
   IABoard();
   ~IABoard();

   void detectBoard();

private:
   I2C _i2c;
   const uint8_t _stack = 0;
};