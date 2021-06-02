/*
 * NormalizedMessageSerializer.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#include "OSELib/SOAP/NormalizedMessageSerializer.h"
#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/SDC/SDCConstants.h"

#include "DataModel/NormalizedMessageModel.hxx"

namespace OSELib
{
	namespace SOAP
	{
		std::string NormalizedMessageSerializer::serialize(const MESSAGEMODEL::Envelope& p_message)
		{
			std::ostringstream t_result;
			xml_schema::NamespaceInfomap t_map;

			t_map["wsa"].name = SDC::NS_ADDRESSING;
			t_map["wse"].name = SDC::NS_EVENTING;
			t_map["dpws"].name = OSELib::WS_NS_DPWS;
			t_map["mm"].name = SDC::NS_MESSAGE_MODEL;

			// Important: Dont pretty print as it can sometimes falsify meaning of messages
			const xml_schema::Flags xercesFlags(xml_schema::Flags::dont_pretty_print | xml_schema::Flags::dont_validate
				| xml_schema::Flags::dont_initialize);

			//MESSAGEMODEL::serializeEnvelope(t_result, p_message, t_map, "UTF-8", xercesFlags);
			MESSAGEMODEL::serializeEnvelope(t_result, p_message, t_map, "UTF-8");
			return t_result.str();
		}

	}  // namespace SOAP
}  // namespace OSELib
