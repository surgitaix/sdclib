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
 *  OperatorContextDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/OperatorContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


OperatorContextDescriptor::OperatorContextDescriptor(
		Handle handle
) : data(Defaults::OperatorContextDescriptorInit(
		handle
))
{}

OperatorContextDescriptor::operator CDM::OperatorContextDescriptor() const {
	return *data;
}

OperatorContextDescriptor::OperatorContextDescriptor(const CDM::OperatorContextDescriptor & object)
: data(new CDM::OperatorContextDescriptor(object))
{ }

OperatorContextDescriptor::OperatorContextDescriptor(const OperatorContextDescriptor & object)
: data(std::make_shared<CDM::OperatorContextDescriptor>(*object.data))
{ }

void OperatorContextDescriptor::copyFrom(const OperatorContextDescriptor & object) {
	data = std::make_shared<CDM::OperatorContextDescriptor>(*object.data);
}

OperatorContextDescriptor & OperatorContextDescriptor:: operator=(const OperatorContextDescriptor& object) {
	copyFrom(object);
	return *this;
}


OperatorContextDescriptor & OperatorContextDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue OperatorContextDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool OperatorContextDescriptor::hasType() const {
	return data->getType().present();
}

OperatorContextDescriptor & OperatorContextDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle OperatorContextDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

OperatorContextDescriptor & OperatorContextDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter OperatorContextDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool OperatorContextDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

OperatorContextDescriptor & OperatorContextDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification OperatorContextDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool OperatorContextDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

