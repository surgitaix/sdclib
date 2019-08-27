
#include "SDCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "SDCLib/Data/SDC/MDIB/ClockState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/EnsembleContextState.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/MdsState.h"
#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextState.h"
#include "SDCLib/Data/SDC/MDIB/MdState.h"
#include "SDCLib/Data/SDC/MDIB/VmdState.h"
#include "SDCLib/Data/SDC/MDIB/ChannelState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/OperatorContextState.h"
#include "SDCLib/Data/SDC/MDIB/PatientContextState.h"
#include "SDCLib/Data/SDC/MDIB/MeansContextState.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/DistributionSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/Range.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/WorkflowContextState.h"

#include <memory>

#include "DataModel/osdm.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {




//// template specialization for API
template std::unique_ptr<AlertConditionState> MdState::findState<AlertConditionState>(const std::string & handle) const;
template std::unique_ptr<AlertSignalState> MdState::findState<AlertSignalState>(const std::string & handle) const;
template std::unique_ptr<AlertSystemState> MdState::findState<AlertSystemState>(const std::string & handle) const;
template std::unique_ptr<ClockState> MdState::findState<ClockState>(const std::string & handle) const;
template std::unique_ptr<EnsembleContextState> MdState::findState<EnsembleContextState>(const std::string & handle) const;
template std::unique_ptr<EnumStringMetricState> MdState::findState<EnumStringMetricState>(const std::string & handle) const;
template std::unique_ptr<MdsState> MdState::findState<MdsState>(const std::string & handle) const;
template std::unique_ptr<LimitAlertConditionState> MdState::findState<LimitAlertConditionState>(const std::string & handle) const;
template std::unique_ptr<LocationContextState> MdState::findState<LocationContextState>(const std::string & handle) const;
template std::unique_ptr<NumericMetricState> MdState::findState<NumericMetricState>(const std::string & handle) const;
template std::unique_ptr<OperatorContextState> MdState::findState<OperatorContextState>(const std::string & handle) const;
template std::unique_ptr<PatientContextState> MdState::findState<PatientContextState>(const std::string & handle) const;
template std::unique_ptr<RealTimeSampleArrayMetricState> MdState::findState<RealTimeSampleArrayMetricState>(const std::string & handle) const;
template std::unique_ptr<StringMetricState> MdState::findState<StringMetricState>(const std::string & handle) const;
template std::unique_ptr<WorkflowContextState> MdState::findState<WorkflowContextState>(const std::string & handle) const;

template<class TState>
std::unique_ptr<TState> MdState::findState(const std::string & handle) const {
	TState outState;
	if (findState(handle, outState)) {
		auto ptr = std::unique_ptr<TState>(new TState(outState));
		return std::move(ptr);
	} else {
		return nullptr;
	}
}

bool MdState::findState(const std::string & handle, AlertConditionState & outState) const {
	LimitAlertConditionState limitAlertState;

	if (findStateImpl<LimitAlertConditionState>(handle, limitAlertState)) {
		return false;
	} else {
		return findStateImpl<AlertConditionState>(handle, outState);
	}
}

bool MdState::findState(const std::string & handle, AlertSignalState & outState) const {
	return findStateImpl<AlertSignalState>(handle, outState);
}

bool MdState::findState(const std::string & handle, AlertSystemState & outState) const {
	return findStateImpl<AlertSystemState>(handle, outState);
}

bool MdState::findState(const std::string & handle, ClockState & outState) const {
	return findStateImpl<ClockState>(handle, outState);
}


bool MdState::findState(const std::string & handle, EnsembleContextState & outState) const {
	return findStateImpl<EnsembleContextState>(handle, outState);
}

bool MdState::findState(const std::string & handle, EnumStringMetricState & outState) const {
	return findStateImpl<EnumStringMetricState>(handle, outState);
}

bool MdState::findState(const std::string & handle, MdsState & outState) const {
	return findStateImpl<MdsState>(handle, outState);
}

bool MdState::findState(const std::string & handle, LimitAlertConditionState & outState) const {
	return findStateImpl<LimitAlertConditionState>(handle, outState);
}

bool MdState::findState(const std::string & handle, LocationContextState & outState) const {
	return findStateImpl<LocationContextState>(handle, outState);
}

bool MdState::findState(const std::string & handle, NumericMetricState & outState) const {
	return findStateImpl<NumericMetricState>(handle, outState);
}

bool MdState::findState(const std::string & handle, OperatorContextState & outState) const {
	return findStateImpl<OperatorContextState>(handle, outState);
}

bool MdState::findState(const std::string & handle, PatientContextState & outState) const {
	return findStateImpl<PatientContextState>(handle, outState);
}

bool MdState::findState(const std::string & handle, RealTimeSampleArrayMetricState & outState) const {
	return findStateImpl<RealTimeSampleArrayMetricState>(handle, outState);
}

bool MdState::findState(const std::string & handle, StringMetricState & outState) const {
	EnumStringMetricState enumState(handle);
	if (findStateImpl<EnumStringMetricState>(handle, enumState)) {
		return false;
	} else {
		return findStateImpl<StringMetricState>(handle, outState);
	}
}

bool MdState::findState(const std::string & handle, WorkflowContextState & outState) const {
	return findStateImpl<WorkflowContextState>(handle, outState);
}

