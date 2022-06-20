#include <string>

#include "Simulator.hpp"
#include "SIWAREX.hpp"
#include "utility.hpp"

void modbusrd(int argc, char *argv[]);
void modbuswr(int argc, char *argv[]);
void testfunction(int argc, char *argv[]);
void runPassive(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   printf("\n===========================\n");
   printf("SiWaSim  --  SIWAREX Tester\n");
   printf("===========================\n\n");

   if (argc == 1)
   {
      printf("No argument passed! Please refer to the documentation or use -h for all available commands.\n");
      return 0;
   }

   if (std::string(argv[1]) == "-h")
   {
      printf("MODBUS:\n");
      printf("modbusrd : Read  MODBUS Registers\n");
      printf("modbuswr : Write MODBUS Registers\n");
      printf("\n");
      return 0;
   }
   if (std::string(argv[1]) == "modbusrd")
   {
      modbusrd(argc, argv);
      return 0;
   }
   if (std::string(argv[1]) == "modbuswr")
   {
      modbuswr(argc, argv);
      return 0;
   }
   if (std::string(argv[1]) == "testfunction")
   {
      testfunction(argc, argv);
      return 0;
   }
   if (std::string(argv[1]) == "runpassive")
   {
      runPassive(argc, argv);
      return 0;
   }

   printf("Unknown argument! Please refer to the documentation for all available commands.\n");

   printf("===========================\n\n");
   return 0;
}

// siwasim modbusrd address type length
void modbusrd(int argc, char *argv[])
{
   if (argc < 4 || argc > 5)
   {
      printf("Wrong command format!\nsiwasim modbusrd <startAddress> <type> <length>\n");
      printf("Available types: 0 = bytes (hex), 1 = uint16, 2 = uint32, 3 = float\n");
      printf("Length is optional. If length is specified, type is ignored!\n");
      return;
   }

   SIWAREX swrx;

   if (argc == 4)
   {
      int type = std::stoi(argv[3]);
      int reg = std::stoi(argv[2]);

      if (type < 0 || type > 3 || reg <= 0)
      {
         printf("Wrong type or register!\n");
         return;
      }

      switch (type)
      {
      case 0:
      {
         std::vector<uint8_t> data = swrx.requestRegisters(reg, 1);
         printBytesRegister(reg, data);
         break;
      }
      case 1:
      {
         std::vector<uint8_t> data = swrx.requestRegisters(reg, 1);
         printf("REG %d: %d\n", reg, (data[0] << 8) + data[1]);
         break;
      }
      case 2:
      {
         std::vector<uint8_t> data = swrx.requestRegisters(reg, 2);
         printf("REG %d: %d\n", reg, ((data[0] << 24) + (data[1] << 16) + (data[2] << 8) + data[3]));
         break;
      }
      case 3:
      {
         printf("FLOAT: %f\n", swrx.requestFloat(reg));
         break;
      }
      default:
         printf("Unknown type!\n");
         break;
      }
      return;
   }

   if (argc == 5)
   {
      int length = std::stoi(argv[4]);
      int reg = std::stoi(argv[2]);

      if (length <= 0 || reg <= 0)
      {
         printf("Wrong length or register!\n");
         return;
      }

      std::vector<uint8_t> data = swrx.requestRegisters(reg, length);

      if (data.size() != length * 2)
      {
         printf("MODBUS ERROR: Data is incomplete!\n");
         return;
      }

      printBytesRegister(reg, data);
   }
   return;
}

// siwasim modbuswr address dataset value
void modbuswr(int argc, char *argv[])
{
   if (argc < 5)
   {
      printf("Wrong command format!\nsiwasim modbuswr <startAddress> <dataset number> <value>\n");
      printf("siwasim modbuswr <startAddress> <dataset number> <value1> <value2> <value3> ...\n\n");
      return;
   }
   if (argc >= 5)
   {
      int reg = std::stoi(argv[2]);
      int ds = std::stoi(argv[3]);

      std::vector<uint16_t> values;

      for (uint8_t i = 0; i < argc - 4; i++)
      {
         values.push_back(std::stoi(argv[i + 4]));
      }

      SIWAREX swrx;
      printf("Writing...\n");
      swrx.writeRegisters(ds, reg, values);
      printf("Done!\n\n");
      return;
   }
}

void testfunction(int argc, char *argv[])
{
   SIWAREX swrx;
   uint16_t reg = 1007, ds = 3;

   std::vector<uint8_t> value;

   value = swrx.requestRegisters(reg, 2);
   printf("BEFORE: %d\n", (value[0] << 8) + value[1]);

   std::this_thread::sleep_for(1s);
   swrx.writeRegister(ds, reg, 2);
   std::this_thread::sleep_for(1s);

   value = swrx.requestRegisters(reg, 1);
   printf("AFTER: %d\n", (value[0] << 8) + value[1]);
}

void runPassive(int argc, char *argv[])
{
   Simulator sim;
   while (true)
   {
      static float weight = 0;
      float flow = sim.runPassive(0.05, &weight);
      printf("Weight: %f  -- Flow: %f\n", weight, flow);
      std::this_thread::sleep_for(50ms);
   }
}