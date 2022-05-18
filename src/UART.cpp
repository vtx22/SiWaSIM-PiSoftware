#include "UART.hpp"

UART::UART()
{
   begin();
}

UART::~UART()
{
   close(uart0);
}

bool UART::begin()
{
   uart0 = open("dev/ttyS0", O_RDWR);

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

   options.c_cc[VTIME] = _messageTimeoutRX;
   options.c_cc[VMIN] = _messageSizeRX;

   tcflush(uart0, TCIFLUSH);

   if (tcsetattr(uart0, TCSANOW, &options) != 0)
   {
      printf("UART ERROR: Unable to configure UART!\n");
      return false;
   }

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

std::vector<uint8_t> UART::receiveMSG()
{
   std::vector<uint8_t> rx;
   uint8_t current_byte;
   int status;

   while (status = read(uart0, &current_byte, 1) > 0)
   {
      rx.push_back(current_byte);
   }

   if (status < 0)
   {
      printf("UART ERROR: Could not receive message!\n");
   }

   return rx;
}