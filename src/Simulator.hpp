#pragma once
#include "PCB.hpp"
#include "Configuration.hpp"

class Simulator
{
public:
   Simulator();
   ~Simulator();

   void setWeightPER(float percentage); // Set the weight from 0 - 100% of nominal Load
   void setWeightKG(float kg);          // Set the weight in kg

private:
   Configuration *_config;
   PCB *_pcb;
};