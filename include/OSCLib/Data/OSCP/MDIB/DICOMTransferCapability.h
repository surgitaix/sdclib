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
 *  DICOMTransferCapability.h
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

#ifndef DICOMTRANSFERCAPABILITY_H_
#define DICOMTRANSFERCAPABILITY_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class DICOMTransferCapability {
private:
	DICOMTransferCapability(const CDM::DICOMTransferCapability & object);
	operator CDM::DICOMTransferCapability() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	DICOMTransferCapability();
	DICOMTransferCapability(const DICOMTransferCapability & object);
	virtual ~DICOMTransferCapability();
    
    void copyFrom(const DICOMTransferCapability & object);
    DICOMTransferCapability & operator=(const DICOMTransferCapability & object);
    
    typedef CDM::DICOMTransferCapability WrappedType;

	DICOMTransferCapability & setSOPClass(const std::string & value);
	std::string getSOPClass() const;

	DICOMTransferCapability & setTransferRole(const DICOMTransferRole & value);
	DICOMTransferRole getTransferRole() const;

	DICOMTransferCapability & addTransferSyntax(const std::string & value);
	std::vector<std::string> getTransferSyntaxes() const;
	void clearTransferSyntaxes();
	
private:
	std::shared_ptr<CDM::DICOMTransferCapability> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* DICOMTRANSFERCAPABILITY_H_ */
