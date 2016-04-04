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
 * MulticastCallback.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#ifndef MULTICASTCALLBACK_H_
#define MULTICASTCALLBACK_H_

#include <string>
#include <memory>

namespace OSCLib {
namespace Comm {

class Message;

class MulticastCallback
{
public:
	MulticastCallback();
	virtual ~MulticastCallback();

    virtual std::shared_ptr<Message> udpMulticastCallback(const Message & msg) = 0;

	const std::string & getMulticastCallbackUUID() const {
		return multicastCallbackUUID;
	}

private:
	const std::string multicastCallbackUUID;
};

} /* namespace Comm */
} /* namespace OSCLib */
#endif /* MULTICASTCALLBACK_H_ */
