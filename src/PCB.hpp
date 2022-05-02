#pragma once
#include "utility.hpp"
#include "GPIO.hpp"
#include "IABoard.hpp"
#include "Configuration.hpp"

// LED Pins
#define PIN_LED_READY 23
#define PIN_LED_BUSY 24
#define PIN_LED_FAULT 25

// PWM Pin
#define PWM_PIN 13

// 24V Power Switch Pins
#define PIN_POWERSW1 4
#define PIN_POWERSW2 26

// Pins for Impedance switching
#define PIN_IMPEDANCE1 5
#define PIN_IMPEDANCE2 6

// Pins for extra switches (e.g. WebServer, WriteProtect)
#define PIN_EXTRASW1 27
#define PIN_EXTRASW2 22

// Analog Channels
#define ADDVOL_CHANNEL 2
#define SUBVOL_CHANNEL 3
#define CELL_DC 1
#define SEN_OUT 4
#define EXC_IN 1
#define SEN_IN 2

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
   void setSENVoltage(float voltage);

   float getEXCVoltage();
   float getSENVoltage();

   void setPWM(float frequency, float dutyCycle);

   void reloadConfig();

private:
   GPIO *_gpio;
   IABoard *_ia;
   Configuration *_config;
};