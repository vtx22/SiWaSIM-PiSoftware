#pragma once

#include <stdint.h>
#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <termios.h>
#include <unistd.h>
//#include <string.h>

class UART
{
public:
   UART();
   ~UART();
   bool begin();
   bool transmitMSG(uint8_t *msg, uint16_t length);
   int receiveMSG(uint8_t *msg);

private:
   int uart0 = -1;
   // std::string _dev;
   const uint8_t _messageSizeRX = 0;     // Number of bytes to wait for
   const uint8_t _messageTimeoutRX = 50; // Read Timeout in 0.1s steps
};