#pragma once
#include <string>

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
   LoadCellMode cellMode = NORMAL; // Loadcell mode to be simulated
   float exc_voltage = 10.f;       // Nominal EXC voltage
   float load_weight = 20.f;       // Nominal Load Weight of the cell in kg
   float initial_weight = 10.f;    // Initial weight (for manual / non-auto mode)
   float addvol_ratio = 500;       // Inverted OpAmp gain (e.g.: At 10V Aout the added / subtracted voltage is 20mV --> ratio = 10V / 20mV = 500)
   float max_diff_voltage = 40;    // Maximum Differential Voltage of SIG+-
   float cellCharecteristic = 4;   // Charecteristik in mV/V

private:
   void parseJSON();
};