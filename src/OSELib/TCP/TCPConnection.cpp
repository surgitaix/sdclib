#include "OSELib/TCP/TCPConnection.h"
#include "OSELib/TCP/TCPServer.h"

namespace Network {

    TCPConnection::TCPConnection(std::shared_ptr<TCPServer> server) :
        _id("6ba7b810-9dad-11d1-80b4-0c04fd430c8"),
        _server(server),
        _context(server->getContextWorker()->getContext()),
        _socket(*_context),
        _strand(*_context),
        _connected(false)
    {
    }


    void TCPConnection::connect()
    {
        _connected = true;

        onConnected();

        auto connection(this->shared_from_this());
        _server->onConnected(connection);

        _receive_buffer.resize(_defaultBufferSize);
        tryReceive();
        trySend();
    }

    void TCPConnection::disconnect()
    {
        if(!_connected)
        {
            return;
        }

        auto self(this->shared_from_this());
        auto disconnectHandler = [this, self]()
        {
            if(!_connected)
            {
                return;
            }
            _socket.close();
            _connected = false;

            onDisconnected();

            auto connection(this->shared_from_this());
            _server->onDisconnected(connection);

            auto unregisterConnectionHandler = [this, self](){
                _server->unregisterConnectionHandler(_id);
            };
            //_server->_strand.dispatch(unregisterConnectionHandler);
       };
       _strand.dispatch(disconnectHandler);
    }

    void TCPConnection::tryReceive()
    {
        if(_receiving)
        {
            return;
        }
        if(!_connected)
        {
            return;
        }

        _receiving = true;
        auto self(this->shared_from_this());
        auto async_receive_handler = [this, self](std::error_code ec, size_t size)
        {
            _receiving = false;
            if(!_connected)
            {
                return;
            }

            if(size > 0)
            {
                onReceived(_receive_buffer.data(), size);
                if(_receive_buffer.size() <= size)
                {
                    _receive_buffer.resize(2*size);
                }
            }

            if (!ec)
                tryReceive();
            else
            {
                sendError(ec);
                disconnect();
            }
        };
        _socket.async_read_some(asio::buffer(_receive_buffer.data(), _receive_buffer.size()),
                                asio::bind_executor(_strand, async_receive_handler));
    }

    void TCPConnection::trySend()
    {
        if(_sending)
        {
            return;
        }

        if(!_connected)
        {
            return;
        }

        _sending = true;
        auto self(this->shared_from_this());
        auto async_write_handler = [this, self](std::error_code ec, size_t size)
        {
            _sending = false;
            if(!_connected)
            {
                return;
            }

            if(size > 0)
            {

            }

            if(!ec)
            {
                trySend();
            }
            else
            {
                sendError(ec);
                disconnect();
            }

        };

    }

    void TCPConnection::sendError(std::error_code ec)
    {
        // Skip end of file error
        if (ec == asio::error::eof)
        {
            return;
        }

        onError(ec.category().name(), ec.message());
    }


    UUID& TCPConnection::getId()
    {
        return _id;
    }

    tcp::socket& TCPConnection::getSocket()
    {
        return _socket;
    }

}
