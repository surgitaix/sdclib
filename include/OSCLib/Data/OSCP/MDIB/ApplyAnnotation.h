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
 *  ApplyAnnotation.h
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

#ifndef APPLYANNOTATION_H_
#define APPLYANNOTATION_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class ApplyAnnotation {
private:
	ApplyAnnotation(const CDM::ApplyAnnotation & object);
	operator CDM::ApplyAnnotation() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class OSCPProvider;
	friend class OSCPConsumer;
public:
	ApplyAnnotation(
		unsigned int annotationindex
		, 
		unsigned int sampleindex
	); 
private:
	ApplyAnnotation(){};
public:
	ApplyAnnotation(const ApplyAnnotation & object);
	virtual ~ApplyAnnotation();
    
    void copyFrom(const ApplyAnnotation & object);
    ApplyAnnotation & operator=(const ApplyAnnotation & object);
    
    typedef CDM::ApplyAnnotation WrappedType;

	ApplyAnnotation & setAnnotationIndex(const unsigned int & value);
	unsigned int getAnnotationIndex() const;

	ApplyAnnotation & setSampleIndex(const unsigned int & value);
	unsigned int getSampleIndex() const;

private:
	std::shared_ptr<CDM::ApplyAnnotation> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* APPLYANNOTATION_H_ */
