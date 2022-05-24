#include "Simulator.hpp"

Simulator::Simulator()
{
   _config = new Configuration(CONFIG_PATH);
   _pcb = new PCB(_config);
   _ia = new IABoard();
   _siwarex = new SIWAREX();

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
   std::vector<uint8_t> data = _siwarex->requestRegisters(1000, 100);

   printf("LENGTH: %d\n", data.size());
   for (uint8_t i = 0; i < data.size(); i++)
   {
      printf("REG: %02X\n", data.at(i));
   }
}

void Simulator::calibrateLCVoltage(bool autoCalib)
{
   std::cout << "\n======================\n";
   std::cout << "OUTPUT VOLTAGE CALIBRATION\n";
   std::cout << "======================\n";

   std::vector<float> xValues, yValues;

   if (autoCalib)
   {
      std::cout << "Auto calibration starting...\n\n";

      for (uint8_t i = 2; i < 11; i++)
      {
         printf("Sampling... (%d of 9)\n", i - 1);
         _ia->setAnalogVolOut(ADDVOL_CHANNEL, i);
         _ia->setAnalogVolOut(SUBVOL_CHANNEL, i);
         std::this_thread::sleep_for(4s);
         float voltage = 0;

         for (uint8_t sample = 0; sample < 5; sample++)
         {
            voltage += _siwarex->getLoadcellVoltage();
         }

         voltage /= 5.f;

         xValues.push_back(i);
         yValues.push_back(voltage / 1000.f);
      }
   }
   else
   {
      for (uint8_t i = 2; i < 11; i++)
      {
         _ia->setAnalogVolOut(ADDVOL_CHANNEL, i);
         _ia->setAnalogVolOut(SUBVOL_CHANNEL, i);

         std::cout << "Enter signed voltage between SIG+ and SIG- (in mV):\n";

         std::string input = "";
         std::getline(std::cin, input);

         xValues.push_back(i);
         yValues.push_back(std::stof(input) / 1000.f);
      }
   }

   float a, b, c, d;

   cubicRegression(xValues, yValues, &a, &b, &c, &d);

   _config->calibrationReg.a = a;
   _config->calibrationReg.b = b;
   _config->calibrationReg.c = c;
   _config->calibrationReg.d = d;

   std::cout << "DONE!\n\n";
}

std::vector<float> Simulator::longTermTest()
{
   _pcb->setLoadcellVoltage(20);
   std::this_thread::sleep_for(5s);
   std::vector<float> yValues;

   int numOfSamples = 100;
   int sample = 0;
   bool state = false;

   printf("Starting...\n");
   std::this_thread::sleep_for(500ms);

   while (sample < numOfSamples)
   {
      yValues.push_back(_siwarex->getLoadcellVoltage());
      _pcb->setEXTRASW1(state);
      state = !state;

      printf("Imp: %f\n", _siwarex->getLoadcellImpedance());

      delay(1000ms);

      sample++;
   }

   return yValues;
}
