/*
 * SDCServiceController.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_SDC_SDCEVENTSERVICECONTROLLER_H_
#define OSELIB_SDC_SDCEVENTSERVICECONTROLLER_H_

#include "OSELib/HTTP/FrontController.h"
#include "OSELib/HTTP/Service.h"
#include "OSELib/SDC/DefaultSDCSchemaGrammarProvider.h"
#include "OSELib/HTTP/StaticContentController.h"

namespace OSELib {
namespace SDC {

template<class IServiceType, class ServiceHandlerType>
class SDCEventServiceController : public HTTP::Service {
public:
	SDCEventServiceController(HTTP::FrontController & controller, IServiceType & serviceImpl) :
		Service(controller, { serviceImpl.getBaseUri() }),
		_serviceImpl(serviceImpl)
	{
	}
	virtual ~SDCEventServiceController() = default;

	Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest & ) override {
		return new ServiceHandlerType(_serviceImpl, _grammarProvider);
	}

private:
	IServiceType & _serviceImpl;
	DefaultSDCSchemaGrammarProvider _grammarProvider;
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* OSELIB_SDC_SDCEVENTSERVICECONTROLLER_H_ */
