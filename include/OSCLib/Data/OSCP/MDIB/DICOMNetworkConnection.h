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
 *  DICOMNetworkConnection.h
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

#ifndef DICOMNETWORKCONNECTION_H_
#define DICOMNETWORKCONNECTION_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class DICOMNetworkConnection {
private:
	DICOMNetworkConnection(const CDM::DICOMNetworkConnection & object);
	operator CDM::DICOMNetworkConnection() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	DICOMNetworkConnection();
	DICOMNetworkConnection(const DICOMNetworkConnection & object);
	virtual ~DICOMNetworkConnection();
    
    void copyFrom(const DICOMNetworkConnection & object);
    DICOMNetworkConnection & operator=(const DICOMNetworkConnection & object);
    
    typedef CDM::DICOMNetworkConnection WrappedType;

	DICOMNetworkConnection & setid(const std::string & value);
	std::string getid() const;

	DICOMNetworkConnection & setHostname(const std::string & value);
	std::string getHostname() const;

	DICOMNetworkConnection & setPort(const unsigned short int & value);
	unsigned short int getPort() const;
	bool getPort(unsigned short int & out) const;
	bool hasPort() const;

	DICOMNetworkConnection & addTLSCipherSuite(const std::string & value);
	std::vector<std::string> getTLSCipherSuites() const;
	void clearTLSCipherSuites();
	
private:
	std::shared_ptr<CDM::DICOMNetworkConnection> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* DICOMNETWORKCONNECTION_H_ */
