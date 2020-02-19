/*
 * SerialConnectionEventHandler.cpp
 *
 *  Created on: Jun 18, 2019
 *      Author: rosenau
 */

#include "SerialConnectionEventHandler.h"
#include <bitset>

namespace Serial {

SerialConnectionEventHandler::SerialConnectionEventHandler(const std::string& p_port, unsigned int p_baud_rate)
: SerialConnection(p_port, p_baud_rate)
{


}

SerialConnectionEventHandler::~SerialConnectionEventHandler()
{

}

void SerialConnectionEventHandler::onConnected() {

}

void SerialConnectionEventHandler::onDisconnected() {

}

void SerialConnectionEventHandler::onReceived(const uint8_t* p_data, size_t)
{

//	Bit Representation of binaryData.
	if((p_data[0]) == 0x01)
	{
		m_dataPackage = 0;
	}

	else if(m_dataPackage == 1)
	{
		m_fingerOut = p_data[0] & 0x01;
	}

	else if(m_dataPackage == 5)
	{
		m_pulseRate = p_data[0] & 0x7F;
	}

	else if(m_dataPackage == 6)
	{
		m_spo2 = p_data[0] & 0x7F;

	}

	m_dataPackage++;

}

void SerialConnectionEventHandler::onSent(const uint8_t* , size_t )
{

}

void SerialConnectionEventHandler::onError(const std::string& , const std::string& )
{

}

int SerialConnectionEventHandler::getPulseRate()
{
	return m_pulseRate;
}

int SerialConnectionEventHandler::getSpo2()
{
	return m_spo2;
}

bool SerialConnectionEventHandler::fingerIsOut()
{
	return m_fingerOut;
}

} /* namespace Serial */
