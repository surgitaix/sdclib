/*
 * Message.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/StreamReader.h"

namespace OSELib {
namespace Helper {

Message::Message(const std::string & content) :
	_content(content)
{
}

std::unique_ptr<Message> Message::create(const std::string & content) {
	return std::unique_ptr<Message>(new Message(content));
}

std::unique_ptr<Message> Message::create(std::istream & stream) {
	StreamReader reader(stream);
	return std::unique_ptr<Message>(new Message(reader.getContent()));
}

const std::string & Message::getContent() const {
	return _content;
}

} /* namespace Helper */
} /* namespace OSELib */
