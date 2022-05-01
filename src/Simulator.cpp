#include "Simulator.hpp"

Simulator::Simulator()
{
   _config = new Configuration("./config.json");
   _pcb = new PCB(_config);
   _ia = new IABoard();
}

Simulator::~Simulator()
{
   delete _config;
   delete _pcb;
   delete _ia;
}

void Simulator::setWeightPER(float percentage)
{
   float voltage = 0.f;

   switch (_config->cellMode)
   {
   default:
   case NORMAL:
      // Max differential voltage (e.g. 4mV/V * 10V = 40mV)
      voltage = _config->cellCharecteristic * _config->exc_voltage;
      // Do not allow overload
      constrainMax(percentage, 1);
      break;
   case OVERLOAD:
      break;
   }

   voltage *= percentage;

   _pcb->setLoadcellVoltage(voltage);
}

void Simulator::setWeightKG(float kg)
{
   setWeightPER(kg / _config->load_weight);
}

void Simulator::bootupAnimation()
{
   _ia->setLED(1, 0);
   _ia->setLED(2, 0);
   _ia->setLED(3, 0);
   _ia->setLED(4, 0);
   std::this_thread::sleep_for(2s);
   _ia->setLED(1, 1);
   std::this_thread::sleep_for(100ms);
   _ia->setLED(2, 1);
   std::this_thread::sleep_for(100ms);
   _ia->setLED(3, 1);
   std::this_thread::sleep_for(100ms);
   _ia->setLED(4, 1);
   std::this_thread::sleep_for(100ms);
}

void Simulator::loadConfig()
{
   _config->loadConfiguration();
}