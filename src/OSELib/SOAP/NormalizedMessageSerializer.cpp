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

#include "NormalizedMessageModel.hxx"

namespace OSELib {
namespace SOAP {

std::string NormalizedMessageSerializer::serialize(const MESSAGEMODEL::Envelope & p_message) {

	std::ostringstream t_result;
	xml_schema::NamespaceInfomap t_map;

	t_map["wsa"].name = SDC::NS_ADDRESSING;
	t_map["wse"].name = SDC::NS_EVENTING;
	t_map["dpws"].name = OSELib::WS_NS_DPWS;
	t_map["mm"].name = SDC::NS_MESSAGE_MODEL;

	// todo make dpws device metadata localizable. Currently the schema does not support it
	/**Background and idea:
	 * I did not find a way to make xsd understand the xml:lang attribute. This should be tried again.
	 * This means that i.e. DPWS Friendly Name is not localizable with different languages.
	 */

	MESSAGEMODEL::Envelope_(t_result, p_message, t_map, "UTF-8");
	return t_result.str();
}

}
}
