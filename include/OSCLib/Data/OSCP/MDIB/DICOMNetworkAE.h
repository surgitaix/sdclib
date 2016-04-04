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
 *  DICOMNetworkAE.h
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

#ifndef DICOMNETWORKAE_H_
#define DICOMNETWORKAE_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class DICOMNetworkAE {
private:
	DICOMNetworkAE(const CDM::DICOMNetworkAE & object);
	operator CDM::DICOMNetworkAE() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	DICOMNetworkAE();
	DICOMNetworkAE(const DICOMNetworkAE & object);
	virtual ~DICOMNetworkAE();
    
    void copyFrom(const DICOMNetworkAE & object);
    DICOMNetworkAE & operator=(const DICOMNetworkAE & object);
    
    typedef CDM::DICOMNetworkAE WrappedType;

	DICOMNetworkAE & setAETitle(const std::string & value);
	std::string getAETitle() const;

	DICOMNetworkAE & setAssociationInitiator(const bool & value);
	bool getAssociationInitiator() const;

	DICOMNetworkAE & setAssociationAcceptor(const bool & value);
	bool getAssociationAcceptor() const;

	DICOMNetworkAE & setDescription(const std::string & value);
	std::string getDescription() const;
	bool getDescription(std::string & out) const;
	bool hasDescription() const;

	DICOMNetworkAE & addNetworkConnectionReference(const std::string & value);
	std::vector<std::string> getNetworkConnectionReferences() const;
	void clearNetworkConnectionReferences();
	
	DICOMNetworkAE & addTransferCapability(const DICOMTransferCapability & value);
	std::vector<DICOMTransferCapability> getTransferCapabilities() const;
	void clearTransferCapabilities();
	
	DICOMNetworkAE & addApplicationCluster(const LocalizedText & value);
	std::vector<LocalizedText> getApplicationClusters() const;
	void clearApplicationClusters();
	
	DICOMNetworkAE & addSupportedCharacterSet(const std::string & value);
	std::vector<std::string> getSupportedCharacterSets() const;
	void clearSupportedCharacterSets();
	
private:
	std::shared_ptr<CDM::DICOMNetworkAE> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* DICOMNETWORKAE_H_ */
