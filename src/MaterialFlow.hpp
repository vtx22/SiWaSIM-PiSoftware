#pragma once
#include <iostream>
#include "Configuration.hpp"
#include "IABoard.hpp"

#include "Eigen/Dense"

using Eigen::MatrixXd;
using Eigen::VectorXd;

class MaterialFlow
{
public:
   MaterialFlow(uint8_t channel);
   MaterialFlow(uint8_t channel, MATERIAL_FLOW flowType);
   ~MaterialFlow();

   void setFlowCurve(CURVE curve);
   void setFlowType(MATERIAL_FLOW flowType);
   float update(float *currentWeight, float dt, bool pinState);
   void calculateFlowCurve();

private:
   uint8_t _channel;
   MATERIAL_FLOW _flowType;

   // bool _lastPinState = 0;
   float _currentFlow = 0;
   // float _lastPinStateTime = 0;

   CURVE _curve;
   QUARTIC_FUNCTION _riseCurve;

   IABoard *_ia;
};
