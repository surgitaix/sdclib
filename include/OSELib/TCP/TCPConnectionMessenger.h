/*
 * TCPConnectionMessenger.h
 *
 *  Created on: Aug 21, 2019
 *      Author: rosenau
 */

#ifndef INCLUDE_OSELIB_TCP_TCPCONNECTIONMESSENGER_H_
#define INCLUDE_OSELIB_TCP_TCPCONNECTIONMESSENGER_H_


#include "TCPConnection.h"
#include "TCPServer.h"

class TCPConnectionMessenger : public Network::TCPConnection
{
public:
	TCPConnectionMessenger(std::shared_ptr<Network::TCPServer> server);
	void sendMessage(const std::string& message);

protected:
	void onError(const std::string& category, const std::string& message) override;
	void onReceived(const void* buffer, size_t size) override;
	void onSent(const void* buffer, size_t size) override;
	void onDisconnected() override;
	void onConnected() override;

	virtual void onMessageReceived(const std::string& ) { }
	virtual void onMessageSent(const std::string& ) { }

private:
	enum class ReceiveState {
		WAIT_FOR_HEADER,
		READ_MSG
	};

	ReceiveState currentState = ReceiveState::WAIT_FOR_HEADER;


	void processMessage(const std::string& message);

	unsigned long msgBytesToRead = 0;
	unsigned long msgBytesRead = 0;
	uint16_t currentMessageNumber;
	std::string receivedMessage = "";
};


#endif /* INCLUDE_OSELIB_TCP_TCPCONNECTIONMESSENGER_H_ */
