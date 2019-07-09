#include "OSELib/TCP/TCPClient.h"
#include <iostream>
#include <functional>
#include <assert.h>
#include <uuid/uuid.h>


namespace Network {
    TCPClient::TCPClient(const std::string& address, unsigned short port)
        : _connected(false),
          _sending(false),
          _receiving(false),
          _connecting(false),
          _resolving(false),
          _contextWorker(new ContextWorker()),
          _context(_contextWorker->getContext()),
          _query(address, std::to_string(port)),
          _resolver(*_context),
          _socket(*_context),
          _strand(*_context)
    {
    }

    TCPClient::~TCPClient()
    {
        _contextWorker->stop();
    }

    void TCPClient::start()
    {
        connectAsync();
        _contextWorker->start();
    }

    void TCPClient::stop()
    {
        disconnect();
        _contextWorker->stop();
    }

    void TCPClient::disconnect()
    {
        _connected = false;
        asio::error_code ignored_ec;
        _socket.close(ignored_ec);
        onDisconnected();
    }

    void TCPClient::connect(tcp::resolver::results_type endpoints)
    {
        _endpoints = endpoints;
        if(_connected)
        {
            std::cout << "Already connected" << std::endl;
            return;
        }

        auto self(this->shared_from_this());
        auto connect_handler = [this, self]()
        {
            auto async_connect_handler = [this, self](std::error_code ec, const asio::ip::tcp::endpoint& endpoint)
            {
                if (_connected)
                {
                    return;
                }

                if(!ec)
                {
                    _endpoint = endpoint;
                    _connected = true;
                    onConnected();
                }
                else {
                    sendError(ec);
                    disconnect();
                }
            };
            asio::async_connect(_socket, _endpoints, asio::bind_executor(_strand, async_connect_handler));
        };
        _strand.post(connect_handler);
    }

    bool TCPClient::connectAsync()
    {
        if (_connected || _resolving || _connecting)
            return false;

        // Post the connect handler
        auto self(this->shared_from_this());
        auto connect_handler = [this, self]()
        {
            if (_connected || _resolving || _connecting)
                return;

            // Async resolve with the connect handler
            _resolving = true;
            auto async_resolve_handler = [this, self](std::error_code ec1, asio::ip::tcp::resolver::results_type endpoints)
            {
                _resolving = false;

                if (_connected || _resolving || _connecting)
                    return;

                if (!ec1)
                {
                    // Async connect with the connect handler
                    _connecting = true;
                    auto async_connect_handler = [this, self](std::error_code ec2, const asio::ip::tcp::endpoint& endpoint)
                    {
                        _connecting = false;

                        if (_connected || _resolving || _connecting)
                            return;

                        if (!ec2)
                        {

                            _socket.set_option(asio::ip::tcp::socket::keep_alive(true));

                            _socket.set_option(asio::ip::tcp::no_delay(true));

                            //  Connect to the server
                            _endpoint = endpoint;


                            // Update the connected flag
                            _connected = true;

                            // Call the client connected handler
                            onConnected();

                            _receive_buffer.resize(_defaultBufferSize);

                            tryReceive();


                            // Try to receive something from the server
                        }
                        else
                        {
                            sendError(ec2);
                            onDisconnected();
                        }
                    };
                    asio::async_connect(_socket, endpoints, bind_executor(_strand, async_connect_handler));
                }
                else
                {
                    sendError(ec1);
                    onDisconnected();
                }
            };

            _resolver.async_resolve(_query, asio::bind_executor(_strand, async_resolve_handler));
        };
        _strand.post(connect_handler);
        return true;
    }

    void TCPClient::send(const void *buffer, size_t size)
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

        const uint8_t* bytes = static_cast<const uint8_t*>(buffer);
        _send_buffer.insert(_send_buffer.end(), bytes, bytes + size);

        auto self(this->shared_from_this());
        auto send_handler = [this, self]()
        {
            trySend();
        };
        _strand.dispatch(send_handler);

    }

    void TCPClient::tryReceive()
    {
        if(_receiving)
        {
            return;
        }
        if (!_connected)
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
            	std::cout << "not connected" << std::endl;
                return;
            }

            if(size > 0)
            {
                onReceived(_receive_buffer.data(), size);

                if(_receive_buffer.size() >= size)
                {
                    _receive_buffer.resize(2 * size);
                }
            }

            if(!ec)
            {
                tryReceive();
            }
            else
            {
                sendError(ec);
                disconnect();
            }
        };
        _socket.async_receive(asio::buffer(_receive_buffer.data(), _receive_buffer.size()),
                                asio::bind_executor(_strand, async_receive_handler));
    }


    void TCPClient::trySend()
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
                return;

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

    void TCPClient::sendError(std::error_code ec)
    {
        // Skip end of file error
        if (ec == asio::error::eof) {
            return;
        }
        onError(ec.category().name(), ec.message());
    }

    bool TCPClient::isConnected()
    {
    	return _connected;
    }
}

