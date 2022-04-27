#include "Simulator.hpp"

Simulator::Simulator()
{
   _config = new Configuration("./config.json");
}

Simulator::~Simulator()
{
}
