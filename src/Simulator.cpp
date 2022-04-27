#include "Simulator.hpp"

Simulator::Simulator()
{
   _config = new Configuration("./config.json");
   _pcb = new PCB(_config);
}

Simulator::~Simulator()
{
}
