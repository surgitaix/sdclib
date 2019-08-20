/*
 * TCPClientMessenger.h
 *
 *  Created on: Jul 8, 2019
 *      Author: rosenau
 */

#ifndef TCPCLIENTMESSENGER_H_
#define TCPCLIENTMESSENGER_H_

#include "../../../include/OSELib/TCP/TCPClient.h"

namespace Network {

class TCPClientMessenger : public TCPClient
{
public:
	TCPClientMessenger(const std::string& address, unsigned short port);
	virtual ~TCPClientMessenger();
protected:
	void onError(const std::string& category, const std::string& message) ;
	void onReceived(const void* buffer, size_t size) ;
	void onSent(const void* buffer, size_t size) ;
	void onDisconnected() ;
	void onConnected() ;
	void sendMessage(const std::string& message);

	virtual void onMessageReceived(const std::string& ) { }
	virtual void onMessageSent(const std::string& ) { }

private:
	void processMessage(const std::string& message);

	enum class ReceiveState {
		WAIT_FOR_HEADER,
		READ_MSG
	};

	ReceiveState currentState = ReceiveState::WAIT_FOR_HEADER;

	uint16_t currentMessageNumber = 0;
	unsigned long msgBytesRead = 0;
	unsigned long msgBytesToRead = 0;
	std::string receivedMessage = "";
};

}

#endif /* INCLUDE_OSELIB_TCP_TCPCLIENTMESSENGER_H_ */
