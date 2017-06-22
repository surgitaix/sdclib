
#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/ClockState.h"
#include "OSCLib/Data/OSCP/MDIB/ComponentState.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextState.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/MdsState.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextState.h"
#include "OSCLib/Data/OSCP/MDIB/MdState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextState.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextState.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextState.h"

#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

bool MDState::findState(const std::string & handle, AlertConditionState & outState) const {
	LimitAlertConditionState limitAlertState;
	if (findStateImpl<LimitAlertConditionState>(handle, limitAlertState)) {
		return false;
	} else {
		return findStateImpl<AlertConditionState>(handle, outState);
	}
}

bool MDState::findState(const std::string & handle, AlertSignalState & outState) const {
	return findStateImpl<AlertSignalState>(handle, outState);
}

bool MDState::findState(const std::string & handle, AlertSystemState & outState) const {
	return findStateImpl<AlertSystemState>(handle, outState);
}

bool MDState::findState(const std::string & handle, ClockState & outState) const {
	return findStateImpl<ClockState>(handle, outState);
}

bool MDState::findState(const std::string & handle, ComponentState & outState) const {
	const CDM::MDState & mdstate(*this->data);
	for (const auto & state : mdstate.State()) {
		if (state.DescriptorHandle() == handle || (state.Handle().present() && state.Handle().get() == handle)) {
			if (dynamic_cast<const AlertConditionState::WrappedType *>(&state)) {
				continue;
			}
			if (dynamic_cast<const AlertSignalState::WrappedType *>(&state)) {
				continue;
			}
			if (dynamic_cast<const AlertSystemState::WrappedType *>(&state)) {
				continue;
			}
			if (dynamic_cast<const EnumStringMetricState::WrappedType *>(&state)) {
				continue;
			}
			if (dynamic_cast<const HydraMDSState::WrappedType *>(&state)) {
				continue;
			}
			if (dynamic_cast<const LimitAlertConditionState::WrappedType *>(&state)) {
				continue;
			}
			if (dynamic_cast<const NumericMetricState::WrappedType *>(&state)) {
				continue;
			}
			if (dynamic_cast<const RealTimeSampleArrayMetricState::WrappedType *>(&state)) {
				continue;
			}
			if (dynamic_cast<const StringMetricState::WrappedType *>(&state)) {
				continue;
			}
			if (const ComponentState::WrappedType * foundState = dynamic_cast<const ComponentState::WrappedType *>(&state)) {
				outState = ConvertFromCDM::convert(*foundState);
				return true;
			}
		}
	}
	return false;
}

bool MDState::findState(const std::string & handle, EnsembleContextState & outState) const {
	return findStateImpl<EnsembleContextState>(handle, outState);
}

bool MDState::findState(const std::string & handle, EnumStringMetricState & outState) const {
	return findStateImpl<EnumStringMetricState>(handle, outState);
}

bool MDState::findState(const std::string & handle, HydraMDSState & outState) const {
	return findStateImpl<HydraMDSState>(handle, outState);
}

bool MDState::findState(const std::string & handle, LimitAlertConditionState & outState) const {
	return findStateImpl<LimitAlertConditionState>(handle, outState);
}

bool MDState::findState(const std::string & handle, LocationContextState & outState) const {
	return findStateImpl<LocationContextState>(handle, outState);
}

bool MDState::findState(const std::string & handle, NumericMetricState & outState) const {
	return findStateImpl<NumericMetricState>(handle, outState);
}

bool MDState::findState(const std::string & handle, OperatorContextState & outState) const {
	return findStateImpl<OperatorContextState>(handle, outState);
}

bool MDState::findState(const std::string & handle, PatientContextState & outState) const {
	return findStateImpl<PatientContextState>(handle, outState);
}

bool MDState::findState(const std::string & handle, RealTimeSampleArrayMetricState & outState) const {
	return findStateImpl<RealTimeSampleArrayMetricState>(handle, outState);
}

bool MDState::findState(const std::string & handle, StringMetricState & outState) const {
	EnumStringMetricState enumState;
	if (findStateImpl<EnumStringMetricState>(handle, enumState)) {
		return false;
	} else {
		return findStateImpl<StringMetricState>(handle, outState);
	}
}

bool MDState::findState(const std::string & handle, WorkflowContextState & outState) const {
	return findStateImpl<WorkflowContextState>(handle, outState);
}

template <class WrapperStateDescriptorType>
bool MDState::findStateImpl(const std::string & handle, WrapperStateDescriptorType & outState) const {
	const CDM::MDState & mdstate(*this->data);
	for (const auto & state : mdstate.State()) {
		if (state.DescriptorHandle() == handle || (state.Handle().present() && state.Handle().get() == handle)) {
			if (const typename WrapperStateDescriptorType::WrappedType * foundState = dynamic_cast<const typename WrapperStateDescriptorType::WrappedType *>(&state)) {
				outState = ConvertFromCDM::convert(*foundState);
				return true;
			}
		}
	}
	return false;
}

MDState & MDState::addState(const AlertConditionState & source) {
	return addStateImpl(source);
}

MDState & MDState::addState(const AlertSignalState & source) {
	return addStateImpl(source);
}

MDState & MDState::addState(const AlertSystemState & source) {
	return addStateImpl(source);
}

MDState & MDState::addState(const ClockState & source) {
	return addStateImpl(source);
}

MDState & MDState::addState(const ComponentState & source) {
	return addStateImpl(source);
}

MDState & MDState::addState(const EnsembleContextState & source) {
	return addStateImpl(source);
}

MDState & MDState::addState(const EnumStringMetricState & source) {
	return addStateImpl(source);
}

MDState & MDState::addState(const HydraMDSState & source) {
	return addStateImpl(source);
}

