#pragma once
#include <string>
#include "json.hpp"

using json = nlohmann::json;

enum LoadCellMode
{
   NORMAL = 0x00,   // Positive differential voltage from 0 - 100% nominal load
   OVERLOAD = 0x01, // Positive differential voltage from 0 - 120% nominal load
   INVERTED = 0x02, // Negative differential voltage from 0 - 100% nominal load

} typedef LoadCellMode;

enum IMPEDANCE
{
   OPEN = 0x00,
   NOMINAL = 0x01,
   SHORT = 0x02,

} typedef IMPEDANCE;

class Configuration
{
public:
   Configuration(std::string path);
   ~Configuration();

   void loadConfiguration();

   // SETTING VARIABLES
   //! Loadcell mode to be simulated
   LoadCellMode cellMode = NORMAL;
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

private:
   void parseJSON();
   std::string _path;
};