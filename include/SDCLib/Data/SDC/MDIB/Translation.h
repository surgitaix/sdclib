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

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "DataModel/osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class Translation
{
private:
	Translation(const CDM::Translation & object);
	operator CDM::Translation() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	Translation(
		CodeIdentifier code
	);
private:
	Translation(){};
public:
	Translation(const Translation& object);
	virtual ~Translation() = default;

    void copyFrom(const Translation& object);
    Translation & operator=(const Translation& object);

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
	std::shared_ptr<CDM::Translation> data = nullptr;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* TRANSLATION_H_ */
