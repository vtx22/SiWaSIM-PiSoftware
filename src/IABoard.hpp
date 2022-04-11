#pragma once
#include "I2C.hpp"

enum TRANSITION
{
   DISABLE = 0x00,
   RISING = 0x01,
   FALLING = 0x02,
   BOTH = 0x03,
   UNDEFINED = 0x04
} typedef TRANSITION;

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
   TRANSITION getTransistionType(uint8_t channel);
   void setTransistionType(uint8_t channel, TRANSITION tran);
   void resetTransitions(uint8_t channel);

   float getAnalogVolOut(uint8_t channel);
   void setAnalogVolOut(uint8_t channel, float voltage);

private:
   I2C *_i2c;
   const uint8_t _stack = 0;
};