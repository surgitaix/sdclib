/*
 * Defaults.cpp
 *
 *  Created on: 27.04.2015
 *      Author: roehser
 */

#include "Poco/UUIDGenerator.h"

#include "OSCLib/Data/OSCP/MDIB/Annotation.h"
#include "OSCLib/Data/OSCP/MDIB/BaseDemographics.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"
#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/Measure.h"
#include "OSCLib/Data/OSCP/MDIB/OperationState.h"
#include "OSCLib/Data/OSCP/MDIB/PersonParticipation.h"
#include "OSCLib/Data/OSCP/MDIB/PersonReference.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContext.h"
#include "OSCLib/Data/OSCP/MDIB/Timestamp.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

const std::string NOT_ASSIGNED("Invalid. Not assigned!");

Defaults::Defaults() {

}

Defaults::~Defaults() {

}

CDM::ActivateOperationDescriptor * Defaults::ActivateOperationDescriptor() {
	return new CDM::ActivateOperationDescriptor(
			NOT_ASSIGNED,
			NOT_ASSIGNED);
}

CDM::AlertConditionDescriptor * Defaults::AlertConditionDescriptor() {
	return new CDM::AlertConditionDescriptor(
			NOT_ASSIGNED,
			CDM::AlertConditionKind::Oth,
			CDM::AlertConditionPriority::None);
}

CDM::AlertConditionReference * Defaults::AlertConditionReference() {
	return new CDM::AlertConditionReference();
}

CDM::AlertConditionState * Defaults::AlertConditionState() {
	return new CDM::AlertConditionState(
			NOT_ASSIGNED,
			CDM::PausableActivation::On,
			CDM::AlertConditionState::PresenceType(false));
}

CDM::AlertSignalDescriptor * Defaults::AlertSignalDescriptor() {
	return new CDM::AlertSignalDescriptor(
			NOT_ASSIGNED,
			NOT_ASSIGNED,
			CDM::AlertSignalManifestation::Vis,
			CDM::AlertSignalDescriptor::LatchingType(false));
}

CDM::AlertSignalState * Defaults::AlertSignalState() {
	return new CDM::AlertSignalState(
			NOT_ASSIGNED,
			CDM::PausableActivation::On);
}

CDM::AlertSystemDescriptor * Defaults::AlertSystemDescriptor() {
	return new CDM::AlertSystemDescriptor(
			NOT_ASSIGNED);
}

CDM::AlertSystemState * Defaults::AlertSystemState() {
	return new CDM::AlertSystemState(
			NOT_ASSIGNED,
			CDM::PausableActivation::On);
}

CDM::Annotation * Defaults::Annotation() {
	return new CDM::Annotation(
			ConvertToCDM::convert(OSCP::CodedValue())
			);
}

CDM::Base64Binary * Defaults::Base64Binary() {
	return new CDM::Base64Binary();
}

CDM::BaseDemographics * Defaults::BaseDemographics() {
	return new CDM::BaseDemographics();
}

CDM::CauseInfo * Defaults::CauseInfo() {
	return new CDM::CauseInfo();
}

CDM::CalibrationInfo * Defaults::CalibrationInfo() {
	return new CDM::CalibrationInfo();
}

CDM::ChannelDescriptor * Defaults::ChannelDescriptor() {
	return new CDM::ChannelDescriptor(
			NOT_ASSIGNED);
}

CDM::ClinicalInfo * Defaults::ClinicalInfo() {
	return new CDM::ClinicalInfo(ConvertToCDM::convert(OSCP::CodedValue()));
}

CDM::ClockDescriptor * Defaults::ClockDescriptor() {
	return new CDM::ClockDescriptor(
			NOT_ASSIGNED);
}

CDM::ClockState * Defaults::ClockState() {
	return new CDM::ClockState(
			NOT_ASSIGNED,
			false);
}

CDM::CodedValue * Defaults::CodedValue() {
	return new CDM::CodedValue("Code not assigned");
}

CDM::ComponentState * Defaults::ComponentState() {
	return new CDM::ComponentState(
			NOT_ASSIGNED);
}

