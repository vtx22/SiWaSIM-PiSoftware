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

   float flow = 0;

   // If the pin state has changed reset the internal timer so that rise / fall times and delays are measured
   if (pinState != _lastPinState)
   {
      _lastPinState = pinState;
      _lastPinStateTime = 0;
   }

   // Check if we are still in a rise / fall time or in a delay
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
   else if (pinState == 0 && _lastPinStateTime < _curve.fallTime)
   {
      flow = _curve.maxFlow / _curve.fallTime * (_curve.fallTime - _lastPinStateTime);
   }
   // If the pin is high and the rise time is over add the maximum flow
   // If the pin is low and the fall time is over the flow is 0 and the weight does not change
   else if (pinState == 1)
   {
      flow = _curve.maxFlow;
   }

   *currentWeight += flow * dt; // Scale with time, e.g. 1 kg/s for 0.5s equals 1 * 0.5 = 0.5kg
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