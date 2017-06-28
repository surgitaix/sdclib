#include "OSCLib/Data/OSCP/MDIB/InvocationInfo.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractGet.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractGetResponse.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractReportPart.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractReport.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractSet.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractSetResponse.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractContextReport.h"
#include "OSCLib/Data/OSCP/MDIB/VersionFrame.h"
#include "OSCLib/Data/OSCP/MDIB/TimeFrame.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractMetricReport.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractComponentReport.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractAlertReport.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractOperationalStateReport.h"
#include "OSCLib/Data/OSCP/MDIB/RetrievabilityInfo.h"
#include "OSCLib/Data/OSCP/MDIB/Mdib.h"
#include "OSCLib/Data/OSCP/MDIB/MdDescription.h"
#include "OSCLib/Data/OSCP/MDIB/MdState.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/Measurement.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractState.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractMultiState.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractDeviceComponentDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractAlertingDeviceComponentDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CalibrationInfo.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractDeviceComponentState.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractAlertingDeviceComponentState.h"
#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MdsState.h"
#include "OSCLib/Data/OSCP/MDIB/VmdDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/VmdState.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelState.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractAlertDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractAlertState.h"
#include "OSCLib/Data/OSCP/MDIB/SystemSignalActivation.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/CauseInfo.h"
#include "OSCLib/Data/OSCP/MDIB/RemedyInfo.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/SampleArrayValue.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/DistributionSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/DistributionSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/ScoDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ScoState.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractSetStateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractOperationState.h"
#include "OSCLib/Data/OSCP/MDIB/SetValueOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetValueOperationState.h"
#include "OSCLib/Data/OSCP/MDIB/SetStringOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetStringOperationState.h"
#include "OSCLib/Data/OSCP/MDIB/ActivateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ActivateOperationState.h"
#include "OSCLib/Data/OSCP/MDIB/SetContextStateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetContextStateOperationState.h"
#include "OSCLib/Data/OSCP/MDIB/SetMetricStateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetMetricStateOperationState.h"
#include "OSCLib/Data/OSCP/MDIB/SetComponentStateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetComponentStateOperationState.h"
#include "OSCLib/Data/OSCP/MDIB/SetAlertStateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetAlertStateOperationState.h"
#include "OSCLib/Data/OSCP/MDIB/ClockDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ClockState.h"
#include "OSCLib/Data/OSCP/MDIB/BatteryDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/BatteryState.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContextState.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AbstractContextState.h"
#include "OSCLib/Data/OSCP/MDIB/BaseDemographics.h"
#include "OSCLib/Data/OSCP/MDIB/PersonReference.h"
#include "OSCLib/Data/OSCP/MDIB/LocationDetail.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/PatientDemographicsCoreData.h"
#include "OSCLib/Data/OSCP/MDIB/NeonatalPatientDemographicsCoreData.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextState.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextState.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ClinicalInfo.h"
#include "OSCLib/Data/OSCP/MDIB/ImagingProcedure.h"
#include "OSCLib/Data/OSCP/MDIB/LocationReference.h"
#include "OSCLib/Data/OSCP/MDIB/OrderDetail.h"
#include "OSCLib/Data/OSCP/MDIB/PersonParticipation.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextState.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextState.h"
#include "OSCLib/Data/OSCP/MDIB/MeansContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MeansContextState.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextState.h"
#include "OSCLib/Data/OSCP/MDIB/ContainmentTree.h"
#include "OSCLib/Data/OSCP/MDIB/ContainmentTreeEntry.h"
#include "OSCLib/Data/OSCP/MDIB/ExtensionType.h"

#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "osdm.hxx"

#include <stdexcept>

/*
 * ConvertFromCDM.cpp
 *
 *  Created on: 22.06.2017
 *      Author: buerger
 *
 *  This file is autogenerated.
 *
 *  Do not edit this file. For customization please edit the ConvertFromCDM_beginning.cxx or ConvertFromCDM_ending.cxx
 */

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


