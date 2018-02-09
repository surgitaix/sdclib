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
 *  PersonReference.h
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

#ifndef PERSONREFERENCE_H_
#define PERSONREFERENCE_H_

#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace SDC {

class PersonReference {
private:
	PersonReference(const CDM::PersonReference & object);
	operator CDM::PersonReference() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	PersonReference(
	); 
	PersonReference(const PersonReference & object);
	virtual ~PersonReference();
    
    void copyFrom(const PersonReference & object);
    PersonReference & operator=(const PersonReference & object);
    
    typedef CDM::PersonReference WrappedType;

	PersonReference & setName(const BaseDemographics & value);
	BaseDemographics getName() const;
	bool getName(BaseDemographics & out) const;
	bool hasName() const;

	PersonReference & addIdentification(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getIdentificationList() const;
	void clearIdentificationList();
	
private:
	std::shared_ptr<CDM::PersonReference> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* PERSONREFERENCE_H_ */
