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
 *  Relation.cpp
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

#include "OSCLib/Data/OSCP/MDIB/Relation.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"

namespace OSCLib {
namespace Data {
namespace OSCP {


Relation::Relation(
		HandleRef entries
) : data(Defaults::RelationInit(
		entries
)) {}

Relation::operator CDM::Relation() const {
	return *data;
}

Relation::Relation(const CDM::Relation & object) : data(new CDM::Relation(object)) {

}

Relation::Relation(const Relation & object) : data(new CDM::Relation(*object.data)) {

}

Relation::~Relation() {

}

void Relation::copyFrom(const Relation & object) {
	*data = *object.data;
}

Relation & Relation:: operator=(const Relation & object) {
	copyFrom(object);
	return *this;
}


Relation & Relation::setCode(const CodedValue & value) {
	data->Code(ConvertToCDM::convert(value));
	return *this;
}

bool Relation::getCode(CodedValue & out) const {
	if (data->Code().present()) {
		out = ConvertFromCDM::convert(data->Code().get());
		return true;
	}
	return false;
}

CodedValue Relation::getCode() const {
	return ConvertFromCDM::convert(data->Code().get());
}
	
bool Relation::hasCode() const {
	return data->Code().present();
}
	
Relation & Relation::setIdentification(const InstanceIdentifier & value) {
	data->Identification(ConvertToCDM::convert(value));
	return *this;
}

bool Relation::getIdentification(InstanceIdentifier & out) const {
	if (data->Identification().present()) {
		out = ConvertFromCDM::convert(data->Identification().get());
		return true;
	}
	return false;
}

InstanceIdentifier Relation::getIdentification() const {
	return ConvertFromCDM::convert(data->Identification().get());
}
	
bool Relation::hasIdentification() const {
	return data->Identification().present();
}
	
Relation & Relation::setEntries(const HandleRef & value) {
	data->Entries(ConvertToCDM::convert(value));
	return *this;
}


HandleRef Relation::getEntries() const {
	return ConvertFromCDM::convert(data->Entries());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

