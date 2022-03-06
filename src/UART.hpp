#pragma once

#include <stdint.h>
#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <termios.h>
#include <unistd.h>
#include <string.h>

class UART
{
public:
   UART();
   ~UART();
   bool begin();
   bool transmitMSG(uint8_t *msg, uint16_t length);

private:
   int uart0 = -1;
   //std::string _dev;
   const uint16_t _messageSizeRX = 10;
};