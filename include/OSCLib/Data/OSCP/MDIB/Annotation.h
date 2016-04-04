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
 *  Annotation.h
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

#ifndef ANNOTATION_H_
#define ANNOTATION_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class Annotation {
private:
	Annotation(const CDM::Annotation & object);
	operator CDM::Annotation() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	Annotation();
	Annotation(const Annotation & object);
	virtual ~Annotation();
    
    void copyFrom(const Annotation & object);
    Annotation & operator=(const Annotation & object);
    
    typedef CDM::Annotation WrappedType;

	Annotation & setCode(const CodedValue & value);
	CodedValue getCode() const;

	Annotation & setSampleIndex(const SampleIndex & value);
	SampleIndex getSampleIndex() const;
	bool getSampleIndex(SampleIndex & out) const;
	bool hasSampleIndex() const;

private:
	std::shared_ptr<CDM::Annotation> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ANNOTATION_H_ */
