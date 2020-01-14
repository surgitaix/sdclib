/*
 * GenericSoapEventCommand.h
 *
 *  Created on: 10.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SOAP_GENERICSOAPEVENTCOMMAND_H_
#define OSELIB_SOAP_GENERICSOAPEVENTCOMMAND_H_

#include "OSELib/SOAP/SoapActionCommand.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"

namespace OSELib
{
	namespace SOAP
	{
		template<class TraitsType>
		class GenericSoapEventCommand : public SoapActionCommand
		{
		protected:
			typename TraitsType::Dispatcher & m_dispatcher;

		public:
			GenericSoapEventCommand(std::unique_ptr<MESSAGEMODEL::Envelope> p_requestMessage, typename TraitsType::Dispatcher & p_dispatcher)
			: SoapActionCommand(std::move(p_requestMessage))
			, m_dispatcher(p_dispatcher)
			{ }
			// Special Member Functions
			GenericSoapEventCommand(const GenericSoapEventCommand& p_obj) = default;
			GenericSoapEventCommand(GenericSoapEventCommand&& p_obj) = default;
			GenericSoapEventCommand& operator=(const GenericSoapEventCommand& p_obj) = default;
			GenericSoapEventCommand& operator=(GenericSoapEventCommand&& p_obj) = default;
			virtual ~GenericSoapEventCommand() = default;

		protected:

			std::unique_ptr<MESSAGEMODEL::Envelope> checkDispatchPreconditions(std::unique_ptr<MESSAGEMODEL::Envelope> p_request) override
			{
				NormalizedMessageAdapter<typename TraitsType::ReportType> t_requestAdapter;
				if (!t_requestAdapter.present(*p_request)) {
					throw SoapActionCommand::MissingRequestBody("Request body missing for " + TraitsType::Action());
				}
				return p_request;
			}

			std::unique_ptr<MESSAGEMODEL::Envelope> dispatch(const MESSAGEMODEL::Envelope & p_request) override
			{
				NormalizedMessageAdapter<typename TraitsType::ReportType> t_requestAdapter;
				const typename TraitsType::ReportType & requestBody(t_requestAdapter.get(p_request));
				dispatchDelegate(requestBody);
				return nullptr;
			}

			virtual void dispatchDelegate(const typename TraitsType::ReportType & p_requestBody)
			{
				TraitsType::dispatch(m_dispatcher, p_requestBody);
			}
		};
	}
}

#endif
