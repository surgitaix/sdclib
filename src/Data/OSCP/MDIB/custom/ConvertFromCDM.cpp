/*
 * ConvertFromCDM.cpp
 *
 *  Created on: 26.01.2015
 *      Author: roehser
 */
#include "OSCLib/Data/OSCP/MDIB/ActivateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ActivateOperationState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionReference.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/ApplyAnnotation.h"
#include "OSCLib/Data/OSCP/MDIB/Base64Binary.h"
#include "OSCLib/Data/OSCP/MDIB/BaseDemographics.h"
#include "OSCLib/Data/OSCP/MDIB/CalibrationInfo.h"
#include "OSCLib/Data/OSCP/MDIB/CauseInfo.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ClinicalInfo.h"
#include "OSCLib/Data/OSCP/MDIB/ClockDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ClockState.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/DateTime.h"
#include "OSCLib/Data/OSCP/MDIB/DicomDeviceDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/DicomNetworkAe.h"
#include "OSCLib/Data/OSCP/MDIB/DicomNetworkConnection.h"
#include "OSCLib/Data/OSCP/MDIB/DicomTransferCapability.h"
#include "OSCLib/Data/OSCP/MDIB/Duration.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextState.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ImagingProcedure.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/Language.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextState.h"
#include "OSCLib/Data/OSCP/MDIB/LocationReference.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/MdDescription.h"
#include "OSCLib/Data/OSCP/MDIB/MdState.h"
#include "OSCLib/Data/OSCP/MDIB/SetAlertStateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetAlertStateOperationState.h"
#include "OSCLib/Data/OSCP/MDIB/SetComponentStateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetComponentStateOperationState.h"
#include "OSCLib/Data/OSCP/MDIB/SetContextStateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetContextStateOperationState.h"
#include "OSCLib/Data/OSCP/MDIB/SetMetricStateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetMetricStateOperationState.h"
#include "OSCLib/Data/OSCP/MDIB/SetStringOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetValueOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContextState.h"
#include "OSCLib/Data/OSCP/MDIB/MetaData.h"
#include "OSCLib/Data/OSCP/MDIB/Timestamp.h"
#include "OSCLib/Data/OSCP/MDIB/TimeZone.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"
#include "OSCLib/Data/OSCP/MDIB/VmdDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextState.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowDetail.h"


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

ActiveOperationState ConvertFromCDM::convert(const CDM::ActivateOperationState & source) {
	return ActiveOperationState(source);
}

