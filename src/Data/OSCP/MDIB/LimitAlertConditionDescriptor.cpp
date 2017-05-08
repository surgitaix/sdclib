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
 *  LimitAlertConditionDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/CauseInfo.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

LimitAlertConditionDescriptor::LimitAlertConditionDescriptor() : data(Defaults::LimitAlertConditionDescriptor()) {
}

LimitAlertConditionDescriptor::operator CDM::LimitAlertConditionDescriptor() const {
	return *data;
}

LimitAlertConditionDescriptor::LimitAlertConditionDescriptor(const CDM::LimitAlertConditionDescriptor & object) : data(new CDM::LimitAlertConditionDescriptor(object)) {

}

LimitAlertConditionDescriptor::LimitAlertConditionDescriptor(const LimitAlertConditionDescriptor & object) : data(new CDM::LimitAlertConditionDescriptor(*object.data)) {

}

LimitAlertConditionDescriptor::~LimitAlertConditionDescriptor() {

}

void LimitAlertConditionDescriptor::copyFrom(const LimitAlertConditionDescriptor & object) {
	*data = *object.data;
}

LimitAlertConditionDescriptor & LimitAlertConditionDescriptor:: operator=(const LimitAlertConditionDescriptor & object) {
	copyFrom(object);
	return *this;
}


LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue LimitAlertConditionDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool LimitAlertConditionDescriptor::hasType() const {
	return data->Type().present();
}
	
LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string LimitAlertConditionDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter LimitAlertConditionDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool LimitAlertConditionDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::setKind(const AlertConditionKind & value) {
	data->Kind(ConvertToCDM::convert(value));
	return *this;
}


AlertConditionKind LimitAlertConditionDescriptor::getKind() const {
	return ConvertFromCDM::convert(data->Kind());
}
	
LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::setPriority(const AlertConditionPriority & value) {
	data->Priority(ConvertToCDM::convert(value));
	return *this;
}


AlertConditionPriority LimitAlertConditionDescriptor::getPriority() const {
	return ConvertFromCDM::convert(data->Priority());
}
	
LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::addSource(const std::string & value) {
	data->Source().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> LimitAlertConditionDescriptor::getSources() const {
	std::vector<std::string> result;
	result.reserve(data->Source().size());
	for (const auto & value: data->Source()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void LimitAlertConditionDescriptor::clearSources() {
	data->Source().clear();
}

LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::addCauseInfo(const CauseInfo & value) {
	data->CauseInfo().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CauseInfo> LimitAlertConditionDescriptor::getCauseInfo() const {
	std::vector<CauseInfo> result;
	result.reserve(data->CauseInfo().size());
	for (const auto & value: data->CauseInfo()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void LimitAlertConditionDescriptor::clearCauseInfo() {
	data->CauseInfo().clear();
}

LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::setMaxLimits(const Range & value) {
	data->MaxLimits(ConvertToCDM::convert(value));
	return *this;
}


Range LimitAlertConditionDescriptor::getMaxLimits() const {
	return ConvertFromCDM::convert(data->MaxLimits());
}
	
LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::setAutoLimitSupported(const bool & value) {
	data->AutoLimitSupported(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionDescriptor::getAutoLimitSupported(bool & out) const {
	if (data->AutoLimitSupported().present()) {
		out = ConvertFromCDM::convert(data->AutoLimitSupported().get());
		return true;
	}
	return false;
}

bool LimitAlertConditionDescriptor::getAutoLimitSupported() const {
	return ConvertFromCDM::convert(data->AutoLimitSupported().get());
}
	
bool LimitAlertConditionDescriptor::hasAutoLimitSupported() const {
	return data->AutoLimitSupported().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

