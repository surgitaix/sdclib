/*
 * fwd.h
 *
 *  Created on: 18.11.2015, matthias
 *  Modified on: 26.09.2019, baumeister
 *
 */

#ifndef OSELIB_FWD_H_
#define OSELIB_FWD_H_

#include "DataModel/BICEPS_ParticipantModel-fwd.hxx"
#include "DataModel/BICEPS_MessageModel-fwd.hxx"
#include "DataModel/eventing-fwd.hxx"
#include "DataModel/MetadataExchange-fwd.hxx"
#include "DataModel/NormalizedMessageModel-fwd.hxx"

namespace Poco
{
    namespace Net
    {
        class HTTPRequestHandler;
        class HTTPRequestHandlerFactory;
        class HTTPServer;
        class HTTPServerRequest;
        class HTTPServerResponse;
        class MulticastSocket;
        class HTTPSClientSession;
        class TimeoutNotification;
        class WritableNotification;
        class ReadableNotification;
    }  // namespace Net
    class Logger;
    class NotificationQueue;
    class URI;
    class ThreadPool;
    class Timespan;
    class Timestamp;
}  // namespace Poco

namespace OSELib
{
    namespace DPWS
    {
        class ActiveSubscriptions;
        class DeviceDescription;
        using DeviceDescription_shared_ptr = std::shared_ptr<DeviceDescription>;
        class DeviceHandler;
        class DeviceServiceController;
        class IDevice;
        class IEventSink;
        class IService;
        class ISubscriptionManager;
        class MDPWSDiscoveryClientAdapter;
        class MDPWSHostAdapter;
        struct MessageAdapter;
        class MessagingContext;
        class MetadataProvider;
        class PingManager;
        class SubscriptionClient;
        class SubscriptionManager;

        struct HelloCallback;

        namespace Impl
        {
            class DPWSDiscoveryClientSocketImpl;
            class DPWSHostSocketImpl;
            class MDPWSStreamingAdapter;
        }  // namespace Impl
    }      // namespace DPWS

    namespace Helper
    {
        template<class T>
        struct AutoRelease;
        class BufferAdapter;
        class DurationWrapper;
        class Message;
        class SchemaGrammarProvider;
        class StreamReader;
        class WithLogger;
        class XercesDocumentWrapper;
        class XercesGrammarPoolProvider;
        class XercesParserWrapper;
        class XercesUniqueElementByTagNameFilter;

        using EmptyXercesGrammarPoolProvider = XercesGrammarPoolProvider;
    }  // namespace Helper

    namespace HTTP
    {
        class FrontController;
        class FrontControllerAdapter;
        class HTTPServer;
        class HTTPRequestHandlerFactory;
        using HTTPRequestHandlerFactory_shared_ptr = std::shared_ptr<HTTPRequestHandlerFactory>;
        class HTTPClientExchanger;
        class HTTPSessionManager;
        class Service;
        class StaticContentController;
    }  // namespace HTTP

    namespace SDC
    {
        class ContextEventSinkHandler;
        class DefaultSDCSchemaGrammarProvider;
        class GetServiceHandler;
        class IContextService;
        class IContextServiceEventSink;
        class IEventReport;
        class IGetService;
        class ISetService;
        class IBICEPSService;
        class IBICEPSServiceEventSink;
        class BICEPSServiceHandler;
        class BICEPSServiceEventSinkHandler;
        class ISetServiceEventSink;
        class IDescriptionEventServiceEventSink;
        class IStateEventServiceEventSink;
        class IWaveformService;
        template<class T1, class T2>
        class SDCEventServiceController;
        template<class T1, class T2>
        class SDCServiceController;
        class ServiceManager;
        class SetServiceEventSingHandler;
        class SetServiceHandler;
        class StateEventServiceEventSinkHandler;
    }  // namespace SDC

    namespace SOAP
    {
        class Command;
        class CommandSoapProcessing;
        template<class T>
        class GenericSoapActionCommand;
        template<class T>
        class GenericSoapEventCommand;
        template<class T>
        class GenericSoapInvoke;
        class GetActionCommand;
        class GetMetadataActionCommand;
        class GetStatusActionCommand;
        class HTTPRequestHandlerExceptionTrap;
        class NormalizedMessageSerializer;
        class NormalizeMessageFilter;
        class RenewActionCommand;
        class SoapActionCommand;
        class SoapFaultCommand;
        class SoapHTTPResponseWrapper;
        class SoapInvoke;
        class SubscribeActionCommand;
        class UnsubscribeActionCommand;
    }  // namespace SOAP

    namespace WSDL
    {
        class WSDLLoader;
    }
}  // namespace OSELib

#endif
