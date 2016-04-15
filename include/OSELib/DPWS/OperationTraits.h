/*
 * OperationTraits.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef DPWS_OPERATIONTRAITS_H_
#define DPWS_OPERATIONTRAITS_H_

#include "OSELib/fwd.h"

namespace OSELib {
namespace DPWS {

struct GetTraits {
	typedef MESSAGEMODEL::Body Request;
	typedef WS::MEX::Metadata Response;
	static std::string OperationName();
	static std::string RequestAction();
	static std::string ResponseAction();
	static xml_schema::Qname ResponseType();
};

struct GetMetadataTraits {
	typedef WS::MEX::GetMetadata Request;
	typedef WS::MEX::Metadata Response;
	static std::string OperationName();
	static std::string RequestAction();
	static xml_schema::Qname RequestType();
	static std::string ResponseAction();
	static xml_schema::Qname ResponseType();
};

struct ProbeTraits {
	typedef WS::DISCOVERY::ProbeType Request;
	typedef WS::DISCOVERY::ProbeMatchesType Response;
	typedef IDevice Dispatcher;
	static std::string OperationName();
	static std::string RequestAction();
	static std::string ResponseAction();
	static std::unique_ptr<Response> dispatch(Dispatcher & dispatcher, const Request & request);
};

struct RenewTraits {
	typedef WS::EVENTING::Renew Request;
	typedef WS::EVENTING::RenewResponse Response;
	typedef WS::EVENTING::Identifier RequestIdentifier;
	typedef ISubscriptionManager Dispatcher;
	static std::string OperationName();
	static std::string RequestAction();
	static xml_schema::Qname RequestType();
	static std::string ResponseAction();
	static xml_schema::Qname ResponseType();
	static std::unique_ptr<Response> dispatch(Dispatcher & dispatcher, const Request & request, const RequestIdentifier & identifier);
};

struct SubscribeTraits {
	typedef WS::EVENTING::Subscribe Request;
	typedef WS::EVENTING::SubscribeResponse Response;
	typedef ISubscriptionManager Dispatcher;
	static std::string OperationName();
	static std::string RequestAction();
	static xml_schema::Qname RequestType();
	static std::string ResponseAction();
	static xml_schema::Qname ResponseType();
	static std::unique_ptr<Response> dispatch(Dispatcher & dispatcher, const Request & request);
};

struct UnsubscribeTraits {
	typedef WS::EVENTING::Unsubscribe Request;
	typedef WS::EVENTING::Identifier RequestIdentifier;
	typedef MESSAGEMODEL::Body Response;
	typedef ISubscriptionManager Dispatcher;
	static std::string OperationName();
	static std::string RequestAction();
	static xml_schema::Qname RequestType();
	static std::string ResponseAction();
	static xml_schema::Qname ResponseType();
	static std::unique_ptr<Response> dispatch(Dispatcher & dispatcher, const Request & request, const RequestIdentifier & identifier);
};

} /* namespace DPWS */
} /* namespace OSELib */

#endif /* DPWS_OPERATIONTRAITS_H_ */
