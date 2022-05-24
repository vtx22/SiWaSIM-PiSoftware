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
   // return requestFloat(LOADCELL_IMPEDANCE);

   std::vector<uint8_t> data = requestRegisters(LOADCELL_VOLTAGE - 2, 4);
   for (auto const &i : data)
   {
      printf("Data: %02X\n", i);
   }
}

float SIWAREX::requestFloat(uint16_t startRegister)
{
   std::vector<uint8_t> msg = requestRegisters(startRegister, 2);
   return bytesToFloat(&msg[0]);
}

std::vector<uint8_t> SIWAREX::requestRegisters(uint16_t startRegister, uint16_t length)
{
   _modbus->transmitRequest(startRegister, length);
   std::vector<uint8_t> msg = _modbus->receiveResponse();

   msg.pop_back();
   msg.pop_back();
   msg.erase(msg.begin());
   msg.erase(msg.begin());
   msg.erase(msg.begin());

   return msg;
}