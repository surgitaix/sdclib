/*
 * OperationTraits.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 01.09.2020, baumeister
 *
 */

#ifndef OSELIB_DPWS_OPERATIONTRAITS_H_
#define OSELIB_DPWS_OPERATIONTRAITS_H_

#include "OSELib/fwd.h"

namespace OSELib
{
    namespace DPWS
    {
        struct GetTraits
        {
            typedef MESSAGEMODEL::Body Request;
            typedef WS::MEX::Metadata Response;
            static std::string OperationName();
            static std::string RequestAction();
            static std::string ResponseAction();
            static xml_schema::Qname ResponseType();
        };

        struct GetMetadataTraits
        {
            typedef WS::MEX::GetMetadata Request;
            typedef WS::MEX::Metadata Response;
            static std::string OperationName();
            static std::string RequestAction();
            static xml_schema::Qname RequestType();
            static std::string ResponseAction();
            static xml_schema::Qname ResponseType();
        };

        struct ProbeTraits
        {
            typedef WS::DISCOVERY::ProbeType Request;
            typedef WS::DISCOVERY::ProbeMatchesType Response;
            typedef IDevice Dispatcher;
            static std::string OperationName();
            static std::string RequestAction();
            static std::string ResponseAction();
            static std::unique_ptr<Response> dispatch(Dispatcher& p_dispatcher, const Request& p_request);
        };


        struct SubscribeTraits
        {
            typedef WS::EVENTING::Subscribe Request;
            typedef WS::EVENTING::SubscribeResponse Response;
            typedef ISubscriptionManager Dispatcher;
            static std::string OperationName();
            static std::string RequestAction();
            static xml_schema::Qname RequestType();
            static std::string ResponseAction();
            static xml_schema::Qname ResponseType();
            static std::unique_ptr<Response> dispatch(Dispatcher& p_dispatcher, const Request& p_request);
        };

        struct RenewTraits
        {
            typedef WS::EVENTING::Renew Request;
            typedef WS::EVENTING::RenewResponse Response;
            typedef WS::EVENTING::Identifier RequestIdentifier;
            typedef ISubscriptionManager Dispatcher;
            static std::string OperationName();
            static std::string RequestAction();
            static xml_schema::Qname RequestType();
            static std::string ResponseAction();
            static xml_schema::Qname ResponseType();
            static std::unique_ptr<Response>
                dispatch(Dispatcher& p_dispatcher, const Request& p_request, const RequestIdentifier& p_identifier);
        };

        struct GetStatusTraits
        {
            typedef WS::EVENTING::GetStatus Request;
            typedef WS::EVENTING::GetStatusResponse Response;
            typedef WS::EVENTING::Identifier RequestIdentifier;
            typedef ISubscriptionManager Dispatcher;
            static std::string OperationName();
            static std::string RequestAction();
            static xml_schema::Qname RequestType();
            static std::string ResponseAction();
            static xml_schema::Qname ResponseType();
            static std::unique_ptr<Response>
                dispatch(Dispatcher& p_dispatcher, const Request& p_request, const RequestIdentifier& p_identifier);
        };

        struct UnsubscribeTraits
        {
            typedef WS::EVENTING::Unsubscribe Request;
            typedef WS::EVENTING::Identifier RequestIdentifier;
            typedef MESSAGEMODEL::Body Response;
            typedef ISubscriptionManager Dispatcher;
            static std::string OperationName();
            static std::string RequestAction();
            static xml_schema::Qname RequestType();
            static std::string ResponseAction();
            static xml_schema::Qname ResponseType();
            static std::unique_ptr<Response>
                dispatch(Dispatcher& p_dispatcher, const Request& p_request, const RequestIdentifier& p_identifier);
        };

        struct SubscriptionEndTraits
        {
            typedef WS::EVENTING::SubscriptionEnd ReportType;
            typedef WS::EVENTING::Identifier RequestIdentifier;
            static xml_schema::Qname MessageType();
            static std::string NotificationName();
            static std::string Action();
        };


    }  // namespace DPWS
}  // namespace OSELib

#endif
