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
 *  @file Device.cpp
 *  @project OSCLib
 *  @date 05.07.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */

#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Comm/Binding.h"
#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Dev/Device.h"
#include "OSCLib/Dev/EndpointReference.h"
#include "OSCLib/Util/DebugOut.h"

#include "Poco/Thread.h"
#include "Poco/ScopedLock.h"

#include <algorithm>
#include <string>
#include <time.h>

using namespace OSCLib::Comm;
using namespace OSCLib::Comm::DPWS;

namespace OSCLib {
namespace Dev {

Device::Device() : metaDataVersion(1), instanceId(time(NULL)), messageNumber(1), running(false)
{
	configureDefaultDPWS11();
	addDefaultCharacteristics();
}

Device::~Device()
{
	if (isRunning()) {
		stop();
        Util::DebugOut(Util::DebugOut::Error, "Device") << "Please stop all devices before they are destroyed!";
	}
}

const DeviceCharacteristics & Device::getDeviceCharacteristics() const
{
    return description;
}

void Device::setDeviceCharacteristics(const DeviceCharacteristics & description)
{
    this->description = description;
}

int Device::getMetaDataVersion() const
{
	return metaDataVersion;
}

void Device::setMetaDataVersion(int metaDataVersion)
{
	this->metaDataVersion = metaDataVersion;
}

int Device::getInstanceId() const
{
	return instanceId;
}

int Device::getMessageNumber() const
{
	return messageNumber;
}

void Device::setInstanceId(int instanceId)
{
	this->instanceId = instanceId;
}

void Device::setMessageNumber(int messageNumber)
{
	this->messageNumber = messageNumber;
}

void Device::incMessageNumber()
{
	++messageNumber;
}

void Device::clearScopes() {
	scopes.clear();
}

const Util::StringVector & Device::getScopes() const
{
	return scopes;
}

void Device::addScope(const std::string& scope)
{
	scopes.push_back(scope);
}

void Device::addScopes(const Util::StringVector & scopes) {
    	for (unsigned int i = 0; i < scopes.size(); ++i)
    		addScope(scopes[i]);
    }

void Device::addManager(Comm::CommunicationManager* man)
{
    Poco::Mutex::ScopedLock lock(mutexManagers);
	managers.insert(man);
}

CommunicationManager* Device::getDefaultCommunicationManager(const std::string& protocol)
{
    Poco::Mutex::ScopedLock lock(mutexManagers);
	ManagerSet::iterator it;
	for (it = managers.begin(); it != managers.end(); ++it)
	{
		if (protocol.compare((*it)->getProtocolDomain()) == 0)
			return *it;
	}
	return nullptr;
}

const std::shared_ptr<Service> Device::getService(unsigned int index) const
{
    Poco::Mutex::ScopedLock lock(mutexServices);
	return services[index];
}

ServiceVector Device::getServices() {
    Poco::Mutex::ScopedLock lock(mutexServices);
    return services;
}

size_t Device::getServiceCount() const
{
    Poco::Mutex::ScopedLock lock(mutexServices);
    return services.size();
}

void Device::addService(std::shared_ptr<Service> service)
{
    Poco::Mutex::ScopedLock lock(mutexServices);
	service->setParentDevice(this);
	services.push_back(service);
}

void Device::removeService(std::shared_ptr<Service> service) {
    Poco::Mutex::ScopedLock lock(mutexServices);
	services.erase(find(services.begin(), services.end(), service));
}

void Device::configureDefaultDPWS11()
{
	if (protocolBindings.find(DPWS11) == protocolBindings.end())
		protocolBindings[DPWS11] = std::vector<std::shared_ptr<OSCLib::Comm::AbstractBinding>>();

	// Create discovery binding
	std::shared_ptr<IPBinding> discoveryBinding(new IPBinding(UDP_MULTICAST_IP_V4, UPD_MULTICAST_DISCOVERY_PORT));
	discoveryBinding->setType(AbstractBinding::UDP_MULTICAST);

	// Make device discoverable in DPWS 1.1 protocol domain
	protocolBindings[DPWS11].push_back(discoveryBinding);

	// Add default device types
	Data::QName dpwsType("Device", WS_NS_DPWS, "dpws");
	addType(dpwsType);
}

void Device::start()
{
	// Check for device bindings and create them if needed using global settings
	if (protocolBindings[DPWS11].size() == 1)
	{
		const std::string bndIp = OSCLibrary::getInstance()->getBindInterface();
		const std::string bndPath = getEndpointReference().getAddress();
		std::shared_ptr<Binding> autoBnd(new Binding(bndIp, OSCLibrary::getInstance()->extractNextPort(), bndPath));
		const std::string bndStr(autoBnd->toString());
		Util::DebugOut(Util::DebugOut::Info, "Device") << "Autobinding device to: "<< bndStr;
		addBinding(DPWS11, autoBnd);
	}
	OSCLibrary::getInstance()->registerDevice(this);
    ServiceVector::iterator it;
    {
        Poco::Mutex::ScopedLock lock(mutexServices);
        for (it = services.begin(); it != services.end(); ++it)
        {
            (*it)->start();
        }
    }
	// Flag need to be set here, otherwise services would trigger device restart
    running = true;
    // Initialize all communication managers
    {
        Poco::Mutex::ScopedLock lockMan(mutexManagers);
        ManagerSet::iterator mIt;
        for (mIt = managers.begin(); mIt != managers.end(); ++mIt)
        {
            (*mIt)->init(this);
        }
    }
}

void Device::stop()
{
	if (OSCLibrary::getInstance()->isInitialized())
	{
		// Stop hosted services
        {
            Poco::Mutex::ScopedLock lock(mutexServices);
            ServiceVector::iterator it;
            for (it = services.begin(); it != services.end(); ++it)
            {
                (*it)->stop();
            }
        }
		// Shutdown all communication managers
        {
            Poco::Mutex::ScopedLock lockMan(mutexManagers);
            ManagerSet::iterator mIt;
            for (mIt = managers.begin(); mIt != managers.end(); ++mIt)
            {
                (*mIt)->shutdown();
            }
        }
	}

	while (OSCLibrary::getInstance()->existsManagerScheduledForShutdown()) {
		Poco::Thread::sleep(10);
	}

	running = false;

	OSCLibrary::getInstance()->unRegisterDevice(this);
}

bool Device::isRunning() const
{
	return running;
}

void Device::clearManagersWithoutDelete() {
    Poco::Mutex::ScopedLock lock(mutexManagers);
	managers.clear();
}

void Device::clearManagersAndDelete() {
    Poco::Mutex::ScopedLock lock(mutexManagers);
	ManagerSet::iterator mIt;
	for (mIt = managers.begin(); mIt != managers.end(); ++mIt)
		delete (*mIt);
	clearManagersWithoutDelete();
}


void Device::addDefaultCharacteristics()
{
	DeviceCharacteristics dc = getDeviceCharacteristics();
	dc.setManufacturer("OR.NET");
	dc.setManufacturerUrl("www.ornet.org");
	dc.addModelName("en-US", "OR.NET Example Model");
	dc.setModelNumber("1");
	dc.setModelUrl("http://www.ornet.com/example");
	dc.addFriendlyName("en-US", "OR.NET Example Device");
	dc.setFirmwareVersion("1.0");
	dc.setSerialNumber("123");
	setDeviceCharacteristics(dc);
}

}
}


