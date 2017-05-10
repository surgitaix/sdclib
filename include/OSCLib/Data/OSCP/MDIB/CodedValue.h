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
 *  CodedValue.h
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

#ifndef CODEDVALUE_H_
#define CODEDVALUE_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class CodedValue {
private:
	CodedValue(const CDM::CodedValue & object);
	operator CDM::CodedValue() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	CodedValue();
	CodedValue(const CodedValue & object);
	virtual ~CodedValue();
    
    void copyFrom(const CodedValue & object);
    CodedValue & operator=(const CodedValue & object);
    
    typedef CDM::CodedValue WrappedType;

	CodedValue & setCodingSystemId(const std::string & value);
	std::string getCodingSystemId() const;
	bool getCodingSystemId(std::string & out) const;
	bool hasCodingSystemId() const;

	CodedValue & setVersionId(const std::string & value);
	std::string getVersionId() const;
	bool getVersionId(std::string & out) const;
	bool hasVersionId() const;

	CodedValue & setCodeId(const std::string & value);
	std::string getCodeId() const;

	CodedValue & addCodingSystemName(const LocalizedText & value);
	std::vector<LocalizedText> getCodingSystemNames() const;
	void clearCodingSystemNames();
	
	CodedValue & addConceptDescription(const LocalizedText & value);
	std::vector<LocalizedText> getConceptDescriptions() const;
	void clearConceptDescriptions();
	
private:
	std::shared_ptr<CDM::CodedValue> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* CODEDVALUE_H_ */
