#pragma once
#include <vector>

#include "SIWAREX_REGISTER.hpp"
#include "Modbus.hpp"
#include "utility.hpp"

class SIWAREX
{
public:
   SIWAREX(Modbus *modbus);
   ~SIWAREX();

   float getLoadcellVoltage();

private:
   Modbus *_modbus;
};