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
   printf("Channel 1 is: %d", board.digitalRead(1));
}
