/*
 * MessageAdapter.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "wsdd-discovery-1.1-schema-os.hxx"
#include "ws-addressing.hxx"

#include "OSELib/DPWS/MessageAdapter.h"

namespace OSELib {
namespace DPWS {

template<class Message>
AddressType MessageAdapter::EPRAddress(const Message & message) {
	return message.EndpointReference().Address();
}

template<class Message>
MetadataVersionType MessageAdapter::MetadataVersion(const Message & message) {
	return message.MetadataVersion();
}

template<class Message>
XAddressesType MessageAdapter::XAddresses(const Message & message) {
	if (message.XAddrs().present()) {
		return message.XAddrs().get();
	} else {
		return XAddressesType();
	}
}

template<class Message>
ScopesType MessageAdapter::Scopes(const Message & message) {
	if (message.Scopes().present()) {
		return message.Scopes().get();
	} else {
		return ScopesType();
	}
}

template<class Message>
TypesType MessageAdapter::Types(const Message & message) {
	if (message.Types().present()) {
		return message.Types().get();
	} else {
		return TypesType();
	}
}

UriType MessageAdapter::URI(const QName & qname) {
	return qname.namespace_();
}

std::string MessageAdapter::LocalName(const QName & qname) {
	return qname.name();
}

template ScopesType MessageAdapter::Scopes(const WS::DISCOVERY::ByeType & message);
template ScopesType MessageAdapter::Scopes(const WS::DISCOVERY::HelloType & message);
template ScopesType MessageAdapter::Scopes(const WS::DISCOVERY::ProbeType & message);
template ScopesType MessageAdapter::Scopes(const WS::DISCOVERY::ProbeMatchType & message);
template ScopesType MessageAdapter::Scopes(const WS::DISCOVERY::ResolveMatchType & message);

template TypesType MessageAdapter::Types(const WS::DISCOVERY::ByeType & message);
template TypesType MessageAdapter::Types(const WS::DISCOVERY::HelloType & message);
template TypesType MessageAdapter::Types(const WS::DISCOVERY::ProbeType & message);
template TypesType MessageAdapter::Types(const WS::DISCOVERY::ProbeMatchType & message);
template TypesType MessageAdapter::Types(const WS::DISCOVERY::ResolveMatchType & message);

template XAddressesType MessageAdapter::XAddresses(const WS::DISCOVERY::ByeType & message);
template XAddressesType MessageAdapter::XAddresses(const WS::DISCOVERY::HelloType & message);
template XAddressesType MessageAdapter::XAddresses(const WS::DISCOVERY::ProbeMatchType & message);
template XAddressesType MessageAdapter::XAddresses(const WS::DISCOVERY::ResolveMatchType & message);

template AddressType MessageAdapter::EPRAddress(const WS::DISCOVERY::ByeType & message);
template AddressType MessageAdapter::EPRAddress(const WS::DISCOVERY::HelloType & message);
template AddressType MessageAdapter::EPRAddress(const WS::DISCOVERY::ResolveType & message);
template AddressType MessageAdapter::EPRAddress(const WS::DISCOVERY::ResolveMatchType & message);
template AddressType MessageAdapter::EPRAddress(const WS::DISCOVERY::ProbeMatchType & message);

template MetadataVersionType MessageAdapter::MetadataVersion(const WS::DISCOVERY::HelloType & message);
template MetadataVersionType MessageAdapter::MetadataVersion(const WS::DISCOVERY::ProbeMatchType & message);
template MetadataVersionType MessageAdapter::MetadataVersion(const WS::DISCOVERY::ResolveMatchType & message);

} /* namespace DPWS */
} /* namespace OSELib */
