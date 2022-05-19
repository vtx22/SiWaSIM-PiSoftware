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
   _modbus->transmitRequest(LOADCELL_VOLTAGE, 2);
   std::vector<uint8_t> msg = _modbus->receiveResponse();

   return bytesToFloat(msg[2], msg[3], msg[4], msg[5]);
}