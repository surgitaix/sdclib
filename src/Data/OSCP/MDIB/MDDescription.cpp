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
 *  MDDescription.cpp
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

#include "OSCLib/Data/OSCP/MDIB/MDDescription.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

MDDescription::MDDescription() : data(Defaults::MDDescription()) {
}

MDDescription::operator CDM::MDDescription() const {
	return *data;
}

MDDescription::MDDescription(const CDM::MDDescription & object) : data(new CDM::MDDescription(object)) {

}

MDDescription::MDDescription(const MDDescription & object) : data(new CDM::MDDescription(*object.data)) {

}

MDDescription::~MDDescription() {

}

void MDDescription::copyFrom(const MDDescription & object) {
	*data = *object.data;
}

MDDescription & MDDescription:: operator=(const MDDescription & object) {
	copyFrom(object);
	return *this;
}


MDDescription & MDDescription::setDescriptionVersion(const VersionCounter & value) {
	data->DescriptionVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MDDescription::getDescriptionVersion(VersionCounter & out) const {
	if (data->DescriptionVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptionVersion().get());
		return true;
	}
	return false;
}

VersionCounter MDDescription::getDescriptionVersion() const {
	return ConvertFromCDM::convert(data->DescriptionVersion().get());
}
	
bool MDDescription::hasDescriptionVersion() const {
	return data->DescriptionVersion().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

