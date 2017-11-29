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
 *  ChannelDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/ProductionSpecification.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {


ChannelDescriptor::ChannelDescriptor(
		Handle handle
) : data(Defaults::ChannelDescriptorInit(
		handle
)) {}

ChannelDescriptor::operator CDM::ChannelDescriptor() const {
	return *data;
}

ChannelDescriptor::ChannelDescriptor(const CDM::ChannelDescriptor & object) : data(new CDM::ChannelDescriptor(object)) {

}

ChannelDescriptor::ChannelDescriptor(const ChannelDescriptor & object) : data(new CDM::ChannelDescriptor(*object.data)) {

}

ChannelDescriptor::~ChannelDescriptor() {

}

void ChannelDescriptor::copyFrom(const ChannelDescriptor & object) {
	data = std::shared_ptr<CDM::ChannelDescriptor>( new CDM::ChannelDescriptor(*object.data));
}

ChannelDescriptor & ChannelDescriptor:: operator=(const ChannelDescriptor & object) {
	copyFrom(object);
	return *this;
}


ChannelDescriptor & ChannelDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue ChannelDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool ChannelDescriptor::hasType() const {
	return data->Type().present();
}
	
ChannelDescriptor & ChannelDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle ChannelDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
ChannelDescriptor & ChannelDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter ChannelDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool ChannelDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
ChannelDescriptor & ChannelDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification ChannelDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool ChannelDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
ChannelDescriptor & ChannelDescriptor::addProductionSpecification(const ProductionSpecification & value) {
	data->ProductionSpecification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ProductionSpecification> ChannelDescriptor::getProductionSpecificationList() const {
	std::vector<ProductionSpecification> result;
	result.reserve(data->ProductionSpecification().size());
	for (const auto & value: data->ProductionSpecification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ChannelDescriptor::clearProductionSpecificationList() {
	data->ProductionSpecification().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

