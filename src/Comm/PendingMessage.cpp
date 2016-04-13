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
 * PendingMessage.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#include "OSCLib/Comm/Message.h"
#include "OSCLib/Comm/PendingMessage.h"
#include "OSCLib/Comm/UnicastCallback.h"
#include "OSCLib/Comm/MulticastCallback.h"

namespace OSCLib {
namespace Comm {

PendingMessage::PendingMessage() : source(nullptr), sourcemc(nullptr) {

}

PendingMessage::PendingMessage(const UnicastCallback * source, const Message & msg, const std::string & logInfo) :
	source(source), sourcemc(nullptr), msg(msg), logInfo(logInfo)	{

}

PendingMessage::PendingMessage(const MulticastCallback * sourcemc, const Message & msg, const std::string & logInfo) :
	source(nullptr), sourcemc(sourcemc), msg(msg), logInfo(logInfo)	{

}


} /* namespace Comm */
} /* namespace OSCLib */
