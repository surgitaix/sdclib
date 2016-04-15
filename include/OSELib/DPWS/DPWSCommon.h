/*
 * DPWSCommon.h
 *
 *  Created on: 11.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_DPWS_DPWSCOMMON_H_
#define OSELIB_DPWS_DPWSCOMMON_H_

#include "NormalizedMessageModel-fwd.hxx"

#include "OSELib/DPWS/Types.h"

namespace OSELib {
namespace DPWS {
namespace Impl {

extern const xml_schema::Uri discoveryUri;
extern const xml_schema::Uri byeUri;
extern const xml_schema::Uri helloUri;
extern const xml_schema::Uri probeUri;
extern const xml_schema::Uri probeMatchesUri;
extern const xml_schema::Uri resolveUri;
extern const xml_schema::Uri resolveMatchesUri;
extern const xml_schema::Uri addressingAnonymousUri;

std::unique_ptr<MESSAGEMODEL::Envelope> parseMessage(std::istream & stream);
const std::string serializeMessage(const MESSAGEMODEL::Envelope & message);

bool compare(const ProbeType & filter, const ProbeMatchType & n);
bool compare(const ResolveType & filter, const ResolveMatchType & n);

} /* namespace Impl */
} /* namespace DPWS */
} /* namespace OSELib */

#endif /* OSELIB_DPWS_DPWSCOMMON_H_ */
