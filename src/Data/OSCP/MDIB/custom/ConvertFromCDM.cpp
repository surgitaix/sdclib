/*
 * ConvertFromCDM.cpp
 *
 *  Created on: 26.01.2015
 *      Author: roehser
 */
#include "OSCLib/Data/OSCP/MDIB/ActivateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionReference.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/Annotation.h"
#include "OSCLib/Data/OSCP/MDIB/Base64Binary.h"
#include "OSCLib/Data/OSCP/MDIB/BaseDemographics.h"
#include "OSCLib/Data/OSCP/MDIB/CalibrationInfo.h"
#include "OSCLib/Data/OSCP/MDIB/CauseInfo.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ClinicalInfo.h"
#include "OSCLib/Data/OSCP/MDIB/ClockDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ClockState.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/ComponentState.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/DateTime.h"
#include "OSCLib/Data/OSCP/MDIB/DicomDeviceDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/DicomNetworkAE.h"
#include "OSCLib/Data/OSCP/MDIB/DicomNetworkConnection.h"
#include "OSCLib/Data/OSCP/MDIB/DicomTransferCapability.h"
#include "OSCLib/Data/OSCP/MDIB/Duration.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextState.h"
#include "OSCLib/Data/OSCP/MDIB/EnumNomenRef.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSState.h"
#include "OSCLib/Data/OSCP/MDIB/ImagingProcedure.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/Language.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextState.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
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
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextState.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayValue.h"
#include "OSCLib/Data/OSCP/MDIB/ReferencedVersion.h"
#include "OSCLib/Data/OSCP/MDIB/RemedyInfo.h"
#include "OSCLib/Data/OSCP/MDIB/RTValueType.h"
#include "OSCLib/Data/OSCP/MDIB/SampleIndex.h"
#include "OSCLib/Data/OSCP/MDIB/SCODescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetAlertStateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetContextOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetRangeOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetStringOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetValueOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContext.h"
#include "OSCLib/Data/OSCP/MDIB/SystemMetaData.h"
#include "OSCLib/Data/OSCP/MDIB/Timestamp.h"
#include "OSCLib/Data/OSCP/MDIB/TimeZone.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"
#include "OSCLib/Data/OSCP/MDIB/VMDDescriptor.h"

#include "osdm.hxx"

#include <stdexcept>

