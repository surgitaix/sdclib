/*
 * PingManager.cpp
 *
 *  Created on: 14.12.2015
 *      Author: matthias
 */

#include "OSELib/DPWS/PingManager.h"

#include "SDCLib/SDCInstance.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"

#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"
#include "OSELib/SOAP/GenericSoapInvoke.h"

using namespace OSELib::DPWS;

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

void PingManager::run()
{
	Helper::XercesGrammarPoolProvider grammarProvider;
	while (Poco::Thread::trySleep(SDCLib::Config::SDC_CONNECTION_TIMEOUT_MS))
    {
		OSELib::DPWS::ProbeTraits::Request request;
		using ProbeInvoke = OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::ProbeTraits>;
		ProbeInvoke probeInvoke(_consumer._deviceDescription.getDeviceURI(), grammarProvider);
		try {
			auto response(probeInvoke.invoke(request, _consumer.getSDCInstance()->getSSLConfig()->getClientContext()));
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

void PingManager::disable()
{
    _thread.wakeUp();
}

