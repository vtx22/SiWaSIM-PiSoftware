#pragma once
#include "Configuration.hpp"
#include "IABoard.hpp"

struct CURVE
{
   //! Delay from input high to flow increase start in seconds
   float startDelay = 0;
   //! Delay from input low to flow decrease start in seconds
   float stopDelay = 0;
   //! Time it takes the flow to reach its maximum in seconds
   float riseTime = 0;
   //! Time it takes the flow to reach zero in seconds
   float fallTime = 0;
   //! Maximal flow after rise time in kg/s
   float maxFlow = 1;
} typedef CURVE;

class MaterialFlow
{
public:
   MaterialFlow(uint8_t channel);
   MaterialFlow(uint8_t channel, MATERIAL_FLOW flowType);
   ~MaterialFlow();

   void setFlowCurve(CURVE curve);
   void setFlowType(MATERIAL_FLOW flowType);
   void update(float *currentWeight, float dt);

private:
   uint8_t _channel;
   MATERIAL_FLOW _flowType;

   bool _lastPinState = false;
   float _currentFlow = 0;
   float _lastPinStateTime = 0;

   CURVE _curve;

   IABoard *_ia;
};
