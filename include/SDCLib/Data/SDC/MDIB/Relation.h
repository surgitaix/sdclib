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
 *  Relation.h
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

#ifndef RELATION_H_
#define RELATION_H_

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "DataModel/osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class Relation
{
private:
	Relation(const CDM::Relation & object);
	operator CDM::Relation() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	Relation(
		Kind kind
		,
		EntryRef entries
	);
private:
	Relation(){};
public:
	Relation(const Relation& object);
	virtual ~Relation() = default;

    void copyFrom(const Relation& object);
    Relation & operator=(const Relation& object);

    typedef CDM::Relation WrappedType;

	Relation & setCode(const CodedValue & value);
	CodedValue getCode() const;
	bool getCode(CodedValue & out) const;
	bool hasCode() const;

	Relation & setIdentification(const InstanceIdentifier & value);
	InstanceIdentifier getIdentification() const;
	bool getIdentification(InstanceIdentifier & out) const;
	bool hasIdentification() const;

	Relation & setKind(const Kind & value);
	Kind getKind() const;

	Relation & setEntries(const EntryRef & value);
	EntryRef getEntries() const;

private:
	std::shared_ptr<CDM::Relation> data = nullptr;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* RELATION_H_ */
