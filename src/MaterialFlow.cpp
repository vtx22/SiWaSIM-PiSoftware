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
   static bool lastPinState = 0;
   static float lastPinStateTime = _curve.riseTime * 2;
   static float flow = 0;
   static float stateChangeFlow = 0;
   // If the pin state has changed reset the internal timer so that rise / fall times and delays are measured
   if (pinState != lastPinState)
   {
      stateChangeFlow = flow;
      lastPinState = pinState;
      lastPinStateTime = 0;
   }

   if (pinState == 1 && lastPinStateTime > _curve.riseTime)
   {
      flow = _curve.maxFlow;
   }
   if (pinState == 1 && lastPinStateTime < _curve.riseTime)
   {
      flow = stateChangeFlow * lastPinStateTime / _curve.riseTime;
   }
   if (pinState == 0 && lastPinStateTime > _curve.fallTime)
   {
      flow = 0;
   }
   if (pinState == 0 && lastPinStateTime < _curve.fallTime)
   {
      flow = stateChangeFlow * (_curve.fallTime - lastPinStateTime) / _curve.fallTime;
   }

   *currentWeight += flow * dt; // Scale with time, e.g. 1 kg/s for 0.5s equals 1 * 0.5 = 0.5kg
   lastPinStateTime += dt;
   printf("FLOW: %f\n", flow);
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