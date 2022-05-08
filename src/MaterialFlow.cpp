#include "MaterialFlow.hpp"

MaterialFlow::MaterialFlow(uint8_t channel) : _channel(channel)
{
   _ia = new IABoard();
}

MaterialFlow::MaterialFlow(uint8_t channel, MATERIAL_FLOW flowType) : _channel(channel), _flowType(flowType)
{
   _ia = new IABoard();
}

MaterialFlow::~MaterialFlow()
{
}

float MaterialFlow::update(float *currentWeight, float dt, bool pinState)
{
   if (_flowType == MATERIAL_FLOW::NONE)
   {
      return 0;
   }

   //_ia->digitalRead(_channel);

   if (_lastPinStateTime > 2)
   {
      pinState = 0;
   }

   float flow = 0;

   // If the pin changed reset the internal timer so that rise / fall times and delays are measures
   if (pinState != _lastPinState)
   {
      _lastPinState = pinState;
      _lastPinStateTime = 0;
   }

   // If the state has not changed, check if we are still in a rise / fall time
   if (pinState == 1 && _lastPinStateTime < _curve.startDelay)
   {
      flow = 0;
   }
   else if (pinState == 1 && _lastPinStateTime <= _curve.riseTime)
   {
      flow = _curve.maxFlow / _curve.riseTime * _lastPinStateTime;
   }
   else if (pinState == 0 && _lastPinState < _curve.stopDelay)
   {
      flow = _curve.maxFlow;
   }
   else if (pinState == 0 && _lastPinStateTime <= _curve.fallTime)
   {
      flow = _curve.maxFlow / _curve.fallTime * (_curve.fallTime - _lastPinStateTime);
   }
   // If the pin is high and the rise time is over add the maximum flow
   // If the pin is low and the fall time is over the flow is 0 and the weight does not change
   else if (pinState == 1)
   {
      flow = _curve.maxFlow;
   }
   std::cout << "FLOW is: " << flow << std::endl;
   *currentWeight += flow * dt;
   _lastPinStateTime += dt;

   return flow;
}

void MaterialFlow::setFlowType(MATERIAL_FLOW flowType)
{
   _flowType = flowType;
}

void MaterialFlow::setFlowCurve(CURVE curve)
{
   _curve = curve;
}