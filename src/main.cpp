#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "I2C.hpp"
#include "UART.hpp"
#include "GPIO.hpp"

int main()
{
   I2C test("/dev/ttyAMA0", 0x50);

   test.writeData(0x00, 0xFF);
}
