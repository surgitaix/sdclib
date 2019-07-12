/*
 * SerialConnectionEventHandler.cpp
 *
 *  Created on: Jun 18, 2019
 *      Author: rosenau
 */

#include "SerialConnectionEventHandler.h"
#include <bitset>

namespace Serial {

SerialConnectionEventHandler::SerialConnectionEventHandler(const std::string& port, unsigned int baud_rate)
: SerialConnection(port, baud_rate),
  spo2(0),
  pulseRate(0),
  dataPackage(0),
  fingerOut(true)
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

//	Bit Representation of binaryData.
//	std::bitset<8> bitRepresentation (binaryData[0]);
//	std::cout << bitRepresentation.to_string() << std::endl;
	const uint8_t* binaryData = reinterpret_cast<const uint8_t*>(data);
	if((binaryData[0]) == 0x01)
	{
		dataPackage = 0;
	}

	else if(dataPackage == 1)
	{
		fingerOut = binaryData[0] &0X01;
	}

	else if(dataPackage == 5)
	{
		pulseRate = binaryData[0] & 0x7F;
	}

	else if(dataPackage == 6)
	{
		spo2 = binaryData[0] & 0x7F;

	}

	dataPackage++;

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

bool SerialConnectionEventHandler::fingerIsOut()
{
	return fingerOut;
}

} /* namespace Serial */
