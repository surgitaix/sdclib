
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "Poco/Buffer.h"
#include "Poco/Observer.h"
#include "Poco/Thread.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/Net/SocketReactor.h"

#include <xercesc/util/PlatformUtils.hpp>

#include "ws-addressing.hxx"
#include "wsdd-discovery-1.1-schema-os.hxx"
#include "NormalizedMessageModel.hxx"

const std::string UDP_MULTICAST_IP_V4("239.255.255.250");
const std::string UDP_MULTICAST_IP_V6("FF02::C");
uint16_t UPD_MULTICAST_DISCOVERY_PORT(3702);
const std::string intendationLevel1("  ");
std::size_t lineLength(80);
const std::string separator(lineLength, '-');

class MulticastHandler {
public:
	MulticastHandler() = default;
	~MulticastHandler() = default;

	void onMulticastSocketReadable(Poco::Net::ReadableNotification * notification) {
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
		std::unique_ptr<MESSAGEMODEL::Envelope> message;
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

		if (message == nullptr) {
			const std::string printMessage("Received unknown data from " + remoteAddr.toString() + " ");
			std::cout << printMessage << std::string(lineLength - printMessage.size(), '-') << std::endl;
			std::cout << socketData << std::endl;
			std::cout << separator << std::endl << std::endl;
			return;
		}

		if (message->Body().Probe().present()) {
			const std::string printMessage("Received Probe from " + remoteAddr.toString() + " ");
			std::cout << printMessage << std::string(lineLength - printMessage.size(), '-') << std::endl;
			std::cout << "Requested types:" << std::endl << std::flush;
			if (message->Body().Probe().get().Types().present()) {
				for (const auto & type : message->Body().Probe().get().Types().get()) {
					std::cout << intendationLevel1 << type.namespace_() << ":" << type.name() << " " << std::endl << std::flush;
				}
			}
			std::cout << "Requested scopes:" << std::endl << std::flush;
			if (message->Body().Probe().get().Scopes().present()) {
				for (const auto & scope : message->Body().Probe().get().Scopes().get()) {
					std::cout << intendationLevel1 << scope << std::endl << std::flush;
				}
			}
			std::cout << separator << std::endl << std::endl;
		} else if (message->Body().Resolve().present()) {
			const std::string printMessage("Received Resolve from " + remoteAddr.toString() + " ");
			std::cout << printMessage << std::string(lineLength - printMessage.size(), '-') << std::endl;
			std::cout << "Requested EPR:" << std::endl << std::flush;
			WS::ADDRESSING::EndpointReference(std::cout, message->Body().Resolve().get().EndpointReference());
			std::cout << separator << std::endl << std::endl;
		} else 	if (message->Body().Hello().present()) {
			const std::string printMessage("Received Hello from " + remoteAddr.toString() + " ");
			std::cout << printMessage << std::string(lineLength - printMessage.size(), '-') << std::endl;
			WS::DISCOVERY::Hello(std::cout, message->Body().Hello().get());
			std::cout << separator << std::endl << std::endl;
		} else 	if (message->Body().Bye().present()) {
			const std::string printMessage("Received Bye from " + remoteAddr.toString() + " ");
			std::cout << printMessage << std::string(lineLength - printMessage.size(), '-') << std::endl;
			WS::DISCOVERY::Bye(std::cout, message->Body().Bye().get());
			std::cout << separator << std::endl << std::endl;
		} else {
			const std::string printMessage("Received unknown data from " + remoteAddr.toString() + " ");
			std::cout << printMessage << std::string(lineLength - printMessage.size(), '-') << std::endl;
			std::cout << socketData << std::endl;
			std::cout << separator << std::endl << std::endl;
		}
	}
};

int main() {
	xercesc::XMLPlatformUtils::Initialize ();
	std::cout << "Listening for DPWS discovery messages ..." << std::endl;

	Poco::Net::SocketAddress ipv4MulticastAddress(UDP_MULTICAST_IP_V4, UPD_MULTICAST_DISCOVERY_PORT);
	Poco::Net::SocketAddress ipv4BindingAddress(Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv4), ipv4MulticastAddress.port());
	Poco::Net::MulticastSocket ipv4Socket(ipv4BindingAddress.family());
	std::cout << "Binding ipv4 address " << ipv4BindingAddress.host().toString() << std::endl;
	ipv4Socket.bind(ipv4BindingAddress, true);
	std::cout << "Joining ipv4 group " << ipv4MulticastAddress.host().toString() << std::endl;
	ipv4Socket.joinGroup(ipv4MulticastAddress.host());
	ipv4Socket.setBlocking(false);

	Poco::Net::SocketAddress ipv6MulticastAddress(UDP_MULTICAST_IP_V6, UPD_MULTICAST_DISCOVERY_PORT);
	Poco::Net::SocketAddress ipv6BindingAddress(Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv6), ipv4MulticastAddress.port());
	Poco::Net::MulticastSocket ipv6Socket(ipv6MulticastAddress.family());
	std::cout << "Binding ipv6 address " << ipv6BindingAddress.host().toString() << std::endl;
	ipv6Socket.bind(Poco::Net::SocketAddress(Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv6), ipv6MulticastAddress.port()), true);
	std::cout << "Joining ipv6 group " << ipv6MulticastAddress.host().toString() << std::endl;
	ipv6Socket.joinGroup(ipv6MulticastAddress.host());
	ipv6Socket.setBlocking(false);

	MulticastHandler multicastHandler;

	Poco::Net::SocketReactor reactor;
	reactor.addEventHandler(ipv4Socket, Poco::Observer<MulticastHandler, Poco::Net::ReadableNotification>(multicastHandler, &MulticastHandler::onMulticastSocketReadable));
	reactor.addEventHandler(ipv6Socket, Poco::Observer<MulticastHandler, Poco::Net::ReadableNotification>(multicastHandler, &MulticastHandler::onMulticastSocketReadable));

	Poco::Thread reactorThread;
	reactorThread.start(reactor);

	char tmp(0);
	std::cin >> tmp;

	reactor.removeEventHandler(ipv4Socket, Poco::Observer<MulticastHandler, Poco::Net::ReadableNotification>(multicastHandler, &MulticastHandler::onMulticastSocketReadable));
	reactor.removeEventHandler(ipv6Socket, Poco::Observer<MulticastHandler, Poco::Net::ReadableNotification>(multicastHandler, &MulticastHandler::onMulticastSocketReadable));
	reactor.stop();
	reactorThread.join();

	xercesc::XMLPlatformUtils::Terminate ();
}
