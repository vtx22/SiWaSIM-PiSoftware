#include "SIWAREX.hpp"

SIWAREX::SIWAREX(Configuration *config) : _config(config)
{
   _modbus = new Modbus();
}

SIWAREX::SIWAREX()
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

   if (msg[1] != 0x03)
   {
      // If the response is an error just return the 3 important bytes
      msg.resize(3);
      printf("MODBUS ERROR: Request Code: 0x03, Error Code: 0x%02X 0x%02X\n", msg[1], msg[2]);
   }
   else
   {
      msg.pop_back();
      msg.pop_back();
      msg.erase(msg.begin());
      msg.erase(msg.begin());
      msg.erase(msg.begin());
   }

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
   _modbus->writeRegister(CMD1_CODE - 1, 2000 + dataset);
   _modbus->writeRegister(CMD1_TRIGGER - 1, 0x01);
   _modbus->writeRegister(startRegister - 1, value);
   _modbus->writeRegister(CMD1_CODE - 1, 4000 + dataset);
   _modbus->writeRegister(CMD1_TRIGGER - 1, 0x01);
}