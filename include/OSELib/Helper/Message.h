/*
 * Message.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_HELPER_MESSAGE_H_
#define OSELIB_HELPER_MESSAGE_H_

#include <memory>
#include <string>

namespace OSELib
{
	namespace Helper
	{
			class Message
			{
			private:
				const std::string m_content;

			public:
				// Special Member Functions
				Message() = delete; // Note: Private Constructor via static create member function
				Message(const Message& p_obj) = default;
				Message(Message&& p_obj) = default;
				Message& operator=(const Message& p_obj) = default;
				Message& operator=(Message&& p_obj) = default;

				static std::unique_ptr<Message> create(const std::string & p_content);
				static std::unique_ptr<Message> create(std::istream & p_stream);

				const std::string & getContent() const;

			private:

				Message(const std::string & p_content);
			};
	}
}

#endif
