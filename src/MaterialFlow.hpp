#pragma once
#include "Configuration.hpp"
#include "IABoard.hpp"

class MaterialFlow
{
public:
   MaterialFlow(uint8_t channel);
   MaterialFlow(uint8_t channel, MATERIAL_FLOW flowType);
   ~MaterialFlow();

   void setFlowType(MATERIAL_FLOW flowType);
   void update(float *currentWeight);

private:
   uint8_t _channel;
   MATERIAL_FLOW _flowType;
   bool _lastPinState = false;
   float _currentFlow = 0;

   IABoard *_ia;
};