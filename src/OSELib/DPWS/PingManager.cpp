/*
 * PingManager.cpp
 *
 *  Created on: 14.12.2015, matthias
 *  Modified on: 05.08.2019, baumeister
 *
 */

#include "OSELib/DPWS/PingManager.h"

#include "SDCLib/SDCInstance.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"

#include "OSELib/DPWS/DeviceDescription.h"
#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"
#include "OSELib/SOAP/GenericSoapInvoke.h"

using namespace OSELib::DPWS;

PingManager::PingManager(SDCLib::Data::SDC::SDCConsumer & p_consumer)
: m_runnableAdapter(*this, &PingManager::run)
, m_consumer(p_consumer)
{
	m_thread.start(m_runnableAdapter);
}

PingManager::~PingManager() {
	m_thread.wakeUp();
	m_thread.join();
}

void PingManager::run()
{
	Helper::XercesGrammarPoolProvider t_grammarProvider;
	while (Poco::Thread::trySleep(SDCLib::Config::SDC_CONNECTION_TIMEOUT_MS))
    {
		OSELib::DPWS::ProbeTraits::Request t_request;
		using ProbeInvoke = OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::ProbeTraits>;

		try {
			ProbeInvoke t_probeInvoke(m_consumer.m_deviceDescription->getDeviceURI(), t_grammarProvider);
			auto t_response(t_probeInvoke.invoke(t_request, m_consumer.getSDCInstance()->getSSLConfig()->getClientContext()));
			if (!t_response) {
				m_consumer.onConnectionLost();
				return;
			}
		} catch (...) {
			m_consumer.onConnectionLost();
			return;
		}
	}
}

void PingManager::disable()
{
    m_thread.wakeUp();
}

