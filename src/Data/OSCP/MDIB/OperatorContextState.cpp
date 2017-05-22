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
 *  OperatorContextState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/OperatorContextState.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/ReferencedVersion.h"
#include "OSCLib/Data/OSCP/MDIB/Timestamp.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/ReferencedVersion.h"
#include "OSCLib/Data/OSCP/MDIB/ReferencedVersion.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OperatorContextState::OperatorContextState() : data(Defaults::OperatorContextState()) {
}

OperatorContextState::operator CDM::OperatorContextState() const {
	return *data;
}

OperatorContextState::OperatorContextState(const CDM::OperatorContextState & object) : data(new CDM::OperatorContextState(object)) {

}

OperatorContextState::OperatorContextState(const OperatorContextState & object) : data(new CDM::OperatorContextState(*object.data)) {

}

OperatorContextState::~OperatorContextState() {

}

void OperatorContextState::copyFrom(const OperatorContextState & object) {
	*data = *object.data;
}

OperatorContextState & OperatorContextState:: operator=(const OperatorContextState & object) {
	copyFrom(object);
	return *this;
}


OperatorContextState & OperatorContextState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion OperatorContextState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool OperatorContextState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
OperatorContextState & OperatorContextState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string OperatorContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
OperatorContextState & OperatorContextState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter OperatorContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool OperatorContextState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
OperatorContextState & OperatorContextState::setContextAssociation(const ContextAssociation & value) {
	data->ContextAssociation(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getContextAssociation(ContextAssociation & out) const {
	if (data->ContextAssociation().present()) {
		out = ConvertFromCDM::convert(data->ContextAssociation().get());
		return true;
	}
	return false;
}

ContextAssociation OperatorContextState::getContextAssociation() const {
	return ConvertFromCDM::convert(data->ContextAssociation().get());
}
	
bool OperatorContextState::hasContextAssociation() const {
	return data->ContextAssociation().present();
}
	
OperatorContextState & OperatorContextState::setBindingMDIBVersion(const ReferencedVersion & value) {
	data->BindingMDIBVersion(ConvertToCDM::convert(value));
	return *this;
}


ReferencedVersion OperatorContextState::getBindingMDIBVersion() const {
	return ConvertFromCDM::convert(data->BindingMDIBVersion());
}
	
OperatorContextState & OperatorContextState::setUnbindingMDIBVersion(const ReferencedVersion & value) {
	data->UnbindingMDIBVersion(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getUnbindingMDIBVersion(ReferencedVersion & out) const {
	if (data->UnbindingMDIBVersion().present()) {
		out = ConvertFromCDM::convert(data->UnbindingMDIBVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion OperatorContextState::getUnbindingMDIBVersion() const {
	return ConvertFromCDM::convert(data->UnbindingMDIBVersion().get());
}
	
bool OperatorContextState::hasUnbindingMDIBVersion() const {
	return data->UnbindingMDIBVersion().present();
}
	
OperatorContextState & OperatorContextState::setBindingStartTime(const Timestamp & value) {
	data->BindingStartTime(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getBindingStartTime(Timestamp & out) const {
	if (data->BindingStartTime().present()) {
		out = ConvertFromCDM::convert(data->BindingStartTime().get());
		return true;
	}
	return false;
}

Timestamp OperatorContextState::getBindingStartTime() const {
	return ConvertFromCDM::convert(data->BindingStartTime().get());
}
	
bool OperatorContextState::hasBindingStartTime() const {
	return data->BindingStartTime().present();
}
	
OperatorContextState & OperatorContextState::setBindingEndTime(const Timestamp & value) {
	data->BindingEndTime(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getBindingEndTime(Timestamp & out) const {
	if (data->BindingEndTime().present()) {
		out = ConvertFromCDM::convert(data->BindingEndTime().get());
		return true;
	}
	return false;
}

Timestamp OperatorContextState::getBindingEndTime() const {
	return ConvertFromCDM::convert(data->BindingEndTime().get());
}
	
bool OperatorContextState::hasBindingEndTime() const {
	return data->BindingEndTime().present();
}
	
OperatorContextState & OperatorContextState::addValidator(const InstanceIdentifier & value) {
	data->Validator().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> OperatorContextState::getValidators() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Validator().size());
	for (const auto & value: data->Validator()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void OperatorContextState::clearValidators() {
	data->Validator().clear();
}

OperatorContextState & OperatorContextState::addIdentification(const InstanceIdentifier & value) {
	data->Identification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> OperatorContextState::getIdentifications() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Identification().size());
	for (const auto & value: data->Identification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void OperatorContextState::clearIdentifications() {
	data->Identification().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

