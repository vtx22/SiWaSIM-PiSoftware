#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

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
   uint8_t rx[100];
   int received = uart.receiveMSG(rx);

   printf("RECEIVED %d BYTES!\n", received);

   for (int i = 0; i < 3; i++)
   {
      printf(" %d ", rx[i]);
   }
}