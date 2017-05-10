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
 *  Author: besting, roehser
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

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class PersonParticipation {
private:
	PersonParticipation(const CDM::PersonParticipation & object);
	operator CDM::PersonParticipation() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	PersonParticipation();
	PersonParticipation(const PersonParticipation & object);
	virtual ~PersonParticipation();
    
    void copyFrom(const PersonParticipation & object);
    PersonParticipation & operator=(const PersonParticipation & object);
    
    typedef CDM::PersonParticipation WrappedType;

	PersonParticipation & addName(const BaseDemographics & value);
	std::vector<BaseDemographics> getNames() const;
	void clearNames();
	
	PersonParticipation & addRole(const CodedValue & value);
	std::vector<CodedValue> getRoles() const;
	void clearRoles();
	
	PersonParticipation & addIdentification(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getIdentifications() const;
private:
	std::shared_ptr<CDM::PersonParticipation> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* PERSONPARTICIPATION_H_ */
