/*
 * TCPBroadcastServerHandler.h
 *
 *  Created on: Aug 21, 2019
 *      Author: rosenau
 */

#ifndef SRC_OSELIB_TCP_TCPBROADCASTSERVERHANDLER_H_
#define SRC_OSELIB_TCP_TCPBROADCASTSERVERHANDLER_H_

#include "TCPServer.h"
#include "TCPConnection.h"
#include "TCPConnectionBroadcastHandler.h"

namespace Network {

class TCPBroadcastServerHandler : public Network::TCPServer {
public:
	static std::shared_ptr<TCPBroadcastServerHandler> getInstance(const std::string& address, const unsigned short port);
	virtual ~TCPBroadcastServerHandler();

	void startup();
	void shutdown();

	void broadcastMessage(const std::string& msg);

	bool isInstantiated();


protected:
    void onConnected(std::shared_ptr<Network::TCPConnection> ) override;
    void onDisconnected(std::shared_ptr<Network::TCPConnection> ) override;
    void onStarted() override;
    void onStopped() override;
    void onError(const std::string & category, const std::string & message) override;

    /**
     * @brief createConnection
     * overrides the createConnection of TCPServer to create a TCPConnectionBroadcastHandler on createConnection
     * to define userspecific even behavior for onEvent in TCPConnection.
     * @param server pointer to the TCPServer that creates the connection (self)
     * @return std::shared_pointer<TCPConnection> TCPConnectionBroadcastHandler pointer to handle events
     */
    std::shared_ptr<Network::TCPConnection> createConnection(std::shared_ptr<TCPServer> server) override;

private:
    TCPBroadcastServerHandler(const std::string address, const unsigned short port);
	TCPBroadcastServerHandler(const TCPBroadcastServerHandler&);
	TCPBroadcastServerHandler& operator=(const TCPBroadcastServerHandler&);

private:
	Network::UUID _curentUUID;
	bool started;
	bool instantiated;
	static std::shared_ptr<TCPBroadcastServerHandler> instance;

};
}

#endif /* SRC_OSELIB_TCP_TCPBROADCASTSERVERHANDLER_H_ */
