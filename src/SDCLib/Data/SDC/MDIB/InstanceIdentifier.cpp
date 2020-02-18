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
 *  InstanceIdentifier.cpp
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, roehser
 */
 


#include "SDCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"

namespace SDCLib {
namespace Data {
namespace SDC {

InstanceIdentifier::InstanceIdentifier()
: data(Defaults::InstanceIdentifierInit())
{ }

InstanceIdentifier::operator CDM::InstanceIdentifier() const {
	return *data;
}

InstanceIdentifier::InstanceIdentifier(const CDM::InstanceIdentifier & object)
: data(new CDM::InstanceIdentifier(object))
{ }

InstanceIdentifier::InstanceIdentifier(const InstanceIdentifier & object)
: data(new CDM::InstanceIdentifier(*object.data))
{ }

void InstanceIdentifier::copyFrom(const InstanceIdentifier & object) {
	data = std::make_shared<CDM::InstanceIdentifier>(*object.data);
}

InstanceIdentifier & InstanceIdentifier:: operator=(const InstanceIdentifier & object) {
	copyFrom(object);
	return *this;
}


InstanceIdentifier & InstanceIdentifier::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool InstanceIdentifier::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue InstanceIdentifier::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}
	
bool InstanceIdentifier::hasType() const {
	return data->getType().present();
}
	
InstanceIdentifier & InstanceIdentifier::setRoot(const Root & value) {
	data->setRoot(ConvertToCDM::convert(value));
	return *this;
}

bool InstanceIdentifier::getRoot(Root & out) const {
	if (data->getRoot().present()) {
		out = ConvertFromCDM::convert(data->getRoot().get());
		return true;
	}
	return false;
}

Root InstanceIdentifier::getRoot() const {
	return ConvertFromCDM::convert(data->getRoot().get());
}
	
bool InstanceIdentifier::hasRoot() const {
	return data->getRoot().present();
}
	
InstanceIdentifier & InstanceIdentifier::setExtension(const Extension & value) {
	data->setExtension1(ConvertToCDM::convert(value));
	return *this;
}

bool InstanceIdentifier::getExtension(Extension & out) const {
	if (data->getExtension1().present()) {
		out = ConvertFromCDM::convert(data->getExtension1().get());
		return true;
	}
	return false;
}

Extension InstanceIdentifier::getExtension() const {
	return ConvertFromCDM::convert(data->getExtension1().get());
}
	
bool InstanceIdentifier::hasExtension() const {
	return data->getExtension1().present();
}
	
InstanceIdentifier & InstanceIdentifier::addIdentifierName(const LocalizedText & value) {
	data->getIdentifierName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> InstanceIdentifier::getIdentifierNameList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->getIdentifierName().size());
	for (const auto & value: data->getIdentifierName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void InstanceIdentifier::clearIdentifierNameList() {
	data->getIdentifierName().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

