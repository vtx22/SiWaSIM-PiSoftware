#include "UART.hpp"

UART::UART()
{
   begin();
}

UART::~UART()
{
}

bool UART::begin()
{
   uart0 = open(_dev.c_str(), O_RDWR);
   if (uart0 < 0)
   {
      printf("UART ERROR: Unable to open port!\n");
      return false;
   }

   //CLOCAL - Ignore modem status lines
   //CREAD - Enable receiver
   //IGNPAR = Ignore characters with parity errors
   struct termios options;
   tcgetattr(uart0, &options);
   options.c_cflag |= B115200 | CS8 | CLOCAL | CREAD;
   options.c_cflag &= ~PARENB;
   options.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);
   options.c_oflag |= 0;
   options.c_lflag &= ~ICANON;
   options.c_cc[VTIME] = 10;
   //options.c_cc[VMIN] = _messageSizeRX;
   tcflush(uart0, TCIFLUSH);
   tcsetattr(uart0, TCSANOW, &options);

   return true;
}