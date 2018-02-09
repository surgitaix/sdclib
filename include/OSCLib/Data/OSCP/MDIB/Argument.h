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
 *  Argument.h
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

#ifndef ARGUMENT_H_
#define ARGUMENT_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace SDC {

class Argument {
private:
	Argument(const CDM::Argument & object);
	operator CDM::Argument() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	Argument(
		CodedValue argname
		, 
		xml_schema::Qname arg
	); 
private:
	Argument(){};
public:
	Argument(const Argument & object);
	virtual ~Argument();
    
    void copyFrom(const Argument & object);
    Argument & operator=(const Argument & object);
    
    typedef CDM::Argument WrappedType;

	Argument & setArgName(const CodedValue & value);
	CodedValue getArgName() const;

	Argument & setArg(const xml_schema::Qname & value);
	xml_schema::Qname getArg() const;

private:
	std::shared_ptr<CDM::Argument> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ARGUMENT_H_ */
