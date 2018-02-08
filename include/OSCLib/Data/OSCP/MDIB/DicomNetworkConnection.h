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
 *  DicomNetworkConnection.h
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

#ifndef DICOMNETWORKCONNECTION_H_
#define DICOMNETWORKCONNECTION_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class DicomNetworkConnection {
private:
	DicomNetworkConnection(const CDM::DicomNetworkConnection & object);
	operator CDM::DicomNetworkConnection() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	DicomNetworkConnection(
		xml_schema::Id id
		, 
		std::string hostname
	); 
private:
	DicomNetworkConnection(){};
public:
	DicomNetworkConnection(const DicomNetworkConnection & object);
	virtual ~DicomNetworkConnection();
    
    void copyFrom(const DicomNetworkConnection & object);
    DicomNetworkConnection & operator=(const DicomNetworkConnection & object);
    
    typedef CDM::DicomNetworkConnection WrappedType;

	DicomNetworkConnection & setid(const xml_schema::Id & value);
	xml_schema::Id getid() const;

	DicomNetworkConnection & setHostname(const std::string & value);
	std::string getHostname() const;

	DicomNetworkConnection & setPort(const unsigned short & value);
	unsigned short getPort() const;
	bool getPort(unsigned short & out) const;
	bool hasPort() const;

	DicomNetworkConnection & addTlsCipherSuite(const std::string & value);
	std::vector<std::string> getTlsCipherSuiteList() const;
	void clearTlsCipherSuiteList();
	
private:
	std::shared_ptr<CDM::DicomNetworkConnection> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* DICOMNETWORKCONNECTION_H_ */
