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
#include "SIWAREX.hpp"

#include "matplotlib/matplotlibcpp.h"
namespace plt = matplotlibcpp;

int main()
{

   // Simulator sim;

   SIWAREX siwarex;
   std::vector<float> data, x;
   int cnt = 0;
   while (cnt < 60 * 30)
   {
      float voltage = siwarex.getLoadcellVoltage();
      printf("Voltage is: %f mV\n", voltage);
      x.push_back(cnt);
      data.push_back(voltage);
      delay(1000ms);
      cnt++;
   }

   plt::figure_size(1600, 900);

   plt::plot(x, data, {{"color", "b"}, {"label", "Cell Voltage in mV"}});
   // plt::plot(x, weightData, {{"color", "r"}, {"label", "weight in kg"}});

   plt::title("Load Cell Voltage with analog bridge");
   plt::xlabel("Time in seconds");
   plt::legend();
   plt::grid(true);
   plt::show();

   // sim.calibrateLCVoltage();
   // sim.testFunction();

   return 0;
}
