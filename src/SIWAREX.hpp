#pragma once
#include <vector>

#include "SIWAREX_REGISTER.hpp"
#include "Modbus.hpp"
#include "utility.hpp"

class SIWAREX
{
public:
   SIWAREX();
   ~SIWAREX();

   float getLoadcellVoltage();
   float getLoadcellImpedance();

   void setMODBUSDelay(uint16_t delay);

   std::vector<uint8_t> requestRegisters(uint16_t startRegister, uint16_t length);

private:
   float requestFloat(uint16_t startRegister);

   Modbus *_modbus;
};