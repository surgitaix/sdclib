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
 *  EnsembleContextDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/EnsembleContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


EnsembleContextDescriptor::EnsembleContextDescriptor(
		Handle handle
) : data(Defaults::EnsembleContextDescriptorInit(
		handle
))
{}

EnsembleContextDescriptor::operator CDM::EnsembleContextDescriptor() const {
	return *data;
}

EnsembleContextDescriptor::EnsembleContextDescriptor(const CDM::EnsembleContextDescriptor & object)
: data(new CDM::EnsembleContextDescriptor(object))
{ }

EnsembleContextDescriptor::EnsembleContextDescriptor(const EnsembleContextDescriptor & object)
: data(std::make_shared<CDM::EnsembleContextDescriptor>(*object.data))
{ }

void EnsembleContextDescriptor::copyFrom(const EnsembleContextDescriptor & object) {
	data = std::make_shared<CDM::EnsembleContextDescriptor>(*object.data);
}

EnsembleContextDescriptor & EnsembleContextDescriptor:: operator=(const EnsembleContextDescriptor& object) {
	copyFrom(object);
	return *this;
}


EnsembleContextDescriptor & EnsembleContextDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue EnsembleContextDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool EnsembleContextDescriptor::hasType() const {
	return data->getType().present();
}

EnsembleContextDescriptor & EnsembleContextDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle EnsembleContextDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

EnsembleContextDescriptor & EnsembleContextDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter EnsembleContextDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool EnsembleContextDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

EnsembleContextDescriptor & EnsembleContextDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification EnsembleContextDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool EnsembleContextDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

