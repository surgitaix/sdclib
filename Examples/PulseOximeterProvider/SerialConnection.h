/*
 * SerialConnection.h
 *
 *  Created on: Jun 17, 2019
 *      Author: rosenau
 */

#ifndef EXAMPLES_PULSEOXIMETERPROVIDER_SERIALCONNECTION_H_
#define EXAMPLES_PULSEOXIMETERPROVIDER_SERIALCONNECTION_H_

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

	void send(const char* buffer, size_t size);

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
    virtual void onSent(const uint8_t*, size_t) {}

    /**
     * @brief onReceived
     * Use this function to define the processing of the incoming data.
     */
    virtual void onReceived(const uint8_t* , size_t ) {}

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
    bool m_connected{false};
    std::atomic<bool> m_sending{false};
    std::shared_ptr<Network::ContextWorker> m_contextWorker = std::make_shared<Network::ContextWorker>();
    std::shared_ptr<asio::io_context> m_context;
    asio::io_context::strand m_strand;
    asio::serial_port m_serialPort;
	std::vector<uint8_t> m_receive_buffer{};
	std::vector<uint8_t> m_send_buffer{};
	std::string m_port{};

	// If no measurement takes place, the pulseoximeter will shutdown for energy saving.
	// If it is restarted, no data can be read from it, due to the missing init sequence.
	// This thread periodically checks, if the pulseoximeter is still connected and if not
	// attempts to send the init sequence to the device.
	std::chrono::time_point<std::chrono::steady_clock> m_lastReceive;
	const int m_reconnectTimeInMS{2000};
	std::thread m_reconnectThread;

};

} /* namespace Serial */

#endif /* EXAMPLES_PULSEOXIMETERPROVIDER_SERIALCONNECTION_H_ */
