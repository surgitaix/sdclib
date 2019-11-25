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
 *  MeansContextDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/MeansContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


MeansContextDescriptor::MeansContextDescriptor(
		Handle handle
) : data(Defaults::MeansContextDescriptorInit(
		handle
)) {}

MeansContextDescriptor::operator CDM::MeansContextDescriptor() const {
	return *data;
}

MeansContextDescriptor::MeansContextDescriptor(const CDM::MeansContextDescriptor & object) : data(new CDM::MeansContextDescriptor(object)) {

}

MeansContextDescriptor::MeansContextDescriptor(const MeansContextDescriptor & object) : data(new CDM::MeansContextDescriptor(*object.data)) {

}

MeansContextDescriptor::~MeansContextDescriptor() {

}

void MeansContextDescriptor::copyFrom(const MeansContextDescriptor & object) {
	data = std::shared_ptr<CDM::MeansContextDescriptor>( new CDM::MeansContextDescriptor(*object.data));
}

MeansContextDescriptor & MeansContextDescriptor:: operator=(const MeansContextDescriptor & object) {
	copyFrom(object);
	return *this;
}


MeansContextDescriptor & MeansContextDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue MeansContextDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool MeansContextDescriptor::hasType() const {
	return data->getType().present();
}

MeansContextDescriptor & MeansContextDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle MeansContextDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

MeansContextDescriptor & MeansContextDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter MeansContextDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool MeansContextDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

MeansContextDescriptor & MeansContextDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification MeansContextDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool MeansContextDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

