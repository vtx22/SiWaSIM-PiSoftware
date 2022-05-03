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
#include "Simulator.hpp"

int main()
{
   Simulator sim;
   sim.bootupAnimation();

   while (true)
   {
      sim.run();
      std::this_thread::sleep_for(1s);
   }

   return 0;
}