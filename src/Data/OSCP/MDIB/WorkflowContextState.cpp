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
 *  WorkflowContextState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/WorkflowContextState.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Order.h"
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

WorkflowContextState::WorkflowContextState() : data(Defaults::WorkflowContextState()) {
}

WorkflowContextState::operator CDM::WorkflowContextState() const {
	return *data;
}

WorkflowContextState::WorkflowContextState(const CDM::WorkflowContextState & object) : data(new CDM::WorkflowContextState(object)) {

}

WorkflowContextState::WorkflowContextState(const WorkflowContextState & object) : data(new CDM::WorkflowContextState(*object.data)) {

}

WorkflowContextState::~WorkflowContextState() {

}

void WorkflowContextState::copyFrom(const WorkflowContextState & object) {
	*data = *object.data;
}

WorkflowContextState & WorkflowContextState:: operator=(const WorkflowContextState & object) {
	copyFrom(object);
	return *this;
}


WorkflowContextState & WorkflowContextState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion WorkflowContextState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool WorkflowContextState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
WorkflowContextState & WorkflowContextState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string WorkflowContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
WorkflowContextState & WorkflowContextState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter WorkflowContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool WorkflowContextState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
WorkflowContextState & WorkflowContextState::setContextAssociation(const ContextAssociation & value) {
	data->ContextAssociation(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getContextAssociation(ContextAssociation & out) const {
	if (data->ContextAssociation().present()) {
		out = ConvertFromCDM::convert(data->ContextAssociation().get());
		return true;
	}
	return false;
}

ContextAssociation WorkflowContextState::getContextAssociation() const {
	return ConvertFromCDM::convert(data->ContextAssociation().get());
}
	
bool WorkflowContextState::hasContextAssociation() const {
	return data->ContextAssociation().present();
}
	
WorkflowContextState & WorkflowContextState::setBindingMDIBVersion(const ReferencedVersion & value) {
	data->BindingMDIBVersion(ConvertToCDM::convert(value));
	return *this;
}


ReferencedVersion WorkflowContextState::getBindingMDIBVersion() const {
	return ConvertFromCDM::convert(data->BindingMDIBVersion());
}
	
WorkflowContextState & WorkflowContextState::setUnbindingMDIBVersion(const ReferencedVersion & value) {
	data->UnbindingMDIBVersion(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getUnbindingMDIBVersion(ReferencedVersion & out) const {
	if (data->UnbindingMDIBVersion().present()) {
		out = ConvertFromCDM::convert(data->UnbindingMDIBVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion WorkflowContextState::getUnbindingMDIBVersion() const {
	return ConvertFromCDM::convert(data->UnbindingMDIBVersion().get());
}
	
bool WorkflowContextState::hasUnbindingMDIBVersion() const {
	return data->UnbindingMDIBVersion().present();
}
	
WorkflowContextState & WorkflowContextState::setBindingStartTime(const Timestamp & value) {
	data->BindingStartTime(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getBindingStartTime(Timestamp & out) const {
	if (data->BindingStartTime().present()) {
		out = ConvertFromCDM::convert(data->BindingStartTime().get());
		return true;
	}
	return false;
}

Timestamp WorkflowContextState::getBindingStartTime() const {
	return ConvertFromCDM::convert(data->BindingStartTime().get());
}
	
bool WorkflowContextState::hasBindingStartTime() const {
	return data->BindingStartTime().present();
}
	
WorkflowContextState & WorkflowContextState::setBindingEndTime(const Timestamp & value) {
	data->BindingEndTime(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getBindingEndTime(Timestamp & out) const {
	if (data->BindingEndTime().present()) {
		out = ConvertFromCDM::convert(data->BindingEndTime().get());
		return true;
	}
	return false;
}

Timestamp WorkflowContextState::getBindingEndTime() const {
	return ConvertFromCDM::convert(data->BindingEndTime().get());
}
	
bool WorkflowContextState::hasBindingEndTime() const {
	return data->BindingEndTime().present();
}
	
WorkflowContextState & WorkflowContextState::addValidator(const InstanceIdentifier & value) {
	data->Validator().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> WorkflowContextState::getValidators() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Validator().size());
	for (const auto & value: data->Validator()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void WorkflowContextState::clearValidators() {
	data->Validator().clear();
}

WorkflowContextState & WorkflowContextState::addIdentification(const InstanceIdentifier & value) {
	data->Identification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> WorkflowContextState::getIdentifications() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Identification().size());
	for (const auto & value: data->Identification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void WorkflowContextState::clearIdentifications() {
	data->Identification().clear();
}

WorkflowContextState & WorkflowContextState::setOrderDetail(const Order & value) {
	data->OrderDetail(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getOrderDetail(Order & out) const {
	if (data->OrderDetail().present()) {
		out = ConvertFromCDM::convert(data->OrderDetail().get());
		return true;
	}
	return false;
}

Order WorkflowContextState::getOrderDetail() const {
	return ConvertFromCDM::convert(data->OrderDetail().get());
}
	
bool WorkflowContextState::hasOrderDetail() const {
	return data->OrderDetail().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

