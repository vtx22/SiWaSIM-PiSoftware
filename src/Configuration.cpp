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
void Configuration::loadConfiguration()
{
   std::ifstream i("output.json");
   json j;
   i >> j;
   std::ofstream o("pretty.json");
   o << std::setw(4) << j << std::endl;
}

void Configuration::parseJSON()
{
}