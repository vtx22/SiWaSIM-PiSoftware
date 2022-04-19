#pragma once
#include "GPIO.hpp"

// LED Pins
#define PIN_LED_READY 23
#define PIN_LED_BUSY 24
#define PIN_LED_FAULT 25

// 24V Power Switch Pins
#define PIN_POWERSW1 4
#define PIN_POWERSW2 26

// Pins for Impedance switching
#define PIN_IMPEDANCE1 5
#define PIN_IMPEDANCE2 6

// Pins for extra switches (e.g. WebServer, WriteProtect)
#define PIN_EXTRASW1 27
#define PIN_EXTRASW2 22

enum IMPEDANCE
{
   OPEN = 0x00,
   NOMINAL = 0x01,
   SHORT = 0x02,
} typedef IMPEDANCE;

class PCB
{
public:
   PCB();
   ~PCB();

   void ledFault(bool state);
   void ledBusy(bool state);
   void ledReady(bool state);

   void setImpedance(IMPEDANCE impedance);

   void setEXTRASW1(bool state);
   void setEXTRASW2(bool state);

   void setPOWERSW1(bool state);
   void setPOWERSW2(bool state);

private:
   GPIO *_gpio;
};