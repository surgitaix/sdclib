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
 *  ProductionSpecification.cpp
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

#include "OSCLib/Data/OSCP/MDIB/ProductionSpecification.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

ProductionSpecification::ProductionSpecification() : data(Defaults::ProductionSpecification()) {
}

ProductionSpecification::operator CDM::ProductionSpecification() const {
	return *data;
}

ProductionSpecification::ProductionSpecification(const CDM::ProductionSpecification & object) : data(new CDM::ProductionSpecification(object)) {

}

ProductionSpecification::ProductionSpecification(const ProductionSpecification & object) : data(new CDM::ProductionSpecification(*object.data)) {

}

ProductionSpecification::~ProductionSpecification() {

}

void ProductionSpecification::copyFrom(const ProductionSpecification & object) {
	*data = *object.data;
}

ProductionSpecification & ProductionSpecification:: operator=(const ProductionSpecification & object) {
	copyFrom(object);
	return *this;
}


ProductionSpecification & ProductionSpecification::setspecType(const CodedValue & value) {
	data->specType(ConvertToCDM::convert(value));
	return *this;
}


CodedValue ProductionSpecification::getspecType() const {
	return ConvertFromCDM::convert(data->specType());
}
	
ProductionSpecification & ProductionSpecification::setproductionSpec(const std::string & value) {
	data->productionSpec(ConvertToCDM::convert(value));
	return *this;
}


std::string ProductionSpecification::getproductionSpec() const {
	return ConvertFromCDM::convert(data->productionSpec());
}
	
ProductionSpecification & ProductionSpecification::setcomponentId(const InstanceIdentifier & value) {
	data->componentId(ConvertToCDM::convert(value));
	return *this;
}

bool ProductionSpecification::getcomponentId(InstanceIdentifier & out) const {
	if (data->componentId().present()) {
		out = ConvertFromCDM::convert(data->componentId().get());
		return true;
	}
	return false;
}

InstanceIdentifier ProductionSpecification::getcomponentId() const {
	return ConvertFromCDM::convert(data->componentId().get());
}
	
bool ProductionSpecification::hascomponentId() const {
	return data->componentId().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

