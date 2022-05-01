#pragma once
#include "PCB.hpp"
#include "Configuration.hpp"
#include "IABoard.hpp"
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
   void bootupAnimation();
   void loadConfig();

private:
   Configuration *_config;
   PCB *_pcb;
   IABoard *_ia;
};