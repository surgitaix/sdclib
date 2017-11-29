/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/*
 *  DicomNetworkConnection.cpp
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, buerger, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/DicomNetworkConnection.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {


DicomNetworkConnection::DicomNetworkConnection(
		xml_schema::Id id
		, 
		std::string hostname
) : data(Defaults::DicomNetworkConnectionInit(
		id
		,
		hostname
)) {}

DicomNetworkConnection::operator CDM::DicomNetworkConnection() const {
	return *data;
}

DicomNetworkConnection::DicomNetworkConnection(const CDM::DicomNetworkConnection & object) : data(new CDM::DicomNetworkConnection(object)) {

}

DicomNetworkConnection::DicomNetworkConnection(const DicomNetworkConnection & object) : data(new CDM::DicomNetworkConnection(*object.data)) {

}

DicomNetworkConnection::~DicomNetworkConnection() {

}

void DicomNetworkConnection::copyFrom(const DicomNetworkConnection & object) {
	data = std::shared_ptr<CDM::DicomNetworkConnection>( new CDM::DicomNetworkConnection(*object.data));
}

DicomNetworkConnection & DicomNetworkConnection:: operator=(const DicomNetworkConnection & object) {
	copyFrom(object);
	return *this;
}


DicomNetworkConnection & DicomNetworkConnection::setid(const xml_schema::Id & value) {
	data->id(ConvertToCDM::convert(value));
	return *this;
}


xml_schema::Id DicomNetworkConnection::getid() const {
	return ConvertFromCDM::convert(data->id());
}
	
DicomNetworkConnection & DicomNetworkConnection::setHostname(const std::string & value) {
	data->Hostname(ConvertToCDM::convert(value));
	return *this;
}


std::string DicomNetworkConnection::getHostname() const {
	return ConvertFromCDM::convert(data->Hostname());
}
	
DicomNetworkConnection & DicomNetworkConnection::setPort(const unsigned short & value) {
	data->Port(ConvertToCDM::convert(value));
	return *this;
}

bool DicomNetworkConnection::getPort(unsigned short & out) const {
	if (data->Port().present()) {
		out = ConvertFromCDM::convert(data->Port().get());
		return true;
	}
	return false;
}

unsigned short DicomNetworkConnection::getPort() const {
	return ConvertFromCDM::convert(data->Port().get());
}
	
bool DicomNetworkConnection::hasPort() const {
	return data->Port().present();
}
	
DicomNetworkConnection & DicomNetworkConnection::addTlsCipherSuite(const std::string & value) {
	data->TlsCipherSuite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> DicomNetworkConnection::getTlsCipherSuiteList() const {
	std::vector<std::string> result;
	result.reserve(data->TlsCipherSuite().size());
	for (const auto & value: data->TlsCipherSuite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomNetworkConnection::clearTlsCipherSuiteList() {
	data->TlsCipherSuite().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

