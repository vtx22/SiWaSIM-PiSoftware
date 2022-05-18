#include "Modbus.hpp"

Modbus::Modbus(UART *uart) : _uart(uart)
{
}

Modbus::~Modbus()
{
}

void Modbus::transmitRequest(uint16_t register, uint16_t length)
{
   std::vector<uint8_t> msg;

   msg.push_back(_address);
   // Function code "Read Holding Registers"
   msg.push_back(0x03);
   // High Byte and Low Byte of start register
   msg.push_back((register >> 8));
   msg.push_back((register & 0xFF));
   // High Byte and Low Byte of number of registers
   msg.push_back((length >> 8));
   msg.push_back((length & 0xFF));

   // Append Checksum
   uint16_t checksum = 0xE7CE; // calculateCRC(msg);

   msg.push_back((checksum & 0xFF));
   msg.push_back((checksum >> 8));

   _uart->transmitMSG(&msg[0], msg.size());
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