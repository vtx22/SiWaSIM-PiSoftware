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
   board.setAnalogVolOut(1, 4.22);
   board.setAnalogVolOut(2, 4.87);
   board.setAnalogVolOut(3, 4.99);
   board.setAnalogVolOut(4, 8.22);
   printf("Vol 1: %f\n", board.getAnalogVolOut(1));
   printf("Vol 2: %f\n", board.getAnalogVolOut(2));
   printf("Vol 3: %f\n", board.getAnalogVolOut(3));
   printf("Vol 4: %f\n", board.getAnalogVolOut(4));
}
