#pragma once

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

   LoadCellMode cellMode = NORMAL;

private:
   void parseJSON();
};