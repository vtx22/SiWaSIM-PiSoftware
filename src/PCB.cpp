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
   setAllOff();
   delete _gpio;
   delete _ia;
}

void PCB::setAllOff()
{
   _gpio->writePin(PIN_LED_READY, false);
   _gpio->writePin(PIN_LED_BUSY, false);
   _gpio->writePin(PIN_LED_FAULT, false);

   _gpio->writePin(PIN_POWERSW1, false);
   _gpio->writePin(PIN_POWERSW2, false);

   _gpio->writePin(PIN_IMPEDANCE1, false);
   _gpio->writePin(PIN_IMPEDANCE2, false);

   _gpio->writePin(PIN_EXTRASW1, false);
   _gpio->writePin(PIN_EXTRASW2, false);
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
   _gpio->writePin(PIN_EXTRASW1, !state);
}

void PCB::setEXTRASW2(bool state)
{
   _gpio->writePin(PIN_EXTRASW2, !state);
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
      addvol = voltage * 0.5 * _config->addvol_ratio / 1000.f;
      break;
   }

   // Correction because if EXC is lower than expected the differential voltage has to decrease for example
   // voltage *= getEXCVoltage() / _config->exc_voltage;

   addvol = solveCubicForVoltage(_config->calibrationReg.a, _config->calibrationReg.b, _config->calibrationReg.c, _config->calibrationReg.d, voltage / 1000.f);

   _ia->setAnalogVolOut(ADDVOL_CHANNEL, addvol);
   _ia->setAnalogVolOut(SUBVOL_CHANNEL, addvol);
}

void PCB::setLoadcellDCVoltage(float voltage)
{
   _ia->setAnalogVolOut(CELL_DC, voltage);
}

void PCB::setSENVoltage(float voltage)
{
   _ia->setAnalogVolOut(SEN_OUT, voltage);
}

float PCB::getEXCVoltage()
{
   return _ia->readAnalogVolIn(EXC_IN);
}

float PCB::getSENVoltage()
{
   return _ia->readAnalogVolIn(SEN_IN);
}

void PCB::setPWM(float frequency, float dutyCycle)
{
   _gpio->setPWM(PWM_PIN, dutyCycle, frequency);
}

void PCB::getBoardStatus()
{
   _ia->getBoardData();
}

void PCB::setCellAddvol(float voltage)
{
   _ia->setAnalogVolOut(ADDVOL_CHANNEL, voltage);
}

void PCB::setCellSubvol(float voltage)
{
   _ia->setAnalogVolOut(SUBVOL_CHANNEL, voltage);
}
