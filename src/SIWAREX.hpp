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

private:
   float requestFloat(uint16_t startRegister);

   std::vector<uint8_t> requestRegisters(uint16_t startRegister, uint16_t length);

   Modbus *_modbus;
};