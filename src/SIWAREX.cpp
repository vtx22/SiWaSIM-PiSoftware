#include "SIWAREX.hpp"

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
   _modbus->transmitRequest(startRegister, 2);
   std::vector<uint8_t> msg = _modbus->receiveResponse();
   return bytesToFloat(&msg[3]);
}

std::vector<uint8_t> SIWAREX::requestRegisters(uint16_t startRegister, uint16_t length)
{
   std::vector<uint8_t> data;

   for (uint16_t i = 0; i < length; i++)
   {
      _modbus->transmitRequest(startRegister + i, 1);
      std::vector<uint8_t> msg = _modbus->receiveResponse();
      data.push_back(msg[0]);
      data.push_back(msg[1]);
   }

   return data;
}