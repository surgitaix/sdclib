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
 *  Base64Binary.h
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

#ifndef BASE64BINARY_H_
#define BASE64BINARY_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class Base64Binary {
private:
	Base64Binary(const CDM::Base64Binary & object);
	operator CDM::Base64Binary() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	Base64Binary();
	Base64Binary(const Base64Binary & object);
	virtual ~Base64Binary();
    
    void copyFrom(const Base64Binary & object);
    Base64Binary & operator=(const Base64Binary & object);
    
    typedef CDM::Base64Binary WrappedType;

	std::vector<char> getData() const;
	Base64Binary & setData(const std::vector<char> & source);
private:
	std::shared_ptr<CDM::Base64Binary> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* BASE64BINARY_H_ */