MDState & MDState::addState(const LimitAlertConditionState & source) {
	return addStateImpl(source);
}

MDState & MDState::addState(const LocationContextState & source) {
	return addStateImpl(source);
}

MDState & MDState::addState(const NumericMetricState & source) {
	return addStateImpl(source);
}

MDState & MDState::addState(const OperationState & source) {
	return addStateImpl(source);
}

MDState & MDState::addState(const OperatorContextState & source) {
	return addStateImpl(source);
}

MDState & MDState::addState(const PatientContextState & source) {
	return addStateImpl(source);
}

MDState & MDState::addState(const RealTimeSampleArrayMetricState & source) {
	return addStateImpl(source);
}

MDState & MDState::addState(const StringMetricState & source) {
	return addStateImpl(source);
}

MDState & MDState::addState(const WorkflowContextState & source) {
	return addStateImpl(source);
}

template <class WrapperStateDescriptorType>
MDState & MDState::addStateImpl(const WrapperStateDescriptorType & source) {
	data->State().push_back(ConvertToCDM::convert(source));
	return *this;
}

std::vector<AlertConditionState> MDState::findAlertConditionStates() const {
	return findStatesImpl<AlertConditionState, LimitAlertConditionState>();
}

std::vector<AlertSignalState> MDState::findAlertSignalStates() const {
	return findStatesImpl<AlertSignalState>();
}

std::vector<AlertSystemState> MDState::findAlertSystemStates() const {
	return findStatesImpl<AlertSystemState>();
}

std::vector<ClockState> MDState::findClockStates() const {
	return findStatesImpl<ClockState>();
}

std::vector<ComponentState> MDState::findComponentStates() const {
	std::vector<ComponentState> result;
	const CDM::MDState & mdstate(*this->data);
	for (const auto & state : mdstate.State()) {
		if (dynamic_cast<const AlertConditionState::WrappedType *>(&state)) {
			continue;
		}
		if (dynamic_cast<const AlertSignalState::WrappedType *>(&state)) {
			continue;
		}
		if (dynamic_cast<const AlertSystemState::WrappedType *>(&state)) {
			continue;
		}
		if (dynamic_cast<const EnumStringMetricState::WrappedType *>(&state)) {
			continue;
		}
		if (dynamic_cast<const HydraMDSState::WrappedType *>(&state)) {
			continue;
		}
		if (dynamic_cast<const LimitAlertConditionState::WrappedType *>(&state)) {
			continue;
		}
		if (dynamic_cast<const NumericMetricState::WrappedType *>(&state)) {
			continue;
		}
		if (dynamic_cast<const RealTimeSampleArrayMetricState::WrappedType *>(&state)) {
			continue;
		}
		if (dynamic_cast<const StringMetricState::WrappedType *>(&state)) {
			continue;
		}
		if (const ComponentState::WrappedType * foundState = dynamic_cast<const ComponentState::WrappedType *>(&state)) {
			result.push_back(ConvertFromCDM::convert(*foundState));
		}
	}
	return result;
}

std::vector<EnsembleContextState> MDState::findEnsembleContextStates() const {
	return findStatesImpl<EnsembleContextState>();
}

std::vector<EnumStringMetricState> MDState::findEnumStringMetricStates() const {
	return findStatesImpl<EnumStringMetricState>();
}

std::vector<HydraMDSState> MDState::findHydraMDSStates() const {
	return findStatesImpl<HydraMDSState>();
}

std::vector<LimitAlertConditionState> MDState::findLimitAlertConditionStates() const {
	return findStatesImpl<LimitAlertConditionState>();
}

std::vector<LocationContextState> MDState::findLocationContextStates() const {
	return findStatesImpl<LocationContextState>();
}

std::vector<NumericMetricState> MDState::findNumericMetricStates() const {
	return findStatesImpl<NumericMetricState>();
}

std::vector<OperatorContextState> MDState::findOperatorContextStates() const {
	return findStatesImpl<OperatorContextState>();
}

std::vector<PatientContextState> MDState::findPatientContextStates() const {
	return findStatesImpl<PatientContextState>();
}

std::vector<RealTimeSampleArrayMetricState> MDState::findRealTimeSampleArrayMetricStates() const {
	return findStatesImpl<RealTimeSampleArrayMetricState>();
}

std::vector<StringMetricState> MDState::findStringMetricStates() const {
	return findStatesImpl<StringMetricState, EnumStringMetricState>();
}

std::vector<WorkflowContextState> MDState::findWorkflowContextStates() const {
	return findStatesImpl<WorkflowContextState>();
}

template <class WrapperStateDescriptorType>
std::vector<WrapperStateDescriptorType> MDState::findStatesImpl() const {
	std::vector<WrapperStateDescriptorType> result;
	const CDM::MDState & mdstate(*this->data);
	for (const auto & state : mdstate.State()) {
		if (const typename WrapperStateDescriptorType::WrappedType * foundState = dynamic_cast<const typename WrapperStateDescriptorType::WrappedType *>(&state)) {
			result.push_back(ConvertFromCDM::convert(*foundState));
		}
	}
	return result;
}

template <class WrapperStateDescriptorType, class ForbiddenType>
std::vector<WrapperStateDescriptorType> MDState::findStatesImpl() const {
	std::vector<WrapperStateDescriptorType> result;
	const CDM::MDState & mdstate(*this->data);
	for (const auto & state : mdstate.State()) {
		if (dynamic_cast<const typename ForbiddenType::WrappedType *>(&state)) {
			continue;
		}
		if (const typename WrapperStateDescriptorType::WrappedType * foundState = dynamic_cast<const typename WrapperStateDescriptorType::WrappedType *>(&state)) {
			result.push_back(ConvertFromCDM::convert(*foundState));
		}
	}
	return result;
}

}
}
}