InvocationState ConvertFromCDM::convert(const CDM::InvocationState & source) {
	switch (source) {
		case CDM::InvocationState::Wait: return InvocationState::Wait;
		case CDM::InvocationState::Start: return InvocationState::Start;
		case CDM::InvocationState::Cnclld: return InvocationState::Cnclld;
		case CDM::InvocationState::CnclldMan: return InvocationState::CnclldMan;
		case CDM::InvocationState::Fin: return InvocationState::Fin;
		case CDM::InvocationState::FinMod: return InvocationState::FinMod;
		case CDM::InvocationState::Fail: return InvocationState::Fail;
	}
	throw std::runtime_error("Illegal value for InvocationState");
}

InvocationError ConvertFromCDM::convert(const CDM::InvocationError & source) {
	switch (source) {
		case CDM::InvocationError::Unspec: return InvocationError::Unspec;
		case CDM::InvocationError::Unkn: return InvocationError::Unkn;
		case CDM::InvocationError::Inv: return InvocationError::Inv;
		case CDM::InvocationError::Oth: return InvocationError::Oth;
	}
	throw std::runtime_error("Illegal value for InvocationError");
}

DescriptionModificationType ConvertFromCDM::convert(const CDM::DescriptionModificationType & source) {
	switch (source) {
		case CDM::DescriptionModificationType::Crt: return DescriptionModificationType::Crt;
		case CDM::DescriptionModificationType::Upt: return DescriptionModificationType::Upt;
		case CDM::DescriptionModificationType::Del: return DescriptionModificationType::Del;
	}
	throw std::runtime_error("Illegal value for DescriptionModificationType");
}

RetrievabilityMethod ConvertFromCDM::convert(const CDM::RetrievabilityMethod & source) {
	switch (source) {
		case CDM::RetrievabilityMethod::Get: return RetrievabilityMethod::Get;
		case CDM::RetrievabilityMethod::Per: return RetrievabilityMethod::Per;
		case CDM::RetrievabilityMethod::Ep: return RetrievabilityMethod::Ep;
		case CDM::RetrievabilityMethod::Strm: return RetrievabilityMethod::Strm;
	}
	throw std::runtime_error("Illegal value for RetrievabilityMethod");
}

MeasurementValidity ConvertFromCDM::convert(const CDM::MeasurementValidity & source) {
	switch (source) {
		case CDM::MeasurementValidity::Vld: return MeasurementValidity::Vld;
		case CDM::MeasurementValidity::Vldated: return MeasurementValidity::Vldated;
		case CDM::MeasurementValidity::Ong: return MeasurementValidity::Ong;
		case CDM::MeasurementValidity::Qst: return MeasurementValidity::Qst;
		case CDM::MeasurementValidity::Calib: return MeasurementValidity::Calib;
		case CDM::MeasurementValidity::Inv: return MeasurementValidity::Inv;
		case CDM::MeasurementValidity::Oflw: return MeasurementValidity::Oflw;
		case CDM::MeasurementValidity::Uflw: return MeasurementValidity::Uflw;
		case CDM::MeasurementValidity::NA: return MeasurementValidity::NA;
	}
	throw std::runtime_error("Illegal value for MeasurementValidity");
}

SafetyClassification ConvertFromCDM::convert(const CDM::SafetyClassification & source) {
	switch (source) {
		case CDM::SafetyClassification::Inf: return SafetyClassification::Inf;
		case CDM::SafetyClassification::MedA: return SafetyClassification::MedA;
		case CDM::SafetyClassification::MedB: return SafetyClassification::MedB;
		case CDM::SafetyClassification::MedC: return SafetyClassification::MedC;
	}
	throw std::runtime_error("Illegal value for SafetyClassification");
}

ComponentActivation ConvertFromCDM::convert(const CDM::ComponentActivation & source) {
	switch (source) {
		case CDM::ComponentActivation::On: return ComponentActivation::On;
		case CDM::ComponentActivation::NotRdy: return ComponentActivation::NotRdy;
		case CDM::ComponentActivation::StndBy: return ComponentActivation::StndBy;
		case CDM::ComponentActivation::Off: return ComponentActivation::Off;
		case CDM::ComponentActivation::Shtdn: return ComponentActivation::Shtdn;
		case CDM::ComponentActivation::Fail: return ComponentActivation::Fail;
	}
	throw std::runtime_error("Illegal value for ComponentActivation");
}

