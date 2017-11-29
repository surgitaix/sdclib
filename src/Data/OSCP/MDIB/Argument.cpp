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
 *  Argument.cpp
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

#include "OSCLib/Data/OSCP/MDIB/Argument.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {


Argument::Argument(
		CodedValue argname
		, 
		xml_schema::Qname arg
) : data(Defaults::ArgumentInit(
		argname
		,
		arg
)) {}

Argument::operator CDM::Argument() const {
	return *data;
}

Argument::Argument(const CDM::Argument & object) : data(new CDM::Argument(object)) {

}

Argument::Argument(const Argument & object) : data(new CDM::Argument(*object.data)) {

}

Argument::~Argument() {

}

void Argument::copyFrom(const Argument & object) {
	data = std::shared_ptr<CDM::Argument>( new CDM::Argument(*object.data));
}

Argument & Argument:: operator=(const Argument & object) {
	copyFrom(object);
	return *this;
}


Argument & Argument::setArgName(const CodedValue & value) {
	data->ArgName(ConvertToCDM::convert(value));
	return *this;
}


CodedValue Argument::getArgName() const {
	return ConvertFromCDM::convert(data->ArgName());
}
	
Argument & Argument::setArg(const xml_schema::Qname & value) {
	data->Arg(ConvertToCDM::convert(value));
	return *this;
}


xml_schema::Qname Argument::getArg() const {
	return ConvertFromCDM::convert(data->Arg());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

