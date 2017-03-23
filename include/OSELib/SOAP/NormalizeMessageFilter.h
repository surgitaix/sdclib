/*
 * NormalizeMessageFilter.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef SOAP_NORMALIZEMESSAGEFILTER_H_
#define SOAP_NORMALIZEMESSAGEFILTER_H_

#include "OSELib/fwd.h"

namespace OSELib {
namespace SOAP {

class NormalizeMessageFilter {
public:
	NormalizeMessageFilter() = delete;
	static std::unique_ptr<MESSAGEMODEL::Envelope> apply(const Helper::XercesDocumentWrapper & msg);
};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* SOAP_NORMALIZEMESSAGEFILTER_H_ */
