#include "OSELib/TCP/TCPConnection.h"
#include "OSELib/TCP/TCPServer.h"
#include <assert.h>

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
        if(_connected)
        {
            return;
        }
        _connected = true;

        onConnected();

        auto connection(this->shared_from_this());
        _server->onConnected(connection);
        _send_buffer.resize(_defaultBufferSize);
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
        _socket.async_receive(asio::buffer(_receive_buffer.data(), _receive_buffer.size()),
                                asio::bind_executor(_strand, async_receive_handler));
    }


    void TCPConnection::send(const void *buffer, size_t size)
    {
        assert(buffer!=nullptr && "buffer is empty");
        if (buffer == nullptr)
        {
            return;
        }

        if(!_connected)
        {
            return;
        }

        if(size == 0)
        {
            return;
        }


		//Body
        const uint8_t* bytes = static_cast<const uint8_t*>(buffer);
        _send_buffer.insert(_send_buffer.end(), bytes, bytes + size);

		std::cout << _send_buffer.size();

        auto self(this->shared_from_this());
        auto send_handler = [this, self]()
        {
            trySend();
        };
        _strand.dispatch(send_handler);
    }


    void TCPConnection::trySend()
    {
        if(_sending)
        {
            return;
        }

        if(_send_buffer.empty())
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
               onSent(_send_buffer.data(), _send_buffer.size());
            }

            if(size == _send_buffer.size())
            {
                _send_buffer.clear();
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
        _socket.async_send(asio::buffer(_send_buffer.data(), _send_buffer.size()), 0,
                            asio::bind_executor(_strand, async_write_handler));

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
