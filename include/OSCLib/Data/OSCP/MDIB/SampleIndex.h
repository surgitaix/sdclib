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
 *  SampleIndex.h
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

#ifndef SAMPLEINDEX_H_
#define SAMPLEINDEX_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class SampleIndex {
private:
	SampleIndex(const CDM::SampleIndex & object);
	operator CDM::SampleIndex() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	SampleIndex();
	SampleIndex(const SampleIndex & object);
	virtual ~SampleIndex();
    
    void copyFrom(const SampleIndex & object);
    SampleIndex & operator=(const SampleIndex & object);
    
    typedef CDM::SampleIndex WrappedType;

	int get() const;
	SampleIndex & set(const int & value); 
private:
	std::shared_ptr<CDM::SampleIndex> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* SAMPLEINDEX_H_ */
