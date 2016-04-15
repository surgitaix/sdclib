/*
 * OSCPServiceController.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSCP_OSCPEVENTSERVICECONTROLLER_H_
#define OSCP_OSCPEVENTSERVICECONTROLLER_H_

#include "OSELib/HTTP/FrontController.h"
#include "OSELib/HTTP/Service.h"
#include "OSELib/OSCP/DefaultOSCPSchemaGrammarProvider.h"
#include "OSELib/HTTP/StaticContentController.h"
#include "OSELib/WSDL/schema.h"

namespace OSELib {
namespace OSCP {

template<class IServiceType, class ServiceHandlerType>
class OSCPEventServiceController : public HTTP::Service {
public:
	OSCPEventServiceController(HTTP::FrontController & controller, IServiceType & serviceImpl) :
		Service(controller, { serviceImpl.getBaseUri() }),
		_serviceImpl(serviceImpl)
	{
	}
	virtual ~OSCPEventServiceController() = default;

	virtual Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest & ) override {
		return new ServiceHandlerType(_serviceImpl, _grammarProvider);
	}

private:
	IServiceType & _serviceImpl;
	DefaultOSCPSchemaGrammarProvider _grammarProvider;
};

} /* namespace OSCP */
} /* namespace OSELib */

#endif /* OSCP_OSCPEVENTSERVICECONTROLLER_H_ */
