#include "Simulator.hpp"

Simulator::Simulator()
{
   _config = new Configuration(CONFIG_PATH);
   _pcb = new PCB(_config);
   _ia = new IABoard();

   reloadConfig();
}

Simulator::~Simulator()
{
   delete _config;
   delete _pcb;
   delete _ia;
}

/*!
Set the output weight as a percentage of the nominal load
@param percentage Percentage from 0 - 1 where 1 represents the nominal load as specified
*/
void Simulator::setWeightPER(float percentage)
{
   float voltage = 0.f;

   switch (_config->cellMode)
   {
   default:
   case NORMAL:
      // Max differential voltage (e.g. 4mV/V * 10V = 40mV)
      voltage = _config->cellCharecteristic * _config->exc_voltage;
      // Do not allow overload
      constrainMax(percentage, 1);
      break;
   case OVERLOAD:
      break;
   }

   voltage *= percentage;

   _pcb->setLoadcellVoltage(voltage);
}

/*!
Set the output weight of the simulated load cell in kg
@param kg Output weight in kilograms
*/
void Simulator::setWeightKG(float kg)
{
   setWeightPER(kg / _config->load_weight);
}

/*!
Starts an animation with the on board LEDs
*/
void Simulator::bootupAnimation()
{
   _ia->setAllLED(0);
   std::this_thread::sleep_for(1s);
   uint8_t cnt = 0;
   while (cnt < 3)
   {
      _ia->setLED(1, 1);
      std::this_thread::sleep_for(500ms);
      _ia->setLED(2, 1);
      std::this_thread::sleep_for(500ms);
      _ia->setLED(3, 1);
      std::this_thread::sleep_for(500ms);
      _ia->setLED(4, 1);
      std::this_thread::sleep_for(500ms);
      _ia->setAllLED(0);
      std::this_thread::sleep_for(500ms);
      cnt++;
   }
}

/*!
Sets the simulated belt velocity in meters per second
@param meterspersecond Velocity in meters / second
*/
void Simulator::setVelocity(float meterspersecond)
{
   setVelocityPER(meterspersecond / _config->speedAt100);
}

/*!
Sets the simulated belt velocity from 0 - 100% of the maximal speed
@param percentage Percentage of the maximal speed from 0 to 1
*/
void Simulator::setVelocityPER(float percentage)
{
   constrainMinMax(percentage, 0, 1);
   setVelocityFRQ(_config->freqAt100 * percentage)
}

/*!
Sets the PWM output to a certain frequency to represent belt movement
@param frequency The frequency of the PWM signal
*/
void Simulator::setVelocityFRQ(float frequency)
{
   // Allow PWM outputs only for belt scale systems
   if (_config->systemType != BELT_SCALE)
   {
      frequency = 0;
   }
   _pcb->setPWM(frequency, 0.5);
}

/*!
Reloads the configuration from the disk an stores the settings
*/
void Simulator::reloadConfig()
{
   _config->loadConfiguration();
}