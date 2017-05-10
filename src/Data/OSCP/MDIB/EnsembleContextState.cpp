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
 *  EnsembleContextState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/EnsembleContextState.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/ReferencedVersion.h"
#include "OSCLib/Data/OSCP/MDIB/Timestamp.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/ReferencedVersion.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

EnsembleContextState::EnsembleContextState() : data(Defaults::EnsembleContextState()) {
}

EnsembleContextState::operator CDM::EnsembleContextState() const {
	return *data;
}

EnsembleContextState::EnsembleContextState(const CDM::EnsembleContextState & object) : data(new CDM::EnsembleContextState(object)) {

}

EnsembleContextState::EnsembleContextState(const EnsembleContextState & object) : data(new CDM::EnsembleContextState(*object.data)) {

}

EnsembleContextState::~EnsembleContextState() {

}

void EnsembleContextState::copyFrom(const EnsembleContextState & object) {
	*data = *object.data;
}

EnsembleContextState & EnsembleContextState:: operator=(const EnsembleContextState & object) {
	copyFrom(object);
	return *this;
}


EnsembleContextState & EnsembleContextState::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getHandle(std::string & out) const {
	if (data->Handle().present()) {
		out = ConvertFromCDM::convert(data->Handle().get());
		return true;
	}
	return false;
}

std::string EnsembleContextState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle().get());
}
	
bool EnsembleContextState::hasHandle() const {
	return data->Handle().present();
}
	
EnsembleContextState & EnsembleContextState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string EnsembleContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
EnsembleContextState & EnsembleContextState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter EnsembleContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool EnsembleContextState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
EnsembleContextState & EnsembleContextState::setContextAssociation(const ContextAssociation & value) {
	data->ContextAssociation(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getContextAssociation(ContextAssociation & out) const {
	if (data->ContextAssociation().present()) {
		out = ConvertFromCDM::convert(data->ContextAssociation().get());
		return true;
	}
	return false;
}

ContextAssociation EnsembleContextState::getContextAssociation() const {
	return ConvertFromCDM::convert(data->ContextAssociation().get());
}
	
bool EnsembleContextState::hasContextAssociation() const {
	return data->ContextAssociation().present();
}
	
EnsembleContextState & EnsembleContextState::setBindingMDIBVersion(const ReferencedVersion & value) {
	data->BindingMDIBVersion(ConvertToCDM::convert(value));
	return *this;
}


ReferencedVersion EnsembleContextState::getBindingMDIBVersion() const {
	return ConvertFromCDM::convert(data->BindingMDIBVersion());
}
	
EnsembleContextState & EnsembleContextState::setUnbindingMDIBVersion(const ReferencedVersion & value) {
	data->UnbindingMDIBVersion(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getUnbindingMDIBVersion(ReferencedVersion & out) const {
	if (data->UnbindingMDIBVersion().present()) {
		out = ConvertFromCDM::convert(data->UnbindingMDIBVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion EnsembleContextState::getUnbindingMDIBVersion() const {
	return ConvertFromCDM::convert(data->UnbindingMDIBVersion().get());
}
	
bool EnsembleContextState::hasUnbindingMDIBVersion() const {
	return data->UnbindingMDIBVersion().present();
}
	
EnsembleContextState & EnsembleContextState::setBindingStartTime(const Timestamp & value) {
	data->BindingStartTime(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getBindingStartTime(Timestamp & out) const {
	if (data->BindingStartTime().present()) {
		out = ConvertFromCDM::convert(data->BindingStartTime().get());
		return true;
	}
	return false;
}

Timestamp EnsembleContextState::getBindingStartTime() const {
	return ConvertFromCDM::convert(data->BindingStartTime().get());
}
	
bool EnsembleContextState::hasBindingStartTime() const {
	return data->BindingStartTime().present();
}
	
EnsembleContextState & EnsembleContextState::setBindingEndTime(const Timestamp & value) {
	data->BindingEndTime(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getBindingEndTime(Timestamp & out) const {
	if (data->BindingEndTime().present()) {
		out = ConvertFromCDM::convert(data->BindingEndTime().get());
		return true;
	}
	return false;
}

Timestamp EnsembleContextState::getBindingEndTime() const {
	return ConvertFromCDM::convert(data->BindingEndTime().get());
}
	
bool EnsembleContextState::hasBindingEndTime() const {
	return data->BindingEndTime().present();
}
	
EnsembleContextState & EnsembleContextState::addValidator(const InstanceIdentifier & value) {
	data->Validator().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> EnsembleContextState::getValidators() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Validator().size());
	for (const auto & value: data->Validator()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void EnsembleContextState::clearValidators() {
	data->Validator().clear();
}

EnsembleContextState & EnsembleContextState::addIdentification(const InstanceIdentifier & value) {
	data->Identification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> EnsembleContextState::getIdentifications() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Identification().size());
	for (const auto & value: data->Identification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void EnsembleContextState::clearIdentifications() {
	data->Identification().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

