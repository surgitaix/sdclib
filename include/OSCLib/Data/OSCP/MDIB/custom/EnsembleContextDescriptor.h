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
 *  EnsembleContextDescriptor.h
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

#ifndef ENSEMBLECONTEXTDESCRIPTOR_H_
#define ENSEMBLECONTEXTDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class EnsembleContextDescriptor {
private:
	EnsembleContextDescriptor(const CDM::EnsembleContextDescriptor & object);
	operator CDM::EnsembleContextDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	EnsembleContextDescriptor();
	EnsembleContextDescriptor(const EnsembleContextDescriptor & object);
	virtual ~EnsembleContextDescriptor();
    
    void copyFrom(const EnsembleContextDescriptor & object);
    EnsembleContextDescriptor & operator=(const EnsembleContextDescriptor & object);
    
    typedef CDM::EnsembleContextDescriptor WrappedType;
    typedef EnsembleContextState StateType;

	EnsembleContextDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	EnsembleContextDescriptor & setHandle(const std::string & value);
	std::string getHandle() const;

	EnsembleContextDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

private:
	std::shared_ptr<CDM::EnsembleContextDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ENSEMBLECONTEXTDESCRIPTOR_H_ */