CalibrationState ConvertFromCDM::convert(const CDM::CalibrationState & source) {
	switch (source) {
		case CDM::CalibrationState::No: return CalibrationState::No;
		case CDM::CalibrationState::Req: return CalibrationState::Req;
		case CDM::CalibrationState::Cal: return CalibrationState::Cal;
	}
	throw std::runtime_error("Illegal value for CalibrationState");
}

CalibrationType ConvertFromCDM::convert(const CDM::CalibrationType & source) {
	switch (source) {
		case CDM::CalibrationType::Offset: return CalibrationType::Offset;
		case CDM::CalibrationType::Gain: return CalibrationType::Gain;
		case CDM::CalibrationType::TP: return CalibrationType::TP;
		case CDM::CalibrationType::Unspec: return CalibrationType::Unspec;
	}
	throw std::runtime_error("Illegal value for CalibrationType");
}

MdsOperatingMode ConvertFromCDM::convert(const CDM::MdsOperatingMode & source) {
	switch (source) {
		case CDM::MdsOperatingMode::Nml: return MdsOperatingMode::Nml;
		case CDM::MdsOperatingMode::Dmo: return MdsOperatingMode::Dmo;
		case CDM::MdsOperatingMode::Srv: return MdsOperatingMode::Srv;
		case CDM::MdsOperatingMode::Mtn: return MdsOperatingMode::Mtn;
	}
	throw std::runtime_error("Illegal value for MdsOperatingMode");
}

AlertActivation ConvertFromCDM::convert(const CDM::AlertActivation & source) {
	switch (source) {
		case CDM::AlertActivation::On: return AlertActivation::On;
		case CDM::AlertActivation::Off: return AlertActivation::Off;
		case CDM::AlertActivation::Psd: return AlertActivation::Psd;
	}
	throw std::runtime_error("Illegal value for AlertActivation");
}

AlertConditionKind ConvertFromCDM::convert(const CDM::AlertConditionKind & source) {
	switch (source) {
		case CDM::AlertConditionKind::Phy: return AlertConditionKind::Phy;
		case CDM::AlertConditionKind::Tec: return AlertConditionKind::Tec;
		case CDM::AlertConditionKind::Oth: return AlertConditionKind::Oth;
	}
	throw std::runtime_error("Illegal value for AlertConditionKind");
}

AlertConditionPriority ConvertFromCDM::convert(const CDM::AlertConditionPriority & source) {
	switch (source) {
		case CDM::AlertConditionPriority::Lo: return AlertConditionPriority::Lo;
		case CDM::AlertConditionPriority::Me: return AlertConditionPriority::Me;
		case CDM::AlertConditionPriority::Hi: return AlertConditionPriority::Hi;
		case CDM::AlertConditionPriority::None: return AlertConditionPriority::None;
	}
	throw std::runtime_error("Illegal value for AlertConditionPriority");
}

AlertConditionMonitoredLimits ConvertFromCDM::convert(const CDM::AlertConditionMonitoredLimits & source) {
	switch (source) {
		case CDM::AlertConditionMonitoredLimits::All: return AlertConditionMonitoredLimits::All;
		case CDM::AlertConditionMonitoredLimits::LoOff: return AlertConditionMonitoredLimits::LoOff;
		case CDM::AlertConditionMonitoredLimits::HiOff: return AlertConditionMonitoredLimits::HiOff;
		case CDM::AlertConditionMonitoredLimits::None: return AlertConditionMonitoredLimits::None;
	}
	throw std::runtime_error("Illegal value for AlertConditionMonitoredLimits");
}

AlertSignalManifestation ConvertFromCDM::convert(const CDM::AlertSignalManifestation & source) {
	switch (source) {
		case CDM::AlertSignalManifestation::Aud: return AlertSignalManifestation::Aud;
		case CDM::AlertSignalManifestation::Vis: return AlertSignalManifestation::Vis;
		case CDM::AlertSignalManifestation::Tan: return AlertSignalManifestation::Tan;
		case CDM::AlertSignalManifestation::Oth: return AlertSignalManifestation::Oth;
	}
	throw std::runtime_error("Illegal value for AlertSignalManifestation");
}

