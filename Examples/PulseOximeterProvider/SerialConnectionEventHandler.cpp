/*
 * SerialConnectionEventHandler.cpp
 *
 *  Created on: Jun 18, 2019
 *      Author: sebastian
 */

#include "SerialConnectionEventHandler.h"
#include <bitset>

namespace Serial {

SerialConnectionEventHandler::SerialConnectionEventHandler(const std::string& port, unsigned int baud_rate)
: SerialConnection(port, baud_rate),
  spo2(0),
  pulseRate(0),
  dataPackage(0)
{


}

SerialConnectionEventHandler::~SerialConnectionEventHandler()
{

}

void SerialConnectionEventHandler::onConnected() {

}

void SerialConnectionEventHandler::onDisconnected() {

}

void SerialConnectionEventHandler::onReceived(const void* data, size_t size)
{
//	const uint8_t* ptr = reinterpret_cast<const uint8_t*>(data);
//	for(unsigned int i = 0; i < size; i++)
//	{
//		std::bitset<8> bitRepresentation (ptr[i]);
//		std::cout << bitRepresentation.to_string();
//	}
//	std::cout << std::endl;

	const uint8_t* binaryData = reinterpret_cast<const uint8_t*>(data);
	if((binaryData[0]) == 0x01)
	{
		dataPackage = 0;
	}

	if(dataPackage == 5)
	{
		pulseRate = binaryData[0] & 0x7F;
		//std::cout << "spo2:" << pulseRate << std::endl;
	}

	if(dataPackage == 6)
	{
		spo2 = binaryData[0] & 0x7F;
		//std::cout << "pulseRate: " << spo2 << std::endl;

	}

	dataPackage++;



//	if(size != 9)
//	{
//		std::cout << size << std::endl;
//		//invalid data
//		return;
//	}
//
//	const uint8_t* binaryData = reinterpret_cast<const uint8_t*>(data);
//
//	if(binaryData[0] != 0x01)
//	{
//		return;
//	}
//
//	spo2 = binaryData[5] & 0x7F;
//	pulseRate = binaryData[6] & 0x7F;
//	std::cout << "pulseRate: " << spo2 << std::endl;
//	std::cout << "spo2:" << pulseRate << std::endl;

}

void SerialConnectionEventHandler::onSent(const void* data, size_t size)
{

}

void SerialConnectionEventHandler::onError(const std::string& category, const std::string& message)
{

}

int SerialConnectionEventHandler::getPulseRate()
{
	return pulseRate;
}

int SerialConnectionEventHandler::getSpo2()
{
	return spo2;
}

} /* namespace Serial */
