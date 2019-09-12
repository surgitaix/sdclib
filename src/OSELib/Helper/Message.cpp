/*
 * Message.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/StreamReader.h"

namespace OSELib {
namespace Helper {

Message::Message(const std::string & p_content)
: m_content(p_content)
{ }

std::unique_ptr<Message> Message::create(const std::string & p_content)
{
	return std::unique_ptr<Message>(new Message(p_content));
}

std::unique_ptr<Message> Message::create(std::istream & p_stream)
{
	OSELib::Helper::StreamReader t_reader(p_stream);
	return std::unique_ptr<Message>(new Message(t_reader.getContent()));
}

const std::string & Message::getContent() const {
	return m_content;
}

}
}
