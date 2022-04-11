#pragma once
#include "I2C.hpp"

class IABoard
{
public:
   IABoard();
   ~IABoard();

   void detectBoard();
   uint8_t digitalRead();
   bool digitalRead(uint8_t channel);

private:
   I2C *_i2c;
   const uint8_t _stack = 0;
};