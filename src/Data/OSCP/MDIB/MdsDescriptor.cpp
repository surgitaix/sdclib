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
 *  MdsDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SCODescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/VMDDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ClockDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContext.h"
#include "OSCLib/Data/OSCP/MDIB/SystemMetaData.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ProductionSpecification.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

MdsDescriptor::MdsDescriptor() : data(Defaults::MdsDescriptor()) {
}

MdsDescriptor::operator CDM::MdsDescriptor() const {
	return *data;
}

MdsDescriptor::MdsDescriptor(const CDM::MdsDescriptor & object) : data(new CDM::MdsDescriptor(object)) {

}

MdsDescriptor::MdsDescriptor(const MdsDescriptor & object) : data(new CDM::MdsDescriptor(*object.data)) {

}

MdsDescriptor::~MdsDescriptor() {

}

void MdsDescriptor::copyFrom(const MdsDescriptor & object) {
	*data = *object.data;
}

MdsDescriptor & MdsDescriptor:: operator=(const MdsDescriptor & object) {
	copyFrom(object);
	return *this;
}


MdsDescriptor & MdsDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue MdsDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool MdsDescriptor::hasType() const {
	return data->Type().present();
}
	
MdsDescriptor & MdsDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string MdsDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
MdsDescriptor & MdsDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter MdsDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool MdsDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
MdsDescriptor & MdsDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification MdsDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool MdsDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
MdsDescriptor & MdsDescriptor::addProductionSpecification(const ProductionSpecification & value) {
	data->ProductionSpecification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ProductionSpecification> MdsDescriptor::getProductionSpecifications() const {
	std::vector<ProductionSpecification> result;
	result.reserve(data->ProductionSpecification().size());
	for (const auto & value: data->ProductionSpecification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MdsDescriptor::clearProductionSpecifications() {
	data->ProductionSpecification().clear();
}

MdsDescriptor & MdsDescriptor::setAlertSystem(const AlertSystemDescriptor & value) {
	data->AlertSystem(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getAlertSystem(AlertSystemDescriptor & out) const {
	if (data->AlertSystem().present()) {
		out = ConvertFromCDM::convert(data->AlertSystem().get());
		return true;
	}
	return false;
}

AlertSystemDescriptor MdsDescriptor::getAlertSystem() const {
	return ConvertFromCDM::convert(data->AlertSystem().get());
}
	
bool MdsDescriptor::hasAlertSystem() const {
	return data->AlertSystem().present();
}
	
MdsDescriptor & MdsDescriptor::setMetaData(const SystemMetaData & value) {
	data->MetaData(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getMetaData(SystemMetaData & out) const {
	if (data->MetaData().present()) {
		out = ConvertFromCDM::convert(data->MetaData().get());
		return true;
	}
	return false;
}

SystemMetaData MdsDescriptor::getMetaData() const {
	return ConvertFromCDM::convert(data->MetaData().get());
}
	
bool MdsDescriptor::hasMetaData() const {
	return data->MetaData().present();
}
	
MdsDescriptor & MdsDescriptor::setContext(const SystemContext & value) {
	data->Context(ConvertToCDM::convert(value));
	return *this;
}


SystemContext MdsDescriptor::getContext() const {
	return ConvertFromCDM::convert(data->Context());
}
	
MdsDescriptor & MdsDescriptor::setClock(const ClockDescriptor & value) {
	data->Clock(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getClock(ClockDescriptor & out) const {
	if (data->Clock().present()) {
		out = ConvertFromCDM::convert(data->Clock().get());
		return true;
	}
	return false;
}

ClockDescriptor MdsDescriptor::getClock() const {
	return ConvertFromCDM::convert(data->Clock().get());
}
	
bool MdsDescriptor::hasClock() const {
	return data->Clock().present();
}
	
MdsDescriptor & MdsDescriptor::setSCO(const SCODescriptor & value) {
	data->SCO(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getSCO(SCODescriptor & out) const {
	if (data->SCO().present()) {
		out = ConvertFromCDM::convert(data->SCO().get());
		return true;
	}
	return false;
}

SCODescriptor MdsDescriptor::getSCO() const {
	return ConvertFromCDM::convert(data->SCO().get());
}
	
bool MdsDescriptor::hasSCO() const {
	return data->SCO().present();
}
	
MdsDescriptor & MdsDescriptor::setBattery(const BatteryDescriptor & value) {
	data->Battery(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getBattery(BatteryDescriptor & out) const {
	if (data->Battery().present()) {
		out = ConvertFromCDM::convert(data->Battery().get());
		return true;
	}
	return false;
}

BatteryDescriptor MdsDescriptor::getBattery() const {
	return ConvertFromCDM::convert(data->Battery().get());
}
	
bool MdsDescriptor::hasBattery() const {
	return data->Battery().present();
}
	
MdsDescriptor & MdsDescriptor::addVMD(const VMDDescriptor & value) {
	data->VMD().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<VMDDescriptor> MdsDescriptor::getVMDs() const {
	std::vector<VMDDescriptor> result;
	result.reserve(data->VMD().size());
	for (const auto & value: data->VMD()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MdsDescriptor::clearVMDs() {
	data->VMD().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

