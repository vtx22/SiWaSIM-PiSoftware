#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

#define CONFIG_PATH "/home/siwasim/SiWaSIM-PiSoftware/Konfiguration/config.json"

// I2C
#define I2C_IABOARD 0x50
#define I2C_DEVICE "/dev/i2c-1"

// MODBUS
#define SIWAREX_ADDRESS 0x14

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

enum LoadCellMode
{
   //! Positive differential voltage from 0 - 100% nominal load
   NORMAL = 0x00,
   //! Positive differential voltage from 0 - 120% nominal load
   OVERLOAD = 0x01,
   //! Negative differential voltage from 0 - 100% nominal load
   INVERTED = 0x02,

} typedef LoadCellMode;

/*!
Types of impedances of the load cell that can be simulated.
Is equivilant with the impedance between EXC+ and EXC-
*/
enum IMPEDANCE
{
   //! Open circuit, high impedance
   OPEN = 0x00,
   //! Nominal impedance of approx. 350 ohms
   NOMINAL = 0x01,
   //! Short circuit, approx. zero impedance
   SHORT = 0x02,

} typedef IMPEDANCE;

/*!
Type of the system represented by the simulator
*/
enum SYSTEM_TYPE
{
   //! Dosing Scale
   DOSING_SCALE = 0x01,
   //! Belt Scale
   BELT_SCALE = 0x02,
} typedef SYSTEM_TYPE;

/*!
Types of different material flows
*/
enum MATERIAL_FLOW
{
   NONE = 0x00,
   EMPTY,
   FINE,
   COARSE,
   XCOARSE,

} typedef MATERIAL_FLOW;

enum RUN_MODE
{
   AUTO,
   PASSIVE,
   MANUAL,
   IDLE,
   OFF

} typedef RUN_MODE;

struct CUBIC_FUNCTION
{
   float a, b, c, d;
} typedef CUBIC_FUNCTION;

class Configuration
{
public:
   Configuration(std::string path);
   ~Configuration();

   void loadConfiguration();

   // SETTING VARIABLES
   //! Loadcell mode to be simulated
   LoadCellMode cellMode = LoadCellMode::NORMAL;
   //! System type to be simulated
   SYSTEM_TYPE systemType = SYSTEM_TYPE::DOSING_SCALE;
   //! Nominal EXC voltage ouputted by the SIWAREX module
   float exc_voltage = 10.f;
   //! Nominal Load Weight of the cell in kg
   float load_weight = 20.f;
   //! Initial weight (for manual / non-auto mode)
   float initial_weight = 10.f;
   //! Inverted OpAmp gain (e.g.: At 10V Aout the added / subtracted voltage is 20mV --> ratio = 10V / 20mV = 500)
   float addvol_ratio = 500;
   //! Maximum Differential Voltage of SIG+-
   float max_diff_voltage = 40;
   //! Characteristic in mV/V
   float cellCharecteristic = 4;
   //! Belt velocity in m/s at 100% speed
   float speedAt100 = 5;
   //! Belt encoder frequency at 100% speed
   float freqAt100 = 10000;

   float startVoltage = 2;
   float endVoltage = 9;

   float a, b, c, d;
   CUBIC_FUNCTION calibrationReg;

   // Input channel assignment
   MATERIAL_FLOW inputChannel1 = MATERIAL_FLOW::EMPTY;
   MATERIAL_FLOW inputChannel2 = MATERIAL_FLOW::FINE;
   MATERIAL_FLOW inputChannel3 = MATERIAL_FLOW::COARSE;
   MATERIAL_FLOW inputChannel4 = MATERIAL_FLOW::XCOARSE;

private:
   void parseJSON();
   std::string _path;
};