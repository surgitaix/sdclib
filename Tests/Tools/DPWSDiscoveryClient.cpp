#include <algorithm>
#include <chrono>
#include <deque>
#include <iostream>
#include <memory>
#include <mutex>
#include <random>
#include <string>
#include <tuple>

#include "Poco/Buffer.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/NotificationQueue.h"
#include "Poco/Observer.h"
#include "Poco/Thread.h"
#include "Poco/Timestamp.h"
#include "Poco/TimedNotificationQueue.h"
#include "Poco/UnbufferedStreamBuf.h"
#include "Poco/UUIDGenerator.h"

#include <xercesc/util/PlatformUtils.hpp>

#include "ws-addressing.hxx"
#include "wsdd-discovery-1.1-schema-os.hxx"

#include "OSELib/DPWS/DPWSClient.h"
#include "OSELib/DPWS/DPWSHost.h"
#include "OSELib/DPWS/MessageAdapter.h"

/* Example usage of Discovery host.
	Host host(AddressType("UDI_123456"));
	XAddressesType dummyAddresses;
	dummyAddresses.push_back(AddressType("http://some.server:1234"));
	host.setXAddresses(dummyAddresses);
	host.start();

	host.stop();
 */

template<class MessageType>
void dump(std::ostream & stream, const MessageType & n) {
	using Get = OSELib::DPWS::MessageAdapter;
	stream << "  EPR: " << Get::EPRAddress(n) << std::endl;
	stream << "  Metadata version: " << Get::MetadataVersion(n) << std::endl;
	stream << "  XAddresses: " << std::endl;
	for (const auto & xaddr : Get::XAddresses(n)) {
		stream << "    " << xaddr << std::endl;
	}
	stream << "  Types: " << std::endl;
	for (const auto & type : Get::Types(n)) {
		stream << "    " << Get::URI(type) << ":"  << Get::LocalName(type) << std::endl;
	}
	stream << "  Scopes: " << std::endl;
	for (const auto & scope : Get::Scopes(n)) {
		stream << "    " << scope << std::endl;
	}
}

template<>
void dump(std::ostream & stream, const OSELib::DPWS::ByeType & n) {
	using Get = OSELib::DPWS::MessageAdapter;
	stream << "  EPR: " << Get::EPRAddress(n) << std::endl;
	stream << "  XAddresses: " << std::endl;
	for (const auto & xaddr : Get::XAddresses(n)) {
		stream << "    " << xaddr << std::endl;
	}
	stream << "  Types: " << std::endl;
	for (const auto & type : Get::Types(n)) {
		stream << "    " << Get::URI(type) << ":"  << Get::LocalName(type) << std::endl;
	}
	stream << "  Scopes: " << std::endl;
	for (const auto & scope : Get::Scopes(n)) {
		stream << "    " << scope << std::endl;
	}
}

std::ostream & operator<<(std::ostream & stream, const OSELib::DPWS::ProbeMatchType & n) {
	stream << "ProbeMatch Notification" << std::endl;
	dump(stream, n);
	return stream;
}

std::ostream & operator<<(std::ostream & stream, const OSELib::DPWS::ResolveMatchType & n) {
	stream << "ResolveMatch Notification" << std::endl;
	dump(stream, n);
	return stream;
}

std::ostream & operator<<(std::ostream & stream, const OSELib::DPWS::ByeType & n) {
	stream << "Bye Notification" << std::endl;
	dump(stream, n);
	return stream;
}

std::ostream & operator<<(std::ostream & stream, const OSELib::DPWS::HelloType & n) {
	stream << "Hello Notification" << std::endl;
	dump(stream, n);
	return stream;
}

int main() {

	xercesc::XMLPlatformUtils::Initialize();

	using Client = OSELib::DPWS::MDPWSClientAdapter;
	using Host = OSELib::DPWS::MDPWSHostAdapter;
	using namespace OSELib;

	struct ProbeMatchCallback : public DPWS::ProbeMatchCallback  {
		ProbeMatchCallback(Poco::Timestamp & time) : _time(time) {}
		virtual ~ProbeMatchCallback() = default;

		virtual void probeMatch(const DPWS::ProbeMatchType & n) override {
			std::cout << "Response after " << Poco::DateTimeFormatter::format(Poco::Timespan(_time.elapsed()), "%s:%i") << " s:ms." << std::endl;
			std::cout << n << std::endl;
		}

		Poco::Timestamp & _time;
	};

	struct ByeCallback : public DPWS::ByeCallback {
		ByeCallback() {}
		virtual ~ByeCallback() = default;

		virtual void bye(const OSELib::DPWS::ByeType & n) override {
			std::cout << n << std::endl;
		}
	};

	struct HelloCallback : public DPWS::HelloCallback {
		HelloCallback() {}
		virtual ~HelloCallback() = default;

		virtual void hello(const DPWS::HelloType & n) override {
			std::cout << n << std::endl;
		}
	};

	ByeCallback byeCb;
	HelloCallback helloCb;

	std::cout << "Listening for DPWS discovery messages ..." << std::endl;
	Client client;
	client.addByeEventHandler(byeCb);
	client.addHelloEventHandler(helloCb);

	/* Example for Resolving an EPR


	struct ResolveMatchCallback : public Client::ResolveMatchCallback  {
		ResolveMatchCallback() {}
		virtual ~ResolveMatchCallback() = default;

		virtual void resolveMatch(const ResolveMatchType & n) override {
			std::cout << n << std::endl;
		}
	};

	ResolveMatchCallback resolveCb;

	while (true) {
		ResolveType resolveFilter(WS::ADDRESSING::EndpointReferenceType(WS::ADDRESSING::AttributedURIType("UDI-PUMP-157Propofol")));
		std::cout << "Resolving ..." << std::endl;
		client.addResolveMatchEventHandler(resolveFilter, resolveCb);
		Poco::Thread::sleep(10000);
		client.removeResolveMatchEventHandler(resolveCb);
		std::cout << "Resolving done." << std::endl;
	}*/

	while (true) {
		std::cout << "Probing ..." << std::endl;

		DPWS::ProbeType probeFilter;
		//i.e. probeFilter.types.emplace_back("http://ornet.org/sm/14/06", "MedicalDevice");

		Poco::Timestamp started;
		ProbeMatchCallback probeCb(started);
		
		client.addProbeMatchEventHandler(probeFilter, probeCb);
		Poco::Thread::sleep(10000);
		client.removeProbeMatchEventHandler(probeCb);
		std::cout << "Probing done." << std::endl;
	}

	client.removeHelloEventHandler(helloCb);
	client.removeByeEventHandler(byeCb);

	xercesc::XMLPlatformUtils::Terminate();
}

