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
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

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


InstanceIdentifier & InstanceIdentifier::setroot(const std::string & value) {
	data->root(ConvertToCDM::convert(value));
	return *this;
}


std::string InstanceIdentifier::getroot() const {
	return ConvertFromCDM::convert(data->root());
}
	
InstanceIdentifier & InstanceIdentifier::setextension(const std::string & value) {
	data->extension(ConvertToCDM::convert(value));
	return *this;
}

bool InstanceIdentifier::getextension(std::string & out) const {
	if (data->extension().present()) {
		out = ConvertFromCDM::convert(data->extension().get());
		return true;
	}
	return false;
}

std::string InstanceIdentifier::getextension() const {
	return ConvertFromCDM::convert(data->extension().get());
}
	
bool InstanceIdentifier::hasextension() const {
	return data->extension().present();
}
	
InstanceIdentifier & InstanceIdentifier::addIdentifierName(const LocalizedText & value) {
	data->IdentifierName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> InstanceIdentifier::getIdentifierNames() const {
	std::vector<LocalizedText> result;
	result.reserve(data->IdentifierName().size());
	for (const auto & value: data->IdentifierName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void InstanceIdentifier::clearIdentifierNames() {
	data->IdentifierName().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

