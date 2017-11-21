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
 *  Translation.h
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

#ifndef TRANSLATION_H_
#define TRANSLATION_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class Translation {
private:
	Translation(const CDM::Translation & object);
	operator CDM::Translation() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	Translation(
		CodeIdentifier code
	); 
	Translation() = delete;
	Translation(const Translation & object);
	virtual ~Translation();
    
    void copyFrom(const Translation & object);
    Translation & operator=(const Translation & object);
    
    typedef CDM::Translation WrappedType;

	Translation & setCode(const CodeIdentifier & value);
	CodeIdentifier getCode() const;

	Translation & setCodingSystem(const xml_schema::Uri & value);
	xml_schema::Uri getCodingSystem() const;
	bool getCodingSystem(xml_schema::Uri & out) const;
	bool hasCodingSystem() const;

	Translation & setCodingSystemVersion(const std::string & value);
	std::string getCodingSystemVersion() const;
	bool getCodingSystemVersion(std::string & out) const;
	bool hasCodingSystemVersion() const;

private:
	std::shared_ptr<CDM::Translation> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* TRANSLATION_H_ */
