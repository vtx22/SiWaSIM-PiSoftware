#include "IABoard.hpp"

IABoard::IABoard()
{
   _i2c = new I2C("/dev/i2c-1", 0x50);
}

IABoard::~IABoard()
{
   delete _i2c;
}

bool IABoard::detectBoard()
{
   _i2c->writeData(0x78);
   if (_i2c->readData() == 0x01)
   {
      printf("IA-Board: Board detected!\n");
      return true;
   }

   printf("IA-Board ERROR: No Board detected!\n");
   return false;
}

uint8_t IABoard::digitalRead()
{
   // Send command to read all 4 digital Inputs
   _i2c->writeData(0x03);
   // Returns one byte, the lowest 4 bits represent the digital value of the channel 1 - 4
   return _i2c->readData();
}

bool IABoard::digitalRead(uint8_t channel)
{
   if (channel > 4 || channel < 1)
   {
      printf("IA-Board ERROR: Channel out of range! Allowed: 1 - 4\n");
      return false;
   }

   uint8_t data = digitalRead();

   // State of channel is the respective bit at position 0 - 3
   return (data & (1 << (channel - 1)));
}

uint16_t IABoard::readTransistions(uint8_t channel)
{
   if (channel > 4 || channel < 1)
   {
      printf("IA-Board ERROR: Channel out of range! Allowed: 1 - 4\n");
      return 0;
   }

   // Send command based on channel, 1=0x6A, 2=0x6C, 3=0x6E, 4=0x70
   _i2c->writeData(0x6A + 2 * (channel - 1));

   // Read 2 bytes that contain the number of pin transistions
   uint8_t data[2] = {0x00, 0x00};
   _i2c->readData(data, 2);

   return (data[0] + (data[1] << 8));
}

uint16_t IABOard::readTransistions(uint8_t channel)
{
   if (channel > 4 || channel < 1)
   {
      printf("IA-Board ERROR: Channel out of range! Allowed: 1 - 4\n");
      return 0;
   }

   // First byte is command, second is the channel
   uint8_t command[2] = {0x69, channel};
   _i2c->writeData(command, 2);
   return 0;
}

TRANSITION IABoard::getTransistionType(uint8_t channel)
{
   if (channel > 4 || channel < 1)
   {
      printf("IA-Board ERROR: Channel out of range! Allowed: 1 - 4\n");
      return UNDEFINED;
   }
}

void IABoard::setTransistionType(uint8_t channel, TRANSITION tran)
{
   if (channel > 4 || channel < 1)
   {
      printf("IA-Board ERROR: Channel out of range! Allowed: 1 - 4\n");
      return;
   }
}

float IABoard::getAnalogVolOut(uint8_t channel)
{
   if (channel > 4 || channel < 1)
   {
      printf("IA-Board ERROR: Channel out of range! Allowed: 1 - 4\n");
      return 0;
   }

   _i2c->writeData(0x04 + 2 * (channel - 1));

   uint8_t voltage[2];
   _i2c->readData(voltage, 2);

   return (float)(voltage[0] + (voltage[1] << 8)) / 1000.f;
}

void IABoard::setAnalogVolOut(uint8_t channel, float voltage)
{
   if (channel > 4 || channel < 1)
   {
      printf("IA-Board ERROR: Channel out of range! Allowed: 1 - 4\n");
      return;
   }
}