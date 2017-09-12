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
 *  Udi.cpp
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

#include "OSCLib/Data/OSCP/MDIB/Udi.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

Udi::Udi() : data(Defaults::Udi()) {
}

Udi::operator CDM::Udi() const {
	return *data;
}

Udi::Udi(const CDM::Udi & object) : data(new CDM::Udi(object)) {

}

Udi::Udi(const Udi & object) : data(new CDM::Udi(*object.data)) {

}

Udi::~Udi() {

}

void Udi::copyFrom(const Udi & object) {
	*data = *object.data;
}

Udi & Udi:: operator=(const Udi & object) {
	copyFrom(object);
	return *this;
}


Udi & Udi::setDeviceIdentifier(const std::string & value) {
	data->DeviceIdentifier(ConvertToCDM::convert(value));
	return *this;
}


std::string Udi::getDeviceIdentifier() const {
	return ConvertFromCDM::convert(data->DeviceIdentifier());
}
	
Udi & Udi::setHumanReadableForm(const std::string & value) {
	data->HumanReadableForm(ConvertToCDM::convert(value));
	return *this;
}


std::string Udi::getHumanReadableForm() const {
	return ConvertFromCDM::convert(data->HumanReadableForm());
}
	
Udi & Udi::setIssuer(const InstanceIdentifier & value) {
	data->Issuer(ConvertToCDM::convert(value));
	return *this;
}


InstanceIdentifier Udi::getIssuer() const {
	return ConvertFromCDM::convert(data->Issuer());
}
	
Udi & Udi::setJurisdiction(const InstanceIdentifier & value) {
	data->Jurisdiction(ConvertToCDM::convert(value));
	return *this;
}

bool Udi::getJurisdiction(InstanceIdentifier & out) const {
	if (data->Jurisdiction().present()) {
		out = ConvertFromCDM::convert(data->Jurisdiction().get());
		return true;
	}
	return false;
}

InstanceIdentifier Udi::getJurisdiction() const {
	return ConvertFromCDM::convert(data->Jurisdiction().get());
}
	
bool Udi::hasJurisdiction() const {
	return data->Jurisdiction().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

