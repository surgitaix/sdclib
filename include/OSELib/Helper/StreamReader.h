/*
 * StreamReader.h
 *
 *  Created on: 13.10.2014, roehser
 *  Modified on: 20.08.2019, baumeister
 *
 */

#ifndef OSELIB_HELPER_STREAMREADER_H_
#define OSELIB_HELPER_STREAMREADER_H_

#include <istream>
#include <string>

namespace OSELib
{
	namespace Helper
	{
		class StreamReader
		{
		private:
			std::istream & _stream;
		public:
			StreamReader(std::istream & stream);
			virtual ~StreamReader();

			std::string getContent();
		};
	}
}

#endif
