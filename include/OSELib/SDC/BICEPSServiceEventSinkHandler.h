/*
 * BICEPSServiceEventSinkHandler.h
 *
 *  Created on: 26.09.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_BICEPSSERVICEEVENTSINKHANDLER_H_
#define OSELIB_SDC_BICEPSSERVICEEVENTSINKHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib
{
	namespace SDC
	{
		class BICEPSServiceEventSinkHandler : public SOAP::HTTPRequestHandlerExceptionTrap
		{
		private:
			IBICEPSServiceEventSink & m_service;
			Helper::XercesGrammarPoolProvider & m_grammarProvider;

		public:
			BICEPSServiceEventSinkHandler(IBICEPSServiceEventSink & service, Helper::XercesGrammarPoolProvider & grammarProvider);
			// Special Member Functions
			BICEPSServiceEventSinkHandler(const BICEPSServiceEventSinkHandler& p_obj) = delete;
			BICEPSServiceEventSinkHandler(BICEPSServiceEventSinkHandler&& p_obj) = delete;
			BICEPSServiceEventSinkHandler& operator=(const BICEPSServiceEventSinkHandler& p_obj) = delete;
			BICEPSServiceEventSinkHandler& operator=(BICEPSServiceEventSinkHandler&& p_obj) = delete;
			~BICEPSServiceEventSinkHandler() = default;

		private:

			virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse);

		};
	}
}

#endif
