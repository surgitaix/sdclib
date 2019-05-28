/*
 * fwd.h
 *
 *  Created on: 18.11.2015
 *      Author: matthias
 */

#ifndef OSELIB_FWD_H_
#define OSELIB_FWD_H_

#include "BICEPS_ParticipantModel-fwd.hxx"
#include "BICEPS_MessageModel-fwd.hxx"
#include "eventing-fwd.hxx"
#include "MetadataExchange-fwd.hxx"
#include "NormalizedMessageModel-fwd.hxx"


namespace Poco {
	namespace Net {
		class HTTPClientSession;
		class HTTPRequestHandler;
		class HTTPServer;
		class HTTPServerRequest;
		class MulticastSocket;
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
			class DPWSHostSocketImpl;
		}

		class ActiveSubscriptions;

		class MDPWSDiscoveryClientAdapter;
		class MDPWSHostAdapter;

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

	namespace SDC {
		class IContextService;
		class IContextServiceEventSink;
		class IEventReport;
		class IStateEventServiceEventSink;
		class ISetServiceEventSink;
		class IGetService;
		class ISetService;
		class IWaveformService;
	}
}

#endif /* OSELIB_FWD_H_ */
