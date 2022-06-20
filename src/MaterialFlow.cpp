#include "MaterialFlow.hpp"

MaterialFlow::MaterialFlow(uint8_t channel) : _channel(channel)
{
   _ia = new IABoard();
   _flowType = MATERIAL_FLOW::NONE;
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
   /*
   if (_flowType == MATERIAL_FLOW::NONE)
   {
      return 0;
   }
   */
   static bool _lastPinState = 0;
   static float _lastPinStateTime = 0;
   float flow = 0;
   // If the pin state has changed reset the internal timer so that rise / fall times and delays are measured
   if (pinState != _lastPinState)
   {
      _lastPinState = pinState;
      _lastPinStateTime = 0;
      printf("IF0\n");
   }

   // Check if we are still in a rise / fall time or in a delay
   if (pinState == 1 && _lastPinStateTime < _curve.startDelay)
   {
      printf("IF1\n");
      flow = 0;
   }
   else if (pinState == 1 && _lastPinStateTime < _curve.riseTime)
   {
      printf("IF2\n");
      flow = _curve.maxFlow / _curve.riseTime * _lastPinStateTime;
   }
   else if (pinState == 0 && _lastPinStateTime < _curve.stopDelay)
   {
      printf("IF3\n");
      flow = _curve.maxFlow;
   }
   else if (pinState == 0 && _lastPinStateTime < _curve.fallTime)
   {
      printf("IF4\n");
      flow = _curve.maxFlow / _curve.fallTime * (_curve.fallTime - _lastPinStateTime);
   }
   // If the pin is high and the rise time is over add the maximum flow
   // If the pin is low and the fall time is over the flow is 0 and the weight does not change
   else if (pinState == 1)
   {
      printf("IF5\n");
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
   calculateFlowCurve();
}

void MaterialFlow::calculateFlowCurve()
{
   QUARTIC_FUNCTION flow;

   // E and D are 0 because f(0) = 0 and f'(0) = 0
   flow.e = flow.d = 0;

   // Fill the solution vector
   VectorXd y(3);
   y(0) = _curve.halfRise * _curve.maxFlow;
   y(1) = _curve.maxFlow;
   y(2) = 0;

   float tRise2 = _curve.riseTime * _curve.riseTime;
   float tRise3 = tRise2 * _curve.riseTime;
   float tRise4 = tRise2 * tRise2;

   MatrixXd m(3, 3);
   m(0, 0) = tRise4 / 16.f;
   m(0, 1) = tRise3 / 8.f;
   m(0, 2) = tRise2 / 4.f;
   m(1, 0) = tRise4;
   m(1, 1) = tRise3;
   m(1, 2) = tRise2;
   m(2, 0) = 4 * tRise3;
   m(2, 1) = 3 * tRise2;
   m(2, 2) = 2 * _curve.riseTime;

   // Vector to store function coefficients
   VectorXd coeff = m.colPivHouseholderQr().solve(y);

   flow.a = coeff(0);
   flow.b = coeff(1);
   flow.c = coeff(2);

   printf("A: %f, B: %f, C: %f\n", flow.a, flow.b, flow.c);

   _riseCurve = flow;
}