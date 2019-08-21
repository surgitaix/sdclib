/*
 * BufferAdapter.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#include "OSELib/Helper/BufferAdapter.h"

namespace OSELib {
namespace Helper {

BufferAdapter::BufferAdapter(const Poco::Buffer<char> & p_buffer, std::size_t p_length)
: std::istream(this)
, m_buffer(p_buffer)
#ifdef min
,	m_length(min(p_length, p_buffer.size()))
#else
,	m_length(std::min(p_length, p_buffer.size()))
#endif
,	m_position(0)
{ }

int BufferAdapter::readFromDevice()
{
	if (m_position < m_length) {
		return charToInt(m_buffer[m_position++]);
	} else {
		return char_traits::eof();
	}
}

}
}
