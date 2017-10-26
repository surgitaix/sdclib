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
 *  LocationReference.h
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

#ifndef LOCATIONREFERENCE_H_
#define LOCATIONREFERENCE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class LocationReference {
private:
	LocationReference(const CDM::LocationReference & object);
	operator CDM::LocationReference() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	LocationReference();
	LocationReference(const LocationReference & object);
	virtual ~LocationReference();
    
    void copyFrom(const LocationReference & object);
    LocationReference & operator=(const LocationReference & object);
    
    typedef CDM::LocationReference WrappedType;

	LocationReference & setLocationDetail(const LocationDetail & value);
	LocationDetail getLocationDetail() const;
	bool getLocationDetail(LocationDetail & out) const;
	bool hasLocationDetail() const;

	LocationReference & addIdentification(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getIdentificationList() const;
	void clearIdentificationList();
	
private:
	std::shared_ptr<CDM::LocationReference> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* LOCATIONREFERENCE_H_ */
