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
   float weight = 0;
   sim.bootupAnimation();
   std::vector<float> data, x, weightData;
   data.push_back(0);
   weightData.push_back(0);
   x.push_back(-0.1);

   for (uint8_t i = 0; i < 50; i++)
   {
      x.push_back(i / 10.f);

      data.push_back(sim.run(0.1, &weight));
      weightData.push_back(weight);
      std::this_thread::sleep_for(100ms);
   }
   plt::figure_size(1600, 900);

   plt::plot(x, data, {{"color", "b"}, {"label", "flow in kg/s"}});
   plt::plot(x, weightData, {{"color", "r"}, {"label", "weight in kg"}});

   plt::title("First flow to weight test");
   plt::xlabel("Time in seconds");
   plt::legend();
   plt::show();

   return 0;
}