namespace OSCLib {
namespace Data {
namespace OSCP {

ConvertFromCDM::ConvertFromCDM() {

}

ConvertFromCDM::~ConvertFromCDM() {

}

bool ConvertFromCDM::convert(const bool & source) {
	return source;
}

double ConvertFromCDM::convert(const double & source) {
	return source;
}

unsigned short int ConvertFromCDM::convert(const unsigned short int & source) {
	return source;
}

unsigned int ConvertFromCDM::convert(const unsigned int & source) {
	return source;
}

int ConvertFromCDM::convert(const int & source) {
	return source;
}

long ConvertFromCDM::convert(const long & source) {
	return source;
}

long long ConvertFromCDM::convert(const long long & source) {
	return source;
}

std::string ConvertFromCDM::convert(const std::string & source) {
	return source;
}

Activation ConvertFromCDM::convert(const CDM::Activation & source) {
	switch(source) {
		case CDM::Activation::On: return Activation::ON; break;
		case CDM::Activation::Off: return Activation::OFF; break;
	}
	throw std::runtime_error("Illegal value for Activation");
}

ActivateOperationDescriptor ConvertFromCDM::convert(const CDM::ActivateOperationDescriptor & source) {
	return ActivateOperationDescriptor(source);
}

AlertConditionDescriptor ConvertFromCDM::convert(const CDM::AlertConditionDescriptor & source) {
	return AlertConditionDescriptor(source);
}

AlertConditionKind ConvertFromCDM::convert(const CDM::AlertConditionKind & source) {
	switch (source) {
		case CDM::AlertConditionKind::Phy: return AlertConditionKind::PHYSIOLOGICAL;
		case CDM::AlertConditionKind::Tec: return AlertConditionKind::TECHNICAL;
		case CDM::AlertConditionKind::Oth: return AlertConditionKind::OTHER;
	}
	throw std::runtime_error("Illegal value for AlertConditionKind");
}

AlertConditionPriority ConvertFromCDM::convert(const CDM::AlertConditionPriority & source) {
	switch (source) {
		case CDM::AlertConditionPriority::Lo: return AlertConditionPriority::LOW;
		case CDM::AlertConditionPriority::Me: return AlertConditionPriority::MEDIUM;
		case CDM::AlertConditionPriority::Hi: return AlertConditionPriority::HIGH;
		case CDM::AlertConditionPriority::None: return AlertConditionPriority::NONE;
	}
	throw std::runtime_error("Illegal value for AlertConditionPriority");
}

AlertConditionReference ConvertFromCDM::convert(const CDM::AlertConditionReference & source) {
	return AlertConditionReference(source);
}

AlertConditionState ConvertFromCDM::convert(const CDM::AlertConditionState & source) {
	return AlertConditionState(source);
}

AlertSignalDescriptor ConvertFromCDM::convert(const CDM::AlertSignalDescriptor & source) {
	return AlertSignalDescriptor(source);
}

AlertSignalManifestation ConvertFromCDM::convert(const CDM::AlertSignalManifestation & source) {
	switch (source) {
		case CDM::AlertSignalManifestation::Aud: return AlertSignalManifestation::AUDIBLE;
		case CDM::AlertSignalManifestation::Vis: return AlertSignalManifestation::VISIBLE;
		case CDM::AlertSignalManifestation::Tan: return AlertSignalManifestation::TANGIBLE;
	}
	throw std::runtime_error("Illegal value for AlertSignalManifestation");
}

AlertSignalState ConvertFromCDM::convert(const CDM::AlertSignalState & source) {
	return AlertSignalState(source);
}

AlertSystemDescriptor ConvertFromCDM::convert(const CDM::AlertSystemDescriptor & source) {
	return AlertSystemDescriptor(source);
}

AlertSystemState ConvertFromCDM::convert(const CDM::AlertSystemState & source) {
	return AlertSystemState(source);
}

Annotation ConvertFromCDM::convert(const CDM::Annotation & source) {
	return Annotation(source);
}

Base64Binary ConvertFromCDM::convert(const CDM::Base64Binary & source) {
	return Base64Binary(source);
}

BaseDemographics ConvertFromCDM::convert(const CDM::BaseDemographics & source) {
	return BaseDemographics(source);
}

CalibrationInfo ConvertFromCDM::convert(const CDM::CalibrationInfo & source) {
	return CalibrationInfo(source);
}

CalibrationState ConvertFromCDM::convert(const CDM::CalibrationState & source) {
	switch (source) {
		case CDM::CalibrationState::Cal: return CalibrationState::Calibrated;
		case CDM::CalibrationState::Req: return CalibrationState::CalibrationRequired;
		case CDM::CalibrationState::No: return CalibrationState::NotCalibrated;
	}
	throw std::runtime_error("Illegal value for CalibrationState");
}

CalibrationType ConvertFromCDM::convert(const CDM::CalibrationType & source) {
	switch (source) {
		case CDM::CalibrationType::Offset: return CalibrationType::Offset;
		case CDM::CalibrationType::Gain: return CalibrationType::Gain;
		case CDM::CalibrationType::TP: return CalibrationType::TwoPointCalibration;
		case CDM::CalibrationType::Unspec: return CalibrationType::Unspecified;
	}
	throw std::runtime_error("Illegal value for CalibrationType");
}

CauseInfo ConvertFromCDM::convert(const CDM::CauseInfo & source) {
	return CauseInfo(source);
}

ChannelDescriptor ConvertFromCDM::convert(const CDM::ChannelDescriptor & source) {
	return ChannelDescriptor(source);
}

ClinicalInfo ConvertFromCDM::convert(const CDM::ClinicalInfo & source) {
	return ClinicalInfo(source);
}

ClockDescriptor ConvertFromCDM::convert(const CDM::ClockDescriptor & source) {
	return ClockDescriptor(source);
}

ClockState ConvertFromCDM::convert(const CDM::ClockState & source) {
	return ClockState(source);
}

CodedValue ConvertFromCDM::convert(const CDM::CodedValue & source) {
	return CodedValue(source);
}

ComponentActivation ConvertFromCDM::convert(const CDM::ComponentActivation & source) {
	switch (source) {
		case CDM::ComponentActivation::Off: return ComponentActivation::OFF;
		case CDM::ComponentActivation::On: return ComponentActivation::ON;
		case CDM::ComponentActivation::NotRdy: return ComponentActivation::NOT_READY;
		case CDM::ComponentActivation::StndBy: return ComponentActivation::STANDBY;
		case CDM::ComponentActivation::Shtdn: return ComponentActivation::SHUTDOWN;
	}
	throw std::runtime_error("Illegal value for ComponentActivation");
}

ComponentState ConvertFromCDM::convert(const CDM::ComponentState & source) {
	return ComponentState(source);
}

ContextAssociation ConvertFromCDM::convert(const CDM::ContextAssociation & source) {
	switch (source) {
		case CDM::ContextAssociation::Assoc: return ContextAssociation::ASSOCIATED;
		case CDM::ContextAssociation::Dis: return ContextAssociation::DISASSOCIATED;
		case CDM::ContextAssociation::No: return ContextAssociation::NO_ASSOCIATION;
		case CDM::ContextAssociation::Pre: return ContextAssociation::PRE_ASSOCIATION;
	}
	throw std::runtime_error("Illegal value for ContextAssociation");
}

DateTime ConvertFromCDM::convert(const CDM::DateTime & source) {
	return DateTime(source);
}

DicomDeviceDescriptor ConvertFromCDM::convert(const CDM::DicomDeviceDescriptor & source) {
	return DicomDeviceDescriptor(source);
}

DicomNetworkAe ConvertFromCDM::convert(const CDM::DicomNetworkAe & source) {
	return DicomNetworkAe(source);
}

DicomNetworkConnection ConvertFromCDM::convert(const CDM::DicomNetworkConnection & source) {
	return DicomNetworkConnection(source);
}

DicomTransferCapability ConvertFromCDM::convert(const CDM::DicomTransferCapability & source) {
	return DicomTransferCapability(source);
}

DicomTransferRole ConvertFromCDM::convert(const CDM::DicomTransferRole & source) {
	switch (source) {
		case CDM::DicomTransferRole::SCU: return DicomTransferRole::SCU;
		case CDM::DicomTransferRole::SCP: return DicomTransferRole::SCP;
	}
	throw std::runtime_error("Illegal value for DicomTransferRole");
}

Duration ConvertFromCDM::convert(const CDM::Duration & source) {
	return Duration(source);
}

EnsembleContextDescriptor ConvertFromCDM::convert(const CDM::EnsembleContextDescriptor & source) {
	return EnsembleContextDescriptor(source);
}

EnsembleContextState ConvertFromCDM::convert(const CDM::EnsembleContextState & source) {
	return EnsembleContextState(source);
}

EnumNomenRef ConvertFromCDM::convert(const CDM::EnumNomenRef & source) {
	return EnumNomenRef(source);
}

EnumStringMetricDescriptor ConvertFromCDM::convert(const CDM::EnumStringMetricDescriptor & source) {
	return EnumStringMetricDescriptor(source);
}

EnumStringMetricState ConvertFromCDM::convert(const CDM::EnumStringMetricState & source) {
	return EnumStringMetricState(source);
}

GenerationMode ConvertFromCDM::convert(const CDM::GenerationMode & source) {
	switch (source) {
		case CDM::GenerationMode::Demo: return GenerationMode::DEMO_DATA;
		case CDM::GenerationMode::Real: return GenerationMode::REAL_DATA;
		case CDM::GenerationMode::Test: return GenerationMode::TEST_DATA;
	}
	throw std::runtime_error("Illegal value for GenerationMode");
}

HydraMDSDescriptor ConvertFromCDM::convert(const CDM::HydraMDSDescriptor & source) {
	return HydraMDSDescriptor(source);
}

HydraMDSState ConvertFromCDM::convert(const CDM::HydraMDSState & source) {
	return HydraMDSState(source);
}

ImagingProcedure ConvertFromCDM::convert(const CDM::ImagingProcedure & source) {
	return ImagingProcedure(source);
}

InstanceIdentifier ConvertFromCDM::convert(const CDM::InstanceIdentifier & source) {
	return InstanceIdentifier(source);
}

IntendedUse ConvertFromCDM::convert(const CDM::IntendedUse & source) {
	switch (source) {
		case CDM::IntendedUse::Inf: return IntendedUse::INFORMATIONAL;
		case CDM::IntendedUse::MedA: return IntendedUse::MEDICAL_A;
		case CDM::IntendedUse::MedB: return IntendedUse::MEDICAL_B;
		case CDM::IntendedUse::MedC: return IntendedUse::MEDICAL_C;
	}
	throw std::runtime_error("Illegal value for IntendedUse");
}

InvocationState ConvertFromCDM::convert(const CDM::InvocationState & source) {
	switch (source) {
		case CDM::InvocationState::Fail: return InvocationState::FAILED;
		case CDM::InvocationState::Wait: return InvocationState::WAITING;
		case CDM::InvocationState::Start: return InvocationState::STARTED;
		case CDM::InvocationState::Cnclld: return InvocationState::CANCELLED;
		case CDM::InvocationState::CnclldMan: return InvocationState::CANCELLED_MANUALLY;
		case CDM::InvocationState::Fin: return InvocationState::FINISHED;
	}
	throw std::runtime_error("Illegal value for InvocationState");
}

Language ConvertFromCDM::convert(const CDM::Language & source) {
	return Language(source);
}

LimitAlertConditionDescriptor ConvertFromCDM::convert(const CDM::LimitAlertConditionDescriptor & source) {
	return LimitAlertConditionDescriptor(source);
}

LimitAlertConditionState ConvertFromCDM::convert(const CDM::LimitAlertConditionState & source) {
	return LimitAlertConditionState(source);
}

LocalizedText ConvertFromCDM::convert(const CDM::LocalizedText & source) {
	return LocalizedText(source);
}

LocationContextDescriptor ConvertFromCDM::convert(const CDM::LocationContextDescriptor & source) {
	return LocationContextDescriptor(source);
}

LocationContextState ConvertFromCDM::convert(const CDM::LocationContextState & source) {
	return LocationContextState(source);
}

MDDescription ConvertFromCDM::convert(const CDM::MDDescription & source) {
	return MDDescription(source);
}

MDState ConvertFromCDM::convert(const CDM::MDState & source) {
	return MDState(source);
}

Measure ConvertFromCDM::convert(const CDM::Measure & source) {
	return Measure(source);
}

MeasurementState ConvertFromCDM::convert(const CDM::MeasurementState & source) {
	return MeasurementState(source);
}

MetricAvailability ConvertFromCDM::convert(const CDM::MetricAvailability & source) {
	switch (source) {
		case CDM::MetricAvailability::Intr: return MetricAvailability::INTERMITTENT;
		case CDM::MetricAvailability::Cont: return MetricAvailability::CONTINUOUS;
	}
	throw std::runtime_error("Illegal value for MetricAvailability");
}

MetricCategory ConvertFromCDM::convert(const CDM::MetricCategory & source) {
	switch (source) {
		case CDM::MetricCategory::Unspec: return MetricCategory::UNSPECIFIED;
		case CDM::MetricCategory::Msrmt: return MetricCategory::MEASUREMENT;
		case CDM::MetricCategory::Clc: return MetricCategory::CALCULATION;
		case CDM::MetricCategory::Set: return MetricCategory::SETTING;
		case CDM::MetricCategory::Preset: return MetricCategory::PRESETTING;
		case CDM::MetricCategory::Rcmm: return MetricCategory::RECOMMENDATION;
	}
	throw std::runtime_error("Illegal value for MetricCategory");
}

MeasurementValidity ConvertFromCDM::convert(const CDM::MeasurementValidity & source) {
	switch (source) {
		case CDM::MeasurementValidity::Vld: return MeasurementValidity::Valid;
		case CDM::MeasurementValidity::Vldated: return MeasurementValidity::ValidatedData;
		case CDM::MeasurementValidity::Ong: return MeasurementValidity::Ongoing;
		case CDM::MeasurementValidity::Qst: return MeasurementValidity::Questionable;
		case CDM::MeasurementValidity::Calib: return MeasurementValidity::CalibrationOngoing;
		case CDM::MeasurementValidity::Inv: return MeasurementValidity::Invalid;
		case CDM::MeasurementValidity::Oflw: return MeasurementValidity::Overflow;
		case CDM::MeasurementValidity::Uflw: return MeasurementValidity::Underflow;
		case CDM::MeasurementValidity::NA: return MeasurementValidity::NotAvailable;
	}
	throw std::runtime_error("Illegal value for MetricMeasurementValidity");
}

AlertConditionMonitoredLimits ConvertFromCDM::convert(const CDM::AlertConditionMonitoredLimits & source) {
	switch (source) {
		case CDM::AlertConditionMonitoredLimits::None: return AlertConditionMonitoredLimits::None;
		case CDM::AlertConditionMonitoredLimits::LoOff: return AlertConditionMonitoredLimits::LoOff;
		case CDM::AlertConditionMonitoredLimits::HiOff: return AlertConditionMonitoredLimits::HiOff;
		case CDM::AlertConditionMonitoredLimits::All: return AlertConditionMonitoredLimits::All;
	}
	throw std::runtime_error("Illegal value for MonitoredAlertLimits");
}

NumericMetricDescriptor ConvertFromCDM::convert(const CDM::NumericMetricDescriptor & source) {
	return NumericMetricDescriptor(source);
}

NumericMetricState ConvertFromCDM::convert(const CDM::NumericMetricState & source) {
	return NumericMetricState(source);
}

NumericMetricValue ConvertFromCDM::convert(const CDM::NumericMetricValue & source) {
	return NumericMetricValue(source);
}

OperatingMode ConvertFromCDM::convert(const CDM::OperatingMode & source) {
	switch (source) {
		case CDM::OperatingMode::Dis: return OperatingMode::DISABLED;
		case CDM::OperatingMode::En: return OperatingMode::ENABLED;
		case CDM::OperatingMode::NA: return OperatingMode::NOT_AVAILABLE;
	}
	throw std::runtime_error("Illegal value for OperatingMode");
}

OperationState ConvertFromCDM::convert(const CDM::OperationState & source) {
	return OperationState(source);
}

OperatorContextDescriptor ConvertFromCDM::convert(const CDM::OperatorContextDescriptor & source) {
	return OperatorContextDescriptor(source);
}

OperatorContextState ConvertFromCDM::convert(const CDM::OperatorContextState & source) {
	return OperatorContextState(source);
}

Order ConvertFromCDM::convert(const CDM::Order & source) {
	return Order(source);
}

OrderDetail ConvertFromCDM::convert(const CDM::OrderDetail & source) {
	return OrderDetail(source);
}

PatientContextDescriptor ConvertFromCDM::convert(const CDM::PatientContextDescriptor & source) {
	return PatientContextDescriptor(source);
}

PatientContextState ConvertFromCDM::convert(const CDM::PatientContextState & source) {
	return PatientContextState(source);
}

PatientDemographicsCoreData ConvertFromCDM::convert(const CDM::PatientDemographicsCoreData & source) {
	return PatientDemographicsCoreData(source);
}

PatientType ConvertFromCDM::convert(const CDM::PatientType & source) {
	switch (source) {
		case CDM::PatientType::Ad: return PatientType::ADULT;
		case CDM::PatientType::Neo: return PatientType::NEONATAL;
		case CDM::PatientType::Ped: return PatientType::PEDIATRIC;
		case CDM::PatientType::Unspec: return PatientType::UNSPECIFIED;
	}
	throw std::runtime_error("Illegal value for PatientType");
}

AlertActivation ConvertFromCDM::convert(const CDM::AlertActivation & source) {
	switch (source) {
		case CDM::AlertActivation::Off: return AlertActivation::Off;
		case CDM::AlertActivation::On: return AlertActivation::On;
		case CDM::AlertActivation::Psd: return AlertActivation::Paused;
	}
	throw std::runtime_error("Illegal value for AlertActivation");
}

PersonParticipation ConvertFromCDM::convert(const CDM::PersonParticipation & source) {
	return PersonParticipation(source);
}

PersonReference ConvertFromCDM::convert(const CDM::PersonReference & source) {
	return PersonReference(source);
}

AlertSignalPrimaryLocation ConvertFromCDM::convert(const CDM::AlertSignalPrimaryLocation & source) {
	switch (source) {
		case CDM::AlertSignalPrimaryLocation::Loc: return AlertSignalPrimaryLocation::Local;
		case CDM::AlertSignalPrimaryLocation::Rem: return AlertSignalPrimaryLocation::Remote;
	}
	throw std::runtime_error("Illegal value for PrimaryAlertSignalLocation");
}

ProductionSpecification ConvertFromCDM::convert(const CDM::ProductionSpecification & source) {
	return ProductionSpecification(source);
}

Range ConvertFromCDM::convert(const CDM::Range & source) {
	return Range(source);
}

RealTimeSampleArrayMetricDescriptor ConvertFromCDM::convert(const CDM::RealTimeSampleArrayMetricDescriptor & source) {
	return RealTimeSampleArrayMetricDescriptor(source);
}

RealTimeSampleArrayMetricState ConvertFromCDM::convert(const CDM::RealTimeSampleArrayMetricState & source) {
	return RealTimeSampleArrayMetricState(source);
}

RealTimeSampleArrayValue ConvertFromCDM::convert(const CDM::RealTimeSampleArrayValue & source) {
	return RealTimeSampleArrayValue(source);
}

ReferencedVersion ConvertFromCDM::convert(const CDM::ReferencedVersion & source) {
	return ReferencedVersion(source);
}

RemedyInfo ConvertFromCDM::convert(const CDM::RemedyInfo & source) {
	return RemedyInfo(source);
}

RTValueType ConvertFromCDM::convert(const CDM::RTValueType & source) {
	return RTValueType(source);
}

SampleIndex ConvertFromCDM::convert(const CDM::SampleIndex & source) {
	return SampleIndex(source);
}

SCODescriptor ConvertFromCDM::convert(const CDM::SCODescriptor & source) {
	return SCODescriptor(source);
}

SetAlertStateOperationDescriptor ConvertFromCDM::convert(const CDM::SetAlertStateOperationDescriptor & source) {
	return SetAlertStateOperationDescriptor(source);
}

SetContextOperationDescriptor ConvertFromCDM::convert(const CDM::SetContextOperationDescriptor & source) {
	return SetContextOperationDescriptor(source);
}

SetRangeOperationDescriptor ConvertFromCDM::convert(const CDM::SetRangeOperationDescriptor & source) {
	return SetRangeOperationDescriptor(source);
}

SetStringOperationDescriptor ConvertFromCDM::convert(const CDM::SetStringOperationDescriptor & source) {
	return SetStringOperationDescriptor(source);
}

SetValueOperationDescriptor ConvertFromCDM::convert(const CDM::SetValueOperationDescriptor & source) {
	return SetValueOperationDescriptor(source);
}

Sex ConvertFromCDM::convert(const CDM::Sex & source) {
	switch (source) {
		case CDM::Sex::Unspec: return Sex::UNSPECIFIED;
		case CDM::Sex::M: return Sex::MALE;
		case CDM::Sex::F: return Sex::FEMALE;
		case CDM::Sex::Unkn: return Sex::UNKNOWN;
	}
	throw std::runtime_error("Illegal value for Sex");
}

AlertSignalPresence ConvertFromCDM::convert(const CDM::AlertSignalPresence & source) {
	switch (source) {
		case CDM::AlertSignalPresence::On: return AlertSignalPresence::On;
		case CDM::AlertSignalPresence::Off: return AlertSignalPresence::Off;
		case CDM::AlertSignalPresence::Ack: return AlertSignalPresence::Acknowledged;
		case CDM::AlertSignalPresence::Latch: return AlertSignalPresence::Latched;
	}
	throw std::runtime_error("Illegal value for SignalPresence");
}

StringMetricDescriptor ConvertFromCDM::convert(const CDM::StringMetricDescriptor & source) {
	return StringMetricDescriptor(source);
}

StringMetricState ConvertFromCDM::convert(const CDM::StringMetricState & source) {
	return StringMetricState(source);
}

StringMetricValue ConvertFromCDM::convert(const CDM::StringMetricValue & source) {
	return StringMetricValue(source);
}

SystemContext ConvertFromCDM::convert(const CDM::SystemContext & source) {
	return SystemContext(source);
}

SystemMetaData ConvertFromCDM::convert(const CDM::SystemMetaData & source) {
	return SystemMetaData(source);
}

Timestamp ConvertFromCDM::convert(const CDM::Timestamp & source) {
	return Timestamp(source);
}

TimeZone ConvertFromCDM::convert(const CDM::TimeZone & source) {
	return TimeZone(source);
}

VersionCounter ConvertFromCDM::convert(const CDM::VersionCounter & source) {
	return VersionCounter(source);
}

VMDDescriptor ConvertFromCDM::convert(const CDM::VMDDescriptor & source) {
	return VMDDescriptor(source);
}

WorkflowContextDescriptor ConvertFromCDM::convert(const CDM::WorkflowContextDescriptor & source) {
	return WorkflowContextDescriptor(source);
}

WorkflowContextState ConvertFromCDM::convert(const CDM::WorkflowContextState & source) {
	return WorkflowContextState(source);
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
