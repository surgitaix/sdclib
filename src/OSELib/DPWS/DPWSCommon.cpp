/*
 * DPWSCommon.cpp
 *
 *  Created on: 11.12.2015, matthias
 *  Modified on: 23.08.2019, baumeister
 *
 */

#include "OSELib/DPWS/DPWSCommon.h"
#include "OSELib/DPWS/MessageAdapter.h"
#include "OSELib/DPWS/Types.h"
#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/SOAP/NormalizedMessageSerializer.h"
#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"

#include "DataModel/NormalizedMessageModel.hxx"

namespace OSELib {
namespace DPWS {
namespace Impl {

const xml_schema::Uri discoveryUri("urn:docs-oasis-open-org:ws-dd:ns:discovery:2009:01");
const xml_schema::Uri byeUri("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Bye");
const xml_schema::Uri helloUri("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Hello");
const xml_schema::Uri probeUri("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Probe");
const xml_schema::Uri probeMatchesUri("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/ProbeMatches");
const xml_schema::Uri resolveUri("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Resolve");
const xml_schema::Uri resolveMatchesUri("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/ResolveMatches");
const xml_schema::Uri addressingAnonymousUri("http://www.w3.org/2005/08/addressing/anonymous");

std::unique_ptr<MESSAGEMODEL::Envelope> parseMessage(std::istream & p_stream)
{
	Helper::XercesGrammarPoolProvider t_grammarProvider;
	try {
		// todo add validation with correct grammar
		SOAP::CommonSoapPreprocessing t_soapHandling(t_grammarProvider);
		t_soapHandling.parse(p_stream);
		return std::move(t_soapHandling.normalizedMessage);
	} catch (...) {
		// todo add proper exception handling
	}
	return nullptr;
}

const std::string serializeMessage(const MESSAGEMODEL::Envelope & p_message)
{
	OSELib::SOAP::NormalizedMessageSerializer t_serializer; // FIXME: Always new instance?
	return t_serializer.serialize(p_message);
}

bool compare(const ProbeType & p_filter, const ProbeMatchType & p_type)
{
	const ScopesType t_foundScopes(MessageAdapter::Scopes(p_type));
	const TypesType t_foundTypes(MessageAdapter::Types(p_type));
	const auto t_matchScopes = [&](const ScopeType & p_scope) {
			return std::find(t_foundScopes.begin(), t_foundScopes.end(), p_scope) != t_foundScopes.end();
	};
	const auto t_matchTypes = [&](const TypeType & qname) {
			return std::find(t_foundTypes.begin(), t_foundTypes.end(), qname) != t_foundTypes.end();
	};

	const ScopesType t_filterScopes(MessageAdapter::Scopes(p_filter));
	const TypesType t_filterTypes(MessageAdapter::Types(p_filter));
	return std::all_of(t_filterScopes.begin(), t_filterScopes.end(), t_matchScopes)
		&& std::all_of(t_filterTypes.begin(), t_filterTypes.end(), t_matchTypes);
}

bool compare(const ResolveType & p_filter, const ResolveMatchType & p_type)
{
	const AddressType t_foundType(MessageAdapter::EPRAddress(p_type));
	const AddressType t_filterType(MessageAdapter::EPRAddress(p_filter));
	return t_foundType == t_filterType;
}

}
}
}

