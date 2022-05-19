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
#include "Modbus.hpp"

#include "matplotlib/matplotlibcpp.h"
namespace plt = matplotlibcpp;

int main()
{

   // Simulator sim;
   Modbus modbus;

   modbus.transmitRequest(3046, 2);
   modbus.receiveResponse();

   /*

   // sim.bootupAnimation();
   float weight = 0;
   sim.bootupAnimation();
   std::vector<float> data, x, weightData;
   data.push_back(0);
   weightData.push_back(0);
   x.push_back(-0.1);

   for (int i = 0; i < 500; i++)
   {
      x.push_back(i / 100.f);

      data.push_back(sim.run(RUN_MODE::PASSIVE, 0.01, &weight));
      weightData.push_back(weight);

      std::cout << "=========" << std::endl;
      std::cout << "i:      " << i << std::endl;
      std::cout << "flow:   " << data.back() << std::endl;
      std::cout << "weight: " << weightData.back() << std::endl;
      std::cout << "=========" << std::endl;
      // std::this_thread::sleep_for(1ms);
   }

   plt::figure_size(1600, 900);

   plt::plot(x, data, {{"color", "b"}, {"label", "flow in kg/s"}});
   plt::plot(x, weightData, {{"color", "r"}, {"label", "weight in kg"}});

   plt::title("First flow test, step time 10ms");
   plt::xlabel("Time in seconds");
   plt::legend();
   plt::grid(true);
   plt::show();
   */

   // sim.calibrateLCVoltage();
   // sim.testFunction();

   return 0;
}
