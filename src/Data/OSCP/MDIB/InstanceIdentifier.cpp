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
 *  InstanceIdentifier.cpp
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

#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

InstanceIdentifier::InstanceIdentifier() : data(Defaults::InstanceIdentifier()) {
}

InstanceIdentifier::operator CDM::InstanceIdentifier() const {
	return *data;
}

InstanceIdentifier::InstanceIdentifier(const CDM::InstanceIdentifier & object) : data(new CDM::InstanceIdentifier(object)) {

}

InstanceIdentifier::InstanceIdentifier(const InstanceIdentifier & object) : data(new CDM::InstanceIdentifier(*object.data)) {

}

InstanceIdentifier::~InstanceIdentifier() {

}

void InstanceIdentifier::copyFrom(const InstanceIdentifier & object) {
	*data = *object.data;
}

InstanceIdentifier & InstanceIdentifier:: operator=(const InstanceIdentifier & object) {
	copyFrom(object);
	return *this;
}


InstanceIdentifier & InstanceIdentifier::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool InstanceIdentifier::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue InstanceIdentifier::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool InstanceIdentifier::hasType() const {
	return data->Type().present();
}
	
InstanceIdentifier & InstanceIdentifier::setRoot(const Root & value) {
	data->Root(ConvertToCDM::convert(value));
	return *this;
}

bool InstanceIdentifier::getRoot(Root & out) const {
	if (data->Root().present()) {
		out = ConvertFromCDM::convert(data->Root().get());
		return true;
	}
	return false;
}

Root InstanceIdentifier::getRoot() const {
	return ConvertFromCDM::convert(data->Root().get());
}
	
bool InstanceIdentifier::hasRoot() const {
	return data->Root().present();
}
	
InstanceIdentifier & InstanceIdentifier::setExtension(const Extension & value) {
	data->Extension1(ConvertToCDM::convert(value));
	return *this;
}

bool InstanceIdentifier::getExtension(Extension & out) const {
	if (data->Extension1().present()) {
		out = ConvertFromCDM::convert(data->Extension1().get());
		return true;
	}
	return false;
}

Extension InstanceIdentifier::getExtension() const {
	return ConvertFromCDM::convert(data->Extension1().get());
}
	
bool InstanceIdentifier::hasExtension() const {
	return data->Extension1().present();
}
	
InstanceIdentifier & InstanceIdentifier::addIdentifierName(const LocalizedText & value) {
	data->IdentifierName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> InstanceIdentifier::getIdentifierNameList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->IdentifierName().size());
	for (const auto & value: data->IdentifierName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void InstanceIdentifier::clearIdentifierNameList() {
	data->IdentifierName().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

