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
 *  ApplyAnnotationType.h
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

#ifndef APPLYANNOTATIONTYPE_H_
#define APPLYANNOTATIONTYPE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class ApplyAnnotationType {
private:
	ApplyAnnotationType(const CDM::ApplyAnnotationType & object);
	operator CDM::ApplyAnnotationType() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	ApplyAnnotationType();
	ApplyAnnotationType(const ApplyAnnotationType & object);
	virtual ~ApplyAnnotationType();
    
    void copyFrom(const ApplyAnnotationType & object);
    ApplyAnnotationType & operator=(const ApplyAnnotationType & object);
    
    typedef CDM::ApplyAnnotationType WrappedType;

	ApplyAnnotationType & setAnnotationIndex(const unsigned int & value);
	unsigned int getAnnotationIndex() const;

	ApplyAnnotationType & setSampleIndex(const unsigned int & value);
	unsigned int getSampleIndex() const;

private:
	std::shared_ptr<CDM::ApplyAnnotationType> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* APPLYANNOTATIONTYPE_H_ */
