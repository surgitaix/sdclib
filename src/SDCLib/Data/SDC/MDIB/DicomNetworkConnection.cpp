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

#include "SDCLib/Data/SDC/MDIB/DicomNetworkConnection.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"


namespace SDCLib {
namespace Data {
namespace SDC {


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
	data->setId(ConvertToCDM::convert(value));
	return *this;
}


xml_schema::Id DicomNetworkConnection::getid() const {
	return ConvertFromCDM::convert(data->getId());
}

DicomNetworkConnection & DicomNetworkConnection::setHostname(const std::string & value) {
	data->setHostname(ConvertToCDM::convert(value));
	return *this;
}


std::string DicomNetworkConnection::getHostname() const {
	return ConvertFromCDM::convert(data->getHostname());
}

DicomNetworkConnection & DicomNetworkConnection::setPort(const unsigned short & value) {
	data->setPort(ConvertToCDM::convert(value));
	return *this;
}

bool DicomNetworkConnection::getPort(unsigned short & out) const {
	if (data->getPort().present()) {
		out = ConvertFromCDM::convert(data->getPort().get());
		return true;
	}
	return false;
}

unsigned short DicomNetworkConnection::getPort() const {
	return ConvertFromCDM::convert(data->getPort().get());
}

bool DicomNetworkConnection::hasPort() const {
	return data->getPort().present();
}

DicomNetworkConnection & DicomNetworkConnection::addTlsCipherSuite(const std::string & value) {
	data->getTlsCipherSuite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> DicomNetworkConnection::getTlsCipherSuiteList() const {
	std::vector<std::string> result;
	result.reserve(data->getTlsCipherSuite().size());
	for (const auto & value: data->getTlsCipherSuite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomNetworkConnection::clearTlsCipherSuiteList() {
	data->getTlsCipherSuite().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

