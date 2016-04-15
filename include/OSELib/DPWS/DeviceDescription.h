/*
 * DeviceDescription.h
 *
 *  Created on: 11.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_DPWS_DEVICEDESCRIPTION_H_
#define OSELIB_DPWS_DEVICEDESCRIPTION_H_

#include <string>
#include "Poco/URI.h"
#include "Poco/Net/IPAddress.h"

namespace OSELib {
namespace DPWS {

class DeviceDescription {
public:
	DeviceDescription();
	virtual ~DeviceDescription();

	// todo move to cpp
	// todo make more general and include all metadata from the probe/get/getresponse for each service so we can look them up here

	std::string getEPR() const {
		return _epr;
	}
	void setEPR(const std::string & epr) {
		_epr = epr;
	}

	Poco::Net::IPAddress getLocalIP() const {
		return _localIP;
	}
	void setLocalIP(const Poco::Net::IPAddress & localIP) {
		_localIP = localIP;
	}

	Poco::URI getDeviceURI() const {
		return _deviceURI;
	}
	void setDeviceURI(const Poco::URI & uri) {
		_deviceURI = uri;
	}

	Poco::URI getContextServiceURI() const {
		return _contextServiceURI;
	}
	void setContextServiceURI(const Poco::URI & uri) {
		_contextServiceURI = uri;
	}

	Poco::URI getEventServiceURI() const {
		return _eventServiceURI;
	}
	void setEventServiceURI(const Poco::URI & uri) {
		_eventServiceURI = uri;
	}

	Poco::URI getGetServiceURI() const {
		return _getServiceURI;
	}
	void setGetServiceURI(const Poco::URI & uri) {
		_getServiceURI = uri;
	}

	Poco::URI getSetServiceURI() const {
		return _setServiceURI;
	}
	void setSetServiceURI(const Poco::URI & uri) {
		_setServiceURI = uri;
	}

private:
	std::string _epr;
	Poco::Net::IPAddress _localIP;

	Poco::URI _deviceURI;

	Poco::URI _contextServiceURI;
	Poco::URI _eventServiceURI;
	Poco::URI _getServiceURI;
	Poco::URI _setServiceURI;
};

} /* namespace DPWS */
} /* namespace OSELib */

#endif /* OSELIB_DPWS_DEVICEDESCRIPTION_H_ */
