/*
 * DeviceDescription.cpp
 *
 *  Created on: 11.12.2015
 *      Author: matthias, sebastian
 *
 *      contains information about the provider
 */

#include "OSELib/DPWS/DeviceDescription.h"

namespace OSELib {
namespace DPWS {

DeviceDescription::DeviceDescription() {

}

std::string DeviceDescription::getEPR() const {
	return _epr;
}
void DeviceDescription::setEPR(const std::string & epr) {
	_epr = epr;
}

Poco::Net::IPAddress DeviceDescription::getLocalIP() const {
	return _localIP;
}
void DeviceDescription::setLocalIP(const Poco::Net::IPAddress & localIP) {
	_localIP = localIP;
}

Poco::URI DeviceDescription::getDeviceURI() const {
	return _deviceURI;
}
void DeviceDescription::setDeviceURI(const Poco::URI & uri) {
	_deviceURI = uri;
}

Poco::URI DeviceDescription::getContextServiceURI() const {
	return _contextServiceURI;
}
void DeviceDescription::setContextServiceURI(const Poco::URI & uri) {
	_contextServiceURI = uri;
}

Poco::URI DeviceDescription::getEventServiceURI() const {
	return _eventServiceURI;
}
void DeviceDescription::setEventServiceURI(const Poco::URI & uri) {
	_eventServiceURI = uri;
}

Poco::URI DeviceDescription::getGetServiceURI() const {
	return _getServiceURI;
}
void DeviceDescription::setGetServiceURI(const Poco::URI & uri) {
	_getServiceURI = uri;
}

Poco::URI DeviceDescription::getSetServiceURI() const {
	return _setServiceURI;
}
void DeviceDescription::setSetServiceURI(const Poco::URI & uri) {
	_setServiceURI = uri;
}

void DeviceDescription::setWaveformEventReportURI(const Poco::URI & uri) {
	_waveformEventReportURI = uri;
}

Poco::URI DeviceDescription::getWaveformEventReportURI() const {
	return _waveformEventReportURI;
}

void DeviceDescription::addStreamMulticastAddressURI(const Poco::URI & uri) {
	_streamMulticastURI.push_back(uri);
}

std::list<Poco::URI>& DeviceDescription::getStreamMulticastAddressURIs() {
	if (!_streamMulticastURI.empty()) {
		return _streamMulticastURI;
	} else {
		throw std::runtime_error("No streaming service found.");
	}

}

DeviceDescription::~DeviceDescription() {

}

} /* namespace DPWS */
} /* namespace OSELib */
