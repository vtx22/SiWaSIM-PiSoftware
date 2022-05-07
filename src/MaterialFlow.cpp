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

void MaterialFlow::update(float *currentWeight, float dt)
{
   if (_flowType == MATERIAL_FLOW::NONE)
   {
      return;
   }

   bool pinState = _ia->digitalRead(_channel);

   if (pinState != _lastPinState)
   {
      if (!pinState)
      {
      }

      _lastPinState = pinState;
      _lastPinStateTime = 0;
      return;
   }

   // If the state has not changed, check if we are still in a rise / fall time
   if (pinState == 1 && _lastPinStateTime < _curve.riseTime)
   {
      *currentWeight += _curve.maxFlow / _curve.riseTime * _lastPinStateTime * dt;
   }
   if (pinState == -1 && _lastPinStateTime < _curve.fallTime)
   {
      *currentWeight += _curve.maxFlow / _curve.fallTime * (_curve.fallTime - _lastPinStateTime) * dt;
   }

   // If the pin is high and the rise time is over add the maximum flow
   // If the pin is low and the fall time is over the flow is 0 and the weight does not change
   if (pinState == 1)
   {
      *currentWeight += _curve.maxFlow * dt;
   }

   _lastPinStateTime += dt;
}

void MaterialFlow::setFlowType(MATERIAL_FLOW flowType)
{
   _flowType = flowType;
}

void MaterialFlow::setFlowCurve(CURVE curve)
{
   _curve = curve;
}