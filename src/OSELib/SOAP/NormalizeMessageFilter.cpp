/*
 * NormalizeMessageFilter.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 22.08.2019, baumeister
 */

#include "OSELib/SOAP/NormalizeMessageFilter.h"
#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/Helper/XercesUniqueElementByTagNameFilter.h"


namespace OSELib {
namespace SOAP {

std::unique_ptr<MESSAGEMODEL::Envelope> NormalizeMessageFilter::apply(const Helper::XercesDocumentWrapper & p_msg)
{

	std::unique_ptr<MESSAGEMODEL::Envelope::HeaderType > t_header(new MESSAGEMODEL::Envelope::HeaderType());
	std::unique_ptr<MESSAGEMODEL::Envelope::BodyType> t_body(new MESSAGEMODEL::Envelope::BodyType());
	std::unique_ptr<MESSAGEMODEL::Envelope> t_result(new MESSAGEMODEL::Envelope(std::move(t_header), std::move(t_body)));

	Helper::XercesUniqueElementByTagNameFilter t_filter(p_msg);

	// We do this manually because the fields might appear in any order,
	// which is not supported by the xsd generated classes from the current model
	if (const auto t_filterResult = t_filter.apply(SDC::NS_ADDRESSING, "Action")) {
		t_result->Header().Action().set(WS::ADDRESSING::AttributedURIType(*t_filterResult));
	}
	if (const auto t_filterResult = t_filter.apply(WS_NS_DISCOVERY, "AppSequence")) {
		t_result->Header().AppSequence().set(WS::DISCOVERY::AppSequenceType(*t_filterResult));
	}
	if (const auto t_filterResult = t_filter.apply(SDC::NS_ADDRESSING, "FaultTo")) {
		t_result->Header().FaultTo().set(WS::ADDRESSING::EndpointReferenceType(*t_filterResult));
	}
	if (const auto t_filterResult = t_filter.apply(SDC::NS_ADDRESSING, "From")) {
		t_result->Header().From().set(WS::ADDRESSING::EndpointReferenceType(*t_filterResult));
	}
	if (const auto t_filterResult = t_filter.apply(SDC::NS_ADDRESSING, "MessageID")) {
		t_result->Header().MessageID().set(WS::ADDRESSING::AttributedURIType(*t_filterResult));
	}
	if (const auto t_filterResult = t_filter.apply(SDC::NS_ADDRESSING, "ReferenceParameters")) {
		t_result->Header().ReferenceParameters().set(WS::ADDRESSING::ReferenceParametersType(*t_filterResult));
	}
	if (const auto t_filterResult = t_filter.apply(SDC::NS_ADDRESSING, "RelatesTo")) {
		t_result->Header().RelatesTo().set(WS::ADDRESSING::RelatesToType(*t_filterResult));
	}
	if (const auto t_filterResult = t_filter.apply(SDC::NS_ADDRESSING, "ReplyTo")) {
		t_result->Header().ReplyTo().set(WS::ADDRESSING::EndpointReferenceType(*t_filterResult));
	}
	if (const auto t_filterResult = t_filter.apply(SDC::NS_ADDRESSING, "To")) {
		t_result->Header().To().set(WS::ADDRESSING::AttributedURIType(*t_filterResult));
	}
	if (const auto t_filterResult = t_filter.apply(SDC::NS_EVENTING, "Identifier")) {
		t_result->Header().Identifier().set(::xml_schema::Uri(*t_filterResult));
	}

	if (const auto t_filterResult = t_filter.apply(OSELib::WS_NS_SOAP_ENVELOPE, "Body")) {
		t_result->Body(MESSAGEMODEL::Body(*t_filterResult));
	}

	return t_result;
}

}
}
