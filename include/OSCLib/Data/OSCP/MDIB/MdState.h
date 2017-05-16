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
 *  MdState.h
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

#ifndef MDSTATE_H_
#define MDSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class MdState {
private:
	MdState(const CDM::MdState & object);
	operator CDM::MdState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	MdState();
	MdState(const MdState & object);
	virtual ~MdState();
    
    void copyFrom(const MdState & object);
    MdState & operator=(const MdState & object);
    
    typedef CDM::MdState WrappedType;

	MdState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;


	bool findState(const std::string & handle, AlertConditionState & outState) const;
	bool findState(const std::string & handle, AlertSignalState & outState) const;
	bool findState(const std::string & handle, AlertSystemState & outState) const;
	bool findState(const std::string & handle, ClockState & outState) const;
	bool findState(const std::string & handle, ComponentState & outState) const;
	bool findState(const std::string & handle, EnsembleContextState & outState) const;
	bool findState(const std::string & handle, EnumStringMetricState & outState) const;
    bool findState(const std::string & handle, HydraMDSState & outState) const;
	bool findState(const std::string & handle, LimitAlertConditionState & outState) const;
	bool findState(const std::string & handle, LocationContextState & outState) const;
	bool findState(const std::string & handle, NumericMetricState & outState) const;
	bool findState(const std::string & handle, OperatorContextState & outState) const;
	bool findState(const std::string & handle, PatientContextState & outState) const;
	bool findState(const std::string & handle, RealTimeSampleArrayMetricState & outState) const;
	bool findState(const std::string & handle, StringMetricState & outState) const;
	bool findState(const std::string & handle, WorkflowContextState & outState) const;

	std::vector<AlertConditionState> findAlertConditionStates() const;
	std::vector<AlertSignalState> findAlertSignalStates() const;
	std::vector<AlertSystemState> findAlertSystemStates() const;
	std::vector<ClockState> findClockStates() const;
	std::vector<ComponentState> findComponentStates() const;
	std::vector<EnsembleContextState> findEnsembleContextStates() const;
	std::vector<EnumStringMetricState> findEnumStringMetricStates() const;
	std::vector<HydraMDSState> findHydraMDSStates() const;
	std::vector<LimitAlertConditionState> findLimitAlertConditionStates() const;
	std::vector<LocationContextState> findLocationContextStates() const;
	std::vector<NumericMetricState> findNumericMetricStates() const;
	std::vector<OperatorContextState> findOperatorContextStates() const;
	std::vector<PatientContextState> findPatientContextStates() const;
	std::vector<RealTimeSampleArrayMetricState> findRealTimeSampleArrayMetricStates() const;
	std::vector<StringMetricState> findStringMetricStates() const;
	std::vector<WorkflowContextState> findWorkflowContextStates() const;

    MDState & addState(const AlertConditionState & source);
    MDState & addState(const AlertSignalState & source);
    MDState & addState(const AlertSystemState & source);
    MDState & addState(const ClockState & source);
    MDState & addState(const ComponentState & source);
    MDState & addState(const EnsembleContextState & source);
    MDState & addState(const EnumStringMetricState & source);
    MDState & addState(const LocationContextState & source);
    MDState & addState(const LimitAlertConditionState & source);
    MDState & addState(const HydraMDSState & source);
    MDState & addState(const NumericMetricState & source);
    MDState & addState(const OperationState & source);
    MDState & addState(const OperatorContextState & source);
    MDState & addState(const PatientContextState & source);
    MDState & addState(const RealTimeSampleArrayMetricState & source);
    MDState & addState(const StringMetricState & source);
    MDState & addState(const WorkflowContextState & source);

private:
    template <class WrapperStateDescriptorType>
    bool findStateImpl(const std::string & handle, WrapperStateDescriptorType & out) const;

    template <class WrapperStateDescriptorType>
    MDState & addStateImpl(const WrapperStateDescriptorType & source);

    template <class WrapperStateDescriptorType, class ForbiddenType>
    std::vector<WrapperStateDescriptorType> findStatesImpl() const;
    template <class WrapperStateDescriptorType>
    std::vector<WrapperStateDescriptorType> findStatesImpl() const;
private:
	std::shared_ptr<CDM::MdState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* MDSTATE_H_ */
