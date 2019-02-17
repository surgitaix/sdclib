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
 * FutureInvocationState.cpp
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, röhser
 */

#include "OSCLib/Data/SDC/FutureInvocationState.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"

namespace SDCLib {
namespace Data {
namespace SDC {

FutureInvocationState::FutureInvocationState() : transactionId(-1), consumer(nullptr) {
	invocationEvents[InvocationState::Cnclld] = std::shared_ptr<Poco::Event>(new Poco::Event(false));
	invocationEvents[InvocationState::CnclldMan] = std::shared_ptr<Poco::Event>(new Poco::Event(false));
	invocationEvents[InvocationState::Fail] = std::shared_ptr<Poco::Event>(new Poco::Event(false));
	invocationEvents[InvocationState::Fin] = std::shared_ptr<Poco::Event>(new Poco::Event(false));
	invocationEvents[InvocationState::Start] = std::shared_ptr<Poco::Event>(new Poco::Event(false));
	invocationEvents[InvocationState::Wait] = std::shared_ptr<Poco::Event>(new Poco::Event(false));
}

FutureInvocationState::~FutureInvocationState() {
	if (consumer != nullptr) {
		consumer->unregisterFutureInvocationListener(transactionId);
	}
}


bool FutureInvocationState::waitReceived(InvocationState expected, int timeout) {
	std::shared_ptr<Poco::Event> event;
	{
		Poco::Mutex::ScopedLock lock(mutex);
		event = invocationEvents[expected];
	}

	return event->tryWait(timeout);
}

int FutureInvocationState::getTransactionId() const {
	return transactionId;
}

void FutureInvocationState::setEvent(InvocationState actual) {
	Poco::Mutex::ScopedLock lock(mutex);
	invocationEvents[actual]->set();
}

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
