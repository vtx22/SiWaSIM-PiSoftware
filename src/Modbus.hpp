#pragma once
#include <vector>
#include <iostream>

#include "UART.hpp"

class Modbus
{
public:
   Modbus();
   ~Modbus();

   void transmitRequest(uint16_t startRegister, uint16_t length);
   void receiveResponse();

private:
   uint16_t calculateCRC(std::vector<uint8_t> data);

   UART *_uart;
   const uint8_t _address = 0x20;
};