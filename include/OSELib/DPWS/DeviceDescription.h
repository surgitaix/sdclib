/*l
 * DeviceDescription.h
 *
 *  Created on: 11.12.2015
 *      Author: sebastian, matthias
 *
 *      Contains information about the provider, to which the consumer connects to. All devices xAddresses are saved here (no validity check). The validity of the connection is checked in each get-method.
 *
 */

#ifndef OSELIB_DPWS_DEVICEDESCRIPTION_H_
#define OSELIB_DPWS_DEVICEDESCRIPTION_H_

#include <string>
#include <list>
#include "Poco/URI.h"
#include "Poco/Net/IPAddress.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "OSELib/Helper/WithLogger.h"


namespace OSELib {
namespace DPWS {

class DeviceDescription : public WithLogger {
public:
	DeviceDescription();
	virtual ~DeviceDescription();

	bool checkURIsValidity(const Poco::URI & uri) const;

	std::string getEPR() const;
	void setEPR(const std::string & epr);

	Poco::Net::IPAddress getLocalIP() const;
	void setLocalIP(const Poco::Net::IPAddress & localIP);

	Poco::URI getDeviceURI() const;
	void addDeviceURI(const Poco::URI & uri);

	Poco::URI getContextServiceURI() const;
	void addContextServiceURI(const Poco::URI & uri);

	Poco::URI getEventServiceURI() const;
	void addStateEventReportServiceURI(const Poco::URI & uri);

	Poco::URI getGetServiceURI() const;
	void addGetServiceURI(const Poco::URI & uri);

	Poco::URI getSetServiceURI() const;
	void addSetServiceURI(const Poco::URI & uri);

	void addWaveformServiceURI(const Poco::URI & uri);
	Poco::URI getWaveformEventReportURI() const;

	void addStreamMulticastAddressURI(const Poco::URI & uri);
	const std::list<Poco::URI>&  getStreamMulticastAddressURIs() const;

private:
	std::string _epr;
	Poco::Net::IPAddress _localIP;


	// there may be more than one streaming addresses for compatibility with other frameworks
	std::list<Poco::URI> _streamMulticastURIs;
	std::list<Poco::URI> _contextServiceURIs;
	std::list<Poco::URI> _eventServiceURIs;
	std::list<Poco::URI> _getServiceURIs;
	std::list<Poco::URI> _setServiceURIs;
	std::list<Poco::URI> _waveformEventReportURIs;
	std::list<Poco::URI> _deviceURIs;

};

} /* namespace DPWS */
} /* namespace OSELib */

#endif /* OSELIB_DPWS_DEVICEDESCRIPTION_H_ */
