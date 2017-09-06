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
 *  ContainmentTree.cpp
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

#include "OSCLib/Data/OSCP/MDIB/ContainmentTree.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/ContainmentTreeEntry.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

ContainmentTree::ContainmentTree() : data(Defaults::ContainmentTree()) {
}

ContainmentTree::operator CDM::ContainmentTree() const {
	return *data;
}

ContainmentTree::ContainmentTree(const CDM::ContainmentTree & object) : data(new CDM::ContainmentTree(object)) {

}

ContainmentTree::ContainmentTree(const ContainmentTree & object) : data(new CDM::ContainmentTree(*object.data)) {

}

ContainmentTree::~ContainmentTree() {

}

void ContainmentTree::copyFrom(const ContainmentTree & object) {
	*data = *object.data;
}

ContainmentTree & ContainmentTree:: operator=(const ContainmentTree & object) {
	copyFrom(object);
	return *this;
}


ContainmentTree & ContainmentTree::addEntry(const ContainmentTreeEntry & value) {
	data->Entry().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ContainmentTreeEntry> ContainmentTree::getEntryLists() const {
	std::vector<ContainmentTreeEntry> result;
	result.reserve(data->Entry().size());
	for (const auto & value: data->Entry()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ContainmentTree::clearEntryLists() {
	data->Entry().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

