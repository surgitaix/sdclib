/*
 * DPWSCommon.cpp
 *
 *  Created on: 11.12.2015
 *      Author: matthias
 */

#include <iostream>

#include "NormalizedMessageModel.hxx"

#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/DPWSCommon.h"
#include "OSELib/DPWS/MessageAdapter.h"
#include "OSELib/DPWS/Types.h"
#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"
#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/SOAP/NormalizedMessageSerializer.h"

namespace OSELib {
namespace DPWS {
namespace Impl {

const xml_schema::Uri discoveryUri("urn:docs-oasis-open-org:ws-dd:ns:discovery:2009:01");
const xml_schema::Uri byeUri("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Bye");
const xml_schema::Uri helloUri("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Hello");
const xml_schema::Uri probeUri("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Probe");
const xml_schema::Uri probeMatchesUri("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/ProbeMatches");
const xml_schema::Uri streamUri("http://message-model-uri/15/04/WaveformStreamService/WaveformStream");
const xml_schema::Uri resolveUri("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Resolve");
const xml_schema::Uri resolveMatchesUri("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/ResolveMatches");
const xml_schema::Uri addressingAnonymousUri("http://www.w3.org/2005/08/addressing/anonymous");

std::unique_ptr<MESSAGEMODEL::Envelope> parseMessage(std::istream & stream) {
	Helper::XercesGrammarPoolProvider grammarProvider;
	try {
		// todo add validation with correct grammar
		SOAP::CommonSoapPreprocessing soapHandling(grammarProvider);
		soapHandling.parse(stream);
		return std::move(soapHandling.normalizedMessage);
	} catch (...) {
		// todo add proper exception handling
	}
	return nullptr;
}

const std::string serializeMessage(const MESSAGEMODEL::Envelope & message) {
	OSELib::SOAP::NormalizedMessageSerializer serializer;
	return serializer.serialize(message);
}

bool compare(const ProbeType & filter, const ProbeMatchType & n) {
	const ScopesType foundScopes(MessageAdapter::Scopes(n));
	const TypesType foundTypes(MessageAdapter::Types(n));
	const auto matchScopes =
		[&](const ScopeType & scope) {
			return std::find(foundScopes.begin(), foundScopes.end(), scope) != foundScopes.end();
		};
	const auto matchTypes =
		[&](const TypeType & qname) {
			return std::find(foundTypes.begin(), foundTypes.end(), qname) != foundTypes.end();
		};

	const ScopesType filterScopes(MessageAdapter::Scopes(filter));
	const TypesType filterTypes(MessageAdapter::Types(filter));
	return std::all_of(filterScopes.begin(), filterScopes.end(), matchScopes)
		&& std::all_of(filterTypes.begin(), filterTypes.end(), matchTypes);
}

bool compare(const ResolveType & filter, const ResolveMatchType & n) {
	const AddressType foundType(MessageAdapter::EPRAddress(n));
	const AddressType filterType(MessageAdapter::EPRAddress(filter));
	return foundType == filterType;
}

} /* namespace Impl */
} /* namespace DPWS */
} /* namespace OSELib */
