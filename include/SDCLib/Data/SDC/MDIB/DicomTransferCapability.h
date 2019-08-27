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
 *  DicomTransferCapability.h
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

#ifndef DICOMTRANSFERCAPABILITY_H_
#define DICOMTRANSFERCAPABILITY_H_

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "DataModel/osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class DicomTransferCapability {
private:
	DicomTransferCapability(const CDM::DicomTransferCapability & object);
	operator CDM::DicomTransferCapability() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	DicomTransferCapability(
		std::string sopclass
		,
		DicomTransferRole transferrole
	);
private:
	DicomTransferCapability(){};
public:
	DicomTransferCapability(const DicomTransferCapability & object);
	virtual ~DicomTransferCapability();

    void copyFrom(const DicomTransferCapability & object);
    DicomTransferCapability & operator=(const DicomTransferCapability & object);

    typedef CDM::DicomTransferCapability WrappedType;

	DicomTransferCapability & setSopClass(const std::string & value);
	std::string getSopClass() const;

	DicomTransferCapability & setTransferRole(const DicomTransferRole & value);
	DicomTransferRole getTransferRole() const;

	DicomTransferCapability & addTransferSyntax(const std::string & value);
	std::vector<std::string> getTransferSyntaxList() const;
	void clearTransferSyntaxList();

private:
	std::shared_ptr<CDM::DicomTransferCapability> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* DICOMTRANSFERCAPABILITY_H_ */
