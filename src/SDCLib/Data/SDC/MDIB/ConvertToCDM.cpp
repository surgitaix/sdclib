#include "SDCLib/Data/SDC/MDIB/DicomTransferCapability.h"
#include "SDCLib/Data/SDC/MDIB/DicomNetworkAe.h"
#include "SDCLib/Data/SDC/MDIB/DicomNetworkConnection.h"
#include "SDCLib/Data/SDC/MDIB/DicomDeviceDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/Mdib.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/MdState.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/Translation.h"
#include "SDCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "SDCLib/Data/SDC/MDIB/Range.h"
#include "SDCLib/Data/SDC/MDIB/Measurement.h"
#include "SDCLib/Data/SDC/MDIB/ApprovedJurisdictions.h"
#include "SDCLib/Data/SDC/MDIB/OperatingJurisdiction.h"
#include "SDCLib/Data/SDC/MDIB/PhysicalConnectorInfo.h"
#include "SDCLib/Data/SDC/MDIB/ProductionSpecification.h"
#include "SDCLib/Data/SDC/MDIB/CalibrationInfo.h"
#include "SDCLib/Data/SDC/MDIB/CalibrationDocumentation.h"
#include "SDCLib/Data/SDC/MDIB/CalibrationResult.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MetaData.h"
#include "SDCLib/Data/SDC/MDIB/Udi.h"
#include "SDCLib/Data/SDC/MDIB/MdsState.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/VmdState.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ChannelState.h"
#include "SDCLib/Data/SDC/MDIB/SystemSignalActivation.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "SDCLib/Data/SDC/MDIB/CauseInfo.h"
#include "SDCLib/Data/SDC/MDIB/RemedyInfo.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/Annotation.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/SampleArrayValue.h"
#include "SDCLib/Data/SDC/MDIB/ApplyAnnotation.h"
#include "SDCLib/Data/SDC/MDIB/Relation.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AllowedValue.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/DistributionSampleArrayMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/DistributionSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/ScoDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ScoState.h"
#include "SDCLib/Data/SDC/MDIB/OperationGroup.h"
#include "SDCLib/Data/SDC/MDIB/SetValueOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SetValueOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetStringOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SetStringOperationState.h"
#include "SDCLib/Data/SDC/MDIB/AllowedValues.h"
#include "SDCLib/Data/SDC/MDIB/ActivateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/Argument.h"
#include "SDCLib/Data/SDC/MDIB/ActivateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetContextStateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SetContextStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetMetricStateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SetMetricStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetComponentStateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SetComponentStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetAlertStateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SetAlertStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/ClockDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ClockState.h"
#include "SDCLib/Data/SDC/MDIB/BatteryDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/BatteryState.h"
#include "SDCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SystemContextState.h"
#include "SDCLib/Data/SDC/MDIB/BaseDemographics.h"
#include "SDCLib/Data/SDC/MDIB/PersonReference.h"
#include "SDCLib/Data/SDC/MDIB/LocationDetail.h"
#include "SDCLib/Data/SDC/MDIB/PatientContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/PatientDemographicsCoreData.h"
#include "SDCLib/Data/SDC/MDIB/NeonatalPatientDemographicsCoreData.h"
#include "SDCLib/Data/SDC/MDIB/PatientContextState.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextState.h"
#include "SDCLib/Data/SDC/MDIB/WorkflowContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ClinicalInfo.h"
#include "SDCLib/Data/SDC/MDIB/RelatedMeasurement.h"
#include "SDCLib/Data/SDC/MDIB/ReferenceRange.h"
#include "SDCLib/Data/SDC/MDIB/ImagingProcedure.h"
#include "SDCLib/Data/SDC/MDIB/LocationReference.h"
#include "SDCLib/Data/SDC/MDIB/OrderDetail.h"
#include "SDCLib/Data/SDC/MDIB/PersonParticipation.h"
#include "SDCLib/Data/SDC/MDIB/WorkflowContextState.h"
#include "SDCLib/Data/SDC/MDIB/WorkflowDetail.h"
#include "SDCLib/Data/SDC/MDIB/RequestedOrderDetail.h"
#include "SDCLib/Data/SDC/MDIB/PerformedOrderDetail.h"
#include "SDCLib/Data/SDC/MDIB/OperatorContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/OperatorContextState.h"
#include "SDCLib/Data/SDC/MDIB/MeansContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MeansContextState.h"
#include "SDCLib/Data/SDC/MDIB/EnsembleContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/EnsembleContextState.h"
#include "SDCLib/Data/SDC/MDIB/ContainmentTree.h"
#include "SDCLib/Data/SDC/MDIB/ContainmentTreeEntry.h"
#include "osdm.hxx"
#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"

#include <stdexcept>


/*
 * ConvertToCDM.cpp
 *
 *  Created on: 22.06.2017
 *      Author: buerger
 *
 *  This file is autogenerated.
 *
 *  Do not edit this file. For customization please edit the ConvertToCDM_beginning.cxx or ConvertToCDM_ending.cxx
 */


