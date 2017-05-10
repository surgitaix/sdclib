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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/DicomNetworkConnection.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

DicomNetworkConnection::DicomNetworkConnection() : data(Defaults::DicomNetworkConnection()) {
}

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
	*data = *object.data;
}

DicomNetworkConnection & DicomNetworkConnection:: operator=(const DicomNetworkConnection & object) {
	copyFrom(object);
	return *this;
}


DicomNetworkConnection & DicomNetworkConnection::setid(const std::string & value) {
	data->id(ConvertToCDM::convert(value));
	return *this;
}


std::string DicomNetworkConnection::getid() const {
	return ConvertFromCDM::convert(data->id());
}
	
DicomNetworkConnection & DicomNetworkConnection::setHostname(const std::string & value) {
	data->Hostname(ConvertToCDM::convert(value));
	return *this;
}


std::string DicomNetworkConnection::getHostname() const {
	return ConvertFromCDM::convert(data->Hostname());
}
	
DicomNetworkConnection & DicomNetworkConnection::setPort(const unsigned short int & value) {
	data->Port(ConvertToCDM::convert(value));
	return *this;
}

bool DicomNetworkConnection::getPort(unsigned short int & out) const {
	if (data->Port().present()) {
		out = ConvertFromCDM::convert(data->Port().get());
		return true;
	}
	return false;
}

unsigned short int DicomNetworkConnection::getPort() const {
	return ConvertFromCDM::convert(data->Port().get());
}
	
bool DicomNetworkConnection::hasPort() const {
	return data->Port().present();
}
	
DicomNetworkConnection & DicomNetworkConnection::addTLSCipherSuite(const std::string & value) {
	data->TLSCipherSuite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> DicomNetworkConnection::getTLSCipherSuites() const {
	std::vector<std::string> result;
	result.reserve(data->TLSCipherSuite().size());
	for (const auto & value: data->TLSCipherSuite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomNetworkConnection::clearTLSCipherSuites() {
	data->TLSCipherSuite().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

