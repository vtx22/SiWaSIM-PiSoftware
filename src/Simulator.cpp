#include "Simulator.hpp"

Simulator::Simulator()
{
   _config = new Configuration(CONFIG_PATH);
   _pcb = new PCB(_config);
   _ia = new IABoard();
   _siwarex = new SIWAREX(_config);

   _materialFlows[0] = new MaterialFlow(1);
   _materialFlows[1] = new MaterialFlow(2);
   _materialFlows[2] = new MaterialFlow(3);
   _materialFlows[3] = new MaterialFlow(4);

   _materialFlows[1]->setFlowType(MATERIAL_FLOW::EMPTY);

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
      percentage = constrainMax(percentage, 1);
      break;
   case LoadCellMode::OVERLOAD:
      break;
   }

   voltage *= percentage;

   _pcb->setLoadcellVoltage(40 * percentage);
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
      runPassive(timestep, weight);
      break;

   default:
      break;
   }
}

float Simulator::runPassive(float timestep, float *weight)
{
   // Update all flows based on digital inputs
   _ia->digitalRead();
   float flow = 0;
   flow += _materialFlows[0]->update(weight, timestep, _ia->getDigitalRead(1));
   flow += _materialFlows[1]->update(weight, timestep, _ia->getDigitalRead(2));
   flow += _materialFlows[2]->update(weight, timestep, _ia->getDigitalRead(3));
   flow += _materialFlows[3]->update(weight, timestep, _ia->getDigitalRead(4));
   setWeightKG(*weight);
   return flow;
}

void Simulator::testFunction()
{
   //_siwarex->setMODBUSDelay(0);
   // std::this_thread::sleep_for(1s);
   uint16_t reg = 1007, ds = 3;

   std::vector<uint8_t> value;

   value = _siwarex->requestRegisters(reg, 1);
   printf("BEFORE: %d\n", (value[0] << 8) + value[1]);

   std::this_thread::sleep_for(1s);

   _siwarex->writeRegister(ds, reg, 1);
   std::this_thread::sleep_for(1s);

   value = _siwarex->requestRegisters(reg, 1);
   printf("AFTER: %d\n", (value[0] << 8) + value[1]);

   return;
   _materialFlows[0]->calculateFlowCurve();
   while (true)
      ;

   bool state = false;
   uint8_t voltage = 0;
   while (true)
   {
      if (voltage > 40)
      {
         voltage = 0;
      }
      _pcb->setLoadcellVoltage(voltage);
      _pcb->setEXTRASW1(state);
      state = !state;
      voltage++;
      std::this_thread::sleep_for(5s);
   }
}

void Simulator::calibrateLCVoltage(bool autoCalib)
{
   std::cout << "\n======================\n";
   std::cout << "OUTPUT VOLTAGE CALIBRATION\n";
   std::cout << "======================\n";

   _pcb->ledBusy(true);
   _pcb->ledReady(false);

   std::vector<float> xValues, yValues;

   if (autoCalib)
   {
      std::cout << "Auto calibration starting...\n\n";

      for (uint8_t i = 0; i < _config->autoSamples; i++)
      {
         float voltageStep = (_config->endVoltage - _config->startVoltage) / (float)_config->autoSamples;
         float dcVoltage = _config->startVoltage + i * voltageStep;

         printf("Sampling... (%d of %d)\n", i + 1, _config->autoSamples);

         _ia->setAnalogVolOut(ADDVOL_CHANNEL, dcVoltage);
         _ia->setAnalogVolOut(SUBVOL_CHANNEL, dcVoltage);

         std::this_thread::sleep_for(4s);

         float voltage = 0;
         for (uint8_t sample = 0; sample < 5; sample++)
         {
            voltage += _siwarex->getLoadcellVoltage();
         }

         voltage /= 5.f;

         xValues.push_back(dcVoltage);
         yValues.push_back(voltage / 1000.f);
      }
   }
   else
   {
      for (uint8_t i = 0; i < _config->manSamples; i++)
      {
         float voltageStep = (_config->endVoltage - _config->startVoltage) / (float)_config->autoSamples;
         float dcVoltage = _config->startVoltage + i * voltageStep;

         _ia->setAnalogVolOut(ADDVOL_CHANNEL, dcVoltage);
         _ia->setAnalogVolOut(SUBVOL_CHANNEL, dcVoltage);

         std::cout << "Enter signed voltage between SIG+ and SIG- (in mV):\n";

         std::string input = "";
         std::getline(std::cin, input);

         xValues.push_back(dcVoltage);
         yValues.push_back(std::stof(input) / 1000.f);
      }
   }

   float a, b, c, d;

   cubicRegression(xValues, yValues, &a, &b, &c, &d);

   _config->calibrationReg.a = a;
   _config->calibrationReg.b = b;
   _config->calibrationReg.c = c;
   _config->calibrationReg.d = d;

   setWeightPER(0.05);

   std::cout << "DONE!\n\n";

   _pcb->ledBusy(false);
   _pcb->ledReady(true);
}

std::vector<float> Simulator::longTermTest()
{

   bool state = false;
   std::vector<float> yValues, setPoints;
   /*
   for (uint8_t i = 0; i < 40; i++)
   {
      _pcb->setLoadcellVoltage(i);
      for (uint8_t sample = 0; sample < 5 * 20 / 3.f; sample++)
      {
         _pcb->setEXTRASW1(state);
         state = !state;
         setPoints.push_back(i);
         yValues.push_back(_siwarex->getLoadcellVoltage());
         delay(150ms);
      }
   }

   std::ofstream file;

   file.open("data.txt", std::ios::out);
   for (int i = 0; i < yValues.size(); i++)
   {
      file << yValues[i] << "\n";
   }
   file.close();

   file.open("setpoints.txt", std::ios::out);
   for (int i = 0; i < setPoints.size(); i++)
   {
      file << setPoints[i] << "\n";
   }
   file.close();

   */
   _pcb->setLoadcellVoltage(20);
   std::this_thread::sleep_for(5s);

   const int numOfSamples = 60 * 60 * 6;
   int sample = 0;

   printf("Starting...\n");
   std::this_thread::sleep_for(500ms);

   _pcb->setEXTRASW1(true);

   while (sample < numOfSamples)
   {
      yValues.push_back(_siwarex->getLoadcellVoltage());

      delay(1000ms);

      sample++;
   }

   std::ofstream file;

   file.open("data.txt", std::ios::out);
   for (int i = 0; i < yValues.size(); i++)
   {
      file << yValues[i] << "\n";
   }
   file.close();

   _pcb->setEXTRASW1(false);

   return yValues;
}
