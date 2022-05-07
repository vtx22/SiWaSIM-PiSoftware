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
   data.push_back(0);
   x.push_back(0);

   for (uint8_t i = 1; i < 51; i++)
   {
      x.push_back(i / 10.f);

      data.push_back(sim.run(0.1) - data.back());

      std::this_thread::sleep_for(100ms);
   }

   plt::plot(x, data);
   plt::show();

   return 0;
}