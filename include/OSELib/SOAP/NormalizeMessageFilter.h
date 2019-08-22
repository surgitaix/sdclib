/*
 * NormalizeMessageFilter.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 22.08.2019, baumeister
 */

#ifndef OSELIB_SOAP_NORMALIZEMESSAGEFILTER_H_
#define OSELIB_SOAP_NORMALIZEMESSAGEFILTER_H_

#include "OSELib/fwd.h"
#include "NormalizedMessageModel.hxx"

namespace OSELib
{
	namespace SOAP
	{

	class NormalizeMessageFilter
	{
		public:
			NormalizeMessageFilter() = delete;
			static std::unique_ptr<MESSAGEMODEL::Envelope> apply(const Helper::XercesDocumentWrapper & p_msg);
		};
	}
}

#endif
