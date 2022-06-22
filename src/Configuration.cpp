#include "Configuration.hpp"

/*!
Creates a new configuration that stores all configuration settings needed for the Simulator.
IMPORTANT: Should only be created once, since there is only one valid configuration for the simulator!
@param path The path to the configuration file on the filesystem
*/
Configuration::Configuration(std::string path) : _path(path)
{
}

Configuration::~Configuration()
{
}

/*!
Loads a configuration file from the file system (specified by path in Configuration(std::string path)) and parses all settings to their respective variables
*/
bool Configuration::loadConfiguration()
{
   // Load JSON file from disc
   json jsonCFG;
   try
   {
      std::ifstream cfg(_path.append("/config.json").c_str());
      cfg >> jsonCFG;
   }
   catch (...)
   {
      printf("ERROR: Could not find config.json!\n");
      return false;
   }

   // Load values line by line (should be simplified in the future)
   cellCharecteristic = jsonCFG.at(0).at("Wert");
   // load_weight = jsonCFG.at(1).at("Wert");
   exc_voltage = jsonCFG.at(2).at("Wert");

   // Load SIWAREX addresses
   /*
   std::fstream addFile;

   // Open file
   addFile.open(_path.append("/addresses.csv").c_str(), std::ios::in);

   if (!addFile.is_open())
   {
      printf("ERROR: Could not open addresses.csv\n");
      throw std::runtime_error("ERROR: Could not open addresses.csv");
   }

   std::string line, val;

   while (std::getline(addFile, line))
   {
      // Create a stringstream of the current line
      std::stringstream ss(line);

      // Keep track of the current column index
      int colIdx = 0;

      // Extract each cell of the line
      while (ss >> val)
      {

         // Add the current integer to the 'colIdx' column's values vector
         result.at(colIdx).second.push_back(val);

         // If the next token is a seperator, ignore it and move on
         if (ss.peek() == ';')
         {
            ss.ignore();
         }
         // Increment the column index
         colIdx++;
      }
   }

   addFile.close();

   MODBUS_DATASET ds;
   ds.dsNumber = 13;
   ds.startRegister = 1480;

   MODBUS_PARAMETER param;
   param.startRegister = 1480;
   param.name = "RS485 Baud Rate";
   param.type = 3;
   param.value = (unsigned short)2;
   ds.params.push_back(param);

   modbus_datasets.push_back(ds);
   */
   return true;
}
