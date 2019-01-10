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
 *  ScoState.cpp
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

#include "OSCLib/Data/SDC/MDIB/ScoState.h"
#include "OSCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/SDC/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/SDC/MDIB/OperationGroup.h"

namespace SDCLib {
namespace Data {
namespace SDC {

ScoState::ScoState(
		HandleRef descriptorhandle
) : data(Defaults::ScoStateInit(
		descriptorhandle
)) {}

ScoState::operator CDM::ScoState() const {
	return *data;
}

ScoState::ScoState(const CDM::ScoState & object) : data(new CDM::ScoState(object)) {

}

ScoState::ScoState(const ScoState & object) : data(new CDM::ScoState(*object.data)) {

}

ScoState::~ScoState() {

}

void ScoState::copyFrom(const ScoState & object) {
	data = std::shared_ptr<CDM::ScoState>( new CDM::ScoState(*object.data));
}

ScoState & ScoState:: operator=(const ScoState & object) {
	copyFrom(object);
	return *this;
}


ScoState & ScoState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ScoState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter ScoState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool ScoState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
ScoState & ScoState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef ScoState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
ScoState & ScoState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ScoState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion ScoState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool ScoState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
ScoState & ScoState::setInvocationRequested(const OperationRef & value) {
	data->InvocationRequested(ConvertToCDM::convert2(value));
	return *this;
}

bool ScoState::getInvocationRequested(OperationRef & out) const {
	if (data->InvocationRequested().present()) {
		out = ConvertFromCDM::convert(data->InvocationRequested().get());
		return true;
	}
	return false;
}

OperationRef ScoState::getInvocationRequested() const {
	return ConvertFromCDM::convert(data->InvocationRequested().get());
}
	
bool ScoState::hasInvocationRequested() const {
	return data->InvocationRequested().present();
}
	
ScoState & ScoState::setInvocationRequired(const OperationRef & value) {
	data->InvocationRequired(ConvertToCDM::convert2(value));
	return *this;
}

bool ScoState::getInvocationRequired(OperationRef & out) const {
	if (data->InvocationRequired().present()) {
		out = ConvertFromCDM::convert(data->InvocationRequired().get());
		return true;
	}
	return false;
}

OperationRef ScoState::getInvocationRequired() const {
	return ConvertFromCDM::convert(data->InvocationRequired().get());
}
	
bool ScoState::hasInvocationRequired() const {
	return data->InvocationRequired().present();
}
	
ScoState & ScoState::addOperationGroup(const OperationGroup & value) {
	data->OperationGroup().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<OperationGroup> ScoState::getOperationGroupList() const {
	std::vector<OperationGroup> result;
	result.reserve(data->OperationGroup().size());
	for (const auto & value: data->OperationGroup()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ScoState::clearOperationGroupList() {
	data->OperationGroup().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

