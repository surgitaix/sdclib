/*
 * Message.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef HELPER_MESSAGE_H_
#define HELPER_MESSAGE_H_

#include <memory>

namespace OSELib {
namespace Helper {

class Message {
public:
	static std::unique_ptr<Message> create(const std::string & content);
	static std::unique_ptr<Message> create(std::istream & stream);

	const std::string & getContent() const;

private:
	Message() = delete;
	Message(const std::string & content);

	const std::string _content;
};

} /* namespace Helper */
} /* namespace OSELib */

#endif /* HELPER_MESSAGE_H_ */
