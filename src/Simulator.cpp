#include "Simulator.hpp"

Simulator::Simulator()
{
   _config = new Configuration("./config.json");
   _pcb = new PCB(_config);
}

Simulator::~Simulator()
{
}

void Simulator::setWeightPER(float percentage)
{
   float voltage = 0.f;

   switch (_config->cellMode)
   {
   default:
   case NORMAL:
      voltage = _config->cellCharecteristic * _config->exc_voltage;
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