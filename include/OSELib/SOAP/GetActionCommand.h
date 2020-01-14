/*
 * GetActionCommand.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SOAP_GETACTIONCOMMAND_H_
#define OSELIB_SOAP_GETACTIONCOMMAND_H_

#include "OSELib/SOAP/SoapActionCommand.h"

namespace OSELib
{
	namespace SOAP
	{

		class GetActionCommand : public SoapActionCommand
		{
		private:
			std::unique_ptr<WS::MEX::Metadata> m_metadata = nullptr;
		public:
			GetActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> p_requestMessage, const WS::MEX::Metadata & p_metadata);
			// Special Member Functions
			GetActionCommand(const GetActionCommand& p_obj) = default;
			GetActionCommand(GetActionCommand&& p_obj) = default;
			GetActionCommand& operator=(const GetActionCommand& p_obj) = default;
			GetActionCommand& operator=(GetActionCommand&& p_obj) = default;
			virtual ~GetActionCommand() = default;

			std::unique_ptr<MESSAGEMODEL::Envelope> dispatch(const MESSAGEMODEL::Envelope & p_request) override;
		};
	}
}

#endif
