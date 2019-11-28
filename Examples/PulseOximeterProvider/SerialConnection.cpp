/*
 * SerialConnection.cpp
 *
 *  Created on: Jun 17, 2019
 *  Modified on: Nov 28, 2019
 *      Author: rosenau, stegemann
 */

#include "SerialConnection.h"
#include <bitset>
#include <fcntl.h>
#include <assert.h>
#include <chrono>

namespace Serial {

SerialConnection::SerialConnection(std::string port, unsigned int baud_rate) :
	_connected(false),
	_sending(false),
	_contextWorker(new Network::ContextWorker()),
	_context(_contextWorker->getContext()),
    _strand(*_context),
	_serialPort(*_context, port),
	_port(port),
	m_lastReceive(std::chrono::steady_clock::now())
{
	m_reconnectThread  = std::thread([&] {
		while(true)
		{
			auto t_now = std::chrono::steady_clock::now();
			auto t_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t_now - m_lastReceive);

			if(t_elapsed.count() > m_reconnectTimeInMS)
			{
				std::cout << "Reconnect" << std::endl;
				reconnect();
			}
		}
	});

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

void SerialConnection::reconnect()
{
	// Reconnect is called, if the last received message exceeds
	// the predefined margin. To prevent multiple messages, reset timer
	m_lastReceive = std::chrono::steady_clock::now();

	// Taken from PulseOximeterProvider
	// TODO: Move to better position
	std::string hex = "7d81a1808080808080";

	int len = hex.length();
	std::string newString;
	for(int i=0; i < len; i+=2)
	{
	    std::string byte = hex.substr(i,2);
	    char chr = (char) (int)strtol(byte.c_str(), nullptr, 16);
	    newString.push_back(chr);
	}
	send(newString.c_str(), newString.size());

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
        	m_lastReceive = std::chrono::steady_clock::now();
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
