/*
 * DeviceDescription.h
 *
 *  Created on: 11.12.2015
 *      Author: matthias, sebastian
 *
 *      contains information about the provider
 *
 */

#ifndef OSELIB_DPWS_DEVICEDESCRIPTION_H_
#define OSELIB_DPWS_DEVICEDESCRIPTION_H_

#include <string>
#include <list>
#include "Poco/URI.h"
#include "Poco/Net/IPAddress.h"


namespace OSELib {
namespace DPWS {

class DeviceDescription {
public:
	DeviceDescription();
	virtual ~DeviceDescription();

	std::string getEPR() const;
	void setEPR(const std::string & epr);

	Poco::Net::IPAddress getLocalIP() const;
	void setLocalIP(const Poco::Net::IPAddress & localIP);

	Poco::URI getDeviceURI() const;
	void setDeviceURI(const Poco::URI & uri);

	Poco::URI getContextServiceURI() const;
	void setContextServiceURI(const Poco::URI & uri);

	Poco::URI getEventServiceURI() const;
	void setEventServiceURI(const Poco::URI & uri);

	Poco::URI getGetServiceURI() const;
	void setGetServiceURI(const Poco::URI & uri);

	Poco::URI getSetServiceURI() const;
	void setSetServiceURI(const Poco::URI & uri);

	void setWaveformEventReportURI(const Poco::URI & uri);
	Poco::URI getWaveformEventReportURI() const;

	void addStreamMulticastAddressURI(const Poco::URI & uri);
	const std::list<Poco::URI>&  getStreamMulticastAddressURIs() const;

private:
	std::string _epr;
	Poco::Net::IPAddress _localIP;

	Poco::URI _deviceURI;

	Poco::URI _contextServiceURI;
	Poco::URI _eventServiceURI;
	Poco::URI _getServiceURI;
	Poco::URI _setServiceURI;
	Poco::URI _waveformEventReportURI;
	// there may be more than one streaming addresses for compatibility with other frameworks
	std::list<Poco::URI> _streamMulticastURI;
};

} /* namespace DPWS */
} /* namespace OSELib */

#endif /* OSELIB_DPWS_DEVICEDESCRIPTION_H_ */
