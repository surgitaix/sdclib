/*
 * PingManager.cpp
 *
 *  Created on: 14.12.2015
 *      Author: matthias
 */

#include "OSCLib/Data/SDC/SDCConsumer.h"

#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/DPWS/PingManager.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"
#include "OSELib/SOAP/GenericSoapInvoke.h"

namespace OSELib {
namespace DPWS {

PingManager::PingManager(SDCLib::Data::SDC::SDCConsumer & consumer) :
	_runnableAdapter(*this, &PingManager::run),
	_consumer(consumer)
{
	_thread.start(_runnableAdapter);
}

PingManager::~PingManager() {
	_thread.wakeUp();
	_thread.join();
}

void PingManager::run() {
	Helper::XercesGrammarPoolProvider grammarProvider;

	while (Poco::Thread::trySleep(5000)) {
		OSELib::DPWS::ProbeTraits::Request request;

		using ProbeInvoke = OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::ProbeTraits>;
		ProbeInvoke probeInvoke(_consumer._deviceDescription.getDeviceURI(), grammarProvider);
		try {
			auto response(probeInvoke.invoke(request));
			if (!response) {
				_consumer.onConnectionLost();
				return;
			}
		} catch (...) {
			_consumer.onConnectionLost();
			return;
		}
	}
}

void PingManager::disable() {
	_thread.wakeUp();
}

} /* namespace DPWS */
} /* namespace OSELib */
