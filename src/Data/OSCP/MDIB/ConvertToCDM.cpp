/*
 * ConvertToCDM.cpp
 *
 *  Created on: 26.01.2015
 *      Author: roehser
 */

#include "OSCLib/Data/OSCP/MDIB/ActivateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionReference.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/Annotation.h"
#include "OSCLib/Data/OSCP/MDIB/BaseDemographics.h"
#include "OSCLib/Data/OSCP/MDIB/Base64Binary.h"
#include "OSCLib/Data/OSCP/MDIB/CalibrationInfo.h"
#include "OSCLib/Data/OSCP/MDIB/CauseInfo.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ClinicalInfo.h"
#include "OSCLib/Data/OSCP/MDIB/ClockDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ClockState.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/ComponentState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/DateTime.h"
#include "OSCLib/Data/OSCP/MDIB/DICOMDeviceDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/DICOMNetworkAE.h"
#include "OSCLib/Data/OSCP/MDIB/DICOMNetworkConnection.h"
#include "OSCLib/Data/OSCP/MDIB/DICOMTransferCapability.h"
#include "OSCLib/Data/OSCP/MDIB/Duration.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextState.h"
#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/MDIB/EnumNomenRef.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSState.h"
#include "OSCLib/Data/OSCP/MDIB/ImagingProcedure.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/Language.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextState.h"
#include "OSCLib/Data/OSCP/MDIB/MDIBContainer.h"
#include "OSCLib/Data/OSCP/MDIB/MDDescription.h"
#include "OSCLib/Data/OSCP/MDIB/MDState.h"
#include "OSCLib/Data/OSCP/MDIB/Measure.h"
#include "OSCLib/Data/OSCP/MDIB/MeasurementState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/OperationState.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextState.h"
#include "OSCLib/Data/OSCP/MDIB/Order.h"
#include "OSCLib/Data/OSCP/MDIB/OrderDetail.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextState.h"
#include "OSCLib/Data/OSCP/MDIB/PatientDemographicsCoreData.h"
#include "OSCLib/Data/OSCP/MDIB/PersonParticipation.h"
#include "OSCLib/Data/OSCP/MDIB/PersonReference.h"
#include "OSCLib/Data/OSCP/MDIB/ProductionSpecification.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayValue.h"
#include "OSCLib/Data/OSCP/MDIB/ReferencedVersion.h"
#include "OSCLib/Data/OSCP/MDIB/RemedyInfo.h"
#include "OSCLib/Data/OSCP/MDIB/RTValueType.h"
#include "OSCLib/Data/OSCP/MDIB/SampleIndex.h"
#include "OSCLib/Data/OSCP/MDIB/SCODescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContext.h"
#include "OSCLib/Data/OSCP/MDIB/SystemMetaData.h"
#include "OSCLib/Data/OSCP/MDIB/Timestamp.h"
#include "OSCLib/Data/OSCP/MDIB/TimeZone.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"
#include "OSCLib/Data/OSCP/MDIB/VMDDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextState.h"

#include "osdm.hxx"

#include <stdexcept>

