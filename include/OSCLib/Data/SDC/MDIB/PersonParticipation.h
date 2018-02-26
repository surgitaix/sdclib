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
 *  PersonParticipation.h
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

#ifndef PERSONPARTICIPATION_H_
#define PERSONPARTICIPATION_H_

#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class PersonParticipation {
private:
	PersonParticipation(const CDM::PersonParticipation & object);
	operator CDM::PersonParticipation() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	PersonParticipation(
	); 
	PersonParticipation(const PersonParticipation & object);
	virtual ~PersonParticipation();
    
    void copyFrom(const PersonParticipation & object);
    PersonParticipation & operator=(const PersonParticipation & object);
    
    typedef CDM::PersonParticipation WrappedType;

	PersonParticipation & setName(const BaseDemographics & value);
	BaseDemographics getName() const;
	bool getName(BaseDemographics & out) const;
	bool hasName() const;

	PersonParticipation & addIdentification(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getIdentificationList() const;
	void clearIdentificationList();
	
	PersonParticipation & addRole(const CodedValue & value);
	std::vector<CodedValue> getRoleList() const;
	void clearRoleList();
	
private:
	std::shared_ptr<CDM::PersonParticipation> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* PERSONPARTICIPATION_H_ */
