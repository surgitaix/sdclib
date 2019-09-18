/*
 * TCPConnectionMessenger.cpp
 *
 *  Created on: Aug 21, 2019
 *      Author: rosenau
 */


#include "OSELib/TCP/TCPConnectionMessenger.h"
#include <chrono>


struct tcp_message_header {
	uint32_t size;
	uint64_t timestamp;
	uint16_t msgNumber;
	uint8_t dropMessage;
	uint8_t delayMessage;
	uint32_t delayDuration;
};

struct tcp_message {
	tcp_message_header header;
	std::vector<char> data;
};

TCPConnectionMessenger::TCPConnectionMessenger(std::shared_ptr<Network::TCPServer> server)	:
	Network::TCPConnection(server),
	currentMessageNumber(0)
{

}

void TCPConnectionMessenger::onReceived(const void *buffer, size_t size)
{
	std::cout << "receiving tcp frame" << std::endl;

	bool readHeader = false;

	std::shared_ptr<tcp_message_header> header = std::make_shared<tcp_message_header>();

	if(currentState == ReceiveState::WAIT_FOR_HEADER && size > sizeof (header))
	{
		std::memcpy(header.get(), buffer, sizeof (tcp_message_header));
		if(header->size == 0)
		{
			return;
		}
		msgBytesToRead = header->size;
		std::cout << "Bytes to Read " << msgBytesToRead << std::endl;
		std::cout << "Timestamp" << header->timestamp << std::endl;
		currentState = ReceiveState::READ_MSG;
		readHeader = true;
	}
		if(currentState == ReceiveState::READ_MSG)
		{
			if(readHeader)
			{
				std::cout << "Header size" << sizeof(tcp_message_header) << std::endl;
				std::cout << "reading after header!" << std::endl;
				const char* p = static_cast<const char*>(buffer);
				receivedMessage = std::string(p + sizeof (tcp_message_header), size - sizeof (tcp_message_header));
				std::cout << receivedMessage.size();
				while (!receivedMessage.empty() && *receivedMessage.rbegin() == 0)
					receivedMessage.resize(receivedMessage.size() - 1);
				msgBytesRead += size;
				std::cout << "Bytes read: " << msgBytesRead << std::endl;
				msgBytesToRead -= size;
				std::cout << "Remeaining bytes to be read: " << msgBytesToRead << std::endl;
			}
			else
			{
				receivedMessage += std::string(static_cast<const char*>(buffer), size);
				while (!receivedMessage.empty() && *receivedMessage.rbegin() == 0)
					receivedMessage.resize(receivedMessage.size() - 1);
				msgBytesRead += size;
				std::cout << "Bytes read: " << msgBytesRead << std::endl;
				msgBytesToRead -= size;
				std::cout << "Remeaining bytes to be read: " << msgBytesToRead << std::endl;
			}
		}
		if(msgBytesToRead <= 0)
		{
			msgBytesRead = 0;
			msgBytesToRead = 0;
			std::cout << "message fully read" << std::endl;
			std::cout << receivedMessage;
			onMessageReceived(receivedMessage);
			receivedMessage.clear();
			currentState = ReceiveState::WAIT_FOR_HEADER;
		}
}

void TCPConnectionMessenger::onSent(const void *buffer, size_t size)
{

}

void TCPConnectionMessenger::onError(const std::string &category, const std::string &message)
{

}

void TCPConnectionMessenger::onDisconnected()
{
	std::cout << "TCPConnectionMessenger disconnected: resetting..." << std::endl;
	msgBytesRead = 0;
	msgBytesToRead = 0;
	currentMessageNumber = 0;
}

void TCPConnectionMessenger::onConnected()
{

}

void TCPConnectionMessenger::sendMessage(const std::string &message)
{
	tcp_message_header header;
	header.msgNumber = currentMessageNumber;
	header.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	header.delayMessage = 0;
	header.delayDuration = 0;
	header.dropMessage = 0;
	header.size = sizeof (tcp_message_header) + message.size();
	const void* v_pointer = static_cast<const void*>(&header);
	const char* c_pointer = static_cast<const char*>(v_pointer);
	std::string data = std::string(c_pointer, sizeof(tcp_message_header));
	data.append(message);
	send(data.c_str(), header.size);
	onMessageSent(message);
}
