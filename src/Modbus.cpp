#include "Modbus.hpp"

Modbus::Modbus()
{
   _uart = new UART();
}

Modbus::~Modbus()
{
   delete _uart;
}

void Modbus::transmitRequest(uint16_t startRegister, uint16_t length)
{
   std::vector<uint8_t> msg;

   msg.push_back(_address);
   // Function code "Read Holding Registers"
   msg.push_back(0x03);
   // High Byte and Low Byte of start register
   msg.push_back((startRegister >> 8));
   msg.push_back((startRegister & 0xFF));
   // High Byte and Low Byte of number of registers
   msg.push_back((length >> 8));
   msg.push_back((length & 0xFF));

   // Append Checksum
   uint16_t checksum = 0xE7CE; // calculateCRC(msg);

   msg.push_back((checksum >> 8));
   msg.push_back((checksum & 0xFF));

   std::cout << "Generated message:\n";
   for (auto const &i : msg)
   {
      printf(" %#04x ", i);
   }
   std::cout << std::endl;

   uint8_t message[8] = {0x20, 0x03, 0x0b, 0xe4, 0x00, 0x02, 0xce, 0xe7};

   //_uart->transmitMSG(&msg[0], msg.size());
   _uart->transmitMSG(message, 8);
}

void Modbus::receiveResponse()
{
   std::vector<uint8_t> msg;
   msg = _uart->receiveMSG();

   std::cout << "Received message:\n";
   for (auto const &i : msg)
   {
      std::cout << " " << i << " ";
   }
   std::cout << std::endl;
}

uint16_t Modbus::calculateCRC(std::vector<uint8_t> data)
{
}