CDM::DateTime * Defaults::DateTime() {
	return new CDM::DateTime(0, 0, 0, 0, 0, 0);
}

CDM::DICOMNetworkAE * Defaults::DICOMNetworkAE() {
	CDM::DICOMDeviceDescriptor::NetworkAEType::NetworkConnectionReferenceType connectionReferences;
	return new CDM::DICOMNetworkAE("undefined title", connectionReferences, false, false);
}

CDM::DICOMDeviceDescriptor * Defaults::DICOMDeviceDescriptor() {

	return new CDM::DICOMDeviceDescriptor(
				NOT_ASSIGNED,
				ConvertToCDM::convert(OSCP::SystemContext()));
}

CDM::DICOMNetworkConnection * Defaults::DICOMNetworkConnection() {
	return new CDM::DICOMNetworkConnection("undefinedId", "127.0.0.1");
}

CDM::DICOMTransferCapability * Defaults::DICOMTransferCapability() {
	return new CDM::DICOMTransferCapability("unknown SOP class", CDM::DICOMTransferRole::SCU);
}

CDM::Duration * Defaults::Duration() {
	return new CDM::Duration(false, 0, 0, 0, 0, 0, 1.0);
}

CDM::EnsembleContextDescriptor * Defaults::EnsembleContextDescriptor() {
	return new CDM::EnsembleContextDescriptor(
			NOT_ASSIGNED);
}

CDM::EnsembleContextState * Defaults::EnsembleContextState() {
	return new CDM::EnsembleContextState(NOT_ASSIGNED, 0);
}

CDM::EnumNomenRef * Defaults::EnumNomenRef() {
	return new CDM::EnumNomenRef(
			ConvertToCDM::convert(OSCP::CodedValue()));
}

CDM::EnumStringMetricDescriptor * Defaults::EnumStringMetricDescriptor() {
	return new CDM::EnumStringMetricDescriptor(
			NOT_ASSIGNED,
			ConvertToCDM::convert(OSCP::CodedValue()),
			CDM::MetricCategory::Unspec,
			CDM::MetricAvailability::Cont);
}

CDM::EnumStringMetricState * Defaults::EnumStringMetricState() {
	return new CDM::EnumStringMetricState(
			NOT_ASSIGNED);
}

CDM::HydraMDSDescriptor * Defaults::HydraMDSDescriptor() {
	return new CDM::HydraMDSDescriptor(
			NOT_ASSIGNED,
			ConvertToCDM::convert(OSCP::SystemContext()));
}

CDM::HydraMDSState * Defaults::HydraMDSState() {
	return new CDM::HydraMDSState(
			NOT_ASSIGNED);
}

CDM::ImagingProcedure * Defaults::ImagingProcedure() {
	return new CDM::ImagingProcedure(
			ConvertToCDM::convert(OSCP::InstanceIdentifier()),
			ConvertToCDM::convert(OSCP::InstanceIdentifier()),
			ConvertToCDM::convert(OSCP::InstanceIdentifier()),
			ConvertToCDM::convert(OSCP::InstanceIdentifier()));
}

CDM::InstanceIdentifier * Defaults::InstanceIdentifier() {
	return new CDM::InstanceIdentifier(NOT_ASSIGNED);
}

CDM::Language * Defaults::Language() {
	return new CDM::Language("en");
}

CDM::LimitAlertConditionDescriptor * Defaults::LimitAlertConditionDescriptor() {
	return new CDM::LimitAlertConditionDescriptor(
			NOT_ASSIGNED,
			CDM::AlertConditionKind::Oth,
			CDM::AlertConditionPriority::None,
			ConvertToCDM::convert(OSCP::Range())
	);
}

CDM::LimitAlertConditionState * Defaults::LimitAlertConditionState() {
	return new CDM::LimitAlertConditionState(
			NOT_ASSIGNED,
			CDM::PausableActivation::On,
			CDM::LimitAlertConditionState::PresenceType(false),
			CDM::MonitoredAlertLimits::None);
}

CDM::LocalizedText * Defaults::LocalizedText() {
	return new CDM::LocalizedText(
			"Text not assigned"
			);
}

