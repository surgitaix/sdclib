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
 *  VMDDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/VMDDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ProductionSpecification.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

VMDDescriptor::VMDDescriptor() : data(Defaults::VMDDescriptor()) {
}

VMDDescriptor::operator CDM::VMDDescriptor() const {
	return *data;
}

VMDDescriptor::VMDDescriptor(const CDM::VMDDescriptor & object) : data(new CDM::VMDDescriptor(object)) {

}

VMDDescriptor::VMDDescriptor(const VMDDescriptor & object) : data(new CDM::VMDDescriptor(*object.data)) {

}

VMDDescriptor::~VMDDescriptor() {

}

void VMDDescriptor::copyFrom(const VMDDescriptor & object) {
	*data = *object.data;
}

VMDDescriptor & VMDDescriptor:: operator=(const VMDDescriptor & object) {
	copyFrom(object);
	return *this;
}


VMDDescriptor & VMDDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool VMDDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue VMDDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool VMDDescriptor::hasType() const {
	return data->Type().present();
}
	
VMDDescriptor & VMDDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string VMDDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
VMDDescriptor & VMDDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool VMDDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter VMDDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool VMDDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
VMDDescriptor & VMDDescriptor::setIntendedUse(const IntendedUse & value) {
	data->IntendedUse(ConvertToCDM::convert(value));
	return *this;
}

bool VMDDescriptor::getIntendedUse(IntendedUse & out) const {
	if (data->IntendedUse().present()) {
		out = ConvertFromCDM::convert(data->IntendedUse().get());
		return true;
	}
	return false;
}

IntendedUse VMDDescriptor::getIntendedUse() const {
	return ConvertFromCDM::convert(data->IntendedUse().get());
}
	
bool VMDDescriptor::hasIntendedUse() const {
	return data->IntendedUse().present();
}
	
VMDDescriptor & VMDDescriptor::addProductionSpecification(const ProductionSpecification & value) {
	data->ProductionSpecification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ProductionSpecification> VMDDescriptor::getProductionSpecifications() const {
	std::vector<ProductionSpecification> result;
	result.reserve(data->ProductionSpecification().size());
	for (const auto & value: data->ProductionSpecification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void VMDDescriptor::clearProductionSpecifications() {
	data->ProductionSpecification().clear();
}

VMDDescriptor & VMDDescriptor::setAlertSystem(const AlertSystemDescriptor & value) {
	data->AlertSystem(ConvertToCDM::convert(value));
	return *this;
}

bool VMDDescriptor::getAlertSystem(AlertSystemDescriptor & out) const {
	if (data->AlertSystem().present()) {
		out = ConvertFromCDM::convert(data->AlertSystem().get());
		return true;
	}
	return false;
}

AlertSystemDescriptor VMDDescriptor::getAlertSystem() const {
	return ConvertFromCDM::convert(data->AlertSystem().get());
}
	
bool VMDDescriptor::hasAlertSystem() const {
	return data->AlertSystem().present();
}
	
VMDDescriptor & VMDDescriptor::addChannel(const ChannelDescriptor & value) {
	data->Channel().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ChannelDescriptor> VMDDescriptor::getChannels() const {
	std::vector<ChannelDescriptor> result;
	result.reserve(data->Channel().size());
	for (const auto & value: data->Channel()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void VMDDescriptor::clearChannels() {
	data->Channel().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

