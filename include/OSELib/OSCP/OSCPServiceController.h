/*
 * OSCPServiceController.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */


#ifndef OSCP_OSCPSERVICECONTROLLER_H_
#define OSCP_OSCPSERVICECONTROLLER_H_

#include "OSELib/HTTP/FrontController.h"
#include "OSELib/HTTP/Service.h"
#include "OSELib/OSCP/DefaultOSCPSchemaGrammarProvider.h"
#include "OSELib/HTTP/StaticContentController.h"
#include "OSELib/WSDL/schema.h"

namespace OSELib {
namespace OSCP {

template<class IServiceType, class ServiceHandlerType>
class OSCPServiceController : public HTTP::Service {
public:
	OSCPServiceController(HTTP::FrontController & controller, IServiceType & serviceImpl) :
		Service(controller, { serviceImpl.getBaseUri() }),
		_serviceImpl(serviceImpl),
		_wsdlController(controller, serviceImpl.getBaseUri() + "/description.wsdl", serviceImpl.getWSDL()),
		_schemaDatamodelController(controller, serviceImpl.getBaseUri() + "/" + SCHEMA::SCHEMA_DATAMODEL_NAME, SCHEMA::SCHEMA_DATAMODEL_CONTENT),
		_schemaMessagemodelController(controller, serviceImpl.getBaseUri() + "/" + SCHEMA::SCHEMA_MESSAGEMODEL_NAME, SCHEMA::SCHEMA_MESSAGEMODEL_CONTENT),
		_schemaExtensionController(controller, serviceImpl.getBaseUri() + "/" + SCHEMA::SCHEMA_EXTENSION_POINT_NAME, SCHEMA::SCHEMA_EXTENSION_POINT_CONTENT)
	{
	}
	virtual ~OSCPServiceController() = default;

	virtual Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest & ) override {
		return new ServiceHandlerType(_serviceImpl, _grammarProvider);
	}

private:
	IServiceType & _serviceImpl;
	DefaultOSCPSchemaGrammarProvider _grammarProvider;
	HTTP::StaticContentController _wsdlController;
	HTTP::StaticContentController _schemaDatamodelController;
	HTTP::StaticContentController _schemaMessagemodelController;
	HTTP::StaticContentController _schemaExtensionController;
};

} /* namespace OSCP */
} /* namespace OSELib */

#endif /* OSCP_OSCPSERVICECONTROLLER_H_ */

