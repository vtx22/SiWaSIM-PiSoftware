#pragma once
#include "I2C.hpp"

class IABoard
{
public:
   IABoard();
   ~IABoard();

   // Check if the board is responding
   bool detectBoard();

   // Read all digital inputs
   uint8_t digitalRead();
   // Read digital input of certain channel 1 - 4
   bool digitalRead(uint8_t channel);

   uint16_t readTransistions(uint8_t channel);

private:
   I2C *_i2c;
   const uint8_t _stack = 0;
};