/*
 * TCPClientEventHandler.cpp
 *
 *  Created on: May 13, 2019
 *      Author: sebastian
 */

#include "OSELib/TCP/TCPClientEventHandler.h"

std::shared_ptr<Network::TCPClientEventHandler> Network::TCPClientEventHandler::instance = nullptr;

namespace Network {

TCPClientEventHandler::~TCPClientEventHandler() {
	shutdown();
}

std::shared_ptr<TCPClientEventHandler> TCPClientEventHandler::getInstance(const std::string& address, const unsigned short port)
{
	if(instance == nullptr)
	{
		instance = std::shared_ptr<TCPClientEventHandler>(new TCPClientEventHandler(address, port));
	}
	return instance;
}

TCPClientEventHandler::TCPClientEventHandler(const std::string& address, const unsigned short port) :
		TCPClient(address, port),
		started(false),
		instantiated(true),
		received(false),
		response("")
{
}

void TCPClientEventHandler::startup()
{
	if(!instantiated || started)
	{
		return;
	}
	else
	{
		instance->start();
		received = false;
		response = "";
		started = true;
	}
}

void TCPClientEventHandler::shutdown()
{
	if(!instantiated)
		return;
	else
	{
		instance->stop();
	}
}

void TCPClientEventHandler::sendRequest(const std::string& req)
{
	if(instantiated)
	{
		received = false;
		send(req.c_str(), sizeof(req));
	}
}

bool TCPClientEventHandler::responseReceived()
{
	return received;
}

void TCPClientEventHandler::onConnected()
{
	std::cout << "TCPClientEventHandler connected" << std::endl;
}

void TCPClientEventHandler::onReceived(void* msg, size_t size)
{
	response = std::string(static_cast<const char*>(msg), size);
	received = true;
}

void TCPClientEventHandler::onDisconnected()
{
	std::cout << "TCPClientEventHandler disconnected" << std::endl;
}

void TCPClientEventHandler::onSent()
{
	received = false;
}

void TCPClientEventHandler::onError(const std::string & category, const std::string & message)
{
	std::cout << "Error occurred: " << category << ": " << message << std::endl;
}

std::string TCPClientEventHandler::getResponse()
{
	if(instantiated)
	{
		return response;
	}
	return "";
}

bool TCPClientEventHandler::isInstantiated()
{
	return instantiated;
}

} /* namespace ACS */
