/*
 *  BICEPSServiceEventSinkHandler.cpp
 *
 *  Created on: 26.09.2019, baumeister
 *
 */

#include "OSELib/SDC/BICEPSServiceEventSinkHandler.h"
#include "OSELib/SDC/ReportTraits.h"
#include "OSELib/SOAP/Command.h"
#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/SOAP/GenericSoapEventCommand.h"
#include "OSELib/SOAP/SoapFaultCommand.h"
#include "OSELib/SOAP/SoapHTTPResponseWrapper.h"
#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"

#include "OSELib/SDC/IBICEPSServiceEventSink.h"
#include "OSELib/SDC/IDescriptionEventServiceEventSink.h"
#include "OSELib/SDC/IStateEventServiceEventSink.h"
#include "OSELib/SDC/IContextServiceEventSink.h"

#include <Poco/Net/HTTPServerRequest.h>

using namespace OSELib;
using namespace OSELib::SDC;

BICEPSServiceEventSinkHandler::BICEPSServiceEventSinkHandler(IBICEPSServiceEventSink & p_service, Helper::XercesGrammarPoolProvider & p_grammarProvider)
: m_service(p_service)
, m_grammarProvider(p_grammarProvider)
{ }

void BICEPSServiceEventSinkHandler::handleRequestImpl(Poco::Net::HTTPServerRequest & p_httpRequest, Poco::Net::HTTPServerResponse & p_httpResponse)
{
	SOAP::CommonSoapPreprocessing t_soapHandling(m_grammarProvider);
	t_soapHandling.parse(p_httpRequest.stream());

	const auto t_soapAction(t_soapHandling.normalizedMessage->getHeader().getAction().get());

	std::unique_ptr<SOAP::Command> t_command(new SOAP::SoapFaultCommand(p_httpResponse));
	
	// Description Event Service
	if (t_soapAction == DescriptionModificationReportTraits::Action()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<DescriptionModificationReportTraits>(std::move(t_soapHandling.normalizedMessage), static_cast<IDescriptionEventServiceEventSink&>(m_service)));
	}
	// StateEventService
	else if (t_soapAction == EpisodicAlertReportTraits::Action()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<EpisodicAlertReportTraits>(std::move(t_soapHandling.normalizedMessage), static_cast<IStateEventServiceEventSink&>(m_service)));
	} else if (t_soapAction == EpisodicComponentReportTraits::Action()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<EpisodicComponentReportTraits>(std::move(t_soapHandling.normalizedMessage), static_cast<IStateEventServiceEventSink&>(m_service)));
	} else if (t_soapAction == EpisodicMetricReportTraits::Action()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<EpisodicMetricReportTraits>(std::move(t_soapHandling.normalizedMessage), static_cast<IStateEventServiceEventSink&>(m_service)));
	} else if (t_soapAction == EpisodicOperationalStateReportTraits::Action()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<EpisodicOperationalStateReportTraits>(std::move(t_soapHandling.normalizedMessage), static_cast<IStateEventServiceEventSink&>(m_service)));
	} else if (t_soapAction == PeriodicAlertReportTraits::Action()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<PeriodicAlertReportTraits>(std::move(t_soapHandling.normalizedMessage), static_cast<IStateEventServiceEventSink&>(m_service)));
	} else if (t_soapAction == PeriodicMetricReportTraits::Action()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<PeriodicMetricReportTraits>(std::move(t_soapHandling.normalizedMessage), static_cast<IStateEventServiceEventSink&>(m_service)));
	}
	// ContextService
	else if (t_soapAction == EpisodicContextReportTraits::Action()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<EpisodicContextReportTraits>(std::move(t_soapHandling.normalizedMessage), static_cast<IContextServiceEventSink&>(m_service)));
	} else if (t_soapAction == PeriodicContextReportTraits::Action()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<PeriodicContextReportTraits>(std::move(t_soapHandling.normalizedMessage), static_cast<IContextServiceEventSink&>(m_service)));
	} else {
		log_error([&] { return "BICEPSServiceEventSinkHandler can't handle action: " + t_soapAction; });
	}

	auto t_responseMessage(t_command->Run());
	if(nullptr == t_responseMessage) {
		log_debug([&] { return "BICEPSServiceEventSinkHandler failed to generate Response for Action: " + t_soapAction; });
	}

	// todo add proper soap fault handling in response

	SOAP::SoapHTTPResponseWrapper t_response(p_httpResponse, SOAP::SoapHTTPResponseWrapper::HTTPStatus::HTTP_ACCEPTED);
	t_response.send("");
	//fixme: Empty?
}
