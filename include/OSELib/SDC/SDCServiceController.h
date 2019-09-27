/*
 * SDCServiceController.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_SDCSERVICECONTROLLER_H_
#define OSELIB_SDC_SDCSERVICECONTROLLER_H_

#include "OSELib/HTTP/Service.h"
#include "OSELib/SDC/DefaultSDCSchemaGrammarProvider.h"
#include "OSELib/HTTP/StaticContentController.h"
#include "OSELib/Schema/Schema.h"

namespace OSELib
{
	namespace SDC
	{
		template<class IServiceType, class ServiceHandlerType>
		class SDCServiceController : public HTTP::Service
		{
		private:
			IServiceType & m_serviceImpl;
			DefaultSDCSchemaGrammarProvider m_grammarProvider;
			HTTP::StaticContentController m_wsdlController;
			HTTP::StaticContentController m_schemaDatamodelController;
			HTTP::StaticContentController m_schemaMessagemodelController;
			HTTP::StaticContentController m_schemaExtensionController;
		public:

			SDCServiceController(HTTP::FrontController& p_controller, IServiceType & p_serviceImpl)
			: Service(p_controller, { p_serviceImpl.getBaseUri() })
			, m_serviceImpl(p_serviceImpl)
			, m_wsdlController(p_controller, p_serviceImpl.getBaseUri() + "/description.wsdl", p_serviceImpl.getWSDL())
			, m_schemaDatamodelController(p_controller, p_serviceImpl.getBaseUri() + "/" + SCHEMA::SCHEMA_BICEPS_PARTICIPANTMODEL_NAME, SCHEMA::SCHEMA_BICEPS_PARTICIPANTMODEL_CONTENT)
			, m_schemaMessagemodelController(p_controller, p_serviceImpl.getBaseUri() + "/" + SCHEMA::SCHEMA_BICEPS_MESSAGEMODEL_NAME, SCHEMA::SCHEMA_BICEPS_MESSAGEMODEL_CONTENT)
			, m_schemaExtensionController(p_controller, p_serviceImpl.getBaseUri() + "/" + SCHEMA::SCHEMA_EXTENSIONPOINT_NAME, SCHEMA::SCHEMA_EXTENSIONPOINT_CONTENT)
			{ }
			// Special Member Functions
			SDCServiceController(const SDCServiceController& p_obj) = delete;
			SDCServiceController(SDCServiceController&& p_obj) = delete;
			SDCServiceController& operator=(const SDCServiceController& p_obj) = delete;
			SDCServiceController& operator=(SDCServiceController&& p_obj) = delete;
			virtual ~SDCServiceController() = default;

			Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest & , bool p_SSL) override {
				return new ServiceHandlerType(m_serviceImpl, m_grammarProvider, p_SSL);
			}

		};
	}
}

#endif

