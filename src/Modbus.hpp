#pragma once
#include <vector>
#include <iostream>

#include "UART.hpp"

class Modbus
{
public:
   Modbus(UART *uart);
   ~Modbus();

   void transmitRequest(uint16_t register, uint16_t length);
   void receiveResponse();

private:
   uint16_t calculateCRC(std::vector<uint8_t> data);

   UART *_uart;
   const uint8_t _address = 0x20;
};