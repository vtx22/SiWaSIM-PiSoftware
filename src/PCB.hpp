#pragma once
#include "utility.hpp"
#include "GPIO.hpp"
#include "IABoard.hpp"
#include "Configuration.hpp"

class PCB
{
public:
   PCB(Configuration *config);
   ~PCB();

   void ledFault(bool state);
   void ledBusy(bool state);
   void ledReady(bool state);

   void setImpedance(IMPEDANCE impedance);

   void setEXTRASW1(bool state);
   void setEXTRASW2(bool state);

   void setPOWERSW1(bool state);
   void setPOWERSW2(bool state);

   void setLoadcellVoltage(float voltage);
   void setLoadcellDCVoltage(float voltage);
   void setCellAddvol(float voltage);
   void setCellSubvol(float voltage);

   void setSENVoltage(float voltage);

   float getEXCVoltage();
   float getSENVoltage();

   void setPWM(float frequency, float dutyCycle);
   void getBoardStatus();

   void reloadConfig();

private:
   GPIO *_gpio;
   IABoard *_ia;
   Configuration *_config;
};