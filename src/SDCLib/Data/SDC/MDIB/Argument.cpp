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

#include "SDCLib/Data/SDC/MDIB/Argument.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


Argument::Argument(
		CodedValue argname
		,
		xml_schema::Qname arg
) : data(Defaults::ArgumentInit(
		argname
		,
		arg
))
{}

Argument::operator CDM::Argument() const {
	return *data;
}

Argument::Argument(const CDM::Argument & object)
: data(new CDM::Argument(object))
{ }

Argument::Argument(const Argument & object)
: data(std::make_shared<CDM::Argument>(*object.data))
{ }

void Argument::copyFrom(const Argument & object) {
	data = std::make_shared<CDM::Argument>(*object.data);
}

Argument & Argument:: operator=(const Argument& object) {
	copyFrom(object);
	return *this;
}


Argument & Argument::setArgName(const CodedValue & value) {
	data->setArgName(ConvertToCDM::convert(value));
	return *this;
}


CodedValue Argument::getArgName() const {
	return ConvertFromCDM::convert(data->getArgName());
}

Argument & Argument::setArg(const xml_schema::Qname & value) {
	data->setArg(ConvertToCDM::convert(value));
	return *this;
}


xml_schema::Qname Argument::getArg() const {
	return ConvertFromCDM::convert(data->getArg());
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

