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
   IABoard board;

   board.detectBoard();

   printf("Vol 1: %f\n", board.getLED(1));
   printf("Vol 2: %f\n", board.getLED(2));
   printf("Vol 3: %f\n", board.getLED(3));
   printf("Vol 4: %f\n", board.getLED(4));
}