AlertSignalPresence ConvertFromCDM::convert(const CDM::AlertSignalPresence & source) {
	switch (source) {
		case CDM::AlertSignalPresence::On: return AlertSignalPresence::On;
		case CDM::AlertSignalPresence::Off: return AlertSignalPresence::Off;
		case CDM::AlertSignalPresence::Latch: return AlertSignalPresence::Latch;
		case CDM::AlertSignalPresence::Ack: return AlertSignalPresence::Ack;
	}
	throw std::runtime_error("Illegal value for AlertSignalPresence");
}

AlertSignalPrimaryLocation ConvertFromCDM::convert(const CDM::AlertSignalPrimaryLocation & source) {
	switch (source) {
		case CDM::AlertSignalPrimaryLocation::Loc: return AlertSignalPrimaryLocation::Loc;
		case CDM::AlertSignalPrimaryLocation::Rem: return AlertSignalPrimaryLocation::Rem;
	}
	throw std::runtime_error("Illegal value for AlertSignalPrimaryLocation");
}

GenerationMode ConvertFromCDM::convert(const CDM::GenerationMode & source) {
	switch (source) {
		case CDM::GenerationMode::Real: return GenerationMode::Real;
		case CDM::GenerationMode::Test: return GenerationMode::Test;
		case CDM::GenerationMode::Demo: return GenerationMode::Demo;
	}
	throw std::runtime_error("Illegal value for GenerationMode");
}

MetricCategory ConvertFromCDM::convert(const CDM::MetricCategory & source) {
	switch (source) {
		case CDM::MetricCategory::Unspec: return MetricCategory::Unspec;
		case CDM::MetricCategory::Msrmt: return MetricCategory::Msrmt;
		case CDM::MetricCategory::Clc: return MetricCategory::Clc;
		case CDM::MetricCategory::Set: return MetricCategory::Set;
		case CDM::MetricCategory::Preset: return MetricCategory::Preset;
		case CDM::MetricCategory::Rcmm: return MetricCategory::Rcmm;
	}
	throw std::runtime_error("Illegal value for MetricCategory");
}

DerivationMethod ConvertFromCDM::convert(const CDM::DerivationMethod & source) {
	switch (source) {
		case CDM::DerivationMethod::Auto: return DerivationMethod::Auto;
		case CDM::DerivationMethod::Man: return DerivationMethod::Man;
	}
	throw std::runtime_error("Illegal value for DerivationMethod");
}

MetricAvailability ConvertFromCDM::convert(const CDM::MetricAvailability & source) {
	switch (source) {
		case CDM::MetricAvailability::Intr: return MetricAvailability::Intr;
		case CDM::MetricAvailability::Cont: return MetricAvailability::Cont;
	}
	throw std::runtime_error("Illegal value for MetricAvailability");
}

OperatingMode ConvertFromCDM::convert(const CDM::OperatingMode & source) {
	switch (source) {
		case CDM::OperatingMode::Dis: return OperatingMode::Dis;
		case CDM::OperatingMode::En: return OperatingMode::En;
		case CDM::OperatingMode::NA: return OperatingMode::NA;
	}
	throw std::runtime_error("Illegal value for OperatingMode");
}

ContextAssociation ConvertFromCDM::convert(const CDM::ContextAssociation & source) {
	switch (source) {
		case CDM::ContextAssociation::No: return ContextAssociation::No;
		case CDM::ContextAssociation::Pre: return ContextAssociation::Pre;
		case CDM::ContextAssociation::Assoc: return ContextAssociation::Assoc;
		case CDM::ContextAssociation::Dis: return ContextAssociation::Dis;
	}
	throw std::runtime_error("Illegal value for ContextAssociation");
}

Sex ConvertFromCDM::convert(const CDM::Sex & source) {
	switch (source) {
		case CDM::Sex::Unspec: return Sex::Unspec;
		case CDM::Sex::M: return Sex::M;
		case CDM::Sex::F: return Sex::F;
		case CDM::Sex::Unkn: return Sex::Unkn;
	}
	throw std::runtime_error("Illegal value for Sex");
}

PatientType ConvertFromCDM::convert(const CDM::PatientType & source) {
	switch (source) {
		case CDM::PatientType::Unspec: return PatientType::Unspec;
		case CDM::PatientType::Ad: return PatientType::Ad;
		case CDM::PatientType::Ped: return PatientType::Ped;
		case CDM::PatientType::Neo: return PatientType::Neo;
	}
	throw std::runtime_error("Illegal value for PatientType");
}

