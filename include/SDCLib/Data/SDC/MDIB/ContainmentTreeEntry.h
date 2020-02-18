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
 *  ContainmentTreeEntry.h
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#ifndef CONTAINMENTTREEENTRY_H_
#define CONTAINMENTTREEENTRY_H_

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "DataModel/osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class ContainmentTreeEntry
{
private:
	ContainmentTreeEntry(const CDM::ContainmentTreeEntry & object);
	operator CDM::ContainmentTreeEntry() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	ContainmentTreeEntry(
	);
	ContainmentTreeEntry(const ContainmentTreeEntry& object);
	virtual ~ContainmentTreeEntry() = default;

    void copyFrom(const ContainmentTreeEntry& object);
    ContainmentTreeEntry & operator=(const ContainmentTreeEntry& object);

    typedef CDM::ContainmentTreeEntry WrappedType;

	ContainmentTreeEntry & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

private:
	std::shared_ptr<CDM::ContainmentTreeEntry> data = nullptr;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* CONTAINMENTTREEENTRY_H_ */
