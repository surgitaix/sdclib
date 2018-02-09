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
 *  Author: besting, buerger, roehser
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

#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace SDC {

class DicomDeviceDescriptor {
private:
	DicomDeviceDescriptor(const CDM::DicomDeviceDescriptor & object);
	operator CDM::DicomDeviceDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	DicomDeviceDescriptor(
		Handle handle
	); 
private:
	DicomDeviceDescriptor(){};
public:
	DicomDeviceDescriptor(const DicomDeviceDescriptor & object);
	virtual ~DicomDeviceDescriptor();
    
    void copyFrom(const DicomDeviceDescriptor & object);
    DicomDeviceDescriptor & operator=(const DicomDeviceDescriptor & object);
    
    typedef CDM::DicomDeviceDescriptor WrappedType;

	DicomDeviceDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	DicomDeviceDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	DicomDeviceDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	DicomDeviceDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	DicomDeviceDescriptor & addProductionSpecification(const ProductionSpecification & value);
	std::vector<ProductionSpecification> getProductionSpecificationList() const;
	void clearProductionSpecificationList();
	
	DicomDeviceDescriptor & setAlertSystem(const AlertSystemDescriptor & value);
	AlertSystemDescriptor getAlertSystem() const;
	bool getAlertSystem(AlertSystemDescriptor & out) const;
	bool hasAlertSystem() const;

	DicomDeviceDescriptor & setSco(const ScoDescriptor & value);
	ScoDescriptor getSco() const;
	bool getSco(ScoDescriptor & out) const;
	bool hasSco() const;

	DicomDeviceDescriptor & setIssuerOfPatientID(const std::string & value);
	std::string getIssuerOfPatientID() const;
	bool getIssuerOfPatientID(std::string & out) const;
	bool hasIssuerOfPatientID() const;

	DicomDeviceDescriptor & addNetworkAe(const DicomNetworkAe & value);
	std::vector<DicomNetworkAe> getNetworkAeList() const;
	void clearNetworkAeList();
	
	DicomDeviceDescriptor & addNetworkConnection(const DicomNetworkConnection & value);
	std::vector<DicomNetworkConnection> getNetworkConnectionList() const;
	void clearNetworkConnectionList();
	
	DicomDeviceDescriptor & addDescription(const LocalizedText & value);
	std::vector<LocalizedText> getDescriptionList() const;
	void clearDescriptionList();
	
	DicomDeviceDescriptor & addStationName(const LocalizedText & value);
	std::vector<LocalizedText> getStationNameList() const;
	void clearStationNameList();
	
private:
	std::shared_ptr<CDM::DicomDeviceDescriptor> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* DICOMDEVICEDESCRIPTOR_H_ */
