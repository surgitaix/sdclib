/*
 * OperationTraits.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include <OSELib/OSCP/OSCPConstants.h>
#include "eventing.hxx"
#include "NormalizedMessageModel.hxx"
#include "wsdd-discovery-1.1-schema-os.hxx"

#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/IDevice.h"
#include "OSELib/DPWS/ISubscriptionManager.h"
#include "OSELib/DPWS/OperationTraits.h"

namespace OSELib {
namespace DPWS {

std::string GetTraits::OperationName() {
	return "Get";
}
std::string GetTraits::RequestAction() {
	return WS_ACTION_GET;
}
std::string GetTraits::ResponseAction() {
	return WS_ACTION_GET_RESPONSE;
}
xml_schema::Qname GetTraits::ResponseType() {
	return xml_schema::Qname(WS_NS_METADATA_EXCHANGE, "Metadata");
}

std::string GetMetadataTraits::OperationName() {
	return "GetMetadata";
}
std::string GetMetadataTraits::RequestAction() {
	return WS_ACTION_GET_METADATA_REQUEST;
}
xml_schema::Qname GetMetadataTraits::RequestType() {
	return xml_schema::Qname(WS_NS_METADATA_EXCHANGE, OperationName());
}
std::string GetMetadataTraits::ResponseAction() {
	return WS_ACTION_GET_METADATA_RESPONSE;
}
xml_schema::Qname GetMetadataTraits::ResponseType() {
	return xml_schema::Qname(WS_NS_METADATA_EXCHANGE, "Metadata");
}

std::string ProbeTraits::OperationName() {
	return "Probe";
}
std::string ProbeTraits::RequestAction() {
	return WS_ACTION_PROBE;
}
std::string ProbeTraits::ResponseAction() {
	return WS_ACTION_PROBE_MATCHES;
}
std::unique_ptr<ProbeTraits::Response> ProbeTraits::dispatch(Dispatcher & dispatcher, const Request & request) {
	return dispatcher.dispatch(request);
}

std::string RenewTraits::OperationName() {
	return "Renew";
}
std::string RenewTraits::RequestAction() {
	return WS_ACTION_RENEW;
}
xml_schema::Qname RenewTraits::RequestType() {
	return xml_schema::Qname(WS_NS_EVENTING, OperationName());
}
std::string RenewTraits::ResponseAction() {
	return WS_ACTION_RENEW_RESPONSE;
}
xml_schema::Qname RenewTraits::ResponseType() {
	return xml_schema::Qname(WS_NS_EVENTING, OperationName() + "Response");
}
std::unique_ptr<RenewTraits::Response> RenewTraits::dispatch(Dispatcher & dispatcher, const Request & request, const RequestIdentifier & identifier) {
	return dispatcher.dispatch(request, identifier);
}

std::string SubscribeTraits::OperationName() {
	return "Subscribe";
}
std::string SubscribeTraits::RequestAction() {
	return WS_ACTION_SUBSCRIBE;
}
xml_schema::Qname SubscribeTraits::RequestType() {
	return xml_schema::Qname(WS_NS_EVENTING, OperationName());
}
std::string SubscribeTraits::ResponseAction() {
	return WS_ACTION_SUBSCRIBE_RESPONSE;
}
xml_schema::Qname SubscribeTraits::ResponseType() {
	return xml_schema::Qname(WS_NS_EVENTING, OperationName() + "Response");
}
std::unique_ptr<SubscribeTraits::Response> SubscribeTraits::dispatch(SubscribeTraits::Dispatcher & dispatcher, const Request & request) {
	return dispatcher.dispatch(request);
}

std::string UnsubscribeTraits::OperationName() {
	return "Unsubscribe";
}
std::string UnsubscribeTraits::RequestAction() {
	return WS_ACTION_UNSUBSCRIBE;
}
xml_schema::Qname UnsubscribeTraits::RequestType() {
	return xml_schema::Qname(WS_NS_EVENTING, OperationName());
}
std::string UnsubscribeTraits::ResponseAction() {
	return WS_ACTION_UNSUBSCRIBE_RESPONSE;
}
xml_schema::Qname UnsubscribeTraits::ResponseType() {
	return xml_schema::Qname(WS_NS_EVENTING, OperationName() + "Response");
}
std::unique_ptr<UnsubscribeTraits::Response> UnsubscribeTraits::dispatch(Dispatcher & dispatcher, const Request & request, const RequestIdentifier & identifier) {
	return dispatcher.dispatch(request, identifier);
}

} /* namespace DPWS */
} /* namespace OSELib */
