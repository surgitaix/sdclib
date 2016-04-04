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
 * OSCPPingManager.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting
 */

#include "OSCLib/Cli/Client.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPPingManager.h"
#include "OSCLib/Util/DebugOut.h"

#include "Poco/ScopedLock.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPPingManager::OSCPPingManager(OSCPConsumer & consumer) :
		consumer(&consumer)
{

}

OSCPPingManager::~OSCPPingManager() {

}

void OSCPPingManager::runImpl() {
	int i = 0;
	while (i < 50 && !isInterrupted()) {
		++i;
		Poco::Thread::sleep(100);
	}

	Poco::Mutex::ScopedLock lock(mutex);
	if (consumer == nullptr) {
		return;
	}

	if (!isInterrupted() && consumer->isValid()) {
		if (!consumer->client->pingSync(2000)) {
			Util::DebugOut(Util::DebugOut::Error, "OSCPPingManager") << "Ping failed!" << std::endl;
			consumer->connected = false;
			consumer->onConnectionLost();
		} else {
			consumer->connected = true;
		}
	}
}

void OSCPPingManager::detachConsumer() {
	Poco::Mutex::ScopedLock lock(mutex);
	consumer = nullptr;
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
