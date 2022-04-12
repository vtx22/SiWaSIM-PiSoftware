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
   time_sleep(0.001);
   board.setLED(1, 0);
   time_sleep(0.001);
   board.setLED(2, 0);
   time_sleep(0.001);
   board.setLED(3, 0);
   time_sleep(0.001);
   board.setLED(4, 0);

   printf("Vol 1: %d\n", board.readAnalogCurIn(1));
   /*
   printf("Vol 2: %d\n", board.getOpenDrainDOUT(2));
   printf("Vol 3: %d\n", board.getOpenDrainDOUT(3));
   printf("Vol 4: %d\n", board.getOpenDrainDOUT(4));
   */
}
