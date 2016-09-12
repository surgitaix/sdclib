/*
 * fwd.h
 *
 *  Created on: 18.11.2015
 *      Author: matthias
 */

#ifndef OSELIB_FWD_H_
#define OSELIB_FWD_H_

#include "BICEPS_DomainModel-fwd.hxx"
#include "BICEPS_MessageModel-fwd.hxx"
#include "ExtensionPoint-fwd.hxx"
#include "eventing-fwd.hxx"
#include "MetadataExchange-fwd.hxx"
#include "NormalizedMessageModel-fwd.hxx"
#include "ws-addressing-fwd.hxx"
#include "wsdd-discovery-1.1-schema-os-fwd.hxx"
#include "wsdd-dpws-1.1-schema-os-fwd.hxx"
#include "wsdl-custom-fwd.hxx"
#include "wsdl-soap-binding-fwd.hxx"
#include "MDPWS-fwd.hxx"

namespace Poco {
	namespace Net {
		class HTTPClientSession;
		class HTTPRequestHandler;
		class HTTPServer;
		class HTTPServerRequest;
	}
	class Logger;
	class NotificationQueue;
	class URI;
	class ThreadPool;
	class Timespan;
	class Timestamp;
}

namespace OSELib {
	namespace DPWS {
		namespace Impl {
			class DPWSDiscoveryClientSocketImpl;
			class DPWSDiscoveryHostSocketImpl;
		}

		class ActiveSubscriptions;

		class DPWSClient;
		class DPWSHost;

		struct HelloCallback;

		class IDevice;
		class ISubscriptionManager;

		class PingManager;
		class SubscriptionClient;
		class SubscriptionManager;
	}

	namespace Helper {
		template<class T>
		struct AutoRelease;
		class Message;
		class XercesDocumentWrapper;
		class XercesGrammarPoolProvider;
		class XercesUniqueElementByTagNameFilter;

		using EmptyXercesGrammarPoolProvider = XercesGrammarPoolProvider;
	}

	namespace HTTP {
		class FrontController;
		class FrontControllerAdapter;
		class HTTPSessionManager;
		class Service;
	}

	namespace OSCP {
		class IContextService;
		class IContextServiceEventSink;
		class IEventReport;
		class IEventReportEventSink;
		class IGetService;
		class ISetService;
	}
}

#endif /* OSELIB_FWD_H_ */
