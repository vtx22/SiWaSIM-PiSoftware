#pragma once
#include "PCB.hpp"
#include "Configuration.hpp"
#include "IABoard.hpp"
#include "MaterialFlow.hpp"

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

class Simulator
{
public:
   Simulator();
   ~Simulator();

   void setWeightPER(float percentage); // Set the weight from 0 - 100% of nominal Load
   void setWeightKG(float kg);          // Set the weight in kg

   void setVelocity(float meterspersecond);
   void setVelocityPER(float percentage);
   void setVelocityFRQ(float frequency);

   void setImpedance(IMPEDANCE impedance);

   void bootupAnimation();
   void reloadConfig();

   float run(RUN_MODE runMode, float timestep, float *weight);
   float runPassive(float timestep, float *weight);

private:
   Configuration *_config;
   PCB *_pcb;
   IABoard *_ia;

   MaterialFlow *_materialFlows[4];
};