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

/**
 *  @file OSCLibrary.cpp
 *  @project OSCLib
 *  @date 24.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 *
 */

#include "OSCLib/OSCLibrary.h"
#include "OSCLib/wsdls.h"
#include "OSCLib/Dev/Device.h"
#include "OSCLib/Comm/CommunicationManager.h"
#include "OSCLib/Comm/DefaultNetworkInterface.h"
#include "OSCLib/Comm/DPWS/DPWS11CommunicationManager.h"
#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/FromString.h"

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/validators/common/Grammar.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/framework/XMLGrammarPoolImpl.hpp>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>
#include <xsd/cxx/xml/dom/bits/error-handler-proxy.hxx>
#include <xsd/cxx/xml/sax/std-input-source.hxx>

#include <xsd/cxx/tree/error-handler.hxx>

#include "Poco/ScopedLock.h"
#include "Poco/Notification.h"

using namespace OSCLib::Dev;
using namespace OSCLib::Comm;
using namespace OSCLib::Comm::DPWS;
using namespace OSCLib::Util;
using namespace OSCLib::Data::OSCP;

namespace OSCLib {

class ShutdownNotification : public Poco::Notification {
public:

    ShutdownNotification(std::shared_ptr<OSCLib::Util::Task> task)
        : task(task) {
    }

    std::shared_ptr<OSCLib::Util::Task> getTask() {
        return task;
    }

private:
    std::shared_ptr<OSCLib::Util::Task> task;
};

class ShutdownTask : public Util::Task
{
public:
    ShutdownTask(Poco::NotificationQueue & queue) :
        queue(queue) {
    }

    ~ShutdownTask()
    {
    }

