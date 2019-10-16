/*
 * GetMetadataActionCommand.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SOAP_GETMETADATAACTIONCOMMAND_H_
#define OSELIB_SOAP_GETMETADATAACTIONCOMMAND_H_

#include "OSELib/SOAP/SoapActionCommand.h"

namespace OSELib
{
	namespace SOAP
	{
		class GetMetadataActionCommand : public SoapActionCommand
		{
		private:
			std::unique_ptr<WS::MEX::Metadata> m_metadata = nullptr;
		public:
			GetMetadataActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> p_requestMessage, const WS::MEX::Metadata & p_metadata);
			// Special Member Functions
			GetMetadataActionCommand(const GetMetadataActionCommand& p_obj) = default;
			GetMetadataActionCommand(GetMetadataActionCommand&& p_obj) = default;
			GetMetadataActionCommand& operator=(const GetMetadataActionCommand& p_obj) = default;
			GetMetadataActionCommand& operator=(GetMetadataActionCommand&& p_obj) = default;
			virtual ~GetMetadataActionCommand() = default;

			std::unique_ptr<MESSAGEMODEL::Envelope> dispatch(const MESSAGEMODEL::Envelope & p_request) override;
			std::unique_ptr<MESSAGEMODEL::Envelope> checkDispatchPreconditions(std::unique_ptr<MESSAGEMODEL::Envelope> p_request) override;
		};
	}
}

#endif
