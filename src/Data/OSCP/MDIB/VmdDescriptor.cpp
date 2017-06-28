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
 *  VmdDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/VmdDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/ScoDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

VmdDescriptor::VmdDescriptor() : data(Defaults::VmdDescriptor()) {
}

VmdDescriptor::operator CDM::VmdDescriptor() const {
	return *data;
}

VmdDescriptor::VmdDescriptor(const CDM::VmdDescriptor & object) : data(new CDM::VmdDescriptor(object)) {

}

VmdDescriptor::VmdDescriptor(const VmdDescriptor & object) : data(new CDM::VmdDescriptor(*object.data)) {

}

VmdDescriptor::~VmdDescriptor() {

}

void VmdDescriptor::copyFrom(const VmdDescriptor & object) {
	*data = *object.data;
}

VmdDescriptor & VmdDescriptor:: operator=(const VmdDescriptor & object) {
	copyFrom(object);
	return *this;
}


VmdDescriptor & VmdDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool VmdDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue VmdDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool VmdDescriptor::hasType() const {
	return data->Type().present();
}
	
VmdDescriptor & VmdDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle VmdDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
VmdDescriptor & VmdDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool VmdDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter VmdDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool VmdDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
VmdDescriptor & VmdDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool VmdDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification VmdDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool VmdDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
VmdDescriptor & VmdDescriptor::setSpecType(const CodedValue & value) {
	data->SpecType(ConvertToCDM::convert(value));
	return *this;
}


CodedValue VmdDescriptor::getSpecType() const {
	return ConvertFromCDM::convert(data->SpecType());
}
	
VmdDescriptor & VmdDescriptor::setProductionSpec(const std::string & value) {
	data->ProductionSpec(ConvertToCDM::convert(value));
	return *this;
}


std::string VmdDescriptor::getProductionSpec() const {
	return ConvertFromCDM::convert(data->ProductionSpec());
}
	
VmdDescriptor & VmdDescriptor::setComponentId(const InstanceIdentifier & value) {
	data->ComponentId(ConvertToCDM::convert(value));
	return *this;
}

bool VmdDescriptor::getComponentId(InstanceIdentifier & out) const {
	if (data->ComponentId().present()) {
		out = ConvertFromCDM::convert(data->ComponentId().get());
		return true;
	}
	return false;
}

InstanceIdentifier VmdDescriptor::getComponentId() const {
	return ConvertFromCDM::convert(data->ComponentId().get());
}
	
bool VmdDescriptor::hasComponentId() const {
	return data->ComponentId().present();
}
	
VmdDescriptor & VmdDescriptor::setAlertSystem(const AlertSystemDescriptor & value) {
	data->AlertSystem(ConvertToCDM::convert(value));
	return *this;
}

bool VmdDescriptor::getAlertSystem(AlertSystemDescriptor & out) const {
	if (data->AlertSystem().present()) {
		out = ConvertFromCDM::convert(data->AlertSystem().get());
		return true;
	}
	return false;
}

AlertSystemDescriptor VmdDescriptor::getAlertSystem() const {
	return ConvertFromCDM::convert(data->AlertSystem().get());
}
	
bool VmdDescriptor::hasAlertSystem() const {
	return data->AlertSystem().present();
}
	
VmdDescriptor & VmdDescriptor::setSco(const ScoDescriptor & value) {
	data->Sco(ConvertToCDM::convert(value));
	return *this;
}

bool VmdDescriptor::getSco(ScoDescriptor & out) const {
	if (data->Sco().present()) {
		out = ConvertFromCDM::convert(data->Sco().get());
		return true;
	}
	return false;
}

ScoDescriptor VmdDescriptor::getSco() const {
	return ConvertFromCDM::convert(data->Sco().get());
}
	
bool VmdDescriptor::hasSco() const {
	return data->Sco().present();
}
	
VmdDescriptor & VmdDescriptor::addChannel(const ChannelDescriptor & value) {
	data->Channel().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ChannelDescriptor> VmdDescriptor::getChannels() const {
	std::vector<ChannelDescriptor> result;
	result.reserve(data->Channel().size());
	for (const auto & value: data->Channel()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void VmdDescriptor::clearChannels() {
	data->Channel().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

