#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <iostream>
#include <memory>
#include <string>

#include "../../../Dependencies/asio/include/asio.hpp"
#include "unused.h"
#include "OSELib/TCP/UUID.h"

namespace  Network{
    using asio::ip::tcp;
    class TCPServer;

    /**
     * @brief The TCPConnection class
     * The TCPConnection handels the connection between a TCPServer and a TCPClient.
     * As well as the message transport between them.
     */
    class TCPConnection : public std::enable_shared_from_this<TCPConnection> {

    public:
        TCPConnection(std::shared_ptr<TCPServer> server);

        //Noncopyable
        TCPConnection(const TCPConnection&) = delete;
        TCPConnection(TCPConnection&&) = delete;
        TCPConnection& operator=(const TCPConnection&) = delete;
        TCPConnection& operator=(TCPConnection&&) = delete;

        virtual ~TCPConnection() = default;

        /**
         * @brief connect
         * Creates a new connection and starts receive and send handler.
         */
        void connect();

        /**
         * @brief disconnect
         * Disconnectes the connection.
         */
        void disconnect();

        /**
         * @brief send
         * Sends the buffer of a given size out over the
         * @param buffer data to be send
         * @param size size of the data to be send
         */
		void send(const void *buffer, size_t size);

        UUID& getId();
        tcp::socket& getSocket();


    protected:
        /**
         * @brief onError
         * Use this function to define the behavior onError.
         * @param categroy error category
         * @param message error message
         */
        virtual void onError(const std::string& category, const std::string& message)
        {
            unused (category, message);
        }

        /**
         * @brief onConnected
         * Use this function to define the behavior onConnected.
         */
        virtual void onConnected() {}

        /**
         * @brief onDisconnected
         * Use this function to define the behavior onDisconnected.
         */
        virtual void onDisconnected() {}

        /**
         * @brief onReceived
         * Use this function to define the behavior onReceived.
         */
        virtual void onReceived(const void* buffer, size_t size) { unused(buffer, size); }

        /**
         * @brief onSent
         * Use this function to define the behavior onReceived.
         */
        virtual void onSent(const void* buffer, size_t size) { unused(buffer, size); }


    private:
        /**
         * @brief tryReceive
         * Tries to asynchronicly receive data from the connected TCPClient.
         */
        void tryReceive();

        /**
         * @brief trySend
         * Tries to asynchronicyl send data to the connected TCPClient.
         */
        void trySend();
        void sendError(std::error_code ec);


    private:
	UUID _id;
	size_t _defaultBufferSize = 1024;
        std::shared_ptr<TCPServer> _server;
        std::shared_ptr<asio::io_service> _context;
        asio::ip::tcp::socket _socket;
        asio::io_context::strand _strand;
        std::atomic<bool> _connected;
        std::atomic<bool> _receiving;
        std::atomic<bool> _sending;
        std::vector<uint8_t> _receive_buffer;
        std::vector<uint8_t> _send_buffer;
    };
}



#endif // TCPCONNECTION_H
