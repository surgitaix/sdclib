/*
 * NormalizedMessageSerializer.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include <OSELib/SDC/SDCConstants.h>
#include "NormalizedMessageModel.hxx"

#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/SOAP/NormalizedMessageSerializer.h"
#include "OSELib/TCP/TCPClientEventHandler.h"
#include <mutex>
#include "chrono"

//Network::TCPClientEventHandler* Network::TCPClientEventHandler::instance = NULL;

namespace OSELib {
namespace SOAP {

std::mutex NormalizedMessageSerializer::_mtx;

std::string NormalizedMessageSerializer::serialize(const MESSAGEMODEL::Envelope & message) {

	std::ostringstream result;
	xml_schema::NamespaceInfomap map;

	map["wsa"].name = SDC::NS_ADDRESSING;
	map["wse"].name = SDC::NS_EVENTING;
	map["dpws"].name = OSELib::WS_NS_DPWS;
	map["mm"].name = SDC::NS_MESSAGE_MODEL;

	// todo make dpws device metadata localizable. Currently the schema does not support it
	/**Background and idea:
	 * I did not find a way to make xsd understand the xml:lang attribute. This should be tried again.
	 * This means that i.e. DPWS Friendly Name is not localizable with different languages.
	 */

	MESSAGEMODEL::Envelope_(result, message, map, "UTF-8");

	#ifdef MESSAGEMANIPULATION
		return manipulateMessage(result.str());
	#endif

	return result.str();
}

std::string NormalizedMessageSerializer::manipulateMessage(const std::string& originalMessage)
{
	std::lock_guard<std::mutex> l(_mtx);

	if(Network::TCPClientEventHandler::getInstance("127.0.0.1", 5000)->isConnected())
	{
		std::cout << "OUTGOING \n" << originalMessage << std::endl;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		Network::TCPClientEventHandler::getInstance("127.0.0.1", 5000)->sendRequest(originalMessage);
		while(!Network::TCPClientEventHandler::getInstance("127.0.0.1", 5000)->responseReceived())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		std::string manipulatedMessage = Network::TCPClientEventHandler::getInstance("127.0.0.1", 5000)->getResponse();

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout << "INCOMING after " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;
		std::cout << manipulatedMessage << std::endl;

		return manipulatedMessage;
	}
	return originalMessage;
}


} /* namespace SOAP */
} /* namespace OSELib */
