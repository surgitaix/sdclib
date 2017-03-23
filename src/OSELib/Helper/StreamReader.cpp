/*
 * StreamReader.cpp
 *
 *  Created on: 13.10.2014
 *      Author: roehser
 */

#include "OSELib/Helper/StreamReader.h"

namespace OSELib {
namespace Helper {

StreamReader::StreamReader(std::istream & stream) :
	_stream(stream)
{
}

StreamReader::~StreamReader() {
}

std::string StreamReader::getContent() {
	constexpr std::size_t DEFAULT_BUFFER_SIZE(10000);
	std::string result;
	result.reserve(DEFAULT_BUFFER_SIZE);
	std::string tmp;
	tmp.reserve(DEFAULT_BUFFER_SIZE);
	while (!_stream.eof() && !_stream.fail()) {
		std::getline(_stream, tmp);
		result += tmp;
	}
	return result;
}
}

} /* namespace OSELib */
