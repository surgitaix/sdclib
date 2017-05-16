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
 *  MdsState.h
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

#ifndef MDSSTATE_H_
#define MDSSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class MdsState {
private:
	MdsState(const CDM::MdsState & object);
	operator CDM::MdsState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	MdsState();
	MdsState(const MdsState & object);
	virtual ~MdsState();
    
    void copyFrom(const MdsState & object);
    MdsState & operator=(const MdsState & object);
    
    typedef CDM::MdsState WrappedType;
    typedef MdsDescriptor DescriptorType;
    typedef OSCPProviderHydraMDSStateHandler ProviderHandlerType;

	MdsState & setLang(const Language & value);
	Language getLang() const;
	bool getLang(Language & out) const;
	bool hasLang() const;

	MdsState & setOperatingMode(const MdsOperatingMode & value);
	MdsOperatingMode getOperatingMode() const;
	bool getOperatingMode(MdsOperatingMode & out) const;
	bool hasOperatingMode() const;

private:
	std::shared_ptr<CDM::MdsState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* MDSSTATE_H_ */
