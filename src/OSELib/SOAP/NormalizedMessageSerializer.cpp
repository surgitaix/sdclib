/*
 * NormalizedMessageSerializer.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include <OSELib/OSCP/SDCConstants.h>
#include "NormalizedMessageModel.hxx"

#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/SOAP/NormalizedMessageSerializer.h"

namespace OSELib {
namespace SOAP {

std::string NormalizedMessageSerializer::serialize(const MESSAGEMODEL::Envelope & message) {

	std::ostringstream result;
	xml_schema::NamespaceInfomap map;

	map["wsa"].name = SDC::NS_ADDRESSING;
	map["dpws"].name = OSELib::WS_NS_DPWS;
	map["mm"].name = SDC::NS_MESSAGE_MODEL;

	// todo make dpws device metadata localizable. Currently the schema does not support it
	/**Background and idea:
	 * I did not find a way to make xsd understand the xml:lang attribute. This should be tried again.
	 * This means that i.e. DPWS Friendly Name is not localizable with different languages.
	 */

	MESSAGEMODEL::Envelope_(result, message, map, "UTF-8");
	return result.str();
}

} /* namespace SOAP */
} /* namespace OSELib */
