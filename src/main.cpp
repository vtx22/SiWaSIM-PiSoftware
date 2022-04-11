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
   board.setOpenDrainPWM(1, 10);
   board.setOpenDrainPWM(2, 20);
   board.setOpenDrainPWM(3, 81.3);
   board.setOpenDrainPWM(4, 99.1);
   printf("Vol 1: %f\n", board.getOpenDrainPWM(1));
   printf("Vol 2: %f\n", board.getOpenDrainPWM(2));
   printf("Vol 3: %f\n", board.getOpenDrainPWM(3));
   printf("Vol 4: %f\n", board.getOpenDrainPWM(4));

   float duty = 0;
   while (true)
   {
      board.setOpenDrainPWM(1, duty);
      duty++;

      if (duty >= 100)
      {
         duty = 0;
      }
      time_sleep(0.05);
   }
}
