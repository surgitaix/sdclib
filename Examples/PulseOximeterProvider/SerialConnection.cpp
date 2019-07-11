/*
 * SerialConnection.cpp
 *
 *  Created on: Jun 17, 2019
 *      Author: rosenau
 */

#include "SerialConnection.h"
#include <bitset>
#include <fcntl.h>
#include <assert.h>

namespace Serial {

SerialConnection::SerialConnection(std::string port, unsigned int baud_rate) :
	_connected(false),
	_sending(false),
	_contextWorker(new Network::ContextWorker()),
	_context(_contextWorker->getContext()),
    _strand(*_context),
	_serialPort(*_context, port),
	_port(port)
{
	flush(_port);
	connect(_port, baud_rate);
}

SerialConnection::~SerialConnection() {

}

void SerialConnection::flush(std::string port)
{
	  int fd = open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
	  tcflush(fd,TCIOFLUSH);
	  close(fd);
}

void SerialConnection::connect(const std::string &port, unsigned int baud_rate)
{
	_serialPort.set_option(asio::serial_port_base::baud_rate(baud_rate));
	_receive_buffer.resize(1);
	_connected = true;
}

void SerialConnection::start()
{
	trySend();
	tryReceive();
	_contextWorker->start();
}

void SerialConnection::stop()
{
	if(!_connected)
	{
		return;
	}
    auto self(this->shared_from_this());
    auto stop_handler = [this, self]()
    {
        _connected = false;
    	_serialPort.cancel();
    	_serialPort.close();
    	_send_buffer.clear();
    	_receive_buffer.clear();
    	flush(_port);
    };
    _strand.post(stop_handler);
}

void SerialConnection::send(const void *buffer, size_t size)
{
	assert(buffer!=nullptr && "buffer is empty");
	if(buffer == nullptr)
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

void SerialConnection::trySend()
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
        }
    };
    _serialPort.async_write_some(asio::buffer(_send_buffer.data(), _send_buffer.size()),
    							 asio::bind_executor(_strand, async_write_handler));


}

void SerialConnection::tryReceive()
{
    if (!_connected)
    {
        return;
    }

    auto self(this->shared_from_this());
    auto async_receive_handler = [this, self](std::error_code ec, size_t size)
    {
        if(!_connected)
        {
        	std::cout << "not connected" << std::endl;
            return;
        }

        if(size > 0)
        {
            onReceived(_receive_buffer.data(), size);
        }

        if(!ec)
        {
            tryReceive();
        }
        else
        {
            sendError(ec);
        }
    };
    _serialPort.async_read_some(asio::buffer(_receive_buffer.data(), _receive_buffer.size()),
                            asio::bind_executor(_strand, async_receive_handler));
}

void SerialConnection::sendError(std::error_code ec)
{
	if(ec == asio::error::eof) {
		return;
	}
	onError(ec.category().name(), ec.message());
}

bool SerialConnection::isConnected()
{
	return _connected;
}

} /* namespace Serial */
