#pragma once
#include <vector>

#include "SIWAREX_REGISTER.hpp"
#include "Configuration.hpp"
#include "Modbus.hpp"
#include "utility.hpp"

class SIWAREX
{
public:
   SIWAREX();
   SIWAREX(Configuration *config);
   ~SIWAREX();

   float getLoadcellVoltage();
   float getLoadcellImpedance();

   void setMODBUSDelay(uint16_t delay);
   uint16_t getMODBUSDelay();

   std::vector<uint8_t> requestRegisters(uint16_t startRegister, uint16_t length);

   MODBUS_PARAMETER getParameter(MODBUS_PARAMETER param);

   void writeRegisters(uint8_t dataset, uint16_t startRegister, std::vector<uint16_t> values);
   void writeRegister(uint8_t dataset, uint16_t startRegister, uint16_t value);

   float requestFloat(uint16_t startRegister);
   void writeFloat(float value);

   void setServiceMode(bool value);

private:
   Modbus *_modbus;
   Configuration *_config;
};