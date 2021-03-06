#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <variant>
#include <vector>
#include <utility>
#include <stdexcept>
#include <sstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

#define CONFIG_PATH "/home/siwasim/SiWaSIM-PiSoftware/Konfiguration"

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

//! Stores coefficients of a function \f$f(x)=ax^3+bx^2+cx+d\f$
struct CUBIC_FUNCTION
{
   float a, b, c, d;
} typedef CUBIC_FUNCTION;

//! Stores coefficients of a function \f$f(x)=ax^4+bx^3+cx^2+dx+e\f$
struct QUARTIC_FUNCTION
{
   float a, b, c, d, e;
} typedef QUARTIC_FUNCTION;

struct CURVE
{
   //! Delay from input high to flow increase start in seconds
   float startDelay = 0;
   //! Delay from input low to flow decrease start in seconds
   float stopDelay = 0;
   //! Time it takes the flow to reach its maximum in seconds
   float riseTime = 0.1;
   //! Time it takes the flow to reach zero in seconds
   float fallTime = 0.1;
   //! Maximal flow after rise time in kg/s
   float maxFlow = 1;
   //! Percentage of maximal flow reached at riseTime / 2
   float halfRise = 0.1;
} typedef CURVE;

//! All possible data types of a SIWAREX parameter
typedef std::variant<short, unsigned short, int, unsigned int, float> modbusValue;

//! Defines a MODBUS parameter of the SIWAREX Module
struct MODBUS_PARAMETER
{
   //! Name / function of the parameter
   std::string name;
   //! First register that stores the parameters
   uint16_t startRegister;
   //! Data type of the parameter: 0 = float, 1 = uint, 2 = int, 3=ushort, 4=short, 5=bool
   uint8_t type;
   modbusValue value;

} typedef MODBUS_PARAMETER;

//! Defines a full MODBUS parameter dataset of the SIWAREX Module
struct MODBUS_DATASET
{
   //! Number of the dataset as specified in the SIWAREX documentation
   uint8_t dsNumber;
   //! First register of the dataset
   uint16_t startRegister;
   //! List of all the parameters of the datset
   std::vector<MODBUS_PARAMETER> params;
} typedef MODBUS_DATASET;

class Configuration
{
public:
   Configuration(std::string path);
   ~Configuration();

   bool loadConfiguration();

   // SETTING VARIABLES
   //! Loadcell mode to be simulated
   LoadCellMode cellMode = LoadCellMode::NORMAL;
   //! System type to be simulated
   SYSTEM_TYPE systemType = SYSTEM_TYPE::DOSING_SCALE;
   //! Nominal EXC voltage ouputted by the SIWAREX module
   float exc_voltage = 10.f;
   //! Nominal Load Weight of the cell in kg
   float load_weight = 100.f;
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

   //! Struct that stores the cubic calibration regressions parameters
   CUBIC_FUNCTION calibrationReg;
   //! Number of samples during auto calibration
   uint8_t autoSamples = 15;
   //! Number of samples during manual calibration
   uint8_t manSamples = 10;

   //! Analog DC output voltage at which the calibration begins
   float startVoltage = 2;
   float endVoltage = 10;

   // Input channel assignment
   MATERIAL_FLOW inputChannel1 = MATERIAL_FLOW::NONE;
   MATERIAL_FLOW inputChannel2 = MATERIAL_FLOW::EMPTY;
   MATERIAL_FLOW inputChannel3 = MATERIAL_FLOW::FINE;
   MATERIAL_FLOW inputChannel4 = MATERIAL_FLOW::COARSE;

   std::vector<MODBUS_DATASET> modbus_datasets;
   uint8_t numberOfDatasets = 1;

private:
   void parseJSON();
   std::string _path;
};