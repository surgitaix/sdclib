#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "../../../Dependencies/asio/include/asio.hpp"
#include "OSELib/TCP/ContextWorker.h"
#include "unused.h"


namespace Network {
    using asio::ip::tcp;

    /**
     * @brief The TCPClient class
     * The TCPClient class provides capabilities to create a connection to a TCPServer.
     * And to send and receive data. All processes are executed asynchronicly in a seperate thread provided
     * by the ContextWorker
     */
    class TCPClient : public std::enable_shared_from_this<TCPClient>
    {
    public:

        TCPClient(const std::string& address, unsigned short port);

        //Noncopyable
        TCPClient(const TCPClient&) = delete;
        TCPClient(TCPClient&&) = delete;
        TCPClient& operator=(const TCPClient&) = delete;
        TCPClient& operator=(TCPClient&&) = delete;

        virtual ~TCPClient();
        /**
         * @brief start
         * Tries to resolve for the given endpoint defined by the address and port in the constructor
         * and starts a Network::ContextWorker in a seperate thread to handle the connection
         */
        void start();

        /**
         * @brief stop
         * Closes the open socket and stops the Network::ContextWorker.
         */
        void stop();

        /**
         * @brief send
         * Sends the buffer of a given size out over the
         * @param buffer data to be send
         * @param size size of the data to be send
         */
        void send(const void* buffer, size_t size);

        void tryReceive();


    private:
        void connect(tcp::resolver::results_type endpoints);

        void disconnect();

        //void tryReceive();

        void trySend();

        void sendError(std::error_code ec);

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
        virtual void onSent() {}

        /**
         * @brief onReceived
         * Use this function to define the processing of the incoming data.
         */
        virtual void onReceived(void* , size_t ) {}

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
        std::shared_ptr<ContextWorker> _contextWorker;
        std::shared_ptr<asio::io_context> _context;
        tcp::resolver::query _query;
        tcp::resolver _resolver;
        tcp::socket _socket;
        asio::streambuf _inputBuffer;
        tcp::resolver::results_type _endpoints;
        tcp::endpoint _endpoint;
        asio::io_context::strand _strand;
        std::vector<uint8_t> _receive_buffer;
        std::vector<uint8_t> _send_buffer;


    };
} // end Network

#endif // TCPCLIENT_H
