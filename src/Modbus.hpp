#pragma once
#include <vector>
#include <iostream>
#include "Configuration.hpp"

#include "UART.hpp"

class Modbus
{
public:
   Modbus();
   ~Modbus();

   void writeRegister(uint16_t startRegister, uint16_t value);
   void writeRegisters(uint16_t startRegister, std::vector<uint16_t> values);

   std::vector<uint8_t> requestRegisters(uint16_t startRegister, uint16_t length);
   uint16_t requestRegister(uint16_t startRegister);

   std::vector<uint8_t> receiveResponse();

private:
   uint16_t calculateCRC(uint8_t *data, int length);

   UART *_uart;
   const uint8_t _address = SIWAREX_ADDRESS;
};