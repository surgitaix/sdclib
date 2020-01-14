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

#include "SDCLib/Data/SDC/MDIB/ScoState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/OperationGroup.h"

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

ScoState::ScoState(const CDM::ScoState & object)
: data(new CDM::ScoState(object))
{ }

ScoState::ScoState(const ScoState & object)
: data(new CDM::ScoState(*object.data))
{ }

void ScoState::copyFrom(const ScoState & object) {
	data = std::make_shared<CDM::ScoState>(*object.data);
}

ScoState & ScoState:: operator=(const ScoState & object) {
	copyFrom(object);
	return *this;
}


ScoState & ScoState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ScoState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter ScoState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}
	
bool ScoState::hasStateVersion() const {
	return data->getStateVersion().present();
}
	
ScoState & ScoState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef ScoState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}
	
ScoState & ScoState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ScoState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion ScoState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}
	
bool ScoState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}
	
ScoState & ScoState::setInvocationRequested(const OperationRef & value) {
	data->setInvocationRequested(ConvertToCDM::convert2(value));
	return *this;
}

bool ScoState::getInvocationRequested(OperationRef & out) const {
	if (data->getInvocationRequested().present()) {
		out = ConvertFromCDM::convert(data->getInvocationRequested().get());
		return true;
	}
	return false;
}

OperationRef ScoState::getInvocationRequested() const {
	return ConvertFromCDM::convert(data->getInvocationRequested().get());
}
	
bool ScoState::hasInvocationRequested() const {
	return data->getInvocationRequested().present();
}
	
ScoState & ScoState::setInvocationRequired(const OperationRef & value) {
	data->setInvocationRequired(ConvertToCDM::convert2(value));
	return *this;
}

bool ScoState::getInvocationRequired(OperationRef & out) const {
	if (data->getInvocationRequired().present()) {
		out = ConvertFromCDM::convert(data->getInvocationRequired().get());
		return true;
	}
	return false;
}

OperationRef ScoState::getInvocationRequired() const {
	return ConvertFromCDM::convert(data->getInvocationRequired().get());
}
	
bool ScoState::hasInvocationRequired() const {
	return data->getInvocationRequired().present();
}
	
ScoState & ScoState::addOperationGroup(const OperationGroup & value) {
	data->getOperationGroup().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<OperationGroup> ScoState::getOperationGroupList() const {
	std::vector<OperationGroup> result;
	result.reserve(data->getOperationGroup().size());
	for (const auto & value: data->getOperationGroup()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ScoState::clearOperationGroupList() {
	data->getOperationGroup().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

