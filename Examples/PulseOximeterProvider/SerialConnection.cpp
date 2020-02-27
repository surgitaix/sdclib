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

SerialConnection::SerialConnection(std::string p_port, unsigned int p_baud_rate) :
	m_context{m_contextWorker->getContext()},
    m_strand{*m_context},
	m_serialPort{*m_context, p_port},
	m_port{p_port},
	m_lastReceive{std::chrono::steady_clock::now()}
{
	// Define the reconnect thread as lambda method.
	m_reconnectThread  = std::thread([&] {
		while(true)
		{
			// Check once per second too reduce load
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

			// Calculate milliseconds between last message from pulseoximeter and now
			auto t_now = std::chrono::steady_clock::now();
			auto t_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t_now - m_lastReceive);

			// If larger than a defined margin, issue reconnect
			if(t_elapsed.count() > m_reconnectTimeInMS)
			{
				std::cout << "Reconnect" << std::endl;
				reconnect();
			}
		}
	});

	flush(m_port);
	connect(m_port, p_baud_rate);
}

SerialConnection::~SerialConnection() {

}

void SerialConnection::flush(std::string p_port)
{
	  int fd = open(p_port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
	  tcflush(fd,TCIOFLUSH);
	  close(fd);
}

void SerialConnection::connect(const std::string &, unsigned int baud_rate)
{
	m_serialPort.set_option(asio::serial_port_base::baud_rate(baud_rate));
	m_receive_buffer.resize(1);
	m_connected = true;
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
	    char chr = static_cast<char>(static_cast<int>(std::strtol(byte.c_str(), nullptr, 16)));
	    newString.push_back(chr);
	}
	send(newString.c_str(), newString.size());

}

void SerialConnection::start()
{
	trySend();
	tryReceive();
	m_contextWorker->start();
}

void SerialConnection::stop()
{
	if(!m_connected)
	{
		return;
	}
    auto self(this->shared_from_this());
    auto stop_handler = [this, self]()
    {
        m_connected = false;
    	m_serialPort.cancel();
    	m_serialPort.close();
    	m_send_buffer.clear();
    	m_receive_buffer.clear();
    	flush(m_port);
    };
    m_strand.post(stop_handler);
}

void SerialConnection::send(const char *buffer, size_t size)
{
	assert(buffer!=nullptr && "buffer is empty");
	if(buffer == nullptr)
	{
		return;
	}

	if(!m_connected)
	{
		return;
	}
	if(size == 0)
	{
		return;
	}

	m_send_buffer.insert(m_send_buffer.end(), buffer, buffer + size);

    auto self(this->shared_from_this());
	auto send_handler = [this, self]()
	{
		trySend();
	};
	m_strand.dispatch(send_handler);
}

void SerialConnection::trySend()
{
    if(m_sending)
    {
        return;
    }

    if(m_send_buffer.empty())
    {
        return;
    }

    if(!m_connected)
    {
        return;
    }

    m_sending = true;
    auto self(this->shared_from_this());
    auto async_write_handler = [this, self](std::error_code ec, size_t size)
    {
        m_sending = false;
        if(!m_connected)
            return;

        if(size > 0)
        {
            onSent(m_send_buffer.data(), m_send_buffer.size());
        }

        if(size == m_send_buffer.size())
        {
            m_send_buffer.clear();
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
    m_serialPort.async_write_some(asio::buffer(m_send_buffer.data(), m_send_buffer.size()),
    							 asio::bind_executor(m_strand, async_write_handler));


}

void SerialConnection::tryReceive()
{
    if (!m_connected)
    {
        return;
    }

    auto self(this->shared_from_this());
    auto async_receive_handler = [this, self](std::error_code ec, size_t size)
    {
        if(!m_connected)
        {
        	std::cout << "not connected" << std::endl;
            return;
        }

        if(size > 0)
        {
        	m_lastReceive = std::chrono::steady_clock::now();
            onReceived(m_receive_buffer.data(), size);
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
    m_serialPort.async_read_some(asio::buffer(m_receive_buffer.data(), m_receive_buffer.size()),
                            asio::bind_executor(m_strand, async_receive_handler));
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
	return m_connected;
}

} /* namespace Serial */