CDM::LocationContextDescriptor * Defaults::LocationContextDescriptor() {
	return new CDM::LocationContextDescriptor(
			NOT_ASSIGNED);
}

CDM::LocationContextState * Defaults::LocationContextState() {
	return new CDM::LocationContextState(NOT_ASSIGNED, 0);
}

CDM::Measure * Defaults::Measure() {
	return new CDM::Measure(
			ConvertToCDM::convert(OSCP::CodedValue()));
}

CDM::MeasurementState * Defaults::MeasurementState() {
	return new CDM::MeasurementState(
			ConvertToCDM::convert(OSCP::MetricMeasurementValidity::Invalid));
}

CDM::MDDescription * Defaults::MDDescription() {
	return new CDM::MDDescription();
}

CDM::MDState * Defaults::MDState() {
	return new CDM::MDState();
}

CDM::NumericMetricDescriptor * Defaults::NumericMetricDescriptor() {
	return new CDM::NumericMetricDescriptor(
			NOT_ASSIGNED,
			ConvertToCDM::convert(OSCP::CodedValue()),
			CDM::MetricCategory::Unspec,
			CDM::MetricAvailability::Cont,
			1.0);
}

CDM::NumericMetricState * Defaults::NumericMetricState() {
	return new CDM::NumericMetricState(
			NOT_ASSIGNED);
}

CDM::NumericMetricValue * Defaults::NumericMetricValue() {
	return new CDM::NumericMetricValue(
			CDM::NumericMetricValue::MeasurementStateType(
					CDM::MetricMeasurementValidity::Inv));
}

CDM::OperationState * Defaults::OperationState() {
	return new CDM::OperationState(
			NOT_ASSIGNED,
			CDM::OperatingMode::En);
}

CDM::OperatorContextDescriptor * Defaults::OperatorContextDescriptor() {
	return new CDM::OperatorContextDescriptor(
			NOT_ASSIGNED);
}

CDM::OperatorContextState * Defaults::OperatorContextState() {
	return new CDM::OperatorContextState(NOT_ASSIGNED, 0);
}

CDM::Order * Defaults::Order() {
	return new CDM::Order(
			ConvertToCDM::convert(OSCP::InstanceIdentifier()),
			ConvertToCDM::convert(OSCP::PersonReference())
	);
}

CDM::OrderDetail * Defaults::OrderDetail() {
	return new CDM::OrderDetail();
}

CDM::PatientContextDescriptor * Defaults::PatientContextDescriptor() {
	return new CDM::PatientContextDescriptor(
			NOT_ASSIGNED);
}

CDM::PatientContextState * Defaults::PatientContextState() {
	return new CDM::PatientContextState(NOT_ASSIGNED, 0);
}

CDM::PatientDemographicsCoreData * Defaults::PatientDemographicsCoreData() {
	return new CDM::PatientDemographicsCoreData();
}

CDM::PersonParticipation * Defaults::PersonParticipation() {
	return new CDM::PersonParticipation();
}

CDM::PersonReference * Defaults::PersonReference() {
	auto value = new CDM::PersonReference();
	value->Identification().push_back(ConvertToCDM::convert(OSCP::InstanceIdentifier()));
	return value;
}

CDM::ProductionSpecification * Defaults::ProductionSpecification() {
	return new CDM::ProductionSpecification(
			ConvertToCDM::convert(OSCP::CodedValue()),
			"not assigned");
}

CDM::Range * Defaults::Range() {
	return new CDM::Range();
}

CDM::RealTimeSampleArrayMetricDescriptor * Defaults::RealTimeSampleArrayMetricDescriptor() {
	return new CDM::RealTimeSampleArrayMetricDescriptor(
			NOT_ASSIGNED,
			ConvertToCDM::convert(OSCP::CodedValue()),
			CDM::MetricCategory::Unspec,
			CDM::MetricAvailability::Cont,
			CDM::RealTimeSampleArrayMetricDescriptor::SamplePeriodType(false, 0, 0, 0, 0, 0, 0.0),
			CDM::RealTimeSampleArrayMetricDescriptor::ResolutionType(1.0));
}

