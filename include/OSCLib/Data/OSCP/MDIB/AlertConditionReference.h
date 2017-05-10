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
 *  AlertConditionReference.h
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

#ifndef ALERTCONDITIONREFERENCE_H_
#define ALERTCONDITIONREFERENCE_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class AlertConditionReference {
private:
	AlertConditionReference(const CDM::AlertConditionReference & object);
	operator CDM::AlertConditionReference() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	AlertConditionReference();
	AlertConditionReference(const AlertConditionReference & object);
	virtual ~AlertConditionReference();
    
    void copyFrom(const AlertConditionReference & object);
    AlertConditionReference & operator=(const AlertConditionReference & object);
    
    typedef CDM::AlertConditionReference WrappedType;

	AlertConditionReference & addHandle(const std::string & source);
	std::vector<std::string> getHandles() const;
private:
	std::shared_ptr<CDM::AlertConditionReference> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ALERTCONDITIONREFERENCE_H_ */
