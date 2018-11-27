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
 *  Author: besting, buerger, roehser
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

#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class DicomNetworkAe {
private:
	DicomNetworkAe(const CDM::DicomNetworkAe & object);
	operator CDM::DicomNetworkAe() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	DicomNetworkAe(
		std::string aetitle
		,
		xml_schema::Idrefs networkconnectionreference
		,
		bool associationinitiator
		,
		bool associationacceptor
	);
private:
	DicomNetworkAe(){};
public:
	DicomNetworkAe(const DicomNetworkAe & object);
	virtual ~DicomNetworkAe();

    void copyFrom(const DicomNetworkAe & object);
    DicomNetworkAe & operator=(const DicomNetworkAe & object);

    typedef CDM::DicomNetworkAe WrappedType;

	DicomNetworkAe & setAeTitle(const std::string & value);
	std::string getAeTitle() const;

	DicomNetworkAe & setNetworkConnectionReference(const xml_schema::Idrefs & value);
	xml_schema::Idrefs getNetworkConnectionReference() const;

	DicomNetworkAe & setAssociationInitiator(const bool & value);
	bool getAssociationInitiator() const;

	DicomNetworkAe & setAssociationAcceptor(const bool & value);
	bool getAssociationAcceptor() const;

	DicomNetworkAe & addTransferCapability(const DicomTransferCapability & value);
	std::vector<DicomTransferCapability> getTransferCapabilityList() const;
	void clearTransferCapabilityList();

	DicomNetworkAe & addDescription(const LocalizedText & value);
	std::vector<LocalizedText> getDescriptionList() const;
	void clearDescriptionList();

private:
	std::shared_ptr<CDM::DicomNetworkAe> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* DICOMNETWORKAE_H_ */
