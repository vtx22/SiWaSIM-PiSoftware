#include <string>

#include "Simulator.hpp"
#include "SIWAREX.hpp"

void modbusrd(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   printf("===========================\n");
   printf("SiWaSim  --  SIWAREX Tester\n");
   printf("===========================\n\n");

   if (argc == 1)
   {
      printf("No argument passed! Please refer to the documentation for all available commands.\n");
      return 0;
   }

   if (std::string(argv[1]) == "modbusrd")
   {
      modbusrd(argc, argv);
   }
   else
   {
      printf("Unknown argument! Please refer to the documentation for all available commands.\n");
   }

   printf("===========================\n\n");
   return 0;
}

// siwasim modbusrd address type length
void modbusrd(int argc, char *argv[])
{
   if (argc < 4 || argc > 5)
   {
      printf("Wrong format! siwasim modbusrd <startAddress> <type> <length>\n");
      printf("Available types: 0 = bytes (hex), 1 = uint16, 2 = uint32, 3 = float\n");
      printf("Length is optional. If length is specified, type is ignored!\n");
      return;
   }

   SIWAREX swrx;

   if (argc == 4)
   {
   }

   if (argc == 5)
   {
      int length = std::atoi(argv[4]);
      int reg = std::atoi(argv[3]);
      printf("%s %s\n", argv[3], argv[4]);
      printf("%d %d\n", reg, length);
      if (length <= 0 || reg <= 0)
      {
         printf("Wrong length or register!\n");
         return;
      }

      std::vector<uint8_t> data = swrx.requestRegisters(reg, length);

      bool toggle = 1;
      for (int i = 0; i < data.size() * 2; i++)
      {
         if (toggle)
         {
            printf("REG %d: %d ", reg + i / 2, data[i]);
         }
         else
         {
            printf("%d\n", data[i]);
            toggle = !toggle;
         }
      }
   }
   return;
}