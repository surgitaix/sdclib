/*
 * DeviceDescription.cpp
 *
 *  Created on: 11.12.2015
 *      Author: buerger, matthias, baumeister
 *
 *      contains information for the consumer about the provider. all addresses are firstly added while discovery. the possibility of establishing a connection is checked before returning a URI.
 */

#include "OSELib/DPWS/DeviceDescription.h"

#include <Poco/Net/StreamSocket.h>

using namespace OSELib;
using namespace OSELib::DPWS;

DeviceDescription::DeviceDescription()
: WithLogger(Log::DISCOVERY)
{

}

bool DeviceDescription::checkURIsValidity(const Poco::URI & p_uri) const
{
	// Checks if a given URI is valid by trying to establish a connection
	try {
		Poco::Net::StreamSocket t_connection;
		t_connection.connect(Poco::Net::SocketAddress(p_uri.getHost(), p_uri.getPort()), Poco::Timespan(50000));
		return true;
	} catch (...) {
		log_debug([&] { return "Contacting xAddress failed: " + p_uri.toString(); });
		return false;
	}
	return false;
}


std::string DeviceDescription::getEPR() const
{
	std::lock_guard<std::mutex> t_lock(m_mutex_epr);
	return m_epr;
}
void DeviceDescription::setEPR(const std::string & p_epr)
{
	if(p_epr.empty()) {
		return;
	}
	std::lock_guard<std::mutex> t_lock(m_mutex_epr);
	m_epr = p_epr;
}

Poco::Net::IPAddress DeviceDescription::getLocalIP() const
{
	std::lock_guard<std::mutex> t_lock(m_mutex_IP);
	return m_localIP;
}
void DeviceDescription::setLocalIP(const Poco::Net::IPAddress & p_localIP)
{
	std::lock_guard<std::mutex> t_lock(m_mutex_IP);
	m_localIP = p_localIP;
}

Poco::URI DeviceDescription::getDeviceURI() const
{
	std::lock_guard<std::mutex> t_lock(m_mutex_URIs);
	if(ml_deviceURIs.empty()) {
		throw std::runtime_error("DeviceURI empty!");
	}
	return ml_deviceURIs.front();
}

void DeviceDescription::addDeviceURI(const Poco::URI & p_uri)
{
	if (checkURIsValidity(p_uri)) {
		std::lock_guard<std::mutex> t_lock(m_mutex_URIs);
		ml_deviceURIs.push_back(p_uri);
	} else {
		throw std::runtime_error("DeviceURI is not valid.");
	}
}

Poco::URI DeviceDescription::getContextServiceURI() const
{
	std::lock_guard<std::mutex> t_lock(m_mutex_URIs);
	for (const auto t_iter : ml_contextServiceURIs) {
		if (checkURIsValidity(t_iter)) {
			return t_iter;
		}
	}
	throw std::runtime_error("No ContextServiceURI valid.");
}
void DeviceDescription::addContextServiceURI(const Poco::URI & p_uri)
{
	std::lock_guard<std::mutex> t_lock(m_mutex_URIs);
	ml_contextServiceURIs.push_back(p_uri);
}

Poco::URI DeviceDescription::getEventServiceURI() const
{
	std::lock_guard<std::mutex> t_lock(m_mutex_URIs);
	for (const auto t_iter : ml_eventServiceURIs) {
		if (checkURIsValidity(t_iter)) {
			return t_iter;
		}
	}
	throw std::runtime_error("All EventServiceURIs are not valid.");
}
void DeviceDescription::addStateEventReportServiceURI(const Poco::URI & p_uri)
{
	std::lock_guard<std::mutex> t_lock(m_mutex_URIs);
	ml_eventServiceURIs.push_back(p_uri);
}

Poco::URI DeviceDescription::getGetServiceURI() const
{
	std::lock_guard<std::mutex> t_lock(m_mutex_URIs);
	for (const auto t_iter : ml_getServiceURIs) {
		if (checkURIsValidity(t_iter)) {
			return t_iter;
		}
	}
	throw std::runtime_error("No GetServiceURI valid.");
}
void DeviceDescription::addGetServiceURI(const Poco::URI & p_uri)
{
	std::lock_guard<std::mutex> t_lock(m_mutex_URIs);
	ml_getServiceURIs.push_back(p_uri);
}

Poco::URI DeviceDescription::getSetServiceURI() const
{
	std::lock_guard<std::mutex> t_lock(m_mutex_URIs);
	for (const auto t_iter : ml_setServiceURIs) {
		if (checkURIsValidity(t_iter)) {
			return t_iter;
		}
	}
	throw std::runtime_error("No SetServiceURI valid.");
}
void DeviceDescription::addSetServiceURI(const Poco::URI & p_uri)
{
	std::lock_guard<std::mutex> t_lock(m_mutex_URIs);
	ml_setServiceURIs.push_back(p_uri);
}

void DeviceDescription::addWaveformServiceURI(const Poco::URI & p_uri)
{
	std::lock_guard<std::mutex> t_lock(m_mutex_URIs);
	ml_waveformEventReportURIs.push_back(p_uri);
}

Poco::URI DeviceDescription::getWaveformEventReportURI() const
{
	std::lock_guard<std::mutex> t_lock(m_mutex_URIs);
	for (const auto t_iter : ml_waveformEventReportURIs) {
		if (checkURIsValidity(t_iter)) {
			return t_iter;
		}
	}
	throw std::runtime_error("No WaveformEventReportURI valid.");
}

void DeviceDescription::addStreamMulticastAddressURI(const Poco::URI & p_uri)
{
	std::lock_guard<std::mutex> t_lock(m_mutex_URIs);
	ml_streamMulticastURIs.push_back(p_uri);
}

// regarding to the standard multiple streaming addresses can be stated by the provider
URIVector DeviceDescription::getStreamMulticastAddressURIs() const
{
	std::lock_guard<std::mutex> t_lock(m_mutex_URIs);
	return ml_streamMulticastURIs;
}

