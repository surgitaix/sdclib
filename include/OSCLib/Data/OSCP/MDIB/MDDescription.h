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
 *  MDDescription.h
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

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class MDDescription {
private:
	MDDescription(const CDM::MDDescription & object);
	operator CDM::MDDescription() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	MDDescription();
	MDDescription(const MDDescription & object);
	virtual ~MDDescription();
    
    void copyFrom(const MDDescription & object);
    MDDescription & operator=(const MDDescription & object);
    
    typedef CDM::MDDescription WrappedType;

	MDDescription & setDescriptionVersion(const VersionCounter & value);
	VersionCounter getDescriptionVersion() const;
	bool getDescriptionVersion(VersionCounter & out) const;
	bool hasDescriptionVersion() const;


	void addHydraMDSDescriptor(const HydraMDSDescriptor & source);
	void addDicomMDSDescriptor(const DICOMDeviceDescriptor & source);
	bool getFirstHydraMDSDescriptor(HydraMDSDescriptor & outDescriptor) const;

	bool findDescriptor(const std::string & handle, AlertConditionDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, AlertSignalDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, AlertSystemDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, ChannelDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, ClockDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, EnsembleContextDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, EnumStringMetricDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, HydraMDSDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, LimitAlertConditionDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, LocationContextDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, NumericMetricDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, OperatorContextDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, PatientContextDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, RealTimeSampleArrayMetricDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, StringMetricDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, VMDDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, WorkflowContextDescriptor & outDescriptor) const;

	std::string getOperationTargetForOperationHandle(const std::string & operationHandle) const;
	std::string getFirstOperationHandleForOperationTarget(const std::string & operationTarget) const;

	std::vector<AlertConditionDescriptor> collectAllAlertConditionDescriptors() const;
	std::vector<AlertSignalDescriptor> collectAllAlertSignalDescriptors() const;
	std::vector<AlertSystemDescriptor> collectAllAlertSystemDescriptors() const;
	std::vector<LimitAlertConditionDescriptor> collectAllLimitAlertConditionDescriptors() const;

	std::vector<ChannelDescriptor> collectAllChannelDescriptors() const;
	std::vector<ClockDescriptor> collectAllClockDescriptors() const;
	std::vector<DICOMDeviceDescriptor> collectAllDICOMDeviceDescriptors() const;
	std::vector<EnumStringMetricDescriptor> collectAllEnumStringMetricDescriptors() const;
	std::vector<HydraMDSDescriptor> collectAllHydraMDSDescriptors() const;
	std::vector<NumericMetricDescriptor> collectAllNumericMetricDescriptors() const;
	std::vector<RealTimeSampleArrayMetricDescriptor> collectAllRealTimeSampleArrayMetricDescriptors() const;
	std::vector<StringMetricDescriptor> collectAllStringMetricDescriptors() const;
	std::vector<VMDDescriptor> collectAllVMDDescriptors() const;

private:
	template <class WrapperMetricDescriptorType>
	bool findMetricDescriptorImpl(const std::string & handle, WrapperMetricDescriptorType & out) const;

	template <class WrapperMetricDescriptorType>
	void collectMetricDescriptorImpl(std::vector<WrapperMetricDescriptorType> & out) const;
	template <class WrapperMetricDescriptorType, class ForbiddenType>
	void collectMetricDescriptorImpl(std::vector<WrapperMetricDescriptorType> & out) const;
private:
	std::shared_ptr<CDM::MDDescription> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* MDDESCRIPTION_H_ */
