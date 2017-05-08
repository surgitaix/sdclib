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
 *  HydraMDSDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/HydraMDSDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SCODescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/VMDDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ClockDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContext.h"
#include "OSCLib/Data/OSCP/MDIB/SystemMetaData.h"
#include "OSCLib/Data/OSCP/MDIB/ProductionSpecification.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

HydraMDSDescriptor::HydraMDSDescriptor() : data(Defaults::HydraMDSDescriptor()) {
}

HydraMDSDescriptor::operator CDM::HydraMDSDescriptor() const {
	return *data;
}

HydraMDSDescriptor::HydraMDSDescriptor(const CDM::HydraMDSDescriptor & object) : data(new CDM::HydraMDSDescriptor(object)) {

}

HydraMDSDescriptor::HydraMDSDescriptor(const HydraMDSDescriptor & object) : data(new CDM::HydraMDSDescriptor(*object.data)) {

}

HydraMDSDescriptor::~HydraMDSDescriptor() {

}

void HydraMDSDescriptor::copyFrom(const HydraMDSDescriptor & object) {
	*data = *object.data;
}

HydraMDSDescriptor & HydraMDSDescriptor:: operator=(const HydraMDSDescriptor & object) {
	copyFrom(object);
	return *this;
}


HydraMDSDescriptor & HydraMDSDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool HydraMDSDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue HydraMDSDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool HydraMDSDescriptor::hasType() const {
	return data->Type().present();
}
	
HydraMDSDescriptor & HydraMDSDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string HydraMDSDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
HydraMDSDescriptor & HydraMDSDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool HydraMDSDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter HydraMDSDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool HydraMDSDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
HydraMDSDescriptor & HydraMDSDescriptor::addProductionSpecification(const ProductionSpecification & value) {
	data->ProductionSpecification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ProductionSpecification> HydraMDSDescriptor::getProductionSpecifications() const {
	std::vector<ProductionSpecification> result;
	result.reserve(data->ProductionSpecification().size());
	for (const auto & value: data->ProductionSpecification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void HydraMDSDescriptor::clearProductionSpecifications() {
	data->ProductionSpecification().clear();
}

HydraMDSDescriptor & HydraMDSDescriptor::setMetaData(const SystemMetaData & value) {
	data->MetaData(ConvertToCDM::convert(value));
	return *this;
}

bool HydraMDSDescriptor::getMetaData(SystemMetaData & out) const {
	if (data->MetaData().present()) {
		out = ConvertFromCDM::convert(data->MetaData().get());
		return true;
	}
	return false;
}

SystemMetaData HydraMDSDescriptor::getMetaData() const {
	return ConvertFromCDM::convert(data->MetaData().get());
}
	
bool HydraMDSDescriptor::hasMetaData() const {
	return data->MetaData().present();
}
	
HydraMDSDescriptor & HydraMDSDescriptor::setContext(const SystemContext & value) {
	data->Context(ConvertToCDM::convert(value));
	return *this;
}


SystemContext HydraMDSDescriptor::getContext() const {
	return ConvertFromCDM::convert(data->Context());
}
	
HydraMDSDescriptor & HydraMDSDescriptor::setClock(const ClockDescriptor & value) {
	data->Clock(ConvertToCDM::convert(value));
	return *this;
}

bool HydraMDSDescriptor::getClock(ClockDescriptor & out) const {
	if (data->Clock().present()) {
		out = ConvertFromCDM::convert(data->Clock().get());
		return true;
	}
	return false;
}

ClockDescriptor HydraMDSDescriptor::getClock() const {
	return ConvertFromCDM::convert(data->Clock().get());
}
	
bool HydraMDSDescriptor::hasClock() const {
	return data->Clock().present();
}
	
HydraMDSDescriptor & HydraMDSDescriptor::setSCO(const SCODescriptor & value) {
	data->SCO(ConvertToCDM::convert(value));
	return *this;
}

bool HydraMDSDescriptor::getSCO(SCODescriptor & out) const {
	if (data->SCO().present()) {
		out = ConvertFromCDM::convert(data->SCO().get());
		return true;
	}
	return false;
}

SCODescriptor HydraMDSDescriptor::getSCO() const {
	return ConvertFromCDM::convert(data->SCO().get());
}
	
bool HydraMDSDescriptor::hasSCO() const {
	return data->SCO().present();
}
	
HydraMDSDescriptor & HydraMDSDescriptor::setAlertSystem(const AlertSystemDescriptor & value) {
	data->AlertSystem(ConvertToCDM::convert(value));
	return *this;
}

bool HydraMDSDescriptor::getAlertSystem(AlertSystemDescriptor & out) const {
	if (data->AlertSystem().present()) {
		out = ConvertFromCDM::convert(data->AlertSystem().get());
		return true;
	}
	return false;
}

AlertSystemDescriptor HydraMDSDescriptor::getAlertSystem() const {
	return ConvertFromCDM::convert(data->AlertSystem().get());
}
	
bool HydraMDSDescriptor::hasAlertSystem() const {
	return data->AlertSystem().present();
}
	
HydraMDSDescriptor & HydraMDSDescriptor::addVMD(const VMDDescriptor & value) {
	data->VMD().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<VMDDescriptor> HydraMDSDescriptor::getVMDs() const {
	std::vector<VMDDescriptor> result;
	result.reserve(data->VMD().size());
	for (const auto & value: data->VMD()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void HydraMDSDescriptor::clearVMDs() {
	data->VMD().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

