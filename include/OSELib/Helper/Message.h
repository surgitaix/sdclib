/*
 * Message.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 10.06.2022, baumeister
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
            Message() = delete;  // Note: Private Constructor via static create member function

            static std::unique_ptr<Message> create(const std::string&);
            static std::unique_ptr<Message> create(std::istream&);

            const std::string& getContent() const;

        private:
            Message(const std::string& p_content);
        };
    }  // namespace Helper
}  // namespace OSELib

#endif
