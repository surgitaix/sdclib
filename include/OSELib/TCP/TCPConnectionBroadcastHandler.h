	/*
 * TCPConnectionBroadcastHandler.h
 *
 *  Created on: Aug 21, 2019
 *      Author: rosenau
 */

#ifndef INCLUDE_OSELIB_TCP_TCPCONNECTIONBROADCASTHANDLER_H_
#define INCLUDE_OSELIB_TCP_TCPCONNECTIONBROADCASTHANDLER_H_

#include "TCPConnectionMessenger.h"
#include "TCPServer.h"

class TCPConnectionBroadcastHandler : public TCPConnectionMessenger
{
public:
	TCPConnectionBroadcastHandler(std::shared_ptr<Network::TCPServer> server);

protected:
    void onError(const std::string& category, const std::string& message) override;
	void onMessageReceived(const std::string& message) override;
	void onMessageSent(const std::string& message) override;
    void onDisconnected() override;
    void onConnected() override;

    /**
     * \brief This is a broadcast server who does not receive incoming messages!
     */
    void onReceived(const void* , size_t ) override;
};



#endif /* INCLUDE_OSELIB_TCP_TCPCONNECTIONBROADCASTHANDLER_H_ */