namespace SDCLib {
namespace Data {
namespace SDC {

ConvertToCDM::ConvertToCDM() {

}

ConvertToCDM::~ConvertToCDM() {

}


bool ConvertToCDM::convert(const bool& source) {
	return source;
}

double ConvertToCDM::convert(const double& source) {
	return source;
}

unsigned int ConvertToCDM::convert(const unsigned int& source) {
	return source;
}

int ConvertToCDM::convert(const int& source) {
	return source;
}

long ConvertToCDM::convert(const long& source) {
	return source;
}

long long ConvertToCDM::convert(const long long& source) {
	return source;
}

unsigned short int ConvertToCDM::convert(const unsigned short int& source) {
	return source;
}

unsigned long ConvertToCDM::convert(const unsigned long& source){
	return source;
}

unsigned long long ConvertToCDM::convert(const unsigned long long& source) {
	return source;
}

std::string ConvertToCDM::convert(const std::string & source) {
	return source;
}

xml_schema::Duration ConvertToCDM::convert(const xml_schema::Duration & source) {
	return source;
}

xml_schema::Qname ConvertToCDM::convert(const xml_schema::Qname & source) {
	return source;
}

xml_schema::Language ConvertToCDM::convert(const xml_schema::Language & source) {
	return source;
}

xml_schema::Uri ConvertToCDM::convert(const xml_schema::Uri & source) {
	return source;
}

xml_schema::DateTime ConvertToCDM::convert(const xml_schema::DateTime & source) {
	return source;
}

xml_schema::Idrefs ConvertToCDM::convert(const xml_schema::Idrefs & source) {
	return source;
}

xml_schema::Id ConvertToCDM::convert(const xml_schema::Id & source) {
	return source;
}


template <class WrapperType>
std::unique_ptr<typename WrapperType::WrappedType> ConvertToCDM::convert(const WrapperType & source) {
	return std::unique_ptr<typename WrapperType::WrappedType>(source.data->_clone());
}


// autogenerated code


CDM::DicomTransferRole ConvertToCDM::convert(const DicomTransferRole & source) {
	switch (source) {
		case DicomTransferRole::Scu: return CDM::DicomTransferRole::Scu;
		case DicomTransferRole::Scp: return CDM::DicomTransferRole::Scp;
	}
	throw std::runtime_error("Illegal value for DicomTransferRole");
}

CDM::MeasurementValidity ConvertToCDM::convert(const MeasurementValidity & source) {
	switch (source) {
		case MeasurementValidity::Vld: return CDM::MeasurementValidity::Vld;
		case MeasurementValidity::Vldated: return CDM::MeasurementValidity::Vldated;
		case MeasurementValidity::Ong: return CDM::MeasurementValidity::Ong;
		case MeasurementValidity::Qst: return CDM::MeasurementValidity::Qst;
		case MeasurementValidity::Calib: return CDM::MeasurementValidity::Calib;
		case MeasurementValidity::Inv: return CDM::MeasurementValidity::Inv;
		case MeasurementValidity::Oflw: return CDM::MeasurementValidity::Oflw;
		case MeasurementValidity::Uflw: return CDM::MeasurementValidity::Uflw;
		case MeasurementValidity::NA: return CDM::MeasurementValidity::NA;
	}
	throw std::runtime_error("Illegal value for MeasurementValidity");
}

CDM::LocalizedTextWidth ConvertToCDM::convert(const LocalizedTextWidth & source) {
	switch (source) {
		case LocalizedTextWidth::xs: return CDM::LocalizedTextWidth::xs;
		case LocalizedTextWidth::s: return CDM::LocalizedTextWidth::s;
		case LocalizedTextWidth::m: return CDM::LocalizedTextWidth::m;
		case LocalizedTextWidth::l: return CDM::LocalizedTextWidth::l;
		case LocalizedTextWidth::xl: return CDM::LocalizedTextWidth::xl;
		case LocalizedTextWidth::xxl: return CDM::LocalizedTextWidth::xxl;
	}
	throw std::runtime_error("Illegal value for LocalizedTextWidth");
}

CDM::SafetyClassification ConvertToCDM::convert(const SafetyClassification & source) {
	switch (source) {
		case SafetyClassification::Inf: return CDM::SafetyClassification::Inf;
		case SafetyClassification::MedA: return CDM::SafetyClassification::MedA;
		case SafetyClassification::MedB: return CDM::SafetyClassification::MedB;
		case SafetyClassification::MedC: return CDM::SafetyClassification::MedC;
	}
	throw std::runtime_error("Illegal value for SafetyClassification");
}

CDM::ComponentActivation ConvertToCDM::convert(const ComponentActivation & source) {
	switch (source) {
		case ComponentActivation::On: return CDM::ComponentActivation::On;
		case ComponentActivation::NotRdy: return CDM::ComponentActivation::NotRdy;
		case ComponentActivation::StndBy: return CDM::ComponentActivation::StndBy;
		case ComponentActivation::Off: return CDM::ComponentActivation::Off;
		case ComponentActivation::Shtdn: return CDM::ComponentActivation::Shtdn;
		case ComponentActivation::Fail: return CDM::ComponentActivation::Fail;
	}
	throw std::runtime_error("Illegal value for ComponentActivation");
}

CDM::CalibrationState ConvertToCDM::convert(const CalibrationState & source) {
	switch (source) {
		case CalibrationState::No: return CDM::CalibrationState::No;
		case CalibrationState::Req: return CDM::CalibrationState::Req;
		case CalibrationState::Run: return CDM::CalibrationState::Run;
		case CalibrationState::Cal: return CDM::CalibrationState::Cal;
		case CalibrationState::Oth: return CDM::CalibrationState::Oth;
	}
	throw std::runtime_error("Illegal value for CalibrationState");
}

CDM::CalibrationType ConvertToCDM::convert(const CalibrationType & source) {
	switch (source) {
		case CalibrationType::Offset: return CDM::CalibrationType::Offset;
		case CalibrationType::Gain: return CDM::CalibrationType::Gain;
		case CalibrationType::TP: return CDM::CalibrationType::TP;
		case CalibrationType::Unspec: return CDM::CalibrationType::Unspec;
	}
	throw std::runtime_error("Illegal value for CalibrationType");
}

CDM::MdsOperatingMode ConvertToCDM::convert(const MdsOperatingMode & source) {
	switch (source) {
		case MdsOperatingMode::Nml: return CDM::MdsOperatingMode::Nml;
		case MdsOperatingMode::Dmo: return CDM::MdsOperatingMode::Dmo;
		case MdsOperatingMode::Srv: return CDM::MdsOperatingMode::Srv;
		case MdsOperatingMode::Mtn: return CDM::MdsOperatingMode::Mtn;
	}
	throw std::runtime_error("Illegal value for MdsOperatingMode");
}

CDM::AlertActivation ConvertToCDM::convert(const AlertActivation & source) {
	switch (source) {
		case AlertActivation::On: return CDM::AlertActivation::On;
		case AlertActivation::Off: return CDM::AlertActivation::Off;
		case AlertActivation::Psd: return CDM::AlertActivation::Psd;
	}
	throw std::runtime_error("Illegal value for AlertActivation");
}

CDM::AlertConditionKind ConvertToCDM::convert(const AlertConditionKind & source) {
	switch (source) {
		case AlertConditionKind::Phy: return CDM::AlertConditionKind::Phy;
		case AlertConditionKind::Tec: return CDM::AlertConditionKind::Tec;
		case AlertConditionKind::Oth: return CDM::AlertConditionKind::Oth;
	}
	throw std::runtime_error("Illegal value for AlertConditionKind");
}

CDM::AlertConditionPriority ConvertToCDM::convert(const AlertConditionPriority & source) {
	switch (source) {
		case AlertConditionPriority::Lo: return CDM::AlertConditionPriority::Lo;
		case AlertConditionPriority::Me: return CDM::AlertConditionPriority::Me;
		case AlertConditionPriority::Hi: return CDM::AlertConditionPriority::Hi;
		case AlertConditionPriority::None: return CDM::AlertConditionPriority::None;
	}
	throw std::runtime_error("Illegal value for AlertConditionPriority");
}

CDM::AlertConditionMonitoredLimits ConvertToCDM::convert(const AlertConditionMonitoredLimits & source) {
	switch (source) {
		case AlertConditionMonitoredLimits::All: return CDM::AlertConditionMonitoredLimits::All;
		case AlertConditionMonitoredLimits::LoOff: return CDM::AlertConditionMonitoredLimits::LoOff;
		case AlertConditionMonitoredLimits::HiOff: return CDM::AlertConditionMonitoredLimits::HiOff;
		case AlertConditionMonitoredLimits::None: return CDM::AlertConditionMonitoredLimits::None;
	}
	throw std::runtime_error("Illegal value for AlertConditionMonitoredLimits");
}

CDM::AlertSignalManifestation ConvertToCDM::convert(const AlertSignalManifestation & source) {
	switch (source) {
		case AlertSignalManifestation::Aud: return CDM::AlertSignalManifestation::Aud;
		case AlertSignalManifestation::Vis: return CDM::AlertSignalManifestation::Vis;
		case AlertSignalManifestation::Tan: return CDM::AlertSignalManifestation::Tan;
		case AlertSignalManifestation::Oth: return CDM::AlertSignalManifestation::Oth;
	}
	throw std::runtime_error("Illegal value for AlertSignalManifestation");
}

CDM::AlertSignalPresence ConvertToCDM::convert(const AlertSignalPresence & source) {
	switch (source) {
		case AlertSignalPresence::On: return CDM::AlertSignalPresence::On;
		case AlertSignalPresence::Off: return CDM::AlertSignalPresence::Off;
		case AlertSignalPresence::Latch: return CDM::AlertSignalPresence::Latch;
		case AlertSignalPresence::Ack: return CDM::AlertSignalPresence::Ack;
	}
	throw std::runtime_error("Illegal value for AlertSignalPresence");
}

CDM::AlertSignalPrimaryLocation ConvertToCDM::convert(const AlertSignalPrimaryLocation & source) {
	switch (source) {
		case AlertSignalPrimaryLocation::Loc: return CDM::AlertSignalPrimaryLocation::Loc;
		case AlertSignalPrimaryLocation::Rem: return CDM::AlertSignalPrimaryLocation::Rem;
	}
	throw std::runtime_error("Illegal value for AlertSignalPrimaryLocation");
}

CDM::GenerationMode ConvertToCDM::convert(const GenerationMode & source) {
	switch (source) {
		case GenerationMode::Real: return CDM::GenerationMode::Real;
		case GenerationMode::Test: return CDM::GenerationMode::Test;
		case GenerationMode::Demo: return CDM::GenerationMode::Demo;
	}
	throw std::runtime_error("Illegal value for GenerationMode");
}

CDM::MetricCategory ConvertToCDM::convert(const MetricCategory & source) {
	switch (source) {
		case MetricCategory::Unspec: return CDM::MetricCategory::Unspec;
		case MetricCategory::Msrmt: return CDM::MetricCategory::Msrmt;
		case MetricCategory::Clc: return CDM::MetricCategory::Clc;
		case MetricCategory::Set: return CDM::MetricCategory::Set;
		case MetricCategory::Preset: return CDM::MetricCategory::Preset;
		case MetricCategory::Rcmm: return CDM::MetricCategory::Rcmm;
	}
	throw std::runtime_error("Illegal value for MetricCategory");
}

CDM::DerivationMethod ConvertToCDM::convert(const DerivationMethod & source) {
	switch (source) {
		case DerivationMethod::Auto: return CDM::DerivationMethod::Auto;
		case DerivationMethod::Man: return CDM::DerivationMethod::Man;
	}
	throw std::runtime_error("Illegal value for DerivationMethod");
}

CDM::MetricAvailability ConvertToCDM::convert(const MetricAvailability & source) {
	switch (source) {
		case MetricAvailability::Intr: return CDM::MetricAvailability::Intr;
		case MetricAvailability::Cont: return CDM::MetricAvailability::Cont;
	}
	throw std::runtime_error("Illegal value for MetricAvailability");
}

CDM::OperatingMode ConvertToCDM::convert(const OperatingMode & source) {
	switch (source) {
		case OperatingMode::Dis: return CDM::OperatingMode::Dis;
		case OperatingMode::En: return CDM::OperatingMode::En;
		case OperatingMode::NA: return CDM::OperatingMode::NA;
	}
	throw std::runtime_error("Illegal value for OperatingMode");
}

CDM::ContextAssociation ConvertToCDM::convert(const ContextAssociation & source) {
	switch (source) {
		case ContextAssociation::No: return CDM::ContextAssociation::No;
		case ContextAssociation::Pre: return CDM::ContextAssociation::Pre;
		case ContextAssociation::Assoc: return CDM::ContextAssociation::Assoc;
		case ContextAssociation::Dis: return CDM::ContextAssociation::Dis;
	}
	throw std::runtime_error("Illegal value for ContextAssociation");
}

CDM::Sex ConvertToCDM::convert(const Sex & source) {
	switch (source) {
		case Sex::Unspec: return CDM::Sex::Unspec;
		case Sex::M: return CDM::Sex::M;
		case Sex::F: return CDM::Sex::F;
		case Sex::Unkn: return CDM::Sex::Unkn;
	}
	throw std::runtime_error("Illegal value for Sex");
}

CDM::PatientType ConvertToCDM::convert(const PatientType & source) {
	switch (source) {
		case PatientType::Unspec: return CDM::PatientType::Unspec;
		case PatientType::Ad: return CDM::PatientType::Ad;
		case PatientType::Ado: return CDM::PatientType::Ado;
		case PatientType::Ped: return CDM::PatientType::Ped;
		case PatientType::Inf: return CDM::PatientType::Inf;
		case PatientType::Neo: return CDM::PatientType::Neo;
		case PatientType::Oth: return CDM::PatientType::Oth;
	}
	throw std::runtime_error("Illegal value for PatientType");
}

CDM::CanEscalate ConvertToCDM::convert(const CanEscalate & source) {
	switch (source) {
		case CanEscalate::Lo: return CDM::CanEscalate::Lo;
		case CanEscalate::Me: return CDM::CanEscalate::Me;
		case CanEscalate::Hi: return CDM::CanEscalate::Hi;
	}
	throw std::runtime_error("Illegal value for CanEscalate");
}

CDM::CanDeescalate ConvertToCDM::convert(const CanDeescalate & source) {
	switch (source) {
		case CanDeescalate::Me: return CDM::CanDeescalate::Me;
		case CanDeescalate::Lo: return CDM::CanDeescalate::Lo;
		case CanDeescalate::None: return CDM::CanDeescalate::None;
	}
	throw std::runtime_error("Illegal value for CanDeescalate");
}

CDM::Kind ConvertToCDM::convert(const Kind & source) {
	switch (source) {
		case Kind::Rcm: return CDM::Kind::Rcm;
		case Kind::PS: return CDM::Kind::PS;
		case Kind::SST: return CDM::Kind::SST;
		case Kind::ECE: return CDM::Kind::ECE;
		case Kind::DCE: return CDM::Kind::DCE;
		case Kind::Oth: return CDM::Kind::Oth;
	}
	throw std::runtime_error("Illegal value for Kind");
}

CDM::AccessLevel ConvertToCDM::convert(const AccessLevel & source) {
	switch (source) {
		case AccessLevel::Usr: return CDM::AccessLevel::Usr;
		case AccessLevel::CSUsr: return CDM::AccessLevel::CSUsr;
		case AccessLevel::RO: return CDM::AccessLevel::RO;
		case AccessLevel::SP: return CDM::AccessLevel::SP;
		case AccessLevel::Oth: return CDM::AccessLevel::Oth;
	}
	throw std::runtime_error("Illegal value for AccessLevel");
}

CDM::ChargeStatus ConvertToCDM::convert(const ChargeStatus & source) {
	switch (source) {
		case ChargeStatus::Ful: return CDM::ChargeStatus::Ful;
		case ChargeStatus::ChB: return CDM::ChargeStatus::ChB;
		case ChargeStatus::DisChB: return CDM::ChargeStatus::DisChB;
		case ChargeStatus::DEB: return CDM::ChargeStatus::DEB;
	}
	throw std::runtime_error("Illegal value for ChargeStatus");
}

CDM::Criticality ConvertToCDM::convert(const Criticality & source) {
	switch (source) {
		case Criticality::Lo: return CDM::Criticality::Lo;
		case Criticality::Hi: return CDM::Criticality::Hi;
	}
	throw std::runtime_error("Illegal value for Criticality");
}

template
std::unique_ptr<typename DicomTransferCapability::WrappedType> ConvertToCDM::convert(const DicomTransferCapability & source);

template
std::unique_ptr<typename DicomNetworkAe::WrappedType> ConvertToCDM::convert(const DicomNetworkAe & source);

template
std::unique_ptr<typename DicomNetworkConnection::WrappedType> ConvertToCDM::convert(const DicomNetworkConnection & source);

template
std::unique_ptr<typename DicomDeviceDescriptor::WrappedType> ConvertToCDM::convert(const DicomDeviceDescriptor & source);

template
std::unique_ptr<typename Mdib::WrappedType> ConvertToCDM::convert(const Mdib & source);

template
std::unique_ptr<typename MdDescription::WrappedType> ConvertToCDM::convert(const MdDescription & source);

template
std::unique_ptr<typename MdState::WrappedType> ConvertToCDM::convert(const MdState & source);

template
std::unique_ptr<typename LocalizedText::WrappedType> ConvertToCDM::convert(const LocalizedText & source);

template
std::unique_ptr<typename CodedValue::WrappedType> ConvertToCDM::convert(const CodedValue & source);

template
std::unique_ptr<typename Translation::WrappedType> ConvertToCDM::convert(const Translation & source);

template
std::unique_ptr<typename InstanceIdentifier::WrappedType> ConvertToCDM::convert(const InstanceIdentifier & source);

template
std::unique_ptr<typename Range::WrappedType> ConvertToCDM::convert(const Range & source);

template
std::unique_ptr<typename Measurement::WrappedType> ConvertToCDM::convert(const Measurement & source);

template
std::unique_ptr<typename ApprovedJurisdictions::WrappedType> ConvertToCDM::convert(const ApprovedJurisdictions & source);

template
std::unique_ptr<typename OperatingJurisdiction::WrappedType> ConvertToCDM::convert(const OperatingJurisdiction & source);

template
std::unique_ptr<typename PhysicalConnectorInfo::WrappedType> ConvertToCDM::convert(const PhysicalConnectorInfo & source);

template
std::unique_ptr<typename ProductionSpecification::WrappedType> ConvertToCDM::convert(const ProductionSpecification & source);

template
std::unique_ptr<typename CalibrationInfo::WrappedType> ConvertToCDM::convert(const CalibrationInfo & source);

template
std::unique_ptr<typename CalibrationDocumentation::WrappedType> ConvertToCDM::convert(const CalibrationDocumentation & source);

template
std::unique_ptr<typename CalibrationResult::WrappedType> ConvertToCDM::convert(const CalibrationResult & source);

template
std::unique_ptr<typename MdsDescriptor::WrappedType> ConvertToCDM::convert(const MdsDescriptor & source);

template
std::unique_ptr<typename MetaData::WrappedType> ConvertToCDM::convert(const MetaData & source);

template
std::unique_ptr<typename Udi::WrappedType> ConvertToCDM::convert(const Udi & source);

template
std::unique_ptr<typename MdsState::WrappedType> ConvertToCDM::convert(const MdsState & source);

template
std::unique_ptr<typename VmdDescriptor::WrappedType> ConvertToCDM::convert(const VmdDescriptor & source);

template
std::unique_ptr<typename VmdState::WrappedType> ConvertToCDM::convert(const VmdState & source);

template
std::unique_ptr<typename ChannelDescriptor::WrappedType> ConvertToCDM::convert(const ChannelDescriptor & source);

template
std::unique_ptr<typename ChannelState::WrappedType> ConvertToCDM::convert(const ChannelState & source);

template
std::unique_ptr<typename SystemSignalActivation::WrappedType> ConvertToCDM::convert(const SystemSignalActivation & source);

template
std::unique_ptr<typename AlertSystemDescriptor::WrappedType> ConvertToCDM::convert(const AlertSystemDescriptor & source);

template
std::unique_ptr<typename AlertSystemState::WrappedType> ConvertToCDM::convert(const AlertSystemState & source);

template
std::unique_ptr<typename CauseInfo::WrappedType> ConvertToCDM::convert(const CauseInfo & source);

template
std::unique_ptr<typename RemedyInfo::WrappedType> ConvertToCDM::convert(const RemedyInfo & source);

template
std::unique_ptr<typename AlertConditionDescriptor::WrappedType> ConvertToCDM::convert(const AlertConditionDescriptor & source);

template
std::unique_ptr<typename AlertConditionState::WrappedType> ConvertToCDM::convert(const AlertConditionState & source);

template
std::unique_ptr<typename LimitAlertConditionDescriptor::WrappedType> ConvertToCDM::convert(const LimitAlertConditionDescriptor & source);

template
std::unique_ptr<typename LimitAlertConditionState::WrappedType> ConvertToCDM::convert(const LimitAlertConditionState & source);

template
std::unique_ptr<typename AlertSignalDescriptor::WrappedType> ConvertToCDM::convert(const AlertSignalDescriptor & source);

template
std::unique_ptr<typename AlertSignalState::WrappedType> ConvertToCDM::convert(const AlertSignalState & source);

template
std::unique_ptr<typename MetricQuality::WrappedType> ConvertToCDM::convert(const MetricQuality & source);

template
std::unique_ptr<typename Annotation::WrappedType> ConvertToCDM::convert(const Annotation & source);

template
std::unique_ptr<typename NumericMetricValue::WrappedType> ConvertToCDM::convert(const NumericMetricValue & source);

template
std::unique_ptr<typename StringMetricValue::WrappedType> ConvertToCDM::convert(const StringMetricValue & source);

template
std::unique_ptr<typename SampleArrayValue::WrappedType> ConvertToCDM::convert(const SampleArrayValue & source);

template
std::unique_ptr<typename ApplyAnnotation::WrappedType> ConvertToCDM::convert(const ApplyAnnotation & source);

template
std::unique_ptr<typename Relation::WrappedType> ConvertToCDM::convert(const Relation & source);

template
std::unique_ptr<typename NumericMetricDescriptor::WrappedType> ConvertToCDM::convert(const NumericMetricDescriptor & source);

template
std::unique_ptr<typename NumericMetricState::WrappedType> ConvertToCDM::convert(const NumericMetricState & source);

template
std::unique_ptr<typename StringMetricDescriptor::WrappedType> ConvertToCDM::convert(const StringMetricDescriptor & source);

template
std::unique_ptr<typename StringMetricState::WrappedType> ConvertToCDM::convert(const StringMetricState & source);

template
std::unique_ptr<typename EnumStringMetricDescriptor::WrappedType> ConvertToCDM::convert(const EnumStringMetricDescriptor & source);

template
std::unique_ptr<typename AllowedValue::WrappedType> ConvertToCDM::convert(const AllowedValue & source);

template
std::unique_ptr<typename EnumStringMetricState::WrappedType> ConvertToCDM::convert(const EnumStringMetricState & source);

template
std::unique_ptr<typename RealTimeSampleArrayMetricDescriptor::WrappedType> ConvertToCDM::convert(const RealTimeSampleArrayMetricDescriptor & source);

template
std::unique_ptr<typename RealTimeSampleArrayMetricState::WrappedType> ConvertToCDM::convert(const RealTimeSampleArrayMetricState & source);

template
std::unique_ptr<typename DistributionSampleArrayMetricDescriptor::WrappedType> ConvertToCDM::convert(const DistributionSampleArrayMetricDescriptor & source);

template
std::unique_ptr<typename DistributionSampleArrayMetricState::WrappedType> ConvertToCDM::convert(const DistributionSampleArrayMetricState & source);

template
std::unique_ptr<typename ScoDescriptor::WrappedType> ConvertToCDM::convert(const ScoDescriptor & source);

template
std::unique_ptr<typename ScoState::WrappedType> ConvertToCDM::convert(const ScoState & source);

template
std::unique_ptr<typename OperationGroup::WrappedType> ConvertToCDM::convert(const OperationGroup & source);

template
std::unique_ptr<typename SetValueOperationDescriptor::WrappedType> ConvertToCDM::convert(const SetValueOperationDescriptor & source);

template
std::unique_ptr<typename SetValueOperationState::WrappedType> ConvertToCDM::convert(const SetValueOperationState & source);

template
std::unique_ptr<typename SetStringOperationDescriptor::WrappedType> ConvertToCDM::convert(const SetStringOperationDescriptor & source);

template
std::unique_ptr<typename SetStringOperationState::WrappedType> ConvertToCDM::convert(const SetStringOperationState & source);

template
std::unique_ptr<typename AllowedValues::WrappedType> ConvertToCDM::convert(const AllowedValues & source);

template
std::unique_ptr<typename ActivateOperationDescriptor::WrappedType> ConvertToCDM::convert(const ActivateOperationDescriptor & source);

template
std::unique_ptr<typename Argument::WrappedType> ConvertToCDM::convert(const Argument & source);

template
std::unique_ptr<typename ActivateOperationState::WrappedType> ConvertToCDM::convert(const ActivateOperationState & source);

template
std::unique_ptr<typename SetContextStateOperationDescriptor::WrappedType> ConvertToCDM::convert(const SetContextStateOperationDescriptor & source);

template
std::unique_ptr<typename SetContextStateOperationState::WrappedType> ConvertToCDM::convert(const SetContextStateOperationState & source);

template
std::unique_ptr<typename SetMetricStateOperationDescriptor::WrappedType> ConvertToCDM::convert(const SetMetricStateOperationDescriptor & source);

template
std::unique_ptr<typename SetMetricStateOperationState::WrappedType> ConvertToCDM::convert(const SetMetricStateOperationState & source);

template
std::unique_ptr<typename SetComponentStateOperationDescriptor::WrappedType> ConvertToCDM::convert(const SetComponentStateOperationDescriptor & source);

template
std::unique_ptr<typename SetComponentStateOperationState::WrappedType> ConvertToCDM::convert(const SetComponentStateOperationState & source);

template
std::unique_ptr<typename SetAlertStateOperationDescriptor::WrappedType> ConvertToCDM::convert(const SetAlertStateOperationDescriptor & source);

template
std::unique_ptr<typename SetAlertStateOperationState::WrappedType> ConvertToCDM::convert(const SetAlertStateOperationState & source);

template
std::unique_ptr<typename ClockDescriptor::WrappedType> ConvertToCDM::convert(const ClockDescriptor & source);

template
std::unique_ptr<typename ClockState::WrappedType> ConvertToCDM::convert(const ClockState & source);

template
std::unique_ptr<typename BatteryDescriptor::WrappedType> ConvertToCDM::convert(const BatteryDescriptor & source);

template
std::unique_ptr<typename BatteryState::WrappedType> ConvertToCDM::convert(const BatteryState & source);

template
std::unique_ptr<typename SystemContextDescriptor::WrappedType> ConvertToCDM::convert(const SystemContextDescriptor & source);

template
std::unique_ptr<typename SystemContextState::WrappedType> ConvertToCDM::convert(const SystemContextState & source);

template
std::unique_ptr<typename BaseDemographics::WrappedType> ConvertToCDM::convert(const BaseDemographics & source);

template
std::unique_ptr<typename PersonReference::WrappedType> ConvertToCDM::convert(const PersonReference & source);

template
std::unique_ptr<typename LocationDetail::WrappedType> ConvertToCDM::convert(const LocationDetail & source);

template
std::unique_ptr<typename PatientContextDescriptor::WrappedType> ConvertToCDM::convert(const PatientContextDescriptor & source);

template
std::unique_ptr<typename PatientDemographicsCoreData::WrappedType> ConvertToCDM::convert(const PatientDemographicsCoreData & source);

template
std::unique_ptr<typename NeonatalPatientDemographicsCoreData::WrappedType> ConvertToCDM::convert(const NeonatalPatientDemographicsCoreData & source);

template
std::unique_ptr<typename PatientContextState::WrappedType> ConvertToCDM::convert(const PatientContextState & source);

template
std::unique_ptr<typename LocationContextDescriptor::WrappedType> ConvertToCDM::convert(const LocationContextDescriptor & source);

template
std::unique_ptr<typename LocationContextState::WrappedType> ConvertToCDM::convert(const LocationContextState & source);

template
std::unique_ptr<typename WorkflowContextDescriptor::WrappedType> ConvertToCDM::convert(const WorkflowContextDescriptor & source);

template
std::unique_ptr<typename ClinicalInfo::WrappedType> ConvertToCDM::convert(const ClinicalInfo & source);

template
std::unique_ptr<typename RelatedMeasurement::WrappedType> ConvertToCDM::convert(const RelatedMeasurement & source);

template
std::unique_ptr<typename ReferenceRange::WrappedType> ConvertToCDM::convert(const ReferenceRange & source);

template
std::unique_ptr<typename ImagingProcedure::WrappedType> ConvertToCDM::convert(const ImagingProcedure & source);

template
std::unique_ptr<typename LocationReference::WrappedType> ConvertToCDM::convert(const LocationReference & source);

template
std::unique_ptr<typename OrderDetail::WrappedType> ConvertToCDM::convert(const OrderDetail & source);

template
std::unique_ptr<typename PersonParticipation::WrappedType> ConvertToCDM::convert(const PersonParticipation & source);

template
std::unique_ptr<typename WorkflowContextState::WrappedType> ConvertToCDM::convert(const WorkflowContextState & source);

template
std::unique_ptr<typename WorkflowDetail::WrappedType> ConvertToCDM::convert(const WorkflowDetail & source);

template
std::unique_ptr<typename RequestedOrderDetail::WrappedType> ConvertToCDM::convert(const RequestedOrderDetail & source);

template
std::unique_ptr<typename PerformedOrderDetail::WrappedType> ConvertToCDM::convert(const PerformedOrderDetail & source);

template
std::unique_ptr<typename OperatorContextDescriptor::WrappedType> ConvertToCDM::convert(const OperatorContextDescriptor & source);

template
std::unique_ptr<typename OperatorContextState::WrappedType> ConvertToCDM::convert(const OperatorContextState & source);

template
std::unique_ptr<typename MeansContextDescriptor::WrappedType> ConvertToCDM::convert(const MeansContextDescriptor & source);

template
std::unique_ptr<typename MeansContextState::WrappedType> ConvertToCDM::convert(const MeansContextState & source);

template
std::unique_ptr<typename EnsembleContextDescriptor::WrappedType> ConvertToCDM::convert(const EnsembleContextDescriptor & source);

template
std::unique_ptr<typename EnsembleContextState::WrappedType> ConvertToCDM::convert(const EnsembleContextState & source);

template
std::unique_ptr<typename ContainmentTree::WrappedType> ConvertToCDM::convert(const ContainmentTree & source);

template
std::unique_ptr<typename ContainmentTreeEntry::WrappedType> ConvertToCDM::convert(const ContainmentTreeEntry & source);

CDM::AlertConditionReference ConvertToCDM::convert(const AlertConditionReference & source) {
	CDM::AlertConditionReference list;
	for (const auto & element : source) {
		list.push_back(element);
	}
	return list;
}

CDM::RealTimeValueType ConvertToCDM::convert(const RealTimeValueType & source) {
	CDM::RealTimeValueType list;
	for (const auto & element : source) {
		list.push_back(element);
	}
	return list;
}

CDM::EntryRef ConvertToCDM::convert1(const EntryRef & source) {
	CDM::EntryRef list;
	for (const auto & element : source) {
		list.push_back(element);
	}
	return list;
}

CDM::OperationRef ConvertToCDM::convert2(const OperationRef & source) {
	CDM::OperationRef list;
	for (const auto & element : source) {
		list.push_back(element);
	}
	return list;
}


// non-auto generated: invocation state from message model -> transform to MDM
MDM::InvocationState ConvertToCDM::convert(const InvocationState & source) {
	switch (source) {
		case InvocationState::Wait: return MDM::InvocationState::Wait;
		case InvocationState::Start: return MDM::InvocationState::Start;
		case InvocationState::Cnclld: return MDM::InvocationState::Cnclld;
		case InvocationState::CnclldMan: return MDM::InvocationState::CnclldMan;
		case InvocationState::Fin: return MDM::InvocationState::Fin;
		case InvocationState::FinMod: return MDM::InvocationState::FinMod;
		case InvocationState::Fail: return MDM::InvocationState::Fail;
	}
	throw std::runtime_error("Illegal value for InvocationState");
}

template <>
std::unique_ptr<typename MdibContainer::WrappedType> ConvertToCDM::convert(const MdibContainer & source) {
	// todo: replace sequence id
	std::unique_ptr<typename MdibContainer::WrappedType> mdibContainer = std::unique_ptr<typename MdibContainer::WrappedType>(new MdibContainer::WrappedType(xml_schema::Uri("0")));
	mdibContainer->MdDescription(convert(source.getMdDescription()));
	mdibContainer->MdState(convert(source.getMdState()));
	mdibContainer->MdibVersion(source.getMdibVersion());
	return mdibContainer;
}

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
