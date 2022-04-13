#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "I2C.hpp"
#include "UART.hpp"
#include "GPIO.hpp"
#include "IABoard.hpp"

int main()
{
   UART uart;

   uint8_t data[3] = {0xFF, 0xEE, 0xAD};

   uart.transmitMSG(data, 3);

   printf("Waiting for message...\n");

   std::vector<uint8_t> received = uart.receiveMSG();

   printf("RECEIVED %d BYTES!\n", received.size());

   for (int i = 0; i < received.size(); i++)
   {
      printf(" %d ", received[i]);
   }
}