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
   std::vector<uint8_t> msg = requestRegisters(startRegister, 2);

   return bytesToFloatSWRX(&msg[0]);
}

std::vector<uint8_t> SIWAREX::requestRegisters(uint16_t startRegister, uint16_t length)
{
   _modbus->transmitRequest(startRegister - 1, length);
   std::vector<uint8_t> msg = _modbus->receiveResponse();

   msg.pop_back();
   msg.pop_back();
   msg.erase(msg.begin());
   msg.erase(msg.begin());
   msg.erase(msg.begin());

   return msg;
}