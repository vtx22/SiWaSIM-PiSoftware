#include "Simulator.hpp"

Simulator::Simulator()
{
   _config = new Configuration(CONFIG_PATH);
   _pcb = new PCB(_config);
   _ia = new IABoard();

   _materialFlows[0] = new MaterialFlow(1);
   _materialFlows[1] = new MaterialFlow(2);
   _materialFlows[2] = new MaterialFlow(3);
   _materialFlows[3] = new MaterialFlow(4);

   reloadConfig();
}

Simulator::~Simulator()
{
   delete _config;
   delete _pcb;
   delete _ia;

   delete _materialFlows[0];
   delete _materialFlows[1];
   delete _materialFlows[2];
   delete _materialFlows[3];
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
   case LoadCellMode::NORMAL:
      // Max differential voltage (e.g. 4mV/V * 10V = 40mV)
      voltage = _config->cellCharecteristic * _config->exc_voltage;
      // Do not allow overload
      constrainMax(percentage, 1);
      break;
   case LoadCellMode::OVERLOAD:
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
   _pcb->getBoardStatus();
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
   setVelocityFRQ(_config->freqAt100 * percentage);
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

void Simulator::setImpedance(IMPEDANCE impedance)
{
   _pcb->setImpedance(impedance);
}

float Simulator::run(RUN_MODE runMode, float timestep, float *weight)
{
   switch (runMode)
   {
   case PASSIVE:
      return runPassive(timestep, weight);
      break;

   default:
      break;
   }
}

float Simulator::runPassive(float timestep, float *weight)
{
   // Refresh Digital Input variables
   //_ia->digitalRead();
   static bool dig = 1;
   static int cnt = 0;
   if (cnt > 199)
   {
      dig = 0;
   }
   cnt++;
   return _materialFlows[0]->update(weight, timestep, dig); //_ia->getDigitalRead(1));
}

void Simulator::testFunction()
{
   setImpedance(IMPEDANCE::NOMINAL);

   _pcb->ledBusy(1);
   _pcb->ledFault(1);
   _pcb->ledReady(1);

   float voltage = 0;
   _pcb->setCellSubvol(10);
   _pcb->setCellAddvol(10);
}

void Simulator::calibrateLCVoltage()
{
   std::cout << "\n======================\n";
   std::cout << "OUTPUT VOLTAGE CALIBRATION\n";
   std::cout << "======================\n";

   _ia->setAnalogVolOut(ADDVOL_CHANNEL, 0);
   _ia->setAnalogVolOut(SUBVOL_CHANNEL, 0);

   std::string f_1_10, f_2_10, b_1, b_2;

   std::cout << "Enter absolute voltage between SIG+ and EXC/2:\n";

   std::getline(std::cin, b_1);

   std::cout << "Enter absolute voltage between SIG- and EXC/2:\n";

   std::getline(std::cin, b_2);

   _ia->setAnalogVolOut(ADDVOL_CHANNEL, 10);
   _ia->setAnalogVolOut(SUBVOL_CHANNEL, 10);

   std::cout << "Enter absolute voltage between SIG+ and EXC/2:\n";

   std::getline(std::cin, f_1_10);

   std::cout << "Enter absolute voltage between SIG- and EXC/2:\n";

   std::getline(std::cin, f_2_10);

   _config->addvol_b = std::stof(b_1);
   _config->subvol_b = std::stof(b_2);

   _config->addvol_m = (std::stof(f_1_10) + std::stof(b_1)) / 10.f;
   _config->subvol_m = (std::stof(f_2_10) - std::stof(b_2)) / 10.f;

   _ia->setAnalogVolOut(ADDVOL_CHANNEL, 0);
   _ia->setAnalogVolOut(SUBVOL_CHANNEL, 0);

   printf("ADDVOL B: %f\n", _config->addvol_b);
   printf("ADDVOL M: %f\n", _config->addvol_m);

   printf("SUBVOL B: %f\n", _config->subvol_b);
   printf("SUBVOL M: %f\n", _config->subvol_m);
}