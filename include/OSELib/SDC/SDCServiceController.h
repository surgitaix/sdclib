/*
 * SDCServiceController.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */


#ifndef OSELIB_SDC_SDCSERVICECONTROLLER_H_
#define OSELIB_SDC_SDCSERVICECONTROLLER_H_

#include "OSELib/HTTP/FrontController.h"
#include "OSELib/HTTP/Service.h"
#include "OSELib/SDC/DefaultSDCSchemaGrammarProvider.h"
#include "OSELib/HTTP/StaticContentController.h"
#include "OSELib/Schema/Schema.h"

namespace OSELib {
namespace SDC {

template<class IServiceType, class ServiceHandlerType>
class SDCServiceController : public HTTP::Service {
public:
	SDCServiceController(HTTP::FrontController & controller, IServiceType & serviceImpl) :
		Service(controller, { serviceImpl.getBaseUri() }),
		_serviceImpl(serviceImpl),
		_wsdlController(controller, serviceImpl.getBaseUri() + "/description.wsdl", serviceImpl.getWSDL()),
		_schemaDatamodelController(controller, serviceImpl.getBaseUri() + "/" + SCHEMA::SCHEMA_BICEPS_PARTICIPANTMODEL_NAME, SCHEMA::SCHEMA_BICEPS_PARTICIPANTMODEL_CONTENT),
		_schemaMessagemodelController(controller, serviceImpl.getBaseUri() + "/" + SCHEMA::SCHEMA_BICEPS_MESSAGEMODEL_NAME, SCHEMA::SCHEMA_BICEPS_MESSAGEMODEL_CONTENT),
		_schemaExtensionController(controller, serviceImpl.getBaseUri() + "/" + SCHEMA::SCHEMA_EXTENSIONPOINT_NAME, SCHEMA::SCHEMA_EXTENSIONPOINT_CONTENT)
	{
	}
	virtual ~SDCServiceController() = default;

	Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest & , bool p_SSL) override {
		return new ServiceHandlerType(_serviceImpl, _grammarProvider, p_SSL);
	}

private:
	IServiceType & _serviceImpl;
	DefaultSDCSchemaGrammarProvider _grammarProvider;
	HTTP::StaticContentController _wsdlController;
	HTTP::StaticContentController _schemaDatamodelController;
	HTTP::StaticContentController _schemaMessagemodelController;
	HTTP::StaticContentController _schemaExtensionController;
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* OSELIB_SDC_SDCSERVICECONTROLLER_H_ */