    void runImpl() {
        while (!isInterrupted()) {
            Poco::AutoPtr<Poco::Notification> pNf(queue.waitDequeueNotification(100));
            while (pNf) {
                ShutdownNotification * s = dynamic_cast<ShutdownNotification*>(pNf.get());
                s->getTask()->interrupt();
                pNf = queue.waitDequeueNotification(100);
            }
        }
    }
private:
    Poco::NotificationQueue & queue;
};

OSCLibrary * OSCLibrary::instance = 0;

OSCLibrary::OSCLibrary() :
		netInterface(nullptr),
		reader(nullptr),
		portStart(0),
		initialized(false),
		pool(nullptr)
{

}

OSCLibrary::~OSCLibrary() {
    shutdown();
}

OSCLibrary * OSCLibrary::getInstance() {
	if (instance == nullptr) {
		instance = ::new OSCLibrary();
	}
	return instance;
}

void OSCLibrary::registerDevice(Dev::Device* device)
{
	// Decide which communication manager covers selected protocols and bindings
	ProtocolBindingMap::const_iterator pIt;
	for (pIt = device->getProtocolBindings().begin();
			pIt != device->getProtocolBindings().end(); ++pIt)
	{
		if (pIt->first == DPWS11)
		{
			DPWS11CommunicationManager * dpwsManager = new DPWS11CommunicationManager();
			device->addManager(dpwsManager);
			Poco::Mutex::ScopedLock lock(mutex);
			deviceSet.insert(device);
		}
	}
}

Comm::NetworkInterface * OSCLibrary::getNetInterface() {
	return netInterface;
}

void OSCLibrary::unRegisterDevice(Dev::Device * device)
{
	{
		Poco::Mutex::ScopedLock lock(mutex);
		if (deviceSet.find(device) == deviceSet.end())
			return;
		deviceSet.erase(device);
	}
	device->clearManagersAndDelete();
}

void OSCLibrary::registerConsumer(Data::OSCP::OSCPConsumer * consumer) {
	Poco::Mutex::ScopedLock lock(mutex);
    consumers.insert(consumer);
}

void OSCLibrary::unRegisterConsumer(Data::OSCP::OSCPConsumer * consumer) {
	Poco::Mutex::ScopedLock lock(mutex);
    if (consumers.find(consumer) == consumers.end())
        return;
    consumers.erase(consumer);
}

void OSCLibrary::registerProvider(Data::OSCP::OSCPProvider * provider) {
	Poco::Mutex::ScopedLock lock(mutex);
    providers.insert(provider);
}

void OSCLibrary::unRegisterProvider(Data::OSCP::OSCPProvider * provider) {
	Poco::Mutex::ScopedLock lock(mutex);
    if (providers.find(provider) == providers.end())
        return;
    providers.erase(provider);
}

void OSCLibrary::cleanUpOSCP() {
	Poco::Mutex::ScopedLock lock(mutex);
	std::set<OSCPConsumer *> ccopy = consumers;
    for (auto &next : ccopy)
    {
    	next->disconnect();
    }
    std::set<OSCPProvider *> pcopy = providers;
    for (auto &next : pcopy)
    {
        next->shutdown();
    }
}

void OSCLibrary::startup(DebugOut::LogLevel debugLevel) {
	if (!initialized) {
        shutdownTask.reset(new ShutdownTask(shutdownQueue));
        shutdownTask->start();
		netInterface = new DefaultNetworkInterface();
        reader = new ReaderThread();
		reader->start();
		initialized = true;
		DebugOut::DEBUG_LEVEL = debugLevel;
		DebugOut(DebugOut::Default, std::cout) << "OSCLib version 0.98_00 (C) 2016 SurgiTAIX AG";
		bindToAll();
        xercesc::XMLPlatformUtils::Initialize();

    	pool = new xercesc::XMLGrammarPoolImpl(xercesc::XMLPlatformUtils::fgMemoryManager);
    	{
			struct ParserDeleter {
			  void operator()(xercesc::DOMLSParser* b) { b->release(); }
			};
			std::unique_ptr<xercesc::DOMLSParser, ParserDeleter> parser(CDM::FromString::createParser());
			{
				std::istringstream extensionstream(SCHEMA_EXTENSION_POINT_CONTENT);
				xsd::cxx::xml::sax::std_input_source iextensionstream (extensionstream, SCHEMA_EXTENSION_POINT_NAME);
				xercesc::Wrapper4InputSource wrapextensionstream (&iextensionstream, false);
				if (!parser->loadGrammar (&wrapextensionstream, xercesc::Grammar::SchemaGrammarType, true)) {
					DebugOut(DebugOut::Error, std::cout) << "unable to load schema" << std::endl;
				}
			}
			{
				std::istringstream datamodelstream(SCHEMA_DATAMODEL_CONTENT);
				xsd::cxx::xml::sax::std_input_source idatamodelstream (datamodelstream, SCHEMA_DATAMODEL_NAME);
				xercesc::Wrapper4InputSource wrapdatamodelstream (&idatamodelstream, false);
				if (!parser->loadGrammar (&wrapdatamodelstream, xercesc::Grammar::SchemaGrammarType, true)) {
					DebugOut(DebugOut::Error, std::cout) << "unable to load schema" << std::endl;
				}
			}
			{
				std::istringstream dicommodelstream(SCHEMA_DICOM_DATAMODEL_CONTENT);
				xsd::cxx::xml::sax::std_input_source idicommodelstream (dicommodelstream, SCHEMA_DICOM_DATAMODEL_NAME);
				xercesc::Wrapper4InputSource wdicommodelstream (&idicommodelstream, false);
				if (!parser->loadGrammar (&wdicommodelstream, xercesc::Grammar::SchemaGrammarType, true)) {
					DebugOut(DebugOut::Error, std::cout) << "unable to load schema" << std::endl;
				}
			}
			{
				std::istringstream messagemodelstream(SCHEMA_MESSAGEMODEL_CONTENT);
				xsd::cxx::xml::sax::std_input_source imessagemodelstream (messagemodelstream, SCHEMA_MESSAGEMODEL_NAME);
				xercesc::Wrapper4InputSource wrapmessagemodelstream (&imessagemodelstream, false);
				if (!parser->loadGrammar (&wrapmessagemodelstream, xercesc::Grammar::SchemaGrammarType, true)) {
					DebugOut(DebugOut::Error, std::cout) << "unable to load schema" << std::endl;
				}
			}
    	}
    	pool->lockPool();

	} else {
		DebugOut(DebugOut::Error, "OSCLibrary") << "OSCLib already initialized!";
	}
}

void OSCLibrary::shutdown() {
	if (initialized) {
        cleanUpOSCP();
        initialized = false;
        deviceSet.clear();
		reader->interrupt();
		delete reader;
		reader = nullptr;
        if (DefaultNetworkInterface* dni = dynamic_cast<DefaultNetworkInterface*>(netInterface)) {
            dni->interruptMessaging();
        }
		delete netInterface;
		netInterface = nullptr;
		DebugOut::closeLogFile();
		pool->unlockPool();
		delete pool;
        xercesc::XMLPlatformUtils::Terminate();
        shutdownTask->interrupt();
		delete instance;
		instance = nullptr;
	}
}

void OSCLibrary::bindToAll() {

	setPortStart(9000);
	OSCLibrary::getInstance()->setBindInterface("0.0.0.0");
}

void OSCLibrary::setBindInterface(const std::string & bindInt) {
	DebugOut(DebugOut::Info, "OSCLibrary") << "Binding to address "<< bindInt;
	this->bindInt = bindInt;
}

std::string OSCLibrary::getBindInterface() {
	return bindInt;
}

void OSCLibrary::setPortStart(int portStart) {
	DebugOut(DebugOut::Info, "OSCLibrary") << "Setting port start number to " << portStart;
	this->portStart = portStart;
}

int OSCLibrary::extractNextPort() {
	int p = portStart++;
	return p;
}

void OSCLibrary::readMessages() {
	netInterface->processIn();
}

void OSCLibrary::processAllScheduledForShutdown() {
    Poco::Mutex::ScopedLock lock(mutex);
    while (!managersShuttingDown.empty()) {
		CommunicationManager * currentManager = *managersShuttingDown.begin();
		currentManager->stopManager();
		managersShuttingDown.pop_front();
	}
}

bool OSCLibrary::existsManagerScheduledForShutdown() {
	Poco::Mutex::ScopedLock lock(mutex);
	return !managersShuttingDown.empty();
}

void OSCLibrary::scheduleManagerForShutdown(CommunicationManager * manager) {
	Poco::Mutex::ScopedLock lock(mutex);
	managersShuttingDown.push_back(manager);
}

void OSCLibrary::scheduleTaskForShutdown(std::shared_ptr<OSCLib::Util::Task> task) {
    shutdownQueue.enqueueNotification(new ShutdownNotification(task));
}

ReaderThread::ReaderThread() {

}

void ReaderThread::runImpl() {
	OSCLibrary::getInstance()->readMessages();
    OSCLibrary::getInstance()->processAllScheduledForShutdown();
	Poco::Thread::sleep(2);
}

} /* namespace OSCLib */
