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
 *  VersionCounter.h
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

#ifndef VERSIONCOUNTER_H_
#define VERSIONCOUNTER_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class VersionCounter {
private:
	VersionCounter(const CDM::VersionCounter & object);
	operator CDM::VersionCounter() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	VersionCounter();
	VersionCounter(const VersionCounter & object);
	virtual ~VersionCounter();
    
    void copyFrom(const VersionCounter & object);
    VersionCounter & operator=(const VersionCounter & object);
    
    typedef CDM::VersionCounter WrappedType;

	long long get() const;
	VersionCounter & set(const long long & value); 
private:
	std::shared_ptr<CDM::VersionCounter> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* VERSIONCOUNTER_H_ */