InvocationInfoConvertFromCDM::convert(const CDM::InvocationInfo & source) {
	return InvocationInfo(source);
}

AbstractGetConvertFromCDM::convert(const CDM::AbstractGet & source) {
	return AbstractGet(source);
}

AbstractGetResponseConvertFromCDM::convert(const CDM::AbstractGetResponse & source) {
	return AbstractGetResponse(source);
}

AbstractReportPartConvertFromCDM::convert(const CDM::AbstractReportPart & source) {
	return AbstractReportPart(source);
}

AbstractReportConvertFromCDM::convert(const CDM::AbstractReport & source) {
	return AbstractReport(source);
}

AbstractSetConvertFromCDM::convert(const CDM::AbstractSet & source) {
	return AbstractSet(source);
}

AbstractSetResponseConvertFromCDM::convert(const CDM::AbstractSetResponse & source) {
	return AbstractSetResponse(source);
}

AbstractContextReportConvertFromCDM::convert(const CDM::AbstractContextReport & source) {
	return AbstractContextReport(source);
}

VersionFrameConvertFromCDM::convert(const CDM::VersionFrame & source) {
	return VersionFrame(source);
}

TimeFrameConvertFromCDM::convert(const CDM::TimeFrame & source) {
	return TimeFrame(source);
}

AbstractMetricReportConvertFromCDM::convert(const CDM::AbstractMetricReport & source) {
	return AbstractMetricReport(source);
}

AbstractComponentReportConvertFromCDM::convert(const CDM::AbstractComponentReport & source) {
	return AbstractComponentReport(source);
}

AbstractAlertReportConvertFromCDM::convert(const CDM::AbstractAlertReport & source) {
	return AbstractAlertReport(source);
}

AbstractOperationalStateReportConvertFromCDM::convert(const CDM::AbstractOperationalStateReport & source) {
	return AbstractOperationalStateReport(source);
}

RetrievabilityInfoConvertFromCDM::convert(const CDM::RetrievabilityInfo & source) {
	return RetrievabilityInfo(source);
}

MdibConvertFromCDM::convert(const CDM::Mdib & source) {
	return Mdib(source);
}

MdDescriptionConvertFromCDM::convert(const CDM::MdDescription & source) {
	return MdDescription(source);
}

MdStateConvertFromCDM::convert(const CDM::MdState & source) {
	return MdState(source);
}

LocalizedTextConvertFromCDM::convert(const CDM::LocalizedText & source) {
	return LocalizedText(source);
}

CodedValueConvertFromCDM::convert(const CDM::CodedValue & source) {
	return CodedValue(source);
}

InstanceIdentifierConvertFromCDM::convert(const CDM::InstanceIdentifier & source) {
	return InstanceIdentifier(source);
}

RangeConvertFromCDM::convert(const CDM::Range & source) {
	return Range(source);
}

MeasurementConvertFromCDM::convert(const CDM::Measurement & source) {
	return Measurement(source);
}

AbstractDescriptorConvertFromCDM::convert(const CDM::AbstractDescriptor & source) {
	return AbstractDescriptor(source);
}

AbstractStateConvertFromCDM::convert(const CDM::AbstractState & source) {
	return AbstractState(source);
}

AbstractMultiStateConvertFromCDM::convert(const CDM::AbstractMultiState & source) {
	return AbstractMultiState(source);
}

AbstractDeviceComponentDescriptorConvertFromCDM::convert(const CDM::AbstractDeviceComponentDescriptor & source) {
	return AbstractDeviceComponentDescriptor(source);
}

AbstractAlertingDeviceComponentDescriptorConvertFromCDM::convert(const CDM::AbstractAlertingDeviceComponentDescriptor & source) {
	return AbstractAlertingDeviceComponentDescriptor(source);
}

CalibrationInfoConvertFromCDM::convert(const CDM::CalibrationInfo & source) {
	return CalibrationInfo(source);
}

AbstractDeviceComponentStateConvertFromCDM::convert(const CDM::AbstractDeviceComponentState & source) {
	return AbstractDeviceComponentState(source);
}

AbstractAlertingDeviceComponentStateConvertFromCDM::convert(const CDM::AbstractAlertingDeviceComponentState & source) {
	return AbstractAlertingDeviceComponentState(source);
}

