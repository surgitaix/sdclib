#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <map>

#include "../../../Dependencies/asio/include/asio.hpp"
#include "OSELib/TCP/TCPConnection.h"
#include "OSELib/TCP/ContextWorker.h"
#include "OSELib/TCP/unused.h"
#include "OSELib/TCP/UUID.h"



namespace Network {
    using asio::ip::tcp;


    static const std::string DEFAULT_ADDRESS = "127.0.0.1";
    static constexpr unsigned int DEFAULT_PORT = 5000;

    /**
     * @brief The TCPServer class
     * The TCPServer class provides capabilities to create connections to multiple TCPClients.
     * Each connection is individually handled by a TCPConnection
     */
    class TCPServer : public std::enable_shared_from_this<TCPServer>
    {
    public:
        TCPServer();
        TCPServer(const std::string& address, unsigned short port);

        //Noncopyable
        TCPServer(const TCPServer&) = delete;
        TCPServer(TCPServer&&) = delete;
        TCPServer& operator=(const TCPServer&) = delete;
        TCPServer& operator=(TCPServer&&) = delete;

	virtual ~TCPServer();

        /**
         * @brief start starts acceptor to handle incoming resolve request to establish
         * connections to TCPClients
         * @return true if the TCPServer was started
         */
        bool start();

        /**
         * @brief stop stops acceptor and closes all open connections
         * @return true if the TCPServer was stopped
         */
        bool stop();

        /**
         * @brief getContextWorker
         * @return _contextWorker of the TCPServer
         */
        std::shared_ptr<ContextWorker>& getContextWorker();

        /**
         * @brief unregisterConnectionHandler
         * @param id removes the TCPConnection with the id from the hash table of connections
         */
        void unregisterConnectionHandler(UUID id);

        const std::string& getAddress() const;
        unsigned short getPort() const;

        void setAddress(const std::string& address);
        void setPort(const unsigned short port);
        void updateEndpoint();


    private:

        /**
         * @brief doAccept
         * accepts incoming resolve requests from TCPClients to create a TCPConnection to them.
         */
        void doAccept();

        /**
         * @brief registerConnection
         * registers the new Connection established during doAccept in the _connections hash table.
         */
        void registerConnection();

        void disconnectAll();

        void sendError(std::error_code ec);

    public:
        /**
         * @brief onConnected
         * Use this function to define the behavior onConnected.
         */
        virtual void onConnected(std::shared_ptr<TCPConnection> ) {}

        /**
         * @brief onDisconnected
         * Use this function to define the behavior onDisconnected.
         */
        virtual void onDisconnected(std::shared_ptr<TCPConnection> ) {}

    protected:
        /**
         * @brief onStarted
         * Use this function to define the behavior onStarted.
         */
        virtual void onStarted() {}

        /**
         * @brief onStopped
         * Use this function to define the behavior onStopped.
         */
        virtual void onStopped() {}

        /**
         * @brief onError
         * Use this function to define the behavior onError.
         */
        virtual void onError(const std::string & category, const std::string & message)
        {
            unused(category, message);
        }

        /**
         * @brief createConnection
         * @param server pointer to the TCPServer that creates the connection
         * @return std::shared_pointer<TCPConnection> TCPConnection pointer
         */
       virtual std::shared_ptr<TCPConnection> createConnection(std::shared_ptr<TCPServer> server);

	std::shared_ptr<TCPConnection> _connection;
	std::map<UUID, std::shared_ptr<TCPConnection>> _connections;
    private:
        bool _started;
        bool _accepting;
        std::shared_ptr<ContextWorker> _contextWorker;
        std::shared_ptr<asio::io_context> _context;
        asio::io_context::strand _strand;
        std::string _address;
        unsigned short _port;
        tcp::acceptor _acceptor;
        asio::ip::tcp::endpoint _endpoint;

    };
}

#endif // TCPSERVER_H
