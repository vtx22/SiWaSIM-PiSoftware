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
   uint16_t calculateCRC(uint8_t *data, int length);

   UART *_uart;
   const uint8_t _address = 20;
};