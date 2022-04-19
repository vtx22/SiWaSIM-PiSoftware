#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "I2C.hpp"
#include "UART.hpp"
#include "GPIO.hpp"
#include "IABoard.hpp"
#include "PCB.hpp"

int main()
{
   PCB pcb;
   bool state = false;
   while (true)
   {
      pcb.ledBusy(state);
      state = !state;
      time_sleep(1);
   }
}