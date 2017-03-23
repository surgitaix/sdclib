/*
 * StreamReader.h
 *
 *  Created on: 13.10.2014
 *      Author: roehser
 */

#ifndef STREAMREADER_H_
#define STREAMREADER_H_

#include <iostream>
#include <string>

namespace OSELib {
namespace Helper {

class StreamReader {
public:
	StreamReader(std::istream & stream);
	virtual ~StreamReader();

	std::string getContent();

private:
	std::istream & _stream;
};

}
} /* namespace OSCLib */

#endif /* STREAMREADER_H_ */
