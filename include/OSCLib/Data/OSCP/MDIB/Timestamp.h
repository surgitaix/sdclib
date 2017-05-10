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
 *  Timestamp.h
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

#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class Timestamp {
private:
	Timestamp(const CDM::Timestamp & object);
	operator CDM::Timestamp() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	Timestamp();
	Timestamp(const Timestamp & object);
	virtual ~Timestamp();
    
    void copyFrom(const Timestamp & object);
    Timestamp & operator=(const Timestamp & object);
    
    typedef CDM::Timestamp WrappedType;

	long long get() const;
	Timestamp & set(const long long & value); 
private:
	std::shared_ptr<CDM::Timestamp> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* TIMESTAMP_H_ */
