/*
 * TCPClientEventHandler.h
 *
 *  Created on: May 13, 2019
 *      Author: sebastian
 */

#ifndef EXAMPLES_ABSTRACTCONSUMERSIMULATOR_TCPCLIENTEVENTHANDLER_H_
#define EXAMPLES_ABSTRACTCONSUMERSIMULATOR_TCPCLIENTEVENTHANDLER_H_

#include "OSELib/TCP/TCPClient.h"

namespace Network {

class TCPClientEventHandler : public TCPClient{
public:
	static std::shared_ptr<TCPClientEventHandler> getInstance(const std::string& address, const unsigned short port);
	virtual ~TCPClientEventHandler();

	void startup();
	void shutdown();

	void sendRequest(const std::string& req);
	std::string getResponse();

	bool responseReceived();
	bool isInstantiated();

private:
	TCPClientEventHandler(const std::string& address, const unsigned short port);
	TCPClientEventHandler(const TCPClientEventHandler&);
	TCPClientEventHandler& operator=(const TCPClientEventHandler&);

	void onConnected() override;
	void onDisconnected() override;
	void onSent() override;
	void onReceived(void* msg, size_t size) override;
	void onError(const std::string& category, const std::string& message) override;

private:
	static std::shared_ptr<TCPClientEventHandler> instance;
	bool started;
	bool instantiated;
	bool received;
	std::string response;


};

} /* namespace ACS */

#endif /* EXAMPLES_ABSTRACTCONSUMERSIMULATOR_TCPCLIENTEVENTHANDLER_H_ */
