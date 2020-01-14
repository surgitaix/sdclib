/*
 * SDCServiceController.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_SDCEVENTSERVICECONTROLLER_H_
#define OSELIB_SDC_SDCEVENTSERVICECONTROLLER_H_

#include "OSELib/HTTP/Service.h"

namespace OSELib
{
	namespace SDC
	{
		template<class IServiceType, class ServiceHandlerType>
		class SDCEventServiceController : public HTTP::Service
		{
		private:
			IServiceType & m_serviceImpl;
			DefaultSDCSchemaGrammarProvider m_grammarProvider;
		public:
			SDCEventServiceController(HTTP::FrontController & p_controller, IServiceType & p_serviceImpl)
			: Service(p_controller, { p_serviceImpl.getBaseUri() })
			, m_serviceImpl(p_serviceImpl)
			{ }
			// Special Member Functions
			SDCEventServiceController(const SDCEventServiceController& p_obj) = delete;
			SDCEventServiceController(SDCEventServiceController&& p_obj) = delete;
			SDCEventServiceController& operator=(const SDCEventServiceController& p_obj) = delete;
			SDCEventServiceController& operator=(SDCEventServiceController&& p_obj) = delete;
			virtual ~SDCEventServiceController() = default;

			Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest & , bool) override {
				return new ServiceHandlerType(m_serviceImpl, m_grammarProvider);
			}
		};
	}
}

#endif
