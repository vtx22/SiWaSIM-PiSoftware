#pragma once
#include "PCB.hpp"
#include "Configuration.hpp"
#include "IABoard.hpp"
#include "MaterialFlow.hpp"
#include "SIWAREX.hpp"

#include <chrono>
#include <thread>
#include <fstream>

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

   void testFunction();

   float run(RUN_MODE runMode, float timestep, float *weight);
   void runPassive(float timestep, float *weight);

   void calibrateLCVoltage(bool autoCalib);
   std::vector<float> longTermTest();

private:
   Configuration *_config;
   PCB *_pcb;
   IABoard *_ia;
   SIWAREX *_siwarex;

   MaterialFlow *_materialFlows[4];
};