#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

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

private:
   void parseJSON();
   std::string _path;
};