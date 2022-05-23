#pragma once
#include <stdlib.h>
#include <vector>

struct PARAMETER
{
   uint16_t startRegister;
   uint8_t length;
   // 0 = float, 1 = uint, 2 = int
   uint8_t type;

} typedef PARAMETER;

struct DATASET
{
   uint16_t startRegister;
   uint8_t length;
   std::vector<PARAMETER> params;
} typedef DATASET;

#define LOADCELL_IMPEDANCE 3056
#define LOADCELL_VOLTAGE 3058
