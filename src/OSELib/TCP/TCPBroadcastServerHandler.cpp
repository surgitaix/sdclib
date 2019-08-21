/*
 * TCPBroadcastServerHandler.cpp
 *
 *  Created on: Aug 21, 2019
 *      Author: rosenau
 */

#include "OSELib/TCP/TCPBroadcastServerHandler.h"

namespace Network {

std::shared_ptr<TCPBroadcastServerHandler> TCPBroadcastServerHandler::instance = nullptr;

std::shared_ptr<TCPBroadcastServerHandler> TCPBroadcastServerHandler::getInstance(const std::string & address, unsigned short int port)
{
	if(instance == nullptr)
	{
		instance = std::shared_ptr<TCPBroadcastServerHandler>(new TCPBroadcastServerHandler(address, port));
	}
	return instance;
}

TCPBroadcastServerHandler::TCPBroadcastServerHandler(const std::string address, const unsigned short port) :
		Network::TCPServer (address, port),
		started(false),
		instantiated(false)
{

}

void TCPBroadcastServerHandler::startup() {
	if(!instantiated || started)
	{
		return;
	}
	else
	{
		std::cout << "Starting up TCPServerSingelton" << std::endl;
		instance->TCPServer::start();
	}
}

void TCPBroadcastServerHandler::shutdown() {
	if(!instantiated)
	{
		return;
	}
	else
	{
		instance->TCPServer::stop();
	}

}

void TCPBroadcastServerHandler::broadcastMessage(const std::string& msg)
{
	 for(auto connection : TCPServer::_connections)
	 {
		 std::static_pointer_cast<TCPConnectionMessenger>(connection.second)->sendMessage(msg);
	 }
}

TCPBroadcastServerHandler::~TCPBroadcastServerHandler()
{

}

void TCPBroadcastServerHandler::onConnected(std::shared_ptr<Network::TCPConnection> connection) {
	_curentUUID = connection->getId();
	std::shared_ptr<TCPConnectionBroadcastHandler> derived = std::dynamic_pointer_cast<TCPConnectionBroadcastHandler> (connection);
}

void TCPBroadcastServerHandler::onDisconnected(std::shared_ptr<Network::TCPConnection>) {

}

void TCPBroadcastServerHandler::onError(const std::string &category, const std::string &message) {

}

void TCPBroadcastServerHandler::onStarted() {

}

void TCPBroadcastServerHandler::onStopped() {

}

std::shared_ptr<Network::TCPConnection> TCPBroadcastServerHandler::createConnection(std::shared_ptr<Network::TCPServer> server){
	return std::make_shared<TCPConnectionBroadcastHandler>(server);
}

}