MdsDescriptorConvertFromCDM::convert(const CDM::MdsDescriptor & source) {
	return MdsDescriptor(source);
}

MdsStateConvertFromCDM::convert(const CDM::MdsState & source) {
	return MdsState(source);
}

VmdDescriptorConvertFromCDM::convert(const CDM::VmdDescriptor & source) {
	return VmdDescriptor(source);
}

VmdStateConvertFromCDM::convert(const CDM::VmdState & source) {
	return VmdState(source);
}

ChannelDescriptorConvertFromCDM::convert(const CDM::ChannelDescriptor & source) {
	return ChannelDescriptor(source);
}

ChannelStateConvertFromCDM::convert(const CDM::ChannelState & source) {
	return ChannelState(source);
}

AbstractAlertDescriptorConvertFromCDM::convert(const CDM::AbstractAlertDescriptor & source) {
	return AbstractAlertDescriptor(source);
}

AbstractAlertStateConvertFromCDM::convert(const CDM::AbstractAlertState & source) {
	return AbstractAlertState(source);
}

SystemSignalActivationConvertFromCDM::convert(const CDM::SystemSignalActivation & source) {
	return SystemSignalActivation(source);
}

AlertSystemDescriptorConvertFromCDM::convert(const CDM::AlertSystemDescriptor & source) {
	return AlertSystemDescriptor(source);
}

AlertSystemStateConvertFromCDM::convert(const CDM::AlertSystemState & source) {
	return AlertSystemState(source);
}

CauseInfoConvertFromCDM::convert(const CDM::CauseInfo & source) {
	return CauseInfo(source);
}

RemedyInfoConvertFromCDM::convert(const CDM::RemedyInfo & source) {
	return RemedyInfo(source);
}

AlertConditionDescriptorConvertFromCDM::convert(const CDM::AlertConditionDescriptor & source) {
	return AlertConditionDescriptor(source);
}

AlertConditionStateConvertFromCDM::convert(const CDM::AlertConditionState & source) {
	return AlertConditionState(source);
}

LimitAlertConditionDescriptorConvertFromCDM::convert(const CDM::LimitAlertConditionDescriptor & source) {
	return LimitAlertConditionDescriptor(source);
}

LimitAlertConditionStateConvertFromCDM::convert(const CDM::LimitAlertConditionState & source) {
	return LimitAlertConditionState(source);
}

AlertSignalDescriptorConvertFromCDM::convert(const CDM::AlertSignalDescriptor & source) {
	return AlertSignalDescriptor(source);
}

AlertSignalStateConvertFromCDM::convert(const CDM::AlertSignalState & source) {
	return AlertSignalState(source);
}

AbstractMetricValueConvertFromCDM::convert(const CDM::AbstractMetricValue & source) {
	return AbstractMetricValue(source);
}

NumericMetricValueConvertFromCDM::convert(const CDM::NumericMetricValue & source) {
	return NumericMetricValue(source);
}

StringMetricValueConvertFromCDM::convert(const CDM::StringMetricValue & source) {
	return StringMetricValue(source);
}

SampleArrayValueConvertFromCDM::convert(const CDM::SampleArrayValue & source) {
	return SampleArrayValue(source);
}

AbstractMetricDescriptorConvertFromCDM::convert(const CDM::AbstractMetricDescriptor & source) {
	return AbstractMetricDescriptor(source);
}

AbstractMetricStateConvertFromCDM::convert(const CDM::AbstractMetricState & source) {
	return AbstractMetricState(source);
}

NumericMetricDescriptorConvertFromCDM::convert(const CDM::NumericMetricDescriptor & source) {
	return NumericMetricDescriptor(source);
}

NumericMetricStateConvertFromCDM::convert(const CDM::NumericMetricState & source) {
	return NumericMetricState(source);
}

StringMetricDescriptorConvertFromCDM::convert(const CDM::StringMetricDescriptor & source) {
	return StringMetricDescriptor(source);
}

StringMetricStateConvertFromCDM::convert(const CDM::StringMetricState & source) {
	return StringMetricState(source);
}

EnumStringMetricDescriptorConvertFromCDM::convert(const CDM::EnumStringMetricDescriptor & source) {
	return EnumStringMetricDescriptor(source);
}