namespace OSCLib {
namespace Data {
namespace OSCP {

ConvertToCDM::ConvertToCDM() {

}

ConvertToCDM::~ConvertToCDM() {

}

bool ConvertToCDM::convert(const bool & source) {
	return source;
}

double ConvertToCDM::convert(const double & source) {
	return source;
}

unsigned int ConvertToCDM::convert(const unsigned int & source) {
	return source;
}

int ConvertToCDM::convert(const int & source) {
	return source;
}

long ConvertToCDM::convert(const long & source) {
	return source;
}

long long ConvertToCDM::convert(const long long & source) {
	return source;
}

std::string ConvertToCDM::convert(const std::string & source) {
	return source;
}

unsigned short int ConvertToCDM::convert(const unsigned short int & source) {
	return source;
}

CDM::AlertConditionKind ConvertToCDM::convert(const AlertConditionKind & source) {
	switch (source) {
		case AlertConditionKind::PHYSIOLOGICAL: return CDM::AlertConditionKind::Phy;
		case AlertConditionKind::TECHNICAL: return CDM::AlertConditionKind::Tec;
		case AlertConditionKind::OTHER: return CDM::AlertConditionKind::Oth;
	}
	throw std::runtime_error("Illegal value for AlertConditionKind");
}

CDM::AlertConditionPriority ConvertToCDM::convert(const AlertConditionPriority & source) {
	switch (source) {
		case AlertConditionPriority::LOW: return CDM::AlertConditionPriority::Lo;
		case AlertConditionPriority::MEDIUM: return CDM::AlertConditionPriority::Me;
		case AlertConditionPriority::HIGH: return CDM::AlertConditionPriority::Hi;
		case AlertConditionPriority::NONE: return CDM::AlertConditionPriority::None;
	}
	throw std::runtime_error("Illegal value for AlertConditionPriority");
}

CDM::AlertSignalManifestation ConvertToCDM::convert(const AlertSignalManifestation & source) {
	switch (source) {
		case AlertSignalManifestation::AUDIBLE: return CDM::AlertSignalManifestation::Aud;
		case AlertSignalManifestation::VISIBLE: return CDM::AlertSignalManifestation::Vis;
		case AlertSignalManifestation::TANGIBLE: return CDM::AlertSignalManifestation::Tan;
	}
	throw std::runtime_error("Illegal value for AlertSignalManifestation");
}

CDM::CalibrationState ConvertToCDM::convert(const CalibrationState & source) {
	switch (source) {
		case CalibrationState::CALIBRATED: return CDM::CalibrationState::Cal;
		case CalibrationState::CALIBRATION_REQUIRED: return CDM::CalibrationState::Req;
		case CalibrationState::NOT_CALIBRATED: return CDM::CalibrationState::No;
	}
	throw std::runtime_error("Illegal value for CalibrationState");
}

CDM::ComponentActivation ConvertToCDM::convert(const ComponentActivation & source) {
	switch (source) {
		case ComponentActivation::OFF: return CDM::ComponentActivation::Off;
		case ComponentActivation::ON: return CDM::ComponentActivation::On;
		case ComponentActivation::NOT_READY: return CDM::ComponentActivation::NotRdy;
		case ComponentActivation::STANDBY: return CDM::ComponentActivation::StndBy;
		case ComponentActivation::SHUTDOWN: return CDM::ComponentActivation::Shtdn;
	}
	throw std::runtime_error("Illegal value for ComponentActivation");
}

CDM::ContextAssociation ConvertToCDM::convert(const ContextAssociation & source) {
	switch (source) {
		case ContextAssociation::ASSOCIATED: return CDM::ContextAssociation::Assoc;
		case ContextAssociation::DISASSOCIATED: return CDM::ContextAssociation::Dis;
		case ContextAssociation::NO_ASSOCIATION: return CDM::ContextAssociation::No;
		case ContextAssociation::PRE_ASSOCIATION: return CDM::ContextAssociation::Pre;
	}
	throw std::runtime_error("Illegal value for ContextAssociation");
}

CDM::DicomTransferRole ConvertToCDM::convert(const DicomTransferRole & source) {
	switch (source) {
		case DicomTransferRole::SCU: return CDM::DicomTransferRole::SCU;
		case DicomTransferRole::SCP: return CDM::DicomTransferRole::SCP;
	}
	throw std::runtime_error("Illegal value for DICOMTransferRole");
}

CDM::GenerationMode ConvertToCDM::convert(const GenerationMode & source) {
	switch (source) {
		case GenerationMode::DEMO_DATA: return CDM::GenerationMode::Demo;
		case GenerationMode::REAL_DATA: return CDM::GenerationMode::Real;
		case GenerationMode::TEST_DATA: return CDM::GenerationMode::Test;
	}
	throw std::runtime_error("Illegal value for GenerationMode");
}

CDM::InvocationState ConvertToCDM::convert(const InvocationState & source) {
	switch (source) {
		case InvocationState::FAILED: return CDM::InvocationState::Fail;
		case InvocationState::WAITING: return CDM::InvocationState::Wait;
		case InvocationState::STARTED: return CDM::InvocationState::Start;
		case InvocationState::CANCELLED: return CDM::InvocationState::Cnclld;
		case InvocationState::CANCELLED_MANUALLY: return CDM::InvocationState::CnclldMan;
		case InvocationState::FINISHED: return CDM::InvocationState::Fin;
	}
	throw std::runtime_error("Illegal value for InvocationState");
}

CDM::MetricAvailability ConvertToCDM::convert(const MetricAvailability & source) {
	switch (source) {
		case MetricAvailability::INTERMITTENT: return CDM::MetricAvailability::Intr;
		case MetricAvailability::CONTINUOUS: return CDM::MetricAvailability::Cont;
	}
	throw std::runtime_error("Illegal value for MetricAvailability");
}

CDM::MetricCategory ConvertToCDM::convert(const MetricCategory & source) {
	switch (source) {
		case MetricCategory::UNSPECIFIED: return CDM::MetricCategory::Unspec;
		case MetricCategory::MEASUREMENT: return CDM::MetricCategory::Msrmt;
		case MetricCategory::CALCULATION: return CDM::MetricCategory::Clc;
		case MetricCategory::SETTING: return CDM::MetricCategory::Set;
		case MetricCategory::PRESETTING: return CDM::MetricCategory::Preset;
		case MetricCategory::RECOMMENDATION: return CDM::MetricCategory::Rcmm;
	}
	throw std::runtime_error("Illegal value for MetricCategory");
}

CDM::MeasurementValidity ConvertToCDM::convert(const MeasurementValidity & source) {
	switch (source) {
		case MeasurementValidity::Valid: return CDM::MetricMeasurementValidity::Vld;
		case MeasurementValidity::ValidatedData: return CDM::MetricMeasurementValidity::Vldated;
		case MeasurementValidity::Questionable: return CDM::MetricMeasurementValidity::Qst;
		case MeasurementValidity::CalibrationOngoing: return CDM::MetricMeasurementValidity::Calib;
		case MeasurementValidity::Invalid: return CDM::MetricMeasurementValidity::Inv;
		case MeasurementValidity::Overflow: return CDM::MetricMeasurementValidity::Oflw;
		case MeasurementValidity::Underflow: return CDM::MetricMeasurementValidity::Uflw;
	}
	throw std::runtime_error("Illegal value for MetricMeasurementValidity");
}

CDM::MetricRetrievability ConvertToCDM::convert(const MetricRetrievability & source) {
	switch (source) {
		case MetricRetrievability::GET: return CDM::MetricRetrievability::Get;
		case MetricRetrievability::PERIODIC: return CDM::MetricRetrievability::Per;
		case MetricRetrievability::EPISODIC: return CDM::MetricRetrievability::Ep;
		case MetricRetrievability::STREAM: return CDM::MetricRetrievability::Strm;
	}
	throw std::runtime_error("Illegal value for Retrievability");
}

CDM::MonitoredAlertLimits ConvertToCDM::convert(const MonitoredAlertLimits & source) {
	switch (source) {
		case MonitoredAlertLimits::NONE: return CDM::MonitoredAlertLimits::None;
		case MonitoredAlertLimits::LOW_OFF: return CDM::MonitoredAlertLimits::LoOff;
		case MonitoredAlertLimits::HIGH_OFF: return CDM::MonitoredAlertLimits::HiOff;
		case MonitoredAlertLimits::ALL: return CDM::MonitoredAlertLimits::All;
	}
	throw std::runtime_error("Illegal value for MonitoredAlertLimits");
}

CDM::OperatingMode ConvertToCDM::convert(const OperatingMode & source) {
	switch (source) {
		case OperatingMode::DISABLED: return CDM::OperatingMode::Dis;
		case OperatingMode::ENABLED: return CDM::OperatingMode::En;
		case OperatingMode::NOT_AVAILABLE: return CDM::OperatingMode::NA;
	}
	throw std::runtime_error("Illegal value for OperatingMode");
}

CDM::PatientType ConvertToCDM::convert(const PatientType & source) {
	switch (source) {
		case PatientType::ADULT: return CDM::PatientType::Ad;
		case PatientType::NEONATAL: return CDM::PatientType::Neo;
		case PatientType::PEDIATRIC: return CDM::PatientType::Ped;
		case PatientType::UNSPECIFIED: return CDM::PatientType::Unspec;
	}
	throw std::runtime_error("Illegal value for PatientType");
}

CDM::PausableActivation ConvertToCDM::convert(const PausableActivation & source) {
	switch (source) {
		case PausableActivation::OFF: return CDM::PausableActivation::Off;
		case PausableActivation::ON: return CDM::PausableActivation::On;
		case PausableActivation::PAUSED: return CDM::PausableActivation::Psd;
	}
	throw std::runtime_error("Illegal value for PausableActivation");
}

CDM::PrimaryAlertSignalLocation ConvertToCDM::convert(const PrimaryAlertSignalLocation & source) {
	switch (source) {
		case PrimaryAlertSignalLocation::LOCAL: return CDM::PrimaryAlertSignalLocation::Loc;
		case PrimaryAlertSignalLocation::REMOTE: return CDM::PrimaryAlertSignalLocation::Rem;
	}
	throw std::runtime_error("Illegal value for PrimaryAlertSignalLocation");
}

CDM::Sex ConvertToCDM::convert(const Sex & source) {
	switch (source) {
		case Sex::UNSPECIFIED: return CDM::Sex::Unspec;
		case Sex::MALE: return CDM::Sex::M;
		case Sex::FEMALE: return CDM::Sex::F;
		case Sex::UNKNOWN: return CDM::Sex::Unkn;
	}
	throw std::runtime_error("Illegal value for Sex");
}

CDM::SignalPresence ConvertToCDM::convert(const SignalPresence & source) {
	switch (source) {
		case SignalPresence::On: return CDM::SignalPresence::On;
		case SignalPresence::Off: return CDM::SignalPresence::Off;
		case SignalPresence::Ack: return CDM::SignalPresence::Ack;
		case SignalPresence::Latch: return CDM::SignalPresence::Latch;
	}
	throw std::runtime_error("Illegal value for SignalPresence");
}

template <class WrapperType>
std::unique_ptr<typename WrapperType::WrappedType> ConvertToCDM::convert(const WrapperType & source) {
	return std::unique_ptr<typename WrapperType::WrappedType>(source.data->_clone());
}

template
std::unique_ptr<typename ActivateOperationDescriptor::WrappedType> ConvertToCDM::convert(const ActivateOperationDescriptor & source);

template
std::unique_ptr<typename AlertConditionDescriptor::WrappedType> ConvertToCDM::convert(const AlertConditionDescriptor & source);

template
std::unique_ptr<typename AlertConditionReference::WrappedType> ConvertToCDM::convert(const AlertConditionReference & source);

template
std::unique_ptr<typename AlertConditionState::WrappedType> ConvertToCDM::convert(const AlertConditionState & source);

template
std::unique_ptr<typename AlertSignalDescriptor::WrappedType> ConvertToCDM::convert(const AlertSignalDescriptor & source);

template
std::unique_ptr<typename AlertSignalState::WrappedType> ConvertToCDM::convert(const AlertSignalState & source);

template
std::unique_ptr<typename AlertSystemDescriptor::WrappedType> ConvertToCDM::convert(const AlertSystemDescriptor & source);

template
std::unique_ptr<typename AlertSystemState::WrappedType> ConvertToCDM::convert(const AlertSystemState & source);

template
std::unique_ptr<typename Annotation::WrappedType> ConvertToCDM::convert(const Annotation & source);

template
std::unique_ptr<typename Base64Binary::WrappedType> ConvertToCDM::convert(const Base64Binary & source);

template
std::unique_ptr<typename BaseDemographics::WrappedType> ConvertToCDM::convert(const BaseDemographics & source);

template
std::unique_ptr<typename CalibrationInfo::WrappedType> ConvertToCDM::convert(const CalibrationInfo & source);

template
std::unique_ptr<typename CauseInfo::WrappedType> ConvertToCDM::convert(const CauseInfo & source);

template
std::unique_ptr<typename ChannelDescriptor::WrappedType> ConvertToCDM::convert(const ChannelDescriptor & source);

template
std::unique_ptr<typename ClinicalInfo::WrappedType> ConvertToCDM::convert(const ClinicalInfo & source);

template
std::unique_ptr<typename ClockDescriptor::WrappedType> ConvertToCDM::convert(const ClockDescriptor & source);

template
std::unique_ptr<typename ClockState::WrappedType> ConvertToCDM::convert(const ClockState & source);

template
std::unique_ptr<typename CodedValue::WrappedType> ConvertToCDM::convert(const CodedValue & source);

template
std::unique_ptr<typename ComponentState::WrappedType> ConvertToCDM::convert(const ComponentState & source);

template
std::unique_ptr<typename DateTime::WrappedType> ConvertToCDM::convert(const DateTime & source);

template
std::unique_ptr<typename DICOMDeviceDescriptor::WrappedType> ConvertToCDM::convert(const DICOMDeviceDescriptor & source);

template
std::unique_ptr<typename DICOMNetworkAE::WrappedType> ConvertToCDM::convert(const DICOMNetworkAE & source);

template
std::unique_ptr<typename DICOMNetworkConnection::WrappedType> ConvertToCDM::convert(const DICOMNetworkConnection & source);

template
std::unique_ptr<typename DICOMTransferCapability::WrappedType> ConvertToCDM::convert(const DICOMTransferCapability & source);

template
std::unique_ptr<typename Duration::WrappedType> ConvertToCDM::convert(const Duration & source);

template
std::unique_ptr<typename EnsembleContextDescriptor::WrappedType> ConvertToCDM::convert(const EnsembleContextDescriptor & source);

template
std::unique_ptr<typename EnsembleContextState::WrappedType> ConvertToCDM::convert(const EnsembleContextState & source);

template
std::unique_ptr<typename EnumNomenRef::WrappedType> ConvertToCDM::convert(const EnumNomenRef & source);

template
std::unique_ptr<typename EnumStringMetricDescriptor::WrappedType> ConvertToCDM::convert(const EnumStringMetricDescriptor & source);

template
std::unique_ptr<typename EnumStringMetricState::WrappedType> ConvertToCDM::convert(const EnumStringMetricState & source);

template
std::unique_ptr<typename HydraMDSDescriptor::WrappedType> ConvertToCDM::convert(const HydraMDSDescriptor & source);

template
std::unique_ptr<typename HydraMDSState::WrappedType> ConvertToCDM::convert(const HydraMDSState & source);

template
std::unique_ptr<typename ImagingProcedure::WrappedType> ConvertToCDM::convert(const ImagingProcedure & source);

template
std::unique_ptr<typename InstanceIdentifier::WrappedType> ConvertToCDM::convert(const InstanceIdentifier & source);

template
std::unique_ptr<typename Language::WrappedType> ConvertToCDM::convert(const Language & source);

template
std::unique_ptr<typename LimitAlertConditionDescriptor::WrappedType> ConvertToCDM::convert(const LimitAlertConditionDescriptor & source);

template
std::unique_ptr<typename LimitAlertConditionState::WrappedType> ConvertToCDM::convert(const LimitAlertConditionState & source);

template
std::unique_ptr<typename LocalizedText::WrappedType> ConvertToCDM::convert(const LocalizedText & source);

template
std::unique_ptr<typename LocationContextDescriptor::WrappedType> ConvertToCDM::convert(const LocationContextDescriptor & source);

template
std::unique_ptr<typename LocationContextState::WrappedType> ConvertToCDM::convert(const LocationContextState & source);

template <>
std::unique_ptr<typename MDIBContainer::WrappedType> ConvertToCDM::convert(const MDIBContainer & source) {
	return std::unique_ptr<typename MDIBContainer::WrappedType>(new MDIBContainer::WrappedType(convert(source.getMDDescription()), convert(source.getMDState()), source.getMDIBVersion()));
}

template
std::unique_ptr<typename MDDescription::WrappedType> ConvertToCDM::convert(const MDDescription & source);

template
std::unique_ptr<typename MDState::WrappedType> ConvertToCDM::convert(const MDState & source);

template
std::unique_ptr<typename Measure::WrappedType> ConvertToCDM::convert(const Measure & source);

template
std::unique_ptr<typename MeasurementState::WrappedType> ConvertToCDM::convert(const MeasurementState & source);

template
std::unique_ptr<typename NumericMetricDescriptor::WrappedType> ConvertToCDM::convert(const NumericMetricDescriptor & source);

template
std::unique_ptr<typename NumericMetricState::WrappedType> ConvertToCDM::convert(const NumericMetricState & source);

template
std::unique_ptr<typename NumericMetricValue::WrappedType> ConvertToCDM::convert(const NumericMetricValue & source);

template
std::unique_ptr<typename OperationState::WrappedType> ConvertToCDM::convert(const OperationState & source);

template
std::unique_ptr<typename OperatorContextDescriptor::WrappedType> ConvertToCDM::convert(const OperatorContextDescriptor & source);

template
std::unique_ptr<typename OperatorContextState::WrappedType> ConvertToCDM::convert(const OperatorContextState & source);

template
std::unique_ptr<typename Order::WrappedType> ConvertToCDM::convert(const Order & source);

template
std::unique_ptr<typename OrderDetail::WrappedType> ConvertToCDM::convert(const OrderDetail & source);

template
std::unique_ptr<typename PatientContextDescriptor::WrappedType> ConvertToCDM::convert(const PatientContextDescriptor & source);

template
std::unique_ptr<typename PatientContextState::WrappedType> ConvertToCDM::convert(const PatientContextState & source);

template
std::unique_ptr<typename PatientDemographicsCoreData::WrappedType> ConvertToCDM::convert(const PatientDemographicsCoreData & source);

template
std::unique_ptr<typename PersonParticipation::WrappedType> ConvertToCDM::convert(const PersonParticipation & source);

template
std::unique_ptr<typename PersonReference::WrappedType> ConvertToCDM::convert(const PersonReference & source);

template
std::unique_ptr<typename ProductionSpecification::WrappedType> ConvertToCDM::convert(const ProductionSpecification & source);

template
std::unique_ptr<typename Range::WrappedType> ConvertToCDM::convert(const Range & source);

template
std::unique_ptr<typename RealTimeSampleArrayMetricDescriptor::WrappedType> ConvertToCDM::convert(const RealTimeSampleArrayMetricDescriptor & source);

template
std::unique_ptr<typename RealTimeSampleArrayMetricState::WrappedType> ConvertToCDM::convert(const RealTimeSampleArrayMetricState & source);

template
std::unique_ptr<typename RealTimeSampleArrayValue::WrappedType> ConvertToCDM::convert(const RealTimeSampleArrayValue & source);

template
std::unique_ptr<typename ReferencedVersion::WrappedType> ConvertToCDM::convert(const ReferencedVersion & source);

template
std::unique_ptr<typename RemedyInfo::WrappedType> ConvertToCDM::convert(const RemedyInfo & source);

template
std::unique_ptr<typename RTValueType::WrappedType> ConvertToCDM::convert(const RTValueType & source);

template
std::unique_ptr<typename SampleIndex::WrappedType> ConvertToCDM::convert(const SampleIndex & source);

template
std::unique_ptr<typename SCODescriptor::WrappedType> ConvertToCDM::convert(const SCODescriptor & source);

template
std::unique_ptr<typename StringMetricDescriptor::WrappedType> ConvertToCDM::convert(const StringMetricDescriptor & source);

template
std::unique_ptr<typename StringMetricState::WrappedType> ConvertToCDM::convert(const StringMetricState & source);

template
std::unique_ptr<typename StringMetricValue::WrappedType> ConvertToCDM::convert(const StringMetricValue & source);

template
std::unique_ptr<typename SystemContext::WrappedType> ConvertToCDM::convert(const SystemContext & source);

template
std::unique_ptr<typename SystemMetaData::WrappedType> ConvertToCDM::convert(const SystemMetaData & source);

template
std::unique_ptr<typename Timestamp::WrappedType> ConvertToCDM::convert(const Timestamp & source);

template
std::unique_ptr<typename TimeZone::WrappedType> ConvertToCDM::convert(const TimeZone & source);

template
std::unique_ptr<typename VersionCounter::WrappedType> ConvertToCDM::convert(const VersionCounter & source);

template
std::unique_ptr<typename VMDDescriptor::WrappedType> ConvertToCDM::convert(const VMDDescriptor & source);

template
std::unique_ptr<typename WorkflowContextDescriptor::WrappedType> ConvertToCDM::convert(const WorkflowContextDescriptor & source);

template
std::unique_ptr<typename WorkflowContextState::WrappedType> ConvertToCDM::convert(const WorkflowContextState & source);

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
