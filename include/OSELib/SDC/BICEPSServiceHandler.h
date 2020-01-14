/*
 * BICEPSServiceHandler.h
 *
 *  Created on: 20.09.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_BICEPSSERVICEHANDLER_H_
#define OSELIB_SDC_BICEPSSERVICEHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib
{
	namespace SDC
	{
		class BICEPSServiceHandler : public SOAP::HTTPRequestHandlerExceptionTrap
		{
		private:
			IBICEPSService & m_service;
			Helper::XercesGrammarPoolProvider & m_grammarProvider;
			const bool m_SSL = true;
		public:
			BICEPSServiceHandler(IBICEPSService & p_service, Helper::XercesGrammarPoolProvider & p_grammarProvider, bool p_SSL);
			// Special Member Functions
			BICEPSServiceHandler(const BICEPSServiceHandler& p_obj) = delete;
			BICEPSServiceHandler(BICEPSServiceHandler&& p_obj) = delete;
			BICEPSServiceHandler& operator=(const BICEPSServiceHandler& p_obj) = delete;
			BICEPSServiceHandler& operator=(BICEPSServiceHandler&& p_obj) = delete;
			~BICEPSServiceHandler() = default;

		private:
			void handleRequestImpl(Poco::Net::HTTPServerRequest & p_httpRequest, Poco::Net::HTTPServerResponse & p_httpResponse);

		};
	}
}

#endif
