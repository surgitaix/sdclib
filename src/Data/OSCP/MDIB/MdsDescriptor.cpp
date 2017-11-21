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
 *  Author: besting, buerger, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ClockDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/BatteryDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ApprovedJurisdictions.h"
#include "OSCLib/Data/OSCP/MDIB/VmdDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ScoDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {


MdsDescriptor::MdsDescriptor(
		Handle handle
) : data(Defaults::MdsDescriptorInit(
		handle
)) {}

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
	
MdsDescriptor & MdsDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle MdsDescriptor::getHandle() const {
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
	
MdsDescriptor & MdsDescriptor::setSco(const ScoDescriptor & value) {
	data->Sco(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getSco(ScoDescriptor & out) const {
	if (data->Sco().present()) {
		out = ConvertFromCDM::convert(data->Sco().get());
		return true;
	}
	return false;
}

ScoDescriptor MdsDescriptor::getSco() const {
	return ConvertFromCDM::convert(data->Sco().get());
}
	
bool MdsDescriptor::hasSco() const {
	return data->Sco().present();
}
	
MdsDescriptor & MdsDescriptor::setSystemContext(const SystemContextDescriptor & value) {
	data->SystemContext(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getSystemContext(SystemContextDescriptor & out) const {
	if (data->SystemContext().present()) {
		out = ConvertFromCDM::convert(data->SystemContext().get());
		return true;
	}
	return false;
}

SystemContextDescriptor MdsDescriptor::getSystemContext() const {
	return ConvertFromCDM::convert(data->SystemContext().get());
}
	
bool MdsDescriptor::hasSystemContext() const {
	return data->SystemContext().present();
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
	
MdsDescriptor & MdsDescriptor::setApprovedJurisdictions(const ApprovedJurisdictions & value) {
	data->ApprovedJurisdictions(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getApprovedJurisdictions(ApprovedJurisdictions & out) const {
	if (data->ApprovedJurisdictions().present()) {
		out = ConvertFromCDM::convert(data->ApprovedJurisdictions().get());
		return true;
	}
	return false;
}

ApprovedJurisdictions MdsDescriptor::getApprovedJurisdictions() const {
	return ConvertFromCDM::convert(data->ApprovedJurisdictions().get());
}
	
bool MdsDescriptor::hasApprovedJurisdictions() const {
	return data->ApprovedJurisdictions().present();
}
	
MdsDescriptor & MdsDescriptor::addBattery(const BatteryDescriptor & value) {
	data->Battery().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<BatteryDescriptor> MdsDescriptor::getBatteryList() const {
	std::vector<BatteryDescriptor> result;
	result.reserve(data->Battery().size());
	for (const auto & value: data->Battery()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MdsDescriptor::clearBatteryList() {
	data->Battery().clear();
}

MdsDescriptor & MdsDescriptor::addVmd(const VmdDescriptor & value) {
	data->Vmd().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<VmdDescriptor> MdsDescriptor::getVmdList() const {
	std::vector<VmdDescriptor> result;
	result.reserve(data->Vmd().size());
	for (const auto & value: data->Vmd()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MdsDescriptor::clearVmdList() {
	data->Vmd().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

