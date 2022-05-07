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

#include "matplotlib/matplotlibcpp.h"
namespace plt = matplotlibcpp;

int main()
{
   Simulator sim;
   // sim.bootupAnimation();

   sim.bootupAnimation();
   std::vector<float> data, x;

   for (uint8_t i = 0; i < 50; i++)
   {
      x.push_back(i / 10.f);
      data.push_back(sim.run(0.1));
      std::this_thread::sleep_for(100ms);
   }

   plt::plot(x, data);
   plt::show();

   return 0;
}