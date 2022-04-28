#include "PCB.hpp"

PCB::PCB(Configuration *config) : _config(config)
{
   _gpio = new GPIO();
   _ia = new IABoard();

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
   delete _gpio;
   delete _ia;
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

void PCB::setLoadcellVoltage(float voltage)
{
   // Restrain voltage to the maximum voltage (limited by the PCB design)
   constrainMax(voltage, _config->max_diff_voltage);

   float addvol = 0.f;

   // Calculate the IA-Board Analog Out Voltage so that the SIG+- output matches the wanted voltage
   switch (_config->cellMode)
   {
   default:
   case NORMAL:
      addvol = voltage * _config->addvol_ratio / 1000.f;
      break;
   }

   // Correction because if EXC is lower than expected the differential voltage has to decrease
   addvol *= getEXCVoltage() / _config->exc_voltage;

   _ia->setAnalogVolOut(2, addvol);
   _ia->setAnalogVolOut(3, addvol);
}

void PCB::setLoadcellDCVoltage(float voltage)
{
   _ia->setAnalogVolOut(1, voltage);
}

void PCB::setSENVoltage(float voltage)
{
   _ia->setAnalogVolOut(4, voltage);
}

float PCB::getEXCVoltage()
{
   return _ia->readAnalogVolIn(1);
}

float PCB::getSENVoltage()
{
   return _ia->readAnalogVolIn(2);
}