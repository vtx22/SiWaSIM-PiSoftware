#pragma once
#include <stdint.h>
#include <vector>

struct MODBUS_PARAMETER
{
   uint16_t startRegister;
   // 0 = float, 1 = uint, 2 = int, 3=ushort, 4=short, 5=bool
   uint8_t type;

} typedef MODBUS_PARAMETER;

struct MODBUS_DATASET
{
   uint8_t dsName;
   uint16_t startRegister;
   std::vector<MODBUS_PARAMETER> params;
} typedef MODBUS_DATASET;

#define LOADCELL_IMPEDANCE 3056
#define LOADCELL_VOLTAGE 3058
#define MODBUS_DELAY 1483
