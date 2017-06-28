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
 *  ScoState.h
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

#ifndef SCOSTATE_H_
#define SCOSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class ScoState {
private:
	ScoState(const CDM::ScoState & object);
	operator CDM::ScoState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	ScoState();
	ScoState(const ScoState & object);
	virtual ~ScoState();
    
    void copyFrom(const ScoState & object);
    ScoState & operator=(const ScoState & object);
    
    typedef CDM::ScoState WrappedType;

	ScoState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;

	ScoState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	ScoState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;

private:
	std::shared_ptr<CDM::ScoState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* SCOSTATE_H_ */
