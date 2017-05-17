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
 *  SystemContextDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/EnsembleContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MeansContextDescriptor.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

SystemContextDescriptor::SystemContextDescriptor() : data(Defaults::SystemContextDescriptor()) {
}

SystemContextDescriptor::operator CDM::SystemContextDescriptor() const {
	return *data;
}

SystemContextDescriptor::SystemContextDescriptor(const CDM::SystemContextDescriptor & object) : data(new CDM::SystemContextDescriptor(object)) {

}

SystemContextDescriptor::SystemContextDescriptor(const SystemContextDescriptor & object) : data(new CDM::SystemContextDescriptor(*object.data)) {

}

SystemContextDescriptor::~SystemContextDescriptor() {

}

void SystemContextDescriptor::copyFrom(const SystemContextDescriptor & object) {
	*data = *object.data;
}

SystemContextDescriptor & SystemContextDescriptor:: operator=(const SystemContextDescriptor & object) {
	copyFrom(object);
	return *this;
}


SystemContextDescriptor & SystemContextDescriptor::setEnsembleContext(const EnsembleContextDescriptor & value) {
	data->EnsembleContext(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextDescriptor::getEnsembleContext(EnsembleContextDescriptor & out) const {
	if (data->EnsembleContext().present()) {
		out = ConvertFromCDM::convert(data->EnsembleContext().get());
		return true;
	}
	return false;
}

EnsembleContextDescriptor SystemContextDescriptor::getEnsembleContext() const {
	return ConvertFromCDM::convert(data->EnsembleContext().get());
}
	
bool SystemContextDescriptor::hasEnsembleContext() const {
	return data->EnsembleContext().present();
}
	
SystemContextDescriptor & SystemContextDescriptor::setLocationContext(const LocationContextDescriptor & value) {
	data->LocationContext(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextDescriptor::getLocationContext(LocationContextDescriptor & out) const {
	if (data->LocationContext().present()) {
		out = ConvertFromCDM::convert(data->LocationContext().get());
		return true;
	}
	return false;
}

LocationContextDescriptor SystemContextDescriptor::getLocationContext() const {
	return ConvertFromCDM::convert(data->LocationContext().get());
}
	
bool SystemContextDescriptor::hasLocationContext() const {
	return data->LocationContext().present();
}
	
SystemContextDescriptor & SystemContextDescriptor::setOperatorContext(const OperatorContextDescriptor & value) {
	data->OperatorContext(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextDescriptor::getOperatorContext(OperatorContextDescriptor & out) const {
	if (data->OperatorContext().present()) {
		out = ConvertFromCDM::convert(data->OperatorContext().get());
		return true;
	}
	return false;
}

OperatorContextDescriptor SystemContextDescriptor::getOperatorContext() const {
	return ConvertFromCDM::convert(data->OperatorContext().get());
}
	
bool SystemContextDescriptor::hasOperatorContext() const {
	return data->OperatorContext().present();
}
	
SystemContextDescriptor & SystemContextDescriptor::setPatientContext(const PatientContextDescriptor & value) {
	data->PatientContext(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextDescriptor::getPatientContext(PatientContextDescriptor & out) const {
	if (data->PatientContext().present()) {
		out = ConvertFromCDM::convert(data->PatientContext().get());
		return true;
	}
	return false;
}

PatientContextDescriptor SystemContextDescriptor::getPatientContext() const {
	return ConvertFromCDM::convert(data->PatientContext().get());
}
	
bool SystemContextDescriptor::hasPatientContext() const {
	return data->PatientContext().present();
}
	
SystemContextDescriptor & SystemContextDescriptor::setWorkflowContext(const WorkflowContextDescriptor & value) {
	data->WorkflowContext(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextDescriptor::getWorkflowContext(WorkflowContextDescriptor & out) const {
	if (data->WorkflowContext().present()) {
		out = ConvertFromCDM::convert(data->WorkflowContext().get());
		return true;
	}
	return false;
}

WorkflowContextDescriptor SystemContextDescriptor::getWorkflowContext() const {
	return ConvertFromCDM::convert(data->WorkflowContext().get());
}
	
bool SystemContextDescriptor::hasWorkflowContext() const {
	return data->WorkflowContext().present();
}
	
SystemContextDescriptor & SystemContextDescriptor::setMeansContext(const MeansContextDescriptor & value) {
	data->MeansContext(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextDescriptor::getMeansContext(MeansContextDescriptor & out) const {
	if (data->MeansContext().present()) {
		out = ConvertFromCDM::convert(data->MeansContext().get());
		return true;
	}
	return false;
}

MeansContextDescriptor SystemContextDescriptor::getMeansContext() const {
	return ConvertFromCDM::convert(data->MeansContext().get());
}
	
bool SystemContextDescriptor::hasMeansContext() const {
	return data->MeansContext().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

