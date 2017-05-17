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
 *  RealTimeValueType.h
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

#ifndef REALTIMEVALUETYPE_H_
#define REALTIMEVALUETYPE_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class RealTimeValueType {
private:
	RealTimeValueType(const CDM::RealTimeValueType & object);
	operator CDM::RealTimeValueType() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	RealTimeValueType();
	RealTimeValueType(const RealTimeValueType & object);
	virtual ~RealTimeValueType();
    
    void copyFrom(const RealTimeValueType & object);
    RealTimeValueType & operator=(const RealTimeValueType & object);
    
    typedef CDM::RealTimeValueType WrappedType;

	RealTimeValueType & setValues(const std::vector<double> & values);
	std::vector<double> getValues() const;
private:
	std::shared_ptr<CDM::RealTimeValueType> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* REALTIMEVALUETYPE_H_ */
