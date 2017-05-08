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
 *  DICOMDeviceDescriptor.h
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

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class DICOMDeviceDescriptor {
private:
	DICOMDeviceDescriptor(const CDM::DICOMDeviceDescriptor & object);
	operator CDM::DICOMDeviceDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	DICOMDeviceDescriptor();
	DICOMDeviceDescriptor(const DICOMDeviceDescriptor & object);
	virtual ~DICOMDeviceDescriptor();
    
    void copyFrom(const DICOMDeviceDescriptor & object);
    DICOMDeviceDescriptor & operator=(const DICOMDeviceDescriptor & object);
    
    typedef CDM::DICOMDeviceDescriptor WrappedType;

	DICOMDeviceDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	DICOMDeviceDescriptor & setHandle(const std::string & value);
	std::string getHandle() const;

	DICOMDeviceDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	DICOMDeviceDescriptor & addProductionSpecification(const ProductionSpecification & value);
	std::vector<ProductionSpecification> getProductionSpecifications() const;
	void clearProductionSpecifications();
	
	DICOMDeviceDescriptor & setMetaData(const SystemMetaData & value);
	SystemMetaData getMetaData() const;
	bool getMetaData(SystemMetaData & out) const;
	bool hasMetaData() const;

	DICOMDeviceDescriptor & setContext(const SystemContext & value);
	SystemContext getContext() const;

	DICOMDeviceDescriptor & setClock(const ClockDescriptor & value);
	ClockDescriptor getClock() const;
	bool getClock(ClockDescriptor & out) const;
	bool hasClock() const;

	DICOMDeviceDescriptor & setDescription(const std::string & value);
	std::string getDescription() const;
	bool getDescription(std::string & out) const;
	bool hasDescription() const;

	DICOMDeviceDescriptor & setStationName(const std::string & value);
	std::string getStationName() const;
	bool getStationName(std::string & out) const;
	bool hasStationName() const;

	DICOMDeviceDescriptor & setIssuerOfPatientID(const std::string & value);
	std::string getIssuerOfPatientID() const;
	bool getIssuerOfPatientID(std::string & out) const;
	bool hasIssuerOfPatientID() const;

	DICOMDeviceDescriptor & addNetworkAE(const DICOMNetworkAE & value);
	std::vector<DICOMNetworkAE> getNetworkAEs() const;
	void clearNetworkAEs();
	
	DICOMDeviceDescriptor & addNetworkConnection(const DICOMNetworkConnection & value);
	std::vector<DICOMNetworkConnection> getNetworkConnection() const;
	void clearNetworkConnection();
	
	DICOMDeviceDescriptor & addSoftwareVersion(const std::string & value);
	std::vector<std::string> getSoftwareVersions() const;
	void clearSoftwareVersions();
	
	DICOMDeviceDescriptor & addInstitutionName(const LocalizedText & value);
	std::vector<LocalizedText> getInstitutionNames() const;
	void clearInstitutionNames();
	
	DICOMDeviceDescriptor & addInstitutionAddress(const LocalizedText & value);
	std::vector<LocalizedText> getInstitutionAddresses() const;
	void clearInstitutionAddresses();
	
	DICOMDeviceDescriptor & addInstitutionalDepartmentName(const LocalizedText & value);
	std::vector<LocalizedText> getInstitutionalDepartmentNames() const;
	void clearInstitutionalDepartmentNames();
	
	DICOMDeviceDescriptor & addPrimaryDeviceType(const LocalizedText & value);
	std::vector<LocalizedText> getPrimaryDeviceTypes() const;
	void clearPrimaryDeviceTypes();
	
	DICOMDeviceDescriptor & addPublicCertificate(const Base64Binary & value);
	std::vector<Base64Binary> getPublicCertificates() const;
	void clearPublicCertificates();
	
private:
	std::shared_ptr<CDM::DICOMDeviceDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* DICOMDEVICEDESCRIPTOR_H_ */
