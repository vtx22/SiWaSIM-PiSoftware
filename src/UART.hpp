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
   UART(std::string dev);
   ~UART();
   bool begin();

private:
   int uart0 = -1;
   std::string _dev;
};