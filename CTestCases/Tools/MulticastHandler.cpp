/*
 * MulticastHandler.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: rosenau
 */

#include "MulticastHandler.h"

namespace TestTools {

MulticastHandler::MulticastHandler() {
	// TODO Auto-generated constructor stub

}

MulticastHandler::~MulticastHandler() {
	// TODO Auto-generated destructor stub
}

void MulticastHandler::onProbeMessageReceived(messagedata_t messagedata) {
	const std::string printMessage("Received Probe from " + messagedata.remoteAddr.toString() + " ");
	std::cout << printMessage << std::string(lineLength - printMessage.size(), '-') << std::endl;
	std::cout << "Requested types:" << std::endl << std::flush;
	if (messagedata.message->Body().Probe().get().Types().present()) {
		for (const auto & type : messagedata.message->Body().Probe().get().Types().get()) {
			std::cout << intendationLevel1 << type.namespace_() << ":" << type.name() << " " << std::endl << std::flush;
		}
	}
	std::cout << "Requested scopes:" << std::endl << std::flush;
	if (messagedata.message->Body().Probe().get().Scopes().present()) {
		for (const auto & scope : messagedata.message->Body().Probe().get().Scopes().get()) {
			std::cout << intendationLevel1 << scope << std::endl << std::flush;
		}
	}
	std::cout << separator << std::endl << std::endl;
}

void MulticastHandler::onResolveMessageReceived(messagedata_t messagedata) {
	const std::string printMessage("Received Resolve from " + messagedata.remoteAddr.toString() + " ");
	std::cout << printMessage << std::string(lineLength - printMessage.size(), '-') << std::endl;
	std::cout << "Requested EPR:" << std::endl << std::flush;
	WS::ADDRESSING::EndpointReference(std::cout, messagedata.message->Body().Resolve().get().EndpointReference());
	std::cout << separator << std::endl << std::endl;
}

void MulticastHandler::onByeMessageReceived(messagedata_t messagedata) {
	const std::string printMessage("Received Bye from " + messagedata.remoteAddr.toString() + " ");
	std::cout << printMessage << std::string(lineLength - printMessage.size(), '-') << std::endl;
	WS::DISCOVERY::Bye(std::cout, messagedata.message->Body().Bye().get());
	std::cout << separator << std::endl << std::endl;
}

void MulticastHandler::onUnknownDataReceived(messagedata_t messagedata) {
	const std::string printMessage("Received unknown data from " + messagedata.remoteAddr.toString() + " ");
	std::cout << printMessage << std::string(lineLength - printMessage.size(), '-') << std::endl;
	std::cout << messagedata.socketData << std::endl;
	std::cout << separator << std::endl << std::endl;
	return;
}

void MulticastHandler::onHelloMessageReceived(messagedata_t messagedata) {
	const std::string printMessage("Received Hello from " + messagedata.remoteAddr.toString() + " ");
	std::cout << printMessage << std::string(lineLength - printMessage.size(), '-') << std::endl;
	WS::DISCOVERY::Hello(std::cout, messagedata.message->Body().Hello().get());
	std::cout << separator << std::endl << std::endl;
}

void MulticastHandler::onMulticastSocketReadable(Poco::Net::ReadableNotification * notification) {
		const Poco::AutoPtr<Poco::Net::ReadableNotification> pNf(notification);
		Poco::Net::MulticastSocket socket(pNf->socket());
		const int available(socket.available());
		if (available == 0) {
			return;
		}

		Poco::Buffer<char> buf(available);
		Poco::Net::SocketAddress remoteAddr;
		const int received(socket.receiveFrom(buf.begin(), available, remoteAddr, 0));

		const std::string socketData(buf.begin(), received);

		std::istringstream stream(socketData);
		std::shared_ptr<MESSAGEMODEL::Envelope> message;
		try {
			message = MESSAGEMODEL::Envelope_(stream, ::xml_schema::Flags::no_xml_declaration | ::xml_schema::Flags::dont_validate | ::xml_schema::Flags::dont_initialize);
		} catch (const xml_schema::Exception& e) {
			std::cout << "Parsing failed with error: " << e << std::endl;
		} catch (const xml_schema::Properties::argument&) {
			std::cout << "Parsing failed with error: Invalid property argument (empty namespace or location)" << std::endl;
		} catch (const xsd::cxx::xml::invalid_utf16_string&) {
			std::cout << "Parsing failed with error: Invalid UTF-16 text in DOM model" << std::endl;
		} catch (const xsd::cxx::xml::invalid_utf8_string&) {
			std::cout << "Parsing failed with error: Invalid UTF-8 text in object model" << std::endl;
		} catch (...) {
			std::cout << "Parsing failed with unknown error." << std::endl;
		}

		messagedata_t receivedMessageData;
		receivedMessageData.message = message;
		receivedMessageData.socketData = socketData;
		receivedMessageData.remoteAddr = remoteAddr;

		if (message == nullptr) {
			onUnknownDataReceived(receivedMessageData);
		}

		if (message->Body().Probe().present()) {
			onProbeMessageReceived(receivedMessageData);
		} else if (message->Body().Resolve().present()) {
			onResolveMessageReceived(receivedMessageData);
		} else 	if (message->Body().Hello().present()) {
			onHelloMessageReceived(receivedMessageData);
		} else 	if (message->Body().Bye().present()) {
			onByeMessageReceived(receivedMessageData);
		} else {
			onUnknownDataReceived(receivedMessageData);
		}
}

} /* namespace TestTools */
