#pragma once
#include "I2C.hpp"
#include "utility.hpp"

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

   // Get the currently set analog output voltage
   float getAnalogVolOut(uint8_t channel);
   // Set the analog output voltage from 0 - 10V, voltage in volts
   void setAnalogVolOut(uint8_t channel, float voltage);

   // Get the currently set analog output current
   float getAnalogCurOut(uint8_t channel);
   // Set the analog output current from 4 - 20mA, current in mA
   void setAnalogCurOut(uint8_t channel, float current);

   // Get the PWM Duty Cycle for the Open Drain Output (if not used as digital out)
   float getOpenDrainPWM(uint8_t channel);
   // Set the PWM Duty Cycle (0 - 100%) for the Open Drain Output
   void setOpenDrainPWM(uint8_t channel, float dutyCycle);

   // Read all digital open drain outputs
   uint8_t getOpenDrainDOUT();
   // Get the currently set open drain digital out value
   bool getOpenDrainDOUT(uint8_t channel);
   // Set the digital open drain output
   void setOpenDrainDOUT(uint8_t channel, bool value);

   // Gets the state of a certain LED
   bool getLED(uint8_t channel);
   // Sets a certain LED Low or High
   void setLED(uint8_t channel, bool value);

private:
   I2C *_i2c;
   const uint8_t _stack = 0;
};