#include <iostream>
#include <fstream>
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
   Simulator sim;
   std::vector<float> data, x;

   sim.calibrateLCVoltage(true);
   sim.testFunction();
   data = sim.longTermTest();

   plt::figure_size(1600, 900);

   plt::plot(x, data, {{"color", "b"}, {"label", "Cell Voltage in mV"}});
   // plt::plot(x, weightData, {{"color", "r"}, {"label", "weight in kg"}});

   plt::title("Load Cell Voltage with SiWaSim");
   plt::xlabel("Time in seconds");
   plt::legend();
   plt::ylim(19.9, 20.1);
   plt::grid(true);
   plt::show();

   // sim.calibrateLCVoltage();
   // sim.testFunction();

   return 0;
}
