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
 *  Author: besting, buerger, roehser
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

#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class MdDescription {
private:
	MdDescription(const CDM::MdDescription & object);
	operator CDM::MdDescription() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
public:
	MdDescription(
	); 
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
	std::vector<MdsDescriptor> getMdsList() const;
	void clearMdsList();
	

	template <class MdsDescriptor>
	void addMdsDescriptor(const MdsDescriptor & source);
	template <class MdsDescriptor>
	bool removeMdsDescriptor(const MdsDescriptor & object);

	bool getFirstMdsDescriptor(MdsDescriptor & outDescriptor) const;

	// use this API method to get a copy of the MDIB's descriptors
	template<class TDescriptor>
	std::unique_ptr<TDescriptor> findDescriptor(const std::string & handle) const;

	std::string getOperationTargetForOperationHandle(const std::string & operationHandle) const;
	std::string getFirstOperationHandleForOperationTarget(const std::string & operationTarget) const;

	std::vector<AlertConditionDescriptor> collectAllAlertConditionDescriptors() const;
	std::vector<AlertSignalDescriptor> collectAllAlertSignalDescriptors() const;
	std::vector<AlertSystemDescriptor> collectAllAlertSystemDescriptors() const;
	std::vector<LimitAlertConditionDescriptor> collectAllLimitAlertConditionDescriptors() const;

	std::vector<ChannelDescriptor> collectAllChannelDescriptors() const;
	std::vector<ClockDescriptor> collectAllClockDescriptors() const;
	std::vector<DicomDeviceDescriptor> collectAllDicomDeviceDescriptors() const;
	std::vector<EnumStringMetricDescriptor> collectAllEnumStringMetricDescriptors() const;
	std::vector<MdsDescriptor> collectAllMdsDescriptors() const;
	std::vector<NumericMetricDescriptor> collectAllNumericMetricDescriptors() const;
	std::vector<RealTimeSampleArrayMetricDescriptor> collectAllRealTimeSampleArrayMetricDescriptors() const;
	std::vector<StringMetricDescriptor> collectAllStringMetricDescriptors() const;
	std::vector<ActivateOperationDescriptor> collectAllActivateOperationDescriptors() const;
	std::vector<SetStringOperationDescriptor> collectAllSetStringOperationDescriptors() const;
	std::vector<SetValueOperationDescriptor> collectAllSetValueOperationDescriptors() const;
	std::vector<VmdDescriptor> collectAllVmdDescriptors() const;

private:
	// historical atavisms: those functions are used inside the framework
	// API use the unique_ptr returning methods
	bool findDescriptor(const std::string & handle, AlertConditionDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, AlertSignalDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, AlertSystemDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, ChannelDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, ClockDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, EnsembleContextDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, EnumStringMetricDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, MdsDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, LimitAlertConditionDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, LocationContextDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, NumericMetricDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, OperatorContextDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, PatientContextDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, RealTimeSampleArrayMetricDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, StringMetricDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, VmdDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, WorkflowContextDescriptor & outDescriptor) const;

	template <class WrapperMetricDescriptorType>
	bool findMetricDescriptorImpl(const std::string & handle, WrapperMetricDescriptorType & out) const;

	template <class WrapperMetricDescriptorType>
	void collectMetricDescriptorImpl(std::vector<WrapperMetricDescriptorType> & out) const;
	template <class WrapperMetricDescriptorType, class ForbiddenType>
	void collectMetricDescriptorImpl(std::vector<WrapperMetricDescriptorType> & out) const;
private:
	std::shared_ptr<CDM::MdDescription> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* MDDESCRIPTION_H_ */
