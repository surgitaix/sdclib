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
 *  HydraMDSDescriptor.h
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

#ifndef HYDRAMDSDESCRIPTOR_H_
#define HYDRAMDSDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class HydraMDSDescriptor {
private:
	HydraMDSDescriptor(const CDM::HydraMDSDescriptor & object);
	operator CDM::HydraMDSDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	HydraMDSDescriptor();
	HydraMDSDescriptor(const HydraMDSDescriptor & object);
	virtual ~HydraMDSDescriptor();
    
    void copyFrom(const HydraMDSDescriptor & object);
    HydraMDSDescriptor & operator=(const HydraMDSDescriptor & object);
    
    typedef CDM::HydraMDSDescriptor WrappedType;

	HydraMDSDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	HydraMDSDescriptor & setHandle(const std::string & value);
	std::string getHandle() const;

	HydraMDSDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	HydraMDSDescriptor & setIntendedUse(const IntendedUse & value);
	IntendedUse getIntendedUse() const;
	bool getIntendedUse(IntendedUse & out) const;
	bool hasIntendedUse() const;

	HydraMDSDescriptor & addProductionSpecification(const ProductionSpecification & value);
	std::vector<ProductionSpecification> getProductionSpecifications() const;
	void clearProductionSpecifications();
	
	HydraMDSDescriptor & setMetaData(const SystemMetaData & value);
	SystemMetaData getMetaData() const;
	bool getMetaData(SystemMetaData & out) const;
	bool hasMetaData() const;

	HydraMDSDescriptor & setContext(const SystemContext & value);
	SystemContext getContext() const;

	HydraMDSDescriptor & setClock(const ClockDescriptor & value);
	ClockDescriptor getClock() const;
	bool getClock(ClockDescriptor & out) const;
	bool hasClock() const;

	HydraMDSDescriptor & setSCO(const SCODescriptor & value);
	SCODescriptor getSCO() const;
	bool getSCO(SCODescriptor & out) const;
	bool hasSCO() const;

	HydraMDSDescriptor & setAlertSystem(const AlertSystemDescriptor & value);
	AlertSystemDescriptor getAlertSystem() const;
	bool getAlertSystem(AlertSystemDescriptor & out) const;
	bool hasAlertSystem() const;

	HydraMDSDescriptor & addVMD(const VMDDescriptor & value);
	std::vector<VMDDescriptor> getVMDs() const;
	void clearVMDs();
	
private:
	std::shared_ptr<CDM::HydraMDSDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* HYDRAMDSDESCRIPTOR_H_ */
