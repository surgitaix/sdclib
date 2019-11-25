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
 *  PatientContextDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/PatientContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


PatientContextDescriptor::PatientContextDescriptor(
		Handle handle
) : data(Defaults::PatientContextDescriptorInit(
		handle
)) {}

PatientContextDescriptor::operator CDM::PatientContextDescriptor() const {
	return *data;
}

PatientContextDescriptor::PatientContextDescriptor(const CDM::PatientContextDescriptor & object) : data(new CDM::PatientContextDescriptor(object)) {

}

PatientContextDescriptor::PatientContextDescriptor(const PatientContextDescriptor & object) : data(new CDM::PatientContextDescriptor(*object.data)) {

}

PatientContextDescriptor::~PatientContextDescriptor() {

}

void PatientContextDescriptor::copyFrom(const PatientContextDescriptor & object) {
	data = std::shared_ptr<CDM::PatientContextDescriptor>( new CDM::PatientContextDescriptor(*object.data));
}

PatientContextDescriptor & PatientContextDescriptor:: operator=(const PatientContextDescriptor & object) {
	copyFrom(object);
	return *this;
}


PatientContextDescriptor & PatientContextDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue PatientContextDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool PatientContextDescriptor::hasType() const {
	return data->getType().present();
}

PatientContextDescriptor & PatientContextDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle PatientContextDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

PatientContextDescriptor & PatientContextDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter PatientContextDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool PatientContextDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

PatientContextDescriptor & PatientContextDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification PatientContextDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool PatientContextDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

