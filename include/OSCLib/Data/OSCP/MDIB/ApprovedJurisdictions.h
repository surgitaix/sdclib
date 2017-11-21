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
 *  ApprovedJurisdictions.h
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

#ifndef APPROVEDJURISDICTIONS_H_
#define APPROVEDJURISDICTIONS_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class ApprovedJurisdictions {
private:
	ApprovedJurisdictions(const CDM::ApprovedJurisdictions & object);
	operator CDM::ApprovedJurisdictions() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	ApprovedJurisdictions(
	); 
	ApprovedJurisdictions(const ApprovedJurisdictions & object);
	virtual ~ApprovedJurisdictions();
    
    void copyFrom(const ApprovedJurisdictions & object);
    ApprovedJurisdictions & operator=(const ApprovedJurisdictions & object);
    
    typedef CDM::ApprovedJurisdictions WrappedType;

	ApprovedJurisdictions & addApprovedJurisdiction(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getApprovedJurisdictionList() const;
	void clearApprovedJurisdictionList();
	
private:
	std::shared_ptr<CDM::ApprovedJurisdictions> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* APPROVEDJURISDICTIONS_H_ */
