/*
 * TCPClientEventHandler.cpp
 *
 *  Created on: May 13, 2019
 *      Author: rosenau
 */

#include "OSELib/TCP/TCPClientEventHandler.h"

namespace Network {

std::shared_ptr<TCPClientEventHandler> TCPClientEventHandler::instance = nullptr;


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
		Network::TCPClientMessenger(address, port),
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
		std::cout << "Starting up TCPClientSingelton" << std::endl;
		instance->TCPClient::start();
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
	received = false;
	if(instantiated)
	{
		sendMessage(req);
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

void TCPClientEventHandler::onMessageReceived(const std::string& msg)
{
	std::cout << "Received:\n" << msg << std::endl;
	response = msg;
	received = true;
}

void TCPClientEventHandler::onDisconnected()
{
	std::cout << "TCPClientEventHandler disconnected" << std::endl;
}

void TCPClientEventHandler::onMessageSent(const std::string &msg)
{
	received = false;
}

void TCPClientEventHandler::onError(const std::string & category, const std::string & message)
{
	std::cout << "Error occurred: " << category << ": " << message << std::endl;
}

const std::string TCPClientEventHandler::getResponse()
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

bool TCPClientEventHandler::isStarted()
{
	return started;
}

} /* namespace ACS */
