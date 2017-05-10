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
 *  SystemContext.cpp
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

#include "OSCLib/Data/OSCP/MDIB/SystemContext.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/EnsembleContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextDescriptor.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

SystemContext::SystemContext() : data(Defaults::SystemContext()) {
}

SystemContext::operator CDM::SystemContext() const {
	return *data;
}

SystemContext::SystemContext(const CDM::SystemContext & object) : data(new CDM::SystemContext(object)) {

}

SystemContext::SystemContext(const SystemContext & object) : data(new CDM::SystemContext(*object.data)) {

}

SystemContext::~SystemContext() {

}

void SystemContext::copyFrom(const SystemContext & object) {
	*data = *object.data;
}

SystemContext & SystemContext:: operator=(const SystemContext & object) {
	copyFrom(object);
	return *this;
}


SystemContext & SystemContext::setEnsembleContext(const EnsembleContextDescriptor & value) {
	data->EnsembleContext(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContext::getEnsembleContext(EnsembleContextDescriptor & out) const {
	if (data->EnsembleContext().present()) {
		out = ConvertFromCDM::convert(data->EnsembleContext().get());
		return true;
	}
	return false;
}

EnsembleContextDescriptor SystemContext::getEnsembleContext() const {
	return ConvertFromCDM::convert(data->EnsembleContext().get());
}
	
bool SystemContext::hasEnsembleContext() const {
	return data->EnsembleContext().present();
}
	
SystemContext & SystemContext::setLocationContext(const LocationContextDescriptor & value) {
	data->LocationContext(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContext::getLocationContext(LocationContextDescriptor & out) const {
	if (data->LocationContext().present()) {
		out = ConvertFromCDM::convert(data->LocationContext().get());
		return true;
	}
	return false;
}

LocationContextDescriptor SystemContext::getLocationContext() const {
	return ConvertFromCDM::convert(data->LocationContext().get());
}
	
bool SystemContext::hasLocationContext() const {
	return data->LocationContext().present();
}
	
SystemContext & SystemContext::setOperatorContext(const OperatorContextDescriptor & value) {
	data->OperatorContext(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContext::getOperatorContext(OperatorContextDescriptor & out) const {
	if (data->OperatorContext().present()) {
		out = ConvertFromCDM::convert(data->OperatorContext().get());
		return true;
	}
	return false;
}

OperatorContextDescriptor SystemContext::getOperatorContext() const {
	return ConvertFromCDM::convert(data->OperatorContext().get());
}
	
bool SystemContext::hasOperatorContext() const {
	return data->OperatorContext().present();
}
	
SystemContext & SystemContext::setPatientContext(const PatientContextDescriptor & value) {
	data->PatientContext(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContext::getPatientContext(PatientContextDescriptor & out) const {
	if (data->PatientContext().present()) {
		out = ConvertFromCDM::convert(data->PatientContext().get());
		return true;
	}
	return false;
}

PatientContextDescriptor SystemContext::getPatientContext() const {
	return ConvertFromCDM::convert(data->PatientContext().get());
}
	
bool SystemContext::hasPatientContext() const {
	return data->PatientContext().present();
}
	
SystemContext & SystemContext::setWorkflowContext(const WorkflowContextDescriptor & value) {
	data->WorkflowContext(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContext::getWorkflowContext(WorkflowContextDescriptor & out) const {
	if (data->WorkflowContext().present()) {
		out = ConvertFromCDM::convert(data->WorkflowContext().get());
		return true;
	}
	return false;
}

WorkflowContextDescriptor SystemContext::getWorkflowContext() const {
	return ConvertFromCDM::convert(data->WorkflowContext().get());
}
	
bool SystemContext::hasWorkflowContext() const {
	return data->WorkflowContext().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

