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
 *  DicomDeviceDescriptor.h
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

#ifndef DICOMDEVICEDESCRIPTOR_H_
#define DICOMDEVICEDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class DicomDeviceDescriptor {
private:
	DicomDeviceDescriptor(const CDM::DicomDeviceDescriptor & object);
	operator CDM::DicomDeviceDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	DicomDeviceDescriptor();
	DicomDeviceDescriptor(const DicomDeviceDescriptor & object);
	virtual ~DicomDeviceDescriptor();
    
    void copyFrom(const DicomDeviceDescriptor & object);
    DicomDeviceDescriptor & operator=(const DicomDeviceDescriptor & object);
    
    typedef CDM::DicomDeviceDescriptor WrappedType;

	DicomDeviceDescriptor & setDescription(const std::string & value);
	std::string getDescription() const;
	bool getDescription(std::string & out) const;
	bool hasDescription() const;

	DicomDeviceDescriptor & setStationName(const std::string & value);
	std::string getStationName() const;
	bool getStationName(std::string & out) const;
	bool hasStationName() const;

	DicomDeviceDescriptor & setIssuerOfPatientID(const std::string & value);
	std::string getIssuerOfPatientID() const;
	bool getIssuerOfPatientID(std::string & out) const;
	bool hasIssuerOfPatientID() const;

	DicomDeviceDescriptor & addNetworkAe(const DicomNetworkAe & value);
	std::vector<DicomNetworkAe> getNetworkAes() const;
	void clearNetworkAes();
	
	DicomDeviceDescriptor & addNetworkConnection(const DicomNetworkConnection & value);
	std::vector<DicomNetworkConnection> getNetworkConnection() const;
	void clearNetworkConnection();
	
	DicomDeviceDescriptor & addSoftwareVersion(const std::string & value);
	std::vector<std::string> getSoftwareVersions() const;
	void clearSoftwareVersions();
	
	DicomDeviceDescriptor & addInstitutionName(const LocalizedText & value);
	std::vector<LocalizedText> getInstitutionNames() const;
	void clearInstitutionNames();
	
	DicomDeviceDescriptor & addInstitutionAddress(const LocalizedText & value);
	std::vector<LocalizedText> getInstitutionAddresses() const;
	void clearInstitutionAddresses();
	
	DicomDeviceDescriptor & addInstitutionalDepartmentName(const LocalizedText & value);
	std::vector<LocalizedText> getInstitutionalDepartmentNames() const;
	void clearInstitutionalDepartmentNames();
	
	DicomDeviceDescriptor & addPrimaryDeviceType(const LocalizedText & value);
	std::vector<LocalizedText> getPrimaryDeviceTypes() const;
	void clearPrimaryDeviceTypes();
	
	DicomDeviceDescriptor & addPublicCertificate(const Base64Binary & value);
	std::vector<Base64Binary> getPublicCertificates() const;
	void clearPublicCertificates();
	
private:
	std::shared_ptr<CDM::DicomDeviceDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* DICOMDEVICEDESCRIPTOR_H_ */
