/*
 * DPWSCommon.h
 *
 *  Created on: 11.12.2015, matthias
 *  Modified on: 23.08.2019, baumeister
 *
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
extern const xml_schema::Uri streamUri;
extern const xml_schema::Uri probeMatchesUri;
extern const xml_schema::Uri resolveUri;
extern const xml_schema::Uri resolveMatchesUri;
extern const xml_schema::Uri addressingAnonymousUri;

std::unique_ptr<MESSAGEMODEL::Envelope> parseMessage(std::istream & p_stream);
const std::string serializeMessage(const MESSAGEMODEL::Envelope & p_message);

bool compare(const ProbeType & p_filter, const ProbeMatchType & p_type);
bool compare(const ResolveType & p_filter, const ResolveMatchType & p_type);

}
}
}

#endif
