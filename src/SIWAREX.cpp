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
   _modbus->transmitRequest(startRegister, length);
   std::vector<uint8_t> msg = _modbus->receiveResponse();

   msg.erase(msg.size() - 1);
   msg.erase(msg.size() - 1);

   msg.erase(msg.begin());
   msg.erase(msg.begin());
   msg.erase(msg.begin());

   return msg;
}