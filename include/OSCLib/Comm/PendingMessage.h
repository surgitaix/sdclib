/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/*
 * PendingMessage.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#ifndef PENDINGMESSAGE_H_
#define PENDINGMESSAGE_H_

#include <string>

#include "Message.h"

namespace OSCLib {
namespace Comm {

class UnicastCallback;
class MulticastCallback;

// Structure for outgoing pending message object
class PendingMessage
{
public:

	PendingMessage();
	PendingMessage(const UnicastCallback * source, const Message & msg, const std::string & logInfo);
    PendingMessage(const MulticastCallback * sourcemc, const Message & msg, const std::string & logInfo);

	const UnicastCallback * source;
    const MulticastCallback * sourcemc;
	Message msg;
	std::string logInfo;
};

} /* namespace Comm */
} /* namespace OSCLib */
#endif /* PENDINGMESSAGE_H_ */
