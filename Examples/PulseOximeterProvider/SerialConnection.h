/*
 * SerialConnection.h
 *
 *  Created on: Jun 17, 2019
 *      Author: rosenau
 */

#ifndef EXAMPLES_PULSEOXIMETERPROVIDER_SERIALCONNECTION_H_
#define EXAMPLES_PULSEOXIMETERPROVIDER_SERIALCONNECTION_H_

#include <iostream>
#include <chrono>
#include <thread>

#include "asio.hpp"
#include "ContextWorker.h"

namespace Serial {

template <typename... Args> inline void unused(Args&&...) {}

class SerialConnection : public std::enable_shared_from_this<SerialConnection> {
public:
	SerialConnection(std::string port, unsigned int baud_rate);

	//Noncopyable
	SerialConnection(const SerialConnection&) = delete;
	SerialConnection(SerialConnection&&) = delete;
	SerialConnection& operator=(const SerialConnection&) = delete;
	SerialConnection& operator=(SerialConnection&&) = delete;

	virtual ~SerialConnection();

	void start();

	void stop();

	void send(const void* buffer, size_t size);

	void writeString(std::string outString);

	void tryReceive();

	bool isConnected();

private:
	void connect(const std::string &port, unsigned int baud_rate);

	void trySend();

	void disconnect();

	void sendError(std::error_code ec);

	void flush(std::string port);

	void reconnect();

protected:
    /**
     * @brief onConnected
     * Use this function to define the behavior when a connection is established.
     */
    virtual void onConnected() {}

    /**
     * @brief onDisconnected
     * Use this function to define the behavior when a connection is closed
     */
    virtual void onDisconnected() {}

    /**
     * @brief onSent
     * Use this function to define the behavior when a data is send.
     */
    virtual void onSent(const void*, size_t) {}

    /**
     * @brief onReceived
     * Use this function to define the processing of the incoming data.
     */
    virtual void onReceived(const void* , size_t ) { std::cout << "Test " << std::endl;}

    /**
     * @brief onError
     * Use this function to define the behavior when an error occurs.
     * @param category error category
     * @param message error message
     */
    virtual void onError(const std::string& category, const std::string& message) {
        unused(category, message);
    }

private:
    bool _connected;
    std::atomic<bool> _sending;
    std::shared_ptr<Network::ContextWorker> _contextWorker;
    std::shared_ptr<asio::io_context> _context;
    asio::io_context::strand _strand;
    asio::serial_port _serialPort;
	std::vector<uint8_t> _receive_buffer;
	std::vector<uint8_t> _send_buffer;
	std::string _port;

	std::chrono::time_point<std::chrono::steady_clock> m_lastReceive;
	const int m_reconnectTimeInMS = 2000;
	std::thread m_reconnectThread;

};

} /* namespace Serial */

#endif /* EXAMPLES_PULSEOXIMETERPROVIDER_SERIALCONNECTION_H_ */
