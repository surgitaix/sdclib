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
 *  PhysicalConnectorInfo.h
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

#ifndef PHYSICALCONNECTORINFO_H_
#define PHYSICALCONNECTORINFO_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class PhysicalConnectorInfo {
private:
	PhysicalConnectorInfo(const CDM::PhysicalConnectorInfo & object);
	operator CDM::PhysicalConnectorInfo() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	PhysicalConnectorInfo(
	); 
	PhysicalConnectorInfo(const PhysicalConnectorInfo & object);
	virtual ~PhysicalConnectorInfo();
    
    void copyFrom(const PhysicalConnectorInfo & object);
    PhysicalConnectorInfo & operator=(const PhysicalConnectorInfo & object);
    
    typedef CDM::PhysicalConnectorInfo WrappedType;

	PhysicalConnectorInfo & setNumber(const int & value);
	int getNumber() const;
	bool getNumber(int & out) const;
	bool hasNumber() const;

	PhysicalConnectorInfo & addLabel(const LocalizedText & value);
	std::vector<LocalizedText> getLabelList() const;
	void clearLabelList();
	
private:
	std::shared_ptr<CDM::PhysicalConnectorInfo> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* PHYSICALCONNECTORINFO_H_ */
