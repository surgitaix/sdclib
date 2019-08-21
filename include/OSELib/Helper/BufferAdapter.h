/*
 * BufferAdapter.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef BUFFERADAPTER_H_
#define BUFFERADAPTER_H_

#include <istream>

#include <Poco/Buffer.h>
#include <Poco/UnbufferedStreamBuf.h>

namespace OSELib
{
	namespace Helper
	{
		class BufferAdapter : public std::istream, public Poco::UnbufferedStreamBuf
		{
		private:
			const Poco::Buffer<char> & m_buffer;
			const std::size_t m_length = 0;
			std::size_t m_position = 0;

		public:
			BufferAdapter(const Poco::Buffer<char> & buffer, std::size_t length);
			virtual ~BufferAdapter() = default;

			int readFromDevice() override;
		};

	}
}

#endif
