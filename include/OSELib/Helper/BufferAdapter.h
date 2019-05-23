/*
 * BufferAdapter.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef BUFFERADAPTER_H_
#define BUFFERADAPTER_H_

#include <istream>

#include "Poco/Buffer.h"
#include "Poco/UnbufferedStreamBuf.h"

namespace OSELib {
namespace Helper {

class BufferAdapter : public std::istream, public Poco::UnbufferedStreamBuf {
public:
	BufferAdapter(const Poco::Buffer<char> & buffer, std::size_t length);
	virtual ~BufferAdapter();

	int readFromDevice() override;

private:
	const Poco::Buffer<char> & _buffer;
	const std::size_t _length;
	std::size_t _position;
};

} /* namespace Helpers */
} /* namespace OSELib */

#endif /* BUFFERADAPTER_H_ */
