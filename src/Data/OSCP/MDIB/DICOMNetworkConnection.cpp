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
 *  DICOMNetworkConnection.cpp
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

#include "OSCLib/Data/OSCP/MDIB/DICOMNetworkConnection.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

DICOMNetworkConnection::DICOMNetworkConnection() : data(Defaults::DICOMNetworkConnection()) {
}

DICOMNetworkConnection::operator CDM::DICOMNetworkConnection() const {
	return *data;
}

DICOMNetworkConnection::DICOMNetworkConnection(const CDM::DICOMNetworkConnection & object) : data(new CDM::DICOMNetworkConnection(object)) {

}

DICOMNetworkConnection::DICOMNetworkConnection(const DICOMNetworkConnection & object) : data(new CDM::DICOMNetworkConnection(*object.data)) {

}

DICOMNetworkConnection::~DICOMNetworkConnection() {

}

void DICOMNetworkConnection::copyFrom(const DICOMNetworkConnection & object) {
	*data = *object.data;
}

DICOMNetworkConnection & DICOMNetworkConnection:: operator=(const DICOMNetworkConnection & object) {
	copyFrom(object);
	return *this;
}


DICOMNetworkConnection & DICOMNetworkConnection::setid(const std::string & value) {
	data->id(ConvertToCDM::convert(value));
	return *this;
}


std::string DICOMNetworkConnection::getid() const {
	return ConvertFromCDM::convert(data->id());
}
	
DICOMNetworkConnection & DICOMNetworkConnection::setHostname(const std::string & value) {
	data->Hostname(ConvertToCDM::convert(value));
	return *this;
}


std::string DICOMNetworkConnection::getHostname() const {
	return ConvertFromCDM::convert(data->Hostname());
}
	
DICOMNetworkConnection & DICOMNetworkConnection::setPort(const unsigned short int & value) {
	data->Port(ConvertToCDM::convert(value));
	return *this;
}

bool DICOMNetworkConnection::getPort(unsigned short int & out) const {
	if (data->Port().present()) {
		out = ConvertFromCDM::convert(data->Port().get());
		return true;
	}
	return false;
}

unsigned short int DICOMNetworkConnection::getPort() const {
	return ConvertFromCDM::convert(data->Port().get());
}
	
bool DICOMNetworkConnection::hasPort() const {
	return data->Port().present();
}
	
DICOMNetworkConnection & DICOMNetworkConnection::addTLSCipherSuite(const std::string & value) {
	data->TLSCipherSuite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> DICOMNetworkConnection::getTLSCipherSuites() const {
	std::vector<std::string> result;
	result.reserve(data->TLSCipherSuite().size());
	for (const auto & value: data->TLSCipherSuite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DICOMNetworkConnection::clearTLSCipherSuites() {
	data->TLSCipherSuite().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