EnumStringMetricStateConvertFromCDM::convert(const CDM::EnumStringMetricState & source) {
	return EnumStringMetricState(source);
}

RealTimeSampleArrayMetricDescriptorConvertFromCDM::convert(const CDM::RealTimeSampleArrayMetricDescriptor & source) {
	return RealTimeSampleArrayMetricDescriptor(source);
}

RealTimeSampleArrayMetricStateConvertFromCDM::convert(const CDM::RealTimeSampleArrayMetricState & source) {
	return RealTimeSampleArrayMetricState(source);
}

DistributionSampleArrayMetricDescriptorConvertFromCDM::convert(const CDM::DistributionSampleArrayMetricDescriptor & source) {
	return DistributionSampleArrayMetricDescriptor(source);
}

DistributionSampleArrayMetricStateConvertFromCDM::convert(const CDM::DistributionSampleArrayMetricState & source) {
	return DistributionSampleArrayMetricState(source);
}

ScoDescriptorConvertFromCDM::convert(const CDM::ScoDescriptor & source) {
	return ScoDescriptor(source);
}

ScoStateConvertFromCDM::convert(const CDM::ScoState & source) {
	return ScoState(source);
}

AbstractOperationDescriptorConvertFromCDM::convert(const CDM::AbstractOperationDescriptor & source) {
	return AbstractOperationDescriptor(source);
}

AbstractSetStateOperationDescriptorConvertFromCDM::convert(const CDM::AbstractSetStateOperationDescriptor & source) {
	return AbstractSetStateOperationDescriptor(source);
}

AbstractOperationStateConvertFromCDM::convert(const CDM::AbstractOperationState & source) {
	return AbstractOperationState(source);
}

SetValueOperationDescriptorConvertFromCDM::convert(const CDM::SetValueOperationDescriptor & source) {
	return SetValueOperationDescriptor(source);
}

SetValueOperationStateConvertFromCDM::convert(const CDM::SetValueOperationState & source) {
	return SetValueOperationState(source);
}

SetStringOperationDescriptorConvertFromCDM::convert(const CDM::SetStringOperationDescriptor & source) {
	return SetStringOperationDescriptor(source);
}

SetStringOperationStateConvertFromCDM::convert(const CDM::SetStringOperationState & source) {
	return SetStringOperationState(source);
}

ActivateOperationDescriptorConvertFromCDM::convert(const CDM::ActivateOperationDescriptor & source) {
	return ActivateOperationDescriptor(source);
}

ActivateOperationStateConvertFromCDM::convert(const CDM::ActivateOperationState & source) {
	return ActivateOperationState(source);
}

SetContextStateOperationDescriptorConvertFromCDM::convert(const CDM::SetContextStateOperationDescriptor & source) {
	return SetContextStateOperationDescriptor(source);
}

SetContextStateOperationStateConvertFromCDM::convert(const CDM::SetContextStateOperationState & source) {
	return SetContextStateOperationState(source);
}

SetMetricStateOperationDescriptorConvertFromCDM::convert(const CDM::SetMetricStateOperationDescriptor & source) {
	return SetMetricStateOperationDescriptor(source);
}

SetMetricStateOperationStateConvertFromCDM::convert(const CDM::SetMetricStateOperationState & source) {
	return SetMetricStateOperationState(source);
}

SetComponentStateOperationDescriptorConvertFromCDM::convert(const CDM::SetComponentStateOperationDescriptor & source) {
	return SetComponentStateOperationDescriptor(source);
}

SetComponentStateOperationStateConvertFromCDM::convert(const CDM::SetComponentStateOperationState & source) {
	return SetComponentStateOperationState(source);
}

SetAlertStateOperationDescriptorConvertFromCDM::convert(const CDM::SetAlertStateOperationDescriptor & source) {
	return SetAlertStateOperationDescriptor(source);
}

SetAlertStateOperationStateConvertFromCDM::convert(const CDM::SetAlertStateOperationState & source) {
	return SetAlertStateOperationState(source);
}

ClockDescriptorConvertFromCDM::convert(const CDM::ClockDescriptor & source) {
	return ClockDescriptor(source);
}

ClockStateConvertFromCDM::convert(const CDM::ClockState & source) {
	return ClockState(source);
}

BatteryDescriptorConvertFromCDM::convert(const CDM::BatteryDescriptor & source) {
	return BatteryDescriptor(source);
}

