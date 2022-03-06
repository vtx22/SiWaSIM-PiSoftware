#include "UART.hpp"

UART::UART(std::string dev) : _dev(_dev)
{
   begin();
}

UART::~UART()
{
   close(uart0);
}

bool UART::begin()
{
   return false;
   uart0 = open(_dev.c_str(), O_RDWR);

   if (uart0 < 0)
   {
      printf("UART ERROR: Unable to open port!\n");
      return false;
   }

   struct termios options;
   tcgetattr(uart0, &options);

   options.c_cflag = B115200 | CS8 | CLOCAL | CREAD | HUPCL;
   options.c_iflag = 0;
   options.c_oflag = 0;
   options.c_lflag = 0;

   options.c_ispeed = B115200;
   options.c_ospeed = B115200;

   options.c_cc[VTIME] = 0;
   options.c_cc[VMIN] = _messageSizeRX;

   tcflush(uart0, TCIFLUSH);
   tcsetattr(uart0, TCSANOW, &options);

   return true;
}

bool UART::transmitMSG(uint8_t *msg, uint16_t length)
{
   if (uart0 < 0)
   {
      printf("UART ERROR: Device not initialized!\n");
      return false;
   }
   if (write(uart0, msg, length) < 0)
   {
      printf("UART ERROR: Could not transmit message!\n");
      return false;
   }

   return true;
}