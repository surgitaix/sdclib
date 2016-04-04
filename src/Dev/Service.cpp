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
 *  @file Service.cpp
 *  @project OSCLib
 *  @date 16.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */

#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Comm/Binding.h"
#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Data/EventSource.h"
#include "OSCLib/Data/Operation.h"
#include "OSCLib/Dev/Device.h"
#include "OSCLib/Dev/EndpointReference.h"
#include "OSCLib/Dev/Service.h"
#include "OSCLib/Util/DebugOut.h"
#ifdef _WIN32
#include <direct.h>
#endif
#include <algorithm>

using namespace OSCLib::Comm;
using namespace OSCLib::Data;
using namespace OSCLib::Util;
using namespace OSCLib::Comm::DPWS;

namespace OSCLib {
namespace Dev {

Service::Service() : parentDevice(nullptr), running(false)
{
	configureDefaultDPWS11();
}

Service::~Service()
{
	if (isRunning()) {
		stop();
		Util::DebugOut(Util::DebugOut::Error, "Service") << "Please stop all services before they are destroyed.";
	}
}

void Service::configureDefaultDPWS11()
{
	if (protocolBindings.find(DPWS11) == protocolBindings.end())
		protocolBindings[DPWS11] = std::vector<std::shared_ptr<OSCLib::Comm::AbstractBinding>>();
}

Device * Service::getParentDevice()
{
	return parentDevice;
}

void Service::setParentDevice(Device * parentDevice)
{
	this->parentDevice = parentDevice;
}

void Service::start()
{
	if (getServiceId().length() == 0)
	{
		DebugOut(DebugOut::Error, "Service") << "Missing Service ID.";
		return;
	}
	if (getParentDevice()->isRunning())
	{
		Util::DebugOut(Util::DebugOut::Error, "Service")  << "Parent device already running, can't start service: " << getServiceId();
		return;
	}
	// Check for service bindings and create them if needed using global settings
	if (protocolBindings[DPWS11].size() == 0)
	{
		const std::string & bindingIp = OSCLibrary::getInstance()->getBindInterface();
		const std::string & bindingPath = getServiceId();
		std::shared_ptr<Binding> autoBind(new Binding(bindingIp, OSCLibrary::getInstance()->extractNextPort(), bindingPath));
		const std::string bindingString(autoBind->toString());
		Util::DebugOut(Util::DebugOut::Info, "Service") << "Autobinding service to: " << bindingString;
		addBinding(DPWS11, autoBind);
	}
	// Check port types, add if needed
	OperationVector::iterator oIt;
	for (oIt = operations.begin(); oIt != operations.end(); ++oIt)
	{
		QName pt = (*oIt)->getPortType();
		QVector::iterator sIt;
		bool found = false;
		for (sIt = types.begin(); sIt != types.end(); ++sIt)
		{
			if (pt == (*sIt))
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			addType(pt);
		}

		if ((*oIt)->getInputAction().length() == 0) {
			(*oIt)->setInputAction((*oIt)->getDefaultInputAction());
		}

		if ((*oIt)->getOutputAction().length() == 0) {
			(*oIt)->setOutputAction((*oIt)->getDefaultOutputAction());
		}
	}

	Dev::EndpointReference epr(getEndpointReference());
	if (epr.getAddress().compare("N/A") == 0) {
		const std::string eprStr(getDefaultTransportAddr(DPWS11));
		if (eprStr.length() == 0)
			Util::DebugOut(Util::DebugOut::Error, "Service")  << "No address available. Missing DPWS 1.1 binding.";
		epr.setAddress(eprStr);
		setEndpointReference(epr);
	}

	running = true;
}

void Service::stop()
{
	running = false;
}

bool Service::isRunning() const
{
	return running;
}

const std::string & Service::getServiceId() const
{
	return serviceId;
}

void Service::setServiceId(const std::string & id)
{
	serviceId = id;
}

const OperationVector & Service::getOperations() const
{
	return operations;
}

void Service::addSubscription(std::shared_ptr<Data::Subscription> subscription) {
	subscriptions.addSubscription(subscription);
}

bool Service::renewSubscription(const std::string & ident, const std::string & expires) {
	return subscriptions.renewSubscription(ident, expires);
}

void Service::cancelSubscription(const std::string & ident) {
	subscriptions.cancelSubscription(ident);
}

std::vector<std::shared_ptr<Data::Subscription>>  Service::getActiveSubscriptions(const std::string & actionString) {
	return subscriptions.getActiveSubscriptions(actionString);
}

void Service::addOperation(std::shared_ptr<Data::Operation> op)
{
	op->setParentService(this);
	operations.push_back(op);
}

void Service::cleanExpiredSubscriptions() {
	subscriptions.cleanExpiredSubscriptions();
}

void Service::setStaticWSDLContent(const std::string & content) {
	this->staticWSDLContent = content;
}

std::string Service::getStaticWSDL() {
	return staticWSDLContent;
}

void Service::addSchemaFile(const std::string & requestName, const std::string & content) {
	schemaFiles[requestName] = content;
}

std::map<std::string, std::string> Service::getSchemaFiles() const {
	return schemaFiles;
}

std::shared_ptr<Operation> Service::getOperation(const std::string& action) const
{
	OperationVector::const_iterator oIt;
	for (oIt = operations.begin(); oIt != operations.end(); ++oIt)
	{
		if (action.compare((*oIt)->getInputAction()) == 0 || action.compare((*oIt)->getOutputAction()) == 0)
			return *oIt;
	}
	return nullptr;
}

const StringVector & Service::getScopes() const
{
	return parentDevice->getScopes();
}

void Service::addEvent(std::shared_ptr<Data::EventSource> event)
{
	addOperation(event);
}

void Service::clearScopes() {
	parentDevice->clearScopes();
}

} /* namespace Device */
} /* namespace OSCLib */