CDM::RealTimeSampleArrayMetricState * Defaults::RealTimeSampleArrayMetricState() {
	return new CDM::RealTimeSampleArrayMetricState(
			NOT_ASSIGNED);
}

CDM::RealTimeSampleArrayValue * Defaults::RealTimeSampleArrayValue() {
	return new CDM::RealTimeSampleArrayValue(
			CDM::RealTimeSampleArrayValue::MeasurementStateType(
					CDM::MetricMeasurementValidity::Inv));
}

CDM::ReferencedVersion * Defaults::ReferencedVersion() {
	return new CDM::ReferencedVersion(0);
}

CDM::RemedyInfo * Defaults::RemedyInfo() {
	return new CDM::RemedyInfo();
}

CDM::RTValueType * Defaults::RTValueType() {
	return new CDM::RTValueType();
}

CDM::SampleIndex * Defaults::SampleIndex() {
	return new CDM::SampleIndex(0);
}

CDM::SCODescriptor * Defaults::SCODescriptor() {
	return new CDM::SCODescriptor(NOT_ASSIGNED);
}

CDM::SetAlertStateOperationDescriptor * Defaults::SetAlertStateOperationDescriptor() {
	return new CDM::SetAlertStateOperationDescriptor(
				NOT_ASSIGNED,
				NOT_ASSIGNED);
}

CDM::SetContextOperationDescriptor * Defaults::SetContextOperationDescriptor() {
	return new CDM::SetContextOperationDescriptor(
				NOT_ASSIGNED,
				NOT_ASSIGNED);
}

CDM::SetRangeOperationDescriptor * Defaults::SetRangeOperationDescriptor() {
	return new CDM::SetRangeOperationDescriptor(
				NOT_ASSIGNED,
				NOT_ASSIGNED,
				ConvertToCDM::convert(OSCP::Range()));
}

CDM::SetStringOperationDescriptor * Defaults::SetStringOperationDescriptor() {
	return new CDM::SetStringOperationDescriptor(
				NOT_ASSIGNED,
				NOT_ASSIGNED);
}

CDM::SetValueOperationDescriptor * Defaults::SetValueOperationDescriptor() {
	return new CDM::SetValueOperationDescriptor(
				NOT_ASSIGNED,
				NOT_ASSIGNED);
}

CDM::StringMetricDescriptor * Defaults::StringMetricDescriptor() {
	return new CDM::StringMetricDescriptor(
			NOT_ASSIGNED,
			ConvertToCDM::convert(OSCP::CodedValue()),
			CDM::MetricCategory::Unspec,
			CDM::MetricAvailability::Cont);
}

CDM::StringMetricState * Defaults::StringMetricState() {
	return new CDM::StringMetricState(
			NOT_ASSIGNED);
}

CDM::StringMetricValue * Defaults::StringMetricValue() {
	return new CDM::StringMetricValue(
			CDM::StringMetricValue::MeasurementStateType(
					CDM::MetricMeasurementValidity::Inv));
}

CDM::SystemContext * Defaults::SystemContext() {
	return new CDM::SystemContext(
			Poco::UUIDGenerator::defaultGenerator().create().toString());
}

CDM::SystemMetaData * Defaults::SystemMetaData() {
	return new CDM::SystemMetaData();
}

CDM::Timestamp * Defaults::Timestamp() {
	return new CDM::Timestamp(0);
}

CDM::TimeZone * Defaults::TimeZone() {
	return new CDM::TimeZone();
}

CDM::VersionCounter * Defaults::VersionCounter() {
	return new CDM::VersionCounter(0);
}

CDM::VMDDescriptor * Defaults::VMDDescriptor() {
	return new CDM::VMDDescriptor(
			NOT_ASSIGNED);
}

CDM::WorkflowContextDescriptor * Defaults::WorkflowContextDescriptor() {
	return new CDM::WorkflowContextDescriptor(
			NOT_ASSIGNED);
}

CDM::WorkflowContextState * Defaults::WorkflowContextState() {
	return new CDM::WorkflowContextState(NOT_ASSIGNED, 0);
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