template <class WrapperStateDescriptorType>
bool MdState::findStateImpl(const std::string & handle, WrapperStateDescriptorType & outState) const {
	const CDM::MdState & mdstate(*this->data);
	for (const auto & state : mdstate.State()) {
		if (state.DescriptorHandle() == handle) {
			if (const typename WrapperStateDescriptorType::WrappedType * foundState = dynamic_cast<const typename WrapperStateDescriptorType::WrappedType *>(&state)) {
				outState = ConvertFromCDM::convert(*foundState);
				return true;
			}
		}
	}
	return false;
}

MdState & MdState::addState(const AlertConditionState & source) {
	return addStateImpl(source);
}

MdState & MdState::addState(const AlertSignalState & source) {
	return addStateImpl(source);
}

MdState & MdState::addState(const AlertSystemState & source) {
	return addStateImpl(source);
}

MdState & MdState::addState(const ClockState & source) {
	return addStateImpl(source);
}

MdState & MdState::addState(const EnsembleContextState & source) {
	return addStateImpl(source);
}

MdState & MdState::addState(const EnumStringMetricState & source) {
	return addStateImpl(source);
}

MdState & MdState::addState(const MdsState & source) {
	return addStateImpl(source);
}

MdState & MdState::addState(const LimitAlertConditionState & source) {
	return addStateImpl(source);
}

MdState & MdState::addState(const LocationContextState & source) {
	return addStateImpl(source);
}

MdState & MdState::addState(const MeansContextState & source) {
	return addStateImpl(source);
}

MdState & MdState::addState(const NumericMetricState & source) {
	return addStateImpl(source);
}

MdState & MdState::addState(const OperatorContextState & source) {
	return addStateImpl(source);
}

MdState & MdState::addState(const PatientContextState & source) {
	return addStateImpl(source);
}

MdState & MdState::addState(const RealTimeSampleArrayMetricState & source) {
	return addStateImpl(source);
}

MdState & MdState::addState(const DistributionSampleArrayMetricState & source) {
	return addStateImpl(source);
}

MdState & MdState::addState(const StringMetricState & source) {
	return addStateImpl(source);
}

MdState & MdState::addState(const WorkflowContextState & source) {
	return addStateImpl(source);
}

MdState & MdState::addState(const VmdState & source) {
	return addStateImpl(source);
}

MdState & MdState::addState(const ChannelState & source) {
	return addStateImpl(source);
}

template <class WrapperStateDescriptorType>
MdState & MdState::addStateImpl(const WrapperStateDescriptorType & source) {
	data->State().push_back(ConvertToCDM::convert(source));
	return *this;
}

std::vector<AlertConditionState> MdState::findAlertConditionStates() const {
	return findStatesImpl<AlertConditionState, LimitAlertConditionState>();
}

std::vector<AlertSignalState> MdState::findAlertSignalStates() const {
	return findStatesImpl<AlertSignalState>();
}

std::vector<AlertSystemState> MdState::findAlertSystemStates() const {
	return findStatesImpl<AlertSystemState>();
}

std::vector<ClockState> MdState::findClockStates() const {
	return findStatesImpl<ClockState>();
}

std::vector<EnsembleContextState> MdState::findEnsembleContextStates() const {
	return findStatesImpl<EnsembleContextState>();
}

std::vector<EnumStringMetricState> MdState::findEnumStringMetricStates() const {
	return findStatesImpl<EnumStringMetricState>();
}

std::vector<MdsState> MdState::findMdsStates() const {
	return findStatesImpl<MdsState>();
}

std::vector<LimitAlertConditionState> MdState::findLimitAlertConditionStates() const {
	return findStatesImpl<LimitAlertConditionState>();
}

std::vector<LocationContextState> MdState::findLocationContextStates() const {
	return findStatesImpl<LocationContextState>();
}

std::vector<NumericMetricState> MdState::findNumericMetricStates() const {
	return findStatesImpl<NumericMetricState>();
}

std::vector<OperatorContextState> MdState::findOperatorContextStates() const {
	return findStatesImpl<OperatorContextState>();
}

std::vector<PatientContextState> MdState::findPatientContextStates() const {
	return findStatesImpl<PatientContextState>();
}

std::vector<RealTimeSampleArrayMetricState> MdState::findRealTimeSampleArrayMetricStates() const {
	return findStatesImpl<RealTimeSampleArrayMetricState>();
}

std::vector<StringMetricState> MdState::findStringMetricStates() const {
	return findStatesImpl<StringMetricState, EnumStringMetricState>();
}

std::vector<WorkflowContextState> MdState::findWorkflowContextStates() const {
	return findStatesImpl<WorkflowContextState>();
}

template <class WrapperStateDescriptorType>
std::vector<WrapperStateDescriptorType> MdState::findStatesImpl() const {
	std::vector<WrapperStateDescriptorType> result;
	const CDM::MdState & mdstate(*this->data);
	for (const auto & state : mdstate.State()) {
		if (const typename WrapperStateDescriptorType::WrappedType * foundState = dynamic_cast<const typename WrapperStateDescriptorType::WrappedType *>(&state)) {
			result.push_back(ConvertFromCDM::convert(*foundState));
		}
	}
	return result;
}

template <class WrapperStateDescriptorType, class ForbiddenType>
std::vector<WrapperStateDescriptorType> MdState::findStatesImpl() const {
	std::vector<WrapperStateDescriptorType> result;
	const CDM::MdState & mdstate(*this->data);
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
