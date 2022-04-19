#include "PCB.hpp"

PCB::PCB()
{
   _gpio = new GPIO();

   // Set all Switch Pins as Output
   _gpio->setPinMode(PIN_LED_READY, PI_OUTPUT);
   _gpio->setPinMode(PIN_LED_BUSY, PI_OUTPUT);
   _gpio->setPinMode(PIN_LED_FAULT, PI_OUTPUT);

   _gpio->setPinMode(PIN_POWERSW1, PI_OUTPUT);
   _gpio->setPinMode(PIN_POWERSW2, PI_OUTPUT);

   _gpio->setPinMode(PIN_IMPEDANCE1, PI_OUTPUT);
   _gpio->setPinMode(PIN_IMPEDANCE2, PI_OUTPUT);

   _gpio->setPinMode(PIN_EXTRASW1, PI_OUTPUT);
   _gpio->setPinMode(PIN_EXTRASW2, PI_OUTPUT);
}

PCB::~PCB()
{
}

void PCB::ledReady(bool state)
{
   _gpio->writePin(PIN_LED_READY, state);
}

void PCB::ledBusy(bool state)
{
   _gpio->writePin(PIN_LED_BUSY, state);
}

void PCB::ledFault(bool state)
{
   _gpio->writePin(PIN_LED_FAULT, state);
}

void PCB::setImpedance(IMPEDANCE impedance)
{
   switch (impedance)
   {
   default:
   case OPEN:
      _gpio->writePin(PIN_IMPEDANCE1, 0);
      _gpio->writePin(PIN_IMPEDANCE2, 0);
      break;
   case NOMINAL:
      _gpio->writePin(PIN_IMPEDANCE1, 1);
      _gpio->writePin(PIN_IMPEDANCE2, 0);
      break;
   case SHORT:
      _gpio->writePin(PIN_IMPEDANCE1, 0);
      _gpio->writePin(PIN_IMPEDANCE2, 1);
      break;
   }
}

void PCB::setEXTRASW1(bool state)
{
   _gpio->writePin(PIN_EXTRASW1, state);
}

void PCB::setEXTRASW2(bool state)
{
   _gpio->writePin(PIN_EXTRASW2, state);
}

void PCB::setPOWERSW1(bool state)
{
   _gpio->writePin(PIN_POWERSW1, state);
}

void PCB::setPOWERSW2(bool state)
{
   _gpio->writePin(PIN_POWERSW2, state);
}