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
 *  RetrievabilityInfo.h
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

#ifndef RETRIEVABILITYINFO_H_
#define RETRIEVABILITYINFO_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class RetrievabilityInfo {
private:
	RetrievabilityInfo(const CDM::RetrievabilityInfo & object);
	operator CDM::RetrievabilityInfo() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	RetrievabilityInfo();
	RetrievabilityInfo(const RetrievabilityInfo & object);
	virtual ~RetrievabilityInfo();
    
    void copyFrom(const RetrievabilityInfo & object);
    RetrievabilityInfo & operator=(const RetrievabilityInfo & object);
    
    typedef CDM::RetrievabilityInfo WrappedType;

	RetrievabilityInfo & setMethod(const RetrievabilityMethod & value);
	RetrievabilityMethod getMethod() const;

	RetrievabilityInfo & setUpdatePeriod(const xml_schema::Duration & value);
	xml_schema::Duration getUpdatePeriod() const;

private:
	std::shared_ptr<CDM::RetrievabilityInfo> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* RETRIEVABILITYINFO_H_ */
