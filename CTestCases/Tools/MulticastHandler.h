/*
 * MulticastHandler.h
 *
 *  Created on: Nov 12, 2018
 *      Author: rosenau
 */

#ifndef CTESTCASES_TOOLS_MULTICASTHANDLER_H_
#define CTESTCASES_TOOLS_MULTICASTHANDLER_H_


#include <iostream>
#include <memory>
#include <sstream>
#include <string>

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
CONSTEXPR_MACRO uint16_t UPD_MULTICAST_DISCOVERY_PORT(3702);
const std::string intendationLevel1("  ");
CONSTEXPR_MACRO std::size_t lineLength(80);
const std::string separator(lineLength, '-');

namespace TestTools {

struct messagedata_t {
	std::shared_ptr<MESSAGEMODEL::Envelope> message;
	Poco::Net::SocketAddress remoteAddr;
	std::string socketData;
};

class MulticastHandler {
public:
	MulticastHandler();
	virtual ~MulticastHandler();
	void onMulticastSocketReadable(Poco::Net::ReadableNotification * notification);

	virtual void onProbeMessageReceived(messagedata_t messagedata);
	virtual void onResolveMessageReceived(messagedata_t messagedata);
	virtual void onByeMessageReceived(messagedata_t messagedata);
	virtual void onUnknownDataReceived(messagedata_t messagedata);
	virtual void onHelloMessageReceived(messagedata_t messagedata);

}; /* namespace TestTools */
}

#endif /* CTESTCASES_TOOLS_MULTICASTHANDLER_H_ */
