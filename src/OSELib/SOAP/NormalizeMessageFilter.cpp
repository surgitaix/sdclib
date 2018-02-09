/*
 * NormalizeMessageFilter.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include <OSELib/SDC/SDCConstants.h>
#include "NormalizedMessageModel.hxx"

#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/Helper/XercesUniqueElementByTagNameFilter.h"
#include "OSELib/SOAP/NormalizeMessageFilter.h"

namespace OSELib {
namespace SOAP {

std::unique_ptr<MESSAGEMODEL::Envelope> NormalizeMessageFilter::apply(const Helper::XercesDocumentWrapper & msg) {

	std::unique_ptr<MESSAGEMODEL::Envelope::HeaderType > header(new MESSAGEMODEL::Envelope::HeaderType());
	std::unique_ptr<MESSAGEMODEL::Envelope::BodyType> body(new MESSAGEMODEL::Envelope::BodyType());
	std::unique_ptr<MESSAGEMODEL::Envelope> result(new MESSAGEMODEL::Envelope(std::move(header), std::move(body)));

	Helper::XercesUniqueElementByTagNameFilter filter(msg);

	// We do this manually because the fields might appear in any order,
	// which is not supported by the xsd generated classes from the current model
	if (const auto filterResult = filter.apply(SDC::NS_ADDRESSING, "Action")) {
		result->Header().Action().set(WS::ADDRESSING::AttributedURIType(*filterResult));
	}
	if (const auto filterResult = filter.apply(WS_NS_DISCOVERY, "AppSequence")) {
		result->Header().AppSequence().set(WS::DISCOVERY::AppSequenceType(*filterResult));
	}
	if (const auto filterResult = filter.apply(SDC::NS_ADDRESSING, "FaultTo")) {
		result->Header().FaultTo().set(WS::ADDRESSING::EndpointReferenceType(*filterResult));
	}
	if (const auto filterResult = filter.apply(SDC::NS_ADDRESSING, "From")) {
		result->Header().From().set(WS::ADDRESSING::EndpointReferenceType(*filterResult));
	}
	if (const auto filterResult = filter.apply(SDC::NS_ADDRESSING, "MessageID")) {
		result->Header().MessageID().set(WS::ADDRESSING::AttributedURIType(*filterResult));
	}
	if (const auto filterResult = filter.apply(SDC::NS_ADDRESSING, "ReferenceParameters")) {
		result->Header().ReferenceParameters().set(WS::ADDRESSING::ReferenceParametersType(*filterResult));
	}
	if (const auto filterResult = filter.apply(SDC::NS_ADDRESSING, "RelatesTo")) {
		result->Header().RelatesTo().set(WS::ADDRESSING::RelatesToType(*filterResult));
	}
	if (const auto filterResult = filter.apply(SDC::NS_ADDRESSING, "ReplyTo")) {
		result->Header().ReplyTo().set(WS::ADDRESSING::EndpointReferenceType(*filterResult));
	}
	if (const auto filterResult = filter.apply(SDC::NS_ADDRESSING, "To")) {
		result->Header().To().set(WS::ADDRESSING::AttributedURIType(*filterResult));
	}
	if (const auto filterResult = filter.apply(SDC::NS_EVENTING, "Identifier")) {
		result->Header().Identifier().set(::xml_schema::Uri(*filterResult));
	}

	if (const auto filterResult = filter.apply(OSELib::WS_NS_SOAP_ENVELOPE, "Body")) {
		result->Body(MESSAGEMODEL::Body(*filterResult));
	}

	return std::move(result);
}

} /* namespace SOAP */
} /* namespace OSELib */
