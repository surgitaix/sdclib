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
 *  MdDescription.h
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

#ifndef MDDESCRIPTION_H_
#define MDDESCRIPTION_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class MdDescription {
private:
	MdDescription(const CDM::MdDescription & object);
	operator CDM::MdDescription() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	MdDescription();
	MdDescription(const MdDescription & object);
	virtual ~MdDescription();
    
    void copyFrom(const MdDescription & object);
    MdDescription & operator=(const MdDescription & object);
    
    typedef CDM::MdDescription WrappedType;

	MdDescription & setDescriptionVersion(const VersionCounter & value);
	VersionCounter getDescriptionVersion() const;
	bool getDescriptionVersion(VersionCounter & out) const;
	bool hasDescriptionVersion() const;

	MdDescription & addMds(const MdsDescriptor & value);
	std::vector<MdsDescriptor> getMdsLists() const;
	void clearMdsLists();
	
private:
	std::shared_ptr<CDM::MdDescription> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* MDDESCRIPTION_H_ */
