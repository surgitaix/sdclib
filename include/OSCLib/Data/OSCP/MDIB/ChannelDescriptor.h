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
 *  ChannelDescriptor.h
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

#ifndef CHANNELDESCRIPTOR_H_
#define CHANNELDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class ChannelDescriptor {
private:
	ChannelDescriptor(const CDM::ChannelDescriptor & object);
	operator CDM::ChannelDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	ChannelDescriptor();
	ChannelDescriptor(const ChannelDescriptor & object);
	virtual ~ChannelDescriptor();
    
    void copyFrom(const ChannelDescriptor & object);
    ChannelDescriptor & operator=(const ChannelDescriptor & object);
    
    typedef CDM::ChannelDescriptor WrappedType;

	ChannelDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	ChannelDescriptor & setHandle(const std::string & value);
	std::string getHandle() const;

	ChannelDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	ChannelDescriptor & setIntendedUse(const IntendedUse & value);
	IntendedUse getIntendedUse() const;
	bool getIntendedUse(IntendedUse & out) const;
	bool hasIntendedUse() const;

	ChannelDescriptor & addProductionSpecification(const ProductionSpecification & value);
	std::vector<ProductionSpecification> getProductionSpecifications() const;
	void clearProductionSpecifications();
	
	ChannelDescriptor & setAlertSystem(const AlertSystemDescriptor & value);
	AlertSystemDescriptor getAlertSystem() const;
	bool getAlertSystem(AlertSystemDescriptor & out) const;
	bool hasAlertSystem() const;


	std::vector<EnumStringMetricDescriptor> getEnumStringMetricDescriptors() const;
	std::vector<NumericMetricDescriptor> getNumericMetricDescriptors() const;
	std::vector<StringMetricDescriptor> getStringMetricDescriptors() const;
	std::vector<RealTimeSampleArrayMetricDescriptor> getRealTimeSampleArrayMetricDescriptors() const;

	ChannelDescriptor & addMetric(const EnumStringMetricDescriptor & source);
	ChannelDescriptor & addMetric(const NumericMetricDescriptor & source);
	ChannelDescriptor & addMetric(const StringMetricDescriptor & source);
	ChannelDescriptor & addMetric(const RealTimeSampleArrayMetricDescriptor & source);

private:
	template<class U, class V>
	void getMetricDescriptors(std::vector<U> & result) const;

	template<class T>
	ChannelDescriptor & addMetricImpl(const T & source);
private:
	std::shared_ptr<CDM::ChannelDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* CHANNELDESCRIPTOR_H_ */
