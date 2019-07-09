/*
 * TCPClientEventHandler.h
 *
 *  Created on: May 13, 2019
 *      Author: sebastian
 */

#ifndef TCPCLIENTEVENTHANDLER_H_
#define TCPCLIENTEVENTHANDLER_H_

#include "OSELib/TCP/TCPClientMessenger.h"

namespace Network {

class TCPClientEventHandler : public TCPClientMessenger{
public:
	static std::shared_ptr<TCPClientEventHandler> getInstance(const std::string& address, const unsigned short port);
	~TCPClientEventHandler();

	void startup();
	void shutdown();

	void sendRequest(const std::string& req);
	const std::string getResponse();

	bool responseReceived();
	bool isInstantiated();

private:
	TCPClientEventHandler(const std::string& address, const unsigned short port);
	TCPClientEventHandler(const TCPClientEventHandler&);
	TCPClientEventHandler& operator=(const TCPClientEventHandler&);

	void onConnected() override;
	void onDisconnected() override;
	void onMessageSent(const std::string& msg) override;
	void onMessageReceived(const std::string& msg) override;
	void onError(const std::string& category, const std::string& message) override;


private:
	static std::shared_ptr<TCPClientEventHandler> instance;
	bool started;
	bool instantiated;
	std::atomic<bool> received;
	std::string response;


};

}

#endif /* TCPCLIENTEVENTHANDLER_H_ */
