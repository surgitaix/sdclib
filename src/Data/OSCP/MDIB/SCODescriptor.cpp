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
 *  SCODescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/SCODescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/ProductionSpecification.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

SCODescriptor::SCODescriptor() : data(Defaults::SCODescriptor()) {
}

SCODescriptor::operator CDM::SCODescriptor() const {
	return *data;
}

SCODescriptor::SCODescriptor(const CDM::SCODescriptor & object) : data(new CDM::SCODescriptor(object)) {

}

SCODescriptor::SCODescriptor(const SCODescriptor & object) : data(new CDM::SCODescriptor(*object.data)) {

}

SCODescriptor::~SCODescriptor() {

}

void SCODescriptor::copyFrom(const SCODescriptor & object) {
	*data = *object.data;
}

SCODescriptor & SCODescriptor:: operator=(const SCODescriptor & object) {
	copyFrom(object);
	return *this;
}


SCODescriptor & SCODescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool SCODescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue SCODescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool SCODescriptor::hasType() const {
	return data->Type().present();
}
	
SCODescriptor & SCODescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string SCODescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
SCODescriptor & SCODescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SCODescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter SCODescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool SCODescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
SCODescriptor & SCODescriptor::addProductionSpecification(const ProductionSpecification & value) {
	data->ProductionSpecification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ProductionSpecification> SCODescriptor::getProductionSpecifications() const {
	std::vector<ProductionSpecification> result;
	result.reserve(data->ProductionSpecification().size());
	for (const auto & value: data->ProductionSpecification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SCODescriptor::clearProductionSpecifications() {
	data->ProductionSpecification().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

