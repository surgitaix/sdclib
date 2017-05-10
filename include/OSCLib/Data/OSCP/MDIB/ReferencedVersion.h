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
 *  ReferencedVersion.h
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

#ifndef REFERENCEDVERSION_H_
#define REFERENCEDVERSION_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class ReferencedVersion {
private:
	ReferencedVersion(const CDM::ReferencedVersion & object);
	operator CDM::ReferencedVersion() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	ReferencedVersion();
	ReferencedVersion(const ReferencedVersion & object);
	virtual ~ReferencedVersion();
    
    void copyFrom(const ReferencedVersion & object);
    ReferencedVersion & operator=(const ReferencedVersion & object);
    
    typedef CDM::ReferencedVersion WrappedType;

	long long get() const;
	ReferencedVersion & set(const long long & value); 
private:
	std::shared_ptr<CDM::ReferencedVersion> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* REFERENCEDVERSION_H_ */
