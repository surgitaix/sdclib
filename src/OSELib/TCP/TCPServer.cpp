#include "OSELib/TCP/TCPServer.h"

#include <iostream>

#include "../../../Dependencies/asio/include/asio/high_resolution_timer.hpp"
#include "../../../Dependencies/asio/include/asio.hpp"


namespace Network {

    TCPServer::TCPServer() :
        _started(false),
        _accepting(false),
        _contextWorker(new ContextWorker()),
        _context(_contextWorker->getContext()),
        _strand(*_context),
        _address(DEFAULT_ADDRESS),
        _port(DEFAULT_PORT),
        _acceptor(*_context)
    {
        if(_context == nullptr) {
            throw std::runtime_error("Invalid context!");
        }
         _endpoint = tcp::endpoint(asio::ip::make_address(_address), _port);
    }

    TCPServer::TCPServer(const std::string& address, unsigned short port) :
        _started(false),
        _accepting(false),
        _contextWorker(new ContextWorker()),
        _context(_contextWorker->getContext()),
        _strand(*_context),
        _address(address),
        _port(port),
        _acceptor(*_context)
    {
       if(_context == nullptr) {
           throw std::runtime_error("Invalid context!");
       }
        _endpoint = tcp::endpoint(asio::ip::make_address(_address), _port);
    }

	TCPServer::~TCPServer()
	{

	}


    bool TCPServer::start()
    {
        if(_started)
        {
            std::cout << "TCP server is already running";
            return false;
        }

        auto self(this->shared_from_this());
        auto startHandler = [this, self]()
        {
            if(_started)
            {
                std::cout << "TCP server is already running";
                return;
            }
            _acceptor = tcp::acceptor(*_context);
            _acceptor.open(_endpoint.protocol());
            _acceptor.bind(_endpoint);
            _acceptor.listen();
            _started = true;

            onStarted();

            doAccept();
        };
        _strand.post(startHandler);
        _contextWorker->start();
        return true;
    }

    bool TCPServer::stop()
    {
        if(!_started)
        {
            return false;
        }

        auto self(this->shared_from_this());
        auto stop_handler = [this, self]()
        {
            _connection.reset();

            _acceptor.close();

            disconnectAll();

            _started = false;
        };
        _strand.post(stop_handler);

        return true;
    }

    void TCPServer::doAccept() {
        if(_accepting)
        {
            return;
        }
        if(!_started)
        {
            return;
        }

        _accepting = true;
        auto self(this->shared_from_this());
        auto acceptHandler = [this, self]()
        {
          _accepting = false;
          if(!_started)
          {
              return;
          }
          _connection = createConnection(self);

          auto asyncAcceptHandler = [this, self](std::error_code ec)
          {
              if(!ec)
              {
                  registerConnection();
                  _connection->connect();
              }
              else {
                  sendError(ec);
              }

              doAccept();

          };
          _acceptor.async_accept(_connection->getSocket(), asio::bind_executor(_strand, asyncAcceptHandler));
        };
        _strand.dispatch(acceptHandler);
    }

    void TCPServer::registerConnection()
    {
		_connections.emplace(_connection->getId(), _connection);
    }

    std::shared_ptr<ContextWorker>& TCPServer::getContextWorker()
    {
        return _contextWorker;
    }

	void TCPServer::unregisterConnectionHandler(UUID id)
    {
        if(_connections[id] != nullptr)
        {
            _connections[id]->disconnect();
            _connections.erase(id);
        }
    }

    void TCPServer::disconnectAll()
    {
        if(!_started)
        {
            return;
        }

        auto self(this->shared_from_this());
        auto disconnect_all_handler = [this, self]()
        {
            if(!_started)
            {
                return;
            }
            for (auto& connection : _connections)
            {
                connection.second->disconnect();
            }
        };
        _strand.dispatch(disconnect_all_handler);
    }

    std::shared_ptr<TCPConnection> TCPServer::createConnection(std::shared_ptr<TCPServer> server)
    {
        return std::make_shared<TCPConnection>(server);
    }

    void TCPServer::sendError(std::error_code ec)
    {
        // Skip end of file error
        if (ec == asio::error::eof) {
            return;
        }
        onError(ec.category().name(), ec.message());
    }

    unsigned short TCPServer::getPort() const
    {
        return _port;
    }

    const std::string& TCPServer::getAddress() const
    {
        return _address;
    }

    void TCPServer::setPort(const unsigned short port)
    {
        _port = port;
        updateEndpoint();
    }

    void TCPServer::setAddress(const std::string& address)
    {
        _address = address;
        updateEndpoint();
    }

    void TCPServer::updateEndpoint()
    {
        _endpoint = tcp::endpoint(asio::ip::make_address(_address), _port);
    }


} // end Network