AlertActivation ConvertFromCDM::convert(const CDM::AlertActivation & source) {
	switch (source) {
		case CDM::AlertActivation::Off: return AlertActivation::Off;
		case CDM::AlertActivation::On: return AlertActivation::On;
		case CDM::AlertActivation::Psd: return AlertActivation::Paused;
	}
	throw std::runtime_error("Illegal value for AlertActivation");
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

ApplyAnnotation ConvertFromCDM::convert(const CDM::ApplyAnnotation & source) {
	return ApplyAnnotation(source);
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

AllowedValue ConvertFromCDM::convert(const CDM::AllowedValue & source) {
	return AllowedValueType(source);
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

InvocationState ConvertFromCDM::convert(const MDM::InvocationState & source) {
	switch (source) {
		case MDM::InvocationState::Fail: return InvocationState::FAILED;
		case MDM::InvocationState::Wait: return InvocationState::WAITING;
		case MDM::InvocationState::Start: return InvocationState::STARTED;
		case MDM::InvocationState::Cnclld: return InvocationState::CANCELLED;
		case MDM::InvocationState::CnclldMan: return InvocationState::CANCELLED_MANUALLY;
		case MDM::InvocationState::Fin: return InvocationState::FINISHED;
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

LocationReference ConvertFromCDM::convert(const CDM::LocationReference & source) {
	return LocationContextState(source);
}

MdDescription ConvertFromCDM::convert(const CDM::MdDescription & source) {
	return MdDescription(source);
}


MdsOperatingMode ConvertFromCDM::convert(const CDM::MdsOperatingMode & source) {
	switch (source) {
		case CDM::MdsOperatingMode::Nml: return MdsOperatingMode::Normal;
		case CDM::MdsOperatingMode::Dmo: return MdsOperatingMode::Demo;
		case CDM::MdsOperatingMode::Srv: return MdsOperatingMode::Service;
		case CDM::MdsOperatingMode::Mtn: return MdsOperatingMode::Maintenance;
	}
	throw std::runtime_error("Illegal value for MdsOperatingMode");
}


MdState ConvertFromCDM::convert(const CDM::MdState & source) {
	return MdState(source);
}

MeansContextDescriptor ConvertFromCDM::convert(const CDM::MeansContextDescriptor & source) {
	return MeansContextDescriptor(source);
}

Measurement ConvertFromCDM::convert(const CDM::Measurement & source) {
	return Measure(source);
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
		case CDM::OperatingMode::Dis: return OperatingMode::Disabled;
		case CDM::OperatingMode::En: return OperatingMode::Enabled;
		case CDM::OperatingMode::NA: return OperatingMode::NotAvailable;
	}
	throw std::runtime_error("Illegal value for OperatingMode");
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

PerformedOrderDetail ConvertFromCDM::convert(const CDM::PerformedOrderDetail & source) {
	return PerformedOrderDetail(source);
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

SampleArrayValue ConvertFromCDM::convert(const CDM::SampleArrayValue & source) {
	return SampleArrayValue(source);
}

ReferencedVersion ConvertFromCDM::convert(const CDM::ReferencedVersion & source) {
	return ReferencedVersion(source);
}

ReferenceRange ConvertFromCDM::convert(const CDM::ReferenceRange & source) {
	return ReferenceRange(source);
}

RelatedMeasurement ConvertFromCDM::convert(const CDM::RelatedMeasurement & source) {
	return RelatedMeasurement(source);
}

RemedyInfo ConvertFromCDM::convert(const CDM::RemedyInfo & source) {
	return RemedyInfo(source);
}

RequestedOrderDetail ConvertFromCDM::convert(const CDM::RequestedOrderDetail & source) {
	return RequestedOrderDetail(source);
}

RealTimeValueType ConvertFromCDM::convert(const CDM::RealTimeValueType & source) {
	return RealTimeValueType(source);
}

SafetyClassification ConvertFromCDM::convert(const CDM::SafetyClassification & source) {
	switch (source) {
		case CDM::SafetyClassification::Inf: return SafetyClassification::Inf;
		case CDM::SafetyClassification::MedA: return SafetyClassification::MedA;
		case CDM::SafetyClassification::MedB: return SafetyClassification::MedB;
		case CDM::SafetyClassification::MedC: return SafetyClassification::MedC;
	}
	throw std::runtime_error("Illegal value for PrimaryAlertSignalLocation");
}

ScoDescriptor ConvertFromCDM::convert(const CDM::ScoDescriptor & source) {
	return ScoDescriptor(source);
}

SetAlertStateOperationDescriptor ConvertFromCDM::convert(const CDM::SetAlertStateOperationDescriptor & source) {
	return SetAlertStateOperationDescriptor(source);
}

SetAlertStateOperationState ConvertFromCDM::convert(const CDM::SetAlertStateOperationState & source) {
	return SetAlertStateOperationState(source);
}

SetComponentStateOperationDescriptor ConvertFromCDM::convert(const CDM::SetComponentStateOperationDescriptor & source) {
	return SetComponentStateOperationDescriptor(source);
}

SetComponentStateOperationState ConvertFromCDM::convert(const CDM::SetComponentStateOperationState & source) {
	return SetComponentStateOperationState(source);
}


SetContextOperationDescriptor ConvertFromCDM::convert(const CDM::SetContextOperationDescriptor & source) {
	return SetContextOperationDescriptor(source);
}

SetContextStateOperationState ConvertFromCDM::convert(const CDM::SetContextStateOperationState & source) {
	return SetContextStateOperationState(source);
}

SetMetricStateOperationDescriptor ConvertFromCDM::convert(const CDM::SetMetricStateOperationDescriptor & source) {
	return SetMetricStateOperationDescriptor(source);
}

SetMetricStateOperationState ConvertFromCDM::convert(const CDM::SetMetricStateOperationState & source) {
	return SetMetricStateOperationState(source);
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

SystemContextDescriptor ConvertFromCDM::convert(const CDM::SystemContextDescriptor & source) {
	return SystemContextDescriptor(source);
}

SystemContextState ConvertFromCDM::convert(const CDM::SystemContextState & source) {
	return SystemContextState(source);
}

MetaData ConvertFromCDM::convert(const CDM::MetaData & source) {
	return MetaData(source);
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

VmdDescriptor ConvertFromCDM::convert(const CDM::VmdDescriptor & source) {
	return VmdDescriptor(source);
}

WorkflowContextDescriptor ConvertFromCDM::convert(const CDM::WorkflowContextDescriptor & source) {
	return WorkflowContextDescriptor(source);
}

WorkflowContextState ConvertFromCDM::convert(const CDM::WorkflowContextState & source) {
	return WorkflowContextState(source);
}

WorkflowDetail ConvertFromCDM::convert(const CDM::WorkflowDetail & source) {
	return WorkflowDetail(source);
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
