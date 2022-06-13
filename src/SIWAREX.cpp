#include "SIWAREX.hpp"

SIWAREX::SIWAREX(Configuration *config) : _config(config)
{
   _modbus = new Modbus();
}

SIWAREX::~SIWAREX()
{
   delete _modbus;
}

float SIWAREX::getLoadcellVoltage()
{
   return requestFloat(LOADCELL_VOLTAGE);
}

float SIWAREX::getLoadcellImpedance()
{
   return requestFloat(LOADCELL_IMPEDANCE);
}

float SIWAREX::requestFloat(uint16_t startRegister)
{
   std::vector<uint8_t> msg = requestRegisters(startRegister, 2);

   return bytesToFloatSWRX(&msg[0]);
}

void SIWAREX::setMODBUSDelay(uint16_t delay)
{
   _modbus->writeRegister(MODBUS_DELAY, delay);
}

uint16_t SIWAREX::getMODBUSDelay()
{
   std::vector<uint8_t> msg = requestRegisters(MODBUS_DELAY, 1);

   return (uint16_t)((msg[0] << 8) + msg[1]);
}

std::vector<uint8_t> SIWAREX::requestRegisters(uint16_t startRegister, uint16_t length)
{
   std::vector<uint8_t> msg = _modbus->requestRegisters(startRegister - 1, length);

   msg.pop_back();
   msg.pop_back();
   msg.erase(msg.begin());
   msg.erase(msg.begin());
   msg.erase(msg.begin());

   return msg;
}

MODBUS_PARAMETER SIWAREX::getParameter(MODBUS_PARAMETER param)
{
   uint16_t length = 0;
   switch (param.type)
   {
   case 0:
   case 1:
      length = 2;
      break;
   case 3:
   case 4:
   default:
      length = 1;
      break;
   }

   // param.value = requestRegisters(param.startRegister, length))[0];
   return param;
}

void SIWAREX::writeRegister(uint8_t dataset, uint16_t startRegister, uint16_t value)
{
   _modbus->writeRegisters(CMD1_CODE - 1, std::vector<uint16_t>{2000 + dataset, 0x01});
   std::this_thread::sleep_for(200ms);
   _modbus->writeRegister(startRegister, value);
   std::this_thread::sleep_for(200ms);
   _modbus->writeRegisters(CMD1_CODE - 1, std::vector<uint16_t>{4000 + dataset, 0x01});
}