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
 *  DicomNetworkAe.h
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

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class DicomNetworkAe {
private:
	DicomNetworkAe(const CDM::DicomNetworkAe & object);
	operator CDM::DicomNetworkAe() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	DicomNetworkAe();
	DicomNetworkAe(const DicomNetworkAe & object);
	virtual ~DicomNetworkAe();
    
    void copyFrom(const DicomNetworkAe & object);
    DicomNetworkAe & operator=(const DicomNetworkAe & object);
    
    typedef CDM::DicomNetworkAe WrappedType;

	DicomNetworkAe & setAeTitle(const std::string & value);
	std::string getAeTitle() const;

	DicomNetworkAe & setNetworkConnectionReference(const std::string & value);
	std::string getNetworkConnectionReference() const;

	DicomNetworkAe & setAssociationInitiator(const bool & value);
	bool getAssociationInitiator() const;

	DicomNetworkAe & setAssociationAcceptor(const bool & value);
	bool getAssociationAcceptor() const;

	DicomNetworkAe & addTransferCapability(const DicomTransferCapability & value);
	std::vector<DicomTransferCapability> getTransferCapabilities() const;
	void clearTransferCapabilities();
	
	DicomNetworkAe & addApplicationCluster(const LocalizedText & value);
	std::vector<LocalizedText> getApplicationClusters() const;
	void clearApplicationClusters();
	
	DicomNetworkAe & addSupportedCharacterSet(const std::string & value);
	std::vector<std::string> getSupportedCharacterSets() const;
	void clearSupportedCharacterSets();
	
	DicomNetworkAe & addDescription(const LocalizedText & value);
	std::vector<LocalizedText> getDescriptions() const;
	void clearDescriptions();
	
private:
	std::shared_ptr<CDM::DicomNetworkAe> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* DICOMNETWORKAE_H_ */
