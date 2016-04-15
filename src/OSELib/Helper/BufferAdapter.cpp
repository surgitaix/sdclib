/*
 * BufferAdapter.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "OSELib/Helper/BufferAdapter.h"

namespace OSELib {
namespace Helper {

BufferAdapter::BufferAdapter(const Poco::Buffer<char> & buffer, std::size_t length) :
	std::istream(this),
	_buffer(buffer),
	_length(std::min(length, buffer.size())),
	_position(0)
{
}

BufferAdapter::~BufferAdapter() = default;

int BufferAdapter::readFromDevice() {
	if (_position < _length) {
		return charToInt(_buffer[_position++]);
	} else {
		return char_traits::eof();
	}
}

} /* namespace Helpers */
} /* namespace OSELib */
