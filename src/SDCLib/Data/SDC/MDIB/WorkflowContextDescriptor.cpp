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
 *  WorkflowContextDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/WorkflowContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


WorkflowContextDescriptor::WorkflowContextDescriptor(
		Handle handle
) : data(Defaults::WorkflowContextDescriptorInit(
		handle
))
{}

WorkflowContextDescriptor::operator CDM::WorkflowContextDescriptor() const {
	return *data;
}

WorkflowContextDescriptor::WorkflowContextDescriptor(const CDM::WorkflowContextDescriptor & object)
: data(new CDM::WorkflowContextDescriptor(object))
{ }

WorkflowContextDescriptor::WorkflowContextDescriptor(const WorkflowContextDescriptor & object)
: data(std::make_shared<CDM::WorkflowContextDescriptor>(*object.data))
{ }

void WorkflowContextDescriptor::copyFrom(const WorkflowContextDescriptor & object) {
	data = std::make_shared<CDM::WorkflowContextDescriptor>(*object.data);
}

WorkflowContextDescriptor & WorkflowContextDescriptor:: operator=(const WorkflowContextDescriptor& object) {
	copyFrom(object);
	return *this;
}


WorkflowContextDescriptor & WorkflowContextDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue WorkflowContextDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool WorkflowContextDescriptor::hasType() const {
	return data->getType().present();
}

WorkflowContextDescriptor & WorkflowContextDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle WorkflowContextDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

WorkflowContextDescriptor & WorkflowContextDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter WorkflowContextDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool WorkflowContextDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

WorkflowContextDescriptor & WorkflowContextDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification WorkflowContextDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool WorkflowContextDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