BatteryStateConvertFromCDM::convert(const CDM::BatteryState & source) {
	return BatteryState(source);
}

SystemContextDescriptorConvertFromCDM::convert(const CDM::SystemContextDescriptor & source) {
	return SystemContextDescriptor(source);
}

SystemContextStateConvertFromCDM::convert(const CDM::SystemContextState & source) {
	return SystemContextState(source);
}

AbstractContextDescriptorConvertFromCDM::convert(const CDM::AbstractContextDescriptor & source) {
	return AbstractContextDescriptor(source);
}

AbstractContextStateConvertFromCDM::convert(const CDM::AbstractContextState & source) {
	return AbstractContextState(source);
}

BaseDemographicsConvertFromCDM::convert(const CDM::BaseDemographics & source) {
	return BaseDemographics(source);
}

PersonReferenceConvertFromCDM::convert(const CDM::PersonReference & source) {
	return PersonReference(source);
}

LocationDetailConvertFromCDM::convert(const CDM::LocationDetail & source) {
	return LocationDetail(source);
}

PatientContextDescriptorConvertFromCDM::convert(const CDM::PatientContextDescriptor & source) {
	return PatientContextDescriptor(source);
}

PatientDemographicsCoreDataConvertFromCDM::convert(const CDM::PatientDemographicsCoreData & source) {
	return PatientDemographicsCoreData(source);
}

NeonatalPatientDemographicsCoreDataConvertFromCDM::convert(const CDM::NeonatalPatientDemographicsCoreData & source) {
	return NeonatalPatientDemographicsCoreData(source);
}

PatientContextStateConvertFromCDM::convert(const CDM::PatientContextState & source) {
	return PatientContextState(source);
}

LocationContextDescriptorConvertFromCDM::convert(const CDM::LocationContextDescriptor & source) {
	return LocationContextDescriptor(source);
}

LocationContextStateConvertFromCDM::convert(const CDM::LocationContextState & source) {
	return LocationContextState(source);
}

WorkflowContextDescriptorConvertFromCDM::convert(const CDM::WorkflowContextDescriptor & source) {
	return WorkflowContextDescriptor(source);
}

ClinicalInfoConvertFromCDM::convert(const CDM::ClinicalInfo & source) {
	return ClinicalInfo(source);
}

ImagingProcedureConvertFromCDM::convert(const CDM::ImagingProcedure & source) {
	return ImagingProcedure(source);
}

LocationReferenceConvertFromCDM::convert(const CDM::LocationReference & source) {
	return LocationReference(source);
}

OrderDetailConvertFromCDM::convert(const CDM::OrderDetail & source) {
	return OrderDetail(source);
}

PersonParticipationConvertFromCDM::convert(const CDM::PersonParticipation & source) {
	return PersonParticipation(source);
}

WorkflowContextStateConvertFromCDM::convert(const CDM::WorkflowContextState & source) {
	return WorkflowContextState(source);
}

OperatorContextDescriptorConvertFromCDM::convert(const CDM::OperatorContextDescriptor & source) {
	return OperatorContextDescriptor(source);
}

OperatorContextStateConvertFromCDM::convert(const CDM::OperatorContextState & source) {
	return OperatorContextState(source);
}

MeansContextDescriptorConvertFromCDM::convert(const CDM::MeansContextDescriptor & source) {
	return MeansContextDescriptor(source);
}

MeansContextStateConvertFromCDM::convert(const CDM::MeansContextState & source) {
	return MeansContextState(source);
}

EnsembleContextDescriptorConvertFromCDM::convert(const CDM::EnsembleContextDescriptor & source) {
	return EnsembleContextDescriptor(source);
}

EnsembleContextStateConvertFromCDM::convert(const CDM::EnsembleContextState & source) {
	return EnsembleContextState(source);
}

ContainmentTreeConvertFromCDM::convert(const CDM::ContainmentTree & source) {
	return ContainmentTree(source);
}

ContainmentTreeEntryConvertFromCDM::convert(const CDM::ContainmentTreeEntry & source) {
	return ContainmentTreeEntry(source);
}

ExtensionTypeConvertFromCDM::convert(const CDM::ExtensionType & source) {
	return ExtensionType(source);
}



} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
