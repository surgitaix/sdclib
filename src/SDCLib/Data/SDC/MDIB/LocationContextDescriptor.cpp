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
 *  LocationContextDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/LocationContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


LocationContextDescriptor::LocationContextDescriptor(
		Handle handle
) : data(Defaults::LocationContextDescriptorInit(
		handle
))
{}

LocationContextDescriptor::operator CDM::LocationContextDescriptor() const {
	return *data;
}

LocationContextDescriptor::LocationContextDescriptor(const CDM::LocationContextDescriptor & object)
: data(new CDM::LocationContextDescriptor(object))
{ }

LocationContextDescriptor::LocationContextDescriptor(const LocationContextDescriptor & object)
: data(std::make_shared<CDM::LocationContextDescriptor>(*object.data))
{ }

void LocationContextDescriptor::copyFrom(const LocationContextDescriptor & object) {
	data = std::make_shared<CDM::LocationContextDescriptor>(*object.data);
}

LocationContextDescriptor & LocationContextDescriptor:: operator=(const LocationContextDescriptor& object) {
	copyFrom(object);
	return *this;
}


LocationContextDescriptor & LocationContextDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue LocationContextDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool LocationContextDescriptor::hasType() const {
	return data->getType().present();
}

LocationContextDescriptor & LocationContextDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle LocationContextDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

LocationContextDescriptor & LocationContextDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter LocationContextDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool LocationContextDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

LocationContextDescriptor & LocationContextDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification LocationContextDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool LocationContextDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

