/*
 * TCPConnectionBroadcastHandler.cpp
 *
 *  Created on: Aug 21, 2019
 *      Author: rosenau
 */

#include "OSELib/TCP/TCPConnectionBroadcastHandler.h"


TCPConnectionBroadcastHandler::TCPConnectionBroadcastHandler(std::shared_ptr<Network::TCPServer> server) : TCPConnectionMessenger (server)
{

}

void TCPConnectionBroadcastHandler::onError(const std::string& category, const std::string& message) {
	std::cout << "An error occurred " << category << " " << message << std::endl;
}

void TCPConnectionBroadcastHandler::onMessageReceived(const std::string& message) {
}

void TCPConnectionBroadcastHandler::onMessageSent(const std::string& message) {
	std::cout << "message sent " << message << std::endl;
}


void TCPConnectionBroadcastHandler::onConnected() {
}

void TCPConnectionBroadcastHandler::onDisconnected() {
}


void TCPConnectionBroadcastHandler::onReceived(const void* , size_t ) {
//Ignore incoming messages!
}


