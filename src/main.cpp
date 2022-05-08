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

   plt::figure_size(1600, 900);
   for (uint8_t i = 0; i < 50; i++)
   {
      x.push_back(i / 10.f);

      data.push_back(sim.run(RUN_MODE::PASSIVE, 0.1, &weight));
      weightData.push_back(weight);
      if (i % 10 == 0)
      {
         plt::clf();

         plt::plot(x, data, {{"color", "b"}, {"label", "flow in kg/s"}});
         plt::plot(x, weightData, {{"color", "r"}, {"label", "weight in kg"}});

         plt::title("First flow test, step time 100ms");
         plt::xlabel("Time in seconds");
         plt::legend();
         plt::grid(true);
         plt::pause(0.01);
      }
      std::this_thread::sleep_for(100ms);
   }
   plt::clf();

   plt::plot(x, data, {{"color", "b"}, {"label", "flow in kg/s"}});
   plt::plot(x, weightData, {{"color", "r"}, {"label", "weight in kg"}});

   plt::title("First flow test, step time 100ms");
   plt::xlabel("Time in seconds");
   plt::legend();
   plt::grid(true);
   plt::show();

   return 0;
}