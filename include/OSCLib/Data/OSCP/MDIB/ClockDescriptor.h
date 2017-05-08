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
 *  ClockDescriptor.h
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

#ifndef CLOCKDESCRIPTOR_H_
#define CLOCKDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class ClockDescriptor {
private:
	ClockDescriptor(const CDM::ClockDescriptor & object);
	operator CDM::ClockDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	ClockDescriptor();
	ClockDescriptor(const ClockDescriptor & object);
	virtual ~ClockDescriptor();
    
    void copyFrom(const ClockDescriptor & object);
    ClockDescriptor & operator=(const ClockDescriptor & object);
    
    typedef CDM::ClockDescriptor WrappedType;

	ClockDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	ClockDescriptor & setHandle(const std::string & value);
	std::string getHandle() const;

	ClockDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	ClockDescriptor & setResolution(const Duration & value);
	Duration getResolution() const;
	bool getResolution(Duration & out) const;
	bool hasResolution() const;

	ClockDescriptor & addTimeProtocol(const CodedValue & value);
	std::vector<CodedValue> getTimeProtocols() const;
	void clearTimeProtocols();
	
private:
	std::shared_ptr<CDM::ClockDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* CLOCKDESCRIPTOR_H_ */
