#include "OSCLib/Data/OSCP/MDIB/Mdib.h"
#include "OSCLib/Data/OSCP/MDIB/MdDescription.h"
#include "OSCLib/Data/OSCP/MDIB/MdState.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/Measurement.h"
#include "OSCLib/Data/OSCP/MDIB/ApprovedJurisdictions.h"
#include "OSCLib/Data/OSCP/MDIB/OperatingJurisdiction.h"
#include "OSCLib/Data/OSCP/MDIB/ProductionSpecification.h"
#include "OSCLib/Data/OSCP/MDIB/CalibrationInfo.h"
#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MetaData.h"
#include "OSCLib/Data/OSCP/MDIB/Udi.h"
#include "OSCLib/Data/OSCP/MDIB/MdsState.h"
#include "OSCLib/Data/OSCP/MDIB/VmdDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/VmdState.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelState.h"
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
#include "OSCLib/Data/OSCP/MDIB/MetricQuality.h"
#include "OSCLib/Data/OSCP/MDIB/Annotation.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/SampleArrayValue.h"
#include "OSCLib/Data/OSCP/MDIB/ApplyAnnotation.h"
#include "OSCLib/Data/OSCP/MDIB/Relation.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AllowedValue.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/DistributionSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/DistributionSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/ScoDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ScoState.h"
#include "OSCLib/Data/OSCP/MDIB/SetValueOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetValueOperationState.h"
#include "OSCLib/Data/OSCP/MDIB/SetStringOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetStringOperationState.h"
#include "OSCLib/Data/OSCP/MDIB/AllowedValues.h"
#include "OSCLib/Data/OSCP/MDIB/ActivateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/Argument.h"
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
#include "OSCLib/Data/OSCP/MDIB/RelatedMeasurement.h"
#include "OSCLib/Data/OSCP/MDIB/ReferenceRange.h"
#include "OSCLib/Data/OSCP/MDIB/ImagingProcedure.h"
#include "OSCLib/Data/OSCP/MDIB/LocationReference.h"
#include "OSCLib/Data/OSCP/MDIB/OrderDetail.h"
#include "OSCLib/Data/OSCP/MDIB/PersonParticipation.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextState.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowDetail.h"
#include "OSCLib/Data/OSCP/MDIB/RequestedOrderDetail.h"
#include "OSCLib/Data/OSCP/MDIB/PerformedOrderDetail.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextState.h"
#include "OSCLib/Data/OSCP/MDIB/MeansContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MeansContextState.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextState.h"
#include "OSCLib/Data/OSCP/MDIB/ContainmentTree.h"
#include "OSCLib/Data/OSCP/MDIB/ContainmentTreeEntry.h"
#include "OSCLib/Data/OSCP/MDIB/DicomTransferCapability.h"
#include "OSCLib/Data/OSCP/MDIB/DicomNetworkAe.h"
#include "OSCLib/Data/OSCP/MDIB/DicomNetworkConnection.h"
#include "OSCLib/Data/OSCP/MDIB/DicomDeviceDescriptor.h"


/*
 * Defaults.h
 *
 *  Created on: 20.07.2017
 *      Author: buerger
 *
 *  This file is autogenerated.
 *
 *  Do not edit this file. For customization please edit the Defaults_beginning.h or Defaults_ending.h
 */

#include "OSCLib/Data/OSCP/MDIB/Defaults.h"
#include "Poco/UUIDGenerator.h"
#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"

#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

const std::string NOT_ASSIGNED("Invalid. Not assigned!");

Defaults::Defaults() {

}

Defaults::~Defaults() {

}


CDM::Mdib  * Defaults::Mdib() {
	return new CDM::Mdib();
}

CDM::MdDescription  * Defaults::MdDescription() {
	return new CDM::MdDescription();
}

CDM::MdState  * Defaults::MdState() {
	return new CDM::MdState();
}

CDM::LocalizedText  * Defaults::LocalizedText() {
	return new CDM::LocalizedText();
}

CDM::CodedValue  * Defaults::CodedValue() {
	return new CDM::CodedValue();
}

CDM::InstanceIdentifier  * Defaults::InstanceIdentifier() {
	return new CDM::InstanceIdentifier();
}

CDM::Range  * Defaults::Range() {
	return new CDM::Range();
}

CDM::Measurement  * Defaults::Measurement() {
	return new CDM::Measurement();
}

CDM::ApprovedJurisdictions  * Defaults::ApprovedJurisdictions() {
	return new CDM::ApprovedJurisdictions();
}

CDM::OperatingJurisdiction  * Defaults::OperatingJurisdiction() {
	return new CDM::OperatingJurisdiction();
}

CDM::ProductionSpecification  * Defaults::ProductionSpecification() {
	return new CDM::ProductionSpecification();
}

CDM::CalibrationInfo  * Defaults::CalibrationInfo() {
	return new CDM::CalibrationInfo();
}

CDM::MdsDescriptor  * Defaults::MdsDescriptor() {
	return new CDM::MdsDescriptor();
}

CDM::MetaData  * Defaults::MetaData() {
	return new CDM::MetaData();
}

CDM::Udi  * Defaults::Udi() {
	return new CDM::Udi();
}

CDM::MdsState  * Defaults::MdsState() {
	return new CDM::MdsState();
}

CDM::VmdDescriptor  * Defaults::VmdDescriptor() {
	return new CDM::VmdDescriptor();
}

CDM::VmdState  * Defaults::VmdState() {
	return new CDM::VmdState();
}

CDM::ChannelDescriptor  * Defaults::ChannelDescriptor() {
	return new CDM::ChannelDescriptor();
}

CDM::ChannelState  * Defaults::ChannelState() {
	return new CDM::ChannelState();
}

CDM::SystemSignalActivation  * Defaults::SystemSignalActivation() {
	return new CDM::SystemSignalActivation();
}

CDM::AlertSystemDescriptor  * Defaults::AlertSystemDescriptor() {
	return new CDM::AlertSystemDescriptor();
}

CDM::AlertSystemState  * Defaults::AlertSystemState() {
	return new CDM::AlertSystemState();
}

CDM::CauseInfo  * Defaults::CauseInfo() {
	return new CDM::CauseInfo();
}

CDM::RemedyInfo  * Defaults::RemedyInfo() {
	return new CDM::RemedyInfo();
}

CDM::AlertConditionDescriptor  * Defaults::AlertConditionDescriptor() {
	return new CDM::AlertConditionDescriptor();
}

CDM::AlertConditionState  * Defaults::AlertConditionState() {
	return new CDM::AlertConditionState();
}

CDM::LimitAlertConditionDescriptor  * Defaults::LimitAlertConditionDescriptor() {
	return new CDM::LimitAlertConditionDescriptor();
}

CDM::LimitAlertConditionState  * Defaults::LimitAlertConditionState() {
	return new CDM::LimitAlertConditionState();
}

CDM::AlertSignalDescriptor  * Defaults::AlertSignalDescriptor() {
	return new CDM::AlertSignalDescriptor();
}

CDM::AlertSignalState  * Defaults::AlertSignalState() {
	return new CDM::AlertSignalState();
}

CDM::MetricQuality  * Defaults::MetricQuality() {
	return new CDM::MetricQuality();
}

CDM::Annotation  * Defaults::Annotation() {
	return new CDM::Annotation();
}

CDM::NumericMetricValue  * Defaults::NumericMetricValue() {
	return new CDM::NumericMetricValue();
}

CDM::StringMetricValue  * Defaults::StringMetricValue() {
	return new CDM::StringMetricValue();
}

CDM::SampleArrayValue  * Defaults::SampleArrayValue() {
	return new CDM::SampleArrayValue();
}

CDM::ApplyAnnotation  * Defaults::ApplyAnnotation() {
	return new CDM::ApplyAnnotation();
}

CDM::Relation  * Defaults::Relation() {
	return new CDM::Relation();
}

CDM::NumericMetricDescriptor  * Defaults::NumericMetricDescriptor() {
	return new CDM::NumericMetricDescriptor();
}

CDM::NumericMetricState  * Defaults::NumericMetricState() {
	return new CDM::NumericMetricState();
}

CDM::StringMetricDescriptor  * Defaults::StringMetricDescriptor() {
	return new CDM::StringMetricDescriptor();
}

CDM::StringMetricState  * Defaults::StringMetricState() {
	return new CDM::StringMetricState();
}

CDM::EnumStringMetricDescriptor  * Defaults::EnumStringMetricDescriptor() {
	return new CDM::EnumStringMetricDescriptor();
}

CDM::AllowedValue  * Defaults::AllowedValue() {
	return new CDM::AllowedValue();
}

CDM::EnumStringMetricState  * Defaults::EnumStringMetricState() {
	return new CDM::EnumStringMetricState();
}

CDM::RealTimeSampleArrayMetricDescriptor  * Defaults::RealTimeSampleArrayMetricDescriptor() {
	return new CDM::RealTimeSampleArrayMetricDescriptor();
}

CDM::RealTimeSampleArrayMetricState  * Defaults::RealTimeSampleArrayMetricState() {
	return new CDM::RealTimeSampleArrayMetricState();
}

CDM::DistributionSampleArrayMetricDescriptor  * Defaults::DistributionSampleArrayMetricDescriptor() {
	return new CDM::DistributionSampleArrayMetricDescriptor();
}

CDM::DistributionSampleArrayMetricState  * Defaults::DistributionSampleArrayMetricState() {
	return new CDM::DistributionSampleArrayMetricState();
}

CDM::ScoDescriptor  * Defaults::ScoDescriptor() {
	return new CDM::ScoDescriptor();
}

CDM::ScoState  * Defaults::ScoState() {
	return new CDM::ScoState();
}

CDM::SetValueOperationDescriptor  * Defaults::SetValueOperationDescriptor() {
	return new CDM::SetValueOperationDescriptor();
}

CDM::SetValueOperationState  * Defaults::SetValueOperationState() {
	return new CDM::SetValueOperationState();
}

CDM::SetStringOperationDescriptor  * Defaults::SetStringOperationDescriptor() {
	return new CDM::SetStringOperationDescriptor();
}

CDM::SetStringOperationState  * Defaults::SetStringOperationState() {
	return new CDM::SetStringOperationState();
}

CDM::AllowedValues  * Defaults::AllowedValues() {
	return new CDM::AllowedValues();
}

CDM::ActivateOperationDescriptor  * Defaults::ActivateOperationDescriptor() {
	return new CDM::ActivateOperationDescriptor();
}

CDM::Argument  * Defaults::Argument() {
	return new CDM::Argument();
}

CDM::ActivateOperationState  * Defaults::ActivateOperationState() {
	return new CDM::ActivateOperationState();
}

CDM::SetContextStateOperationDescriptor  * Defaults::SetContextStateOperationDescriptor() {
	return new CDM::SetContextStateOperationDescriptor();
}

CDM::SetContextStateOperationState  * Defaults::SetContextStateOperationState() {
	return new CDM::SetContextStateOperationState();
}

CDM::SetMetricStateOperationDescriptor  * Defaults::SetMetricStateOperationDescriptor() {
	return new CDM::SetMetricStateOperationDescriptor();
}

CDM::SetMetricStateOperationState  * Defaults::SetMetricStateOperationState() {
	return new CDM::SetMetricStateOperationState();
}

CDM::SetComponentStateOperationDescriptor  * Defaults::SetComponentStateOperationDescriptor() {
	return new CDM::SetComponentStateOperationDescriptor();
}

CDM::SetComponentStateOperationState  * Defaults::SetComponentStateOperationState() {
	return new CDM::SetComponentStateOperationState();
}

CDM::SetAlertStateOperationDescriptor  * Defaults::SetAlertStateOperationDescriptor() {
	return new CDM::SetAlertStateOperationDescriptor();
}

CDM::SetAlertStateOperationState  * Defaults::SetAlertStateOperationState() {
	return new CDM::SetAlertStateOperationState();
}

CDM::ClockDescriptor  * Defaults::ClockDescriptor() {
	return new CDM::ClockDescriptor();
}

CDM::ClockState  * Defaults::ClockState() {
	return new CDM::ClockState();
}

CDM::BatteryDescriptor  * Defaults::BatteryDescriptor() {
	return new CDM::BatteryDescriptor();
}

CDM::BatteryState  * Defaults::BatteryState() {
	return new CDM::BatteryState();
}

CDM::SystemContextDescriptor  * Defaults::SystemContextDescriptor() {
	return new CDM::SystemContextDescriptor();
}

CDM::SystemContextState  * Defaults::SystemContextState() {
	return new CDM::SystemContextState();
}

CDM::BaseDemographics  * Defaults::BaseDemographics() {
	return new CDM::BaseDemographics();
}

CDM::PersonReference  * Defaults::PersonReference() {
	return new CDM::PersonReference();
}

CDM::LocationDetail  * Defaults::LocationDetail() {
	return new CDM::LocationDetail();
}

CDM::PatientContextDescriptor  * Defaults::PatientContextDescriptor() {
	return new CDM::PatientContextDescriptor();
}

CDM::PatientDemographicsCoreData  * Defaults::PatientDemographicsCoreData() {
	return new CDM::PatientDemographicsCoreData();
}

CDM::NeonatalPatientDemographicsCoreData  * Defaults::NeonatalPatientDemographicsCoreData() {
	return new CDM::NeonatalPatientDemographicsCoreData();
}

CDM::PatientContextState  * Defaults::PatientContextState() {
	return new CDM::PatientContextState();
}

CDM::LocationContextDescriptor  * Defaults::LocationContextDescriptor() {
	return new CDM::LocationContextDescriptor();
}

CDM::LocationContextState  * Defaults::LocationContextState() {
	return new CDM::LocationContextState();
}

CDM::WorkflowContextDescriptor  * Defaults::WorkflowContextDescriptor() {
	return new CDM::WorkflowContextDescriptor();
}

CDM::ClinicalInfo  * Defaults::ClinicalInfo() {
	return new CDM::ClinicalInfo();
}

CDM::RelatedMeasurement  * Defaults::RelatedMeasurement() {
	return new CDM::RelatedMeasurement();
}

CDM::ReferenceRange  * Defaults::ReferenceRange() {
	return new CDM::ReferenceRange();
}

CDM::ImagingProcedure  * Defaults::ImagingProcedure() {
	return new CDM::ImagingProcedure();
}

CDM::LocationReference  * Defaults::LocationReference() {
	return new CDM::LocationReference();
}

CDM::OrderDetail  * Defaults::OrderDetail() {
	return new CDM::OrderDetail();
}

CDM::PersonParticipation  * Defaults::PersonParticipation() {
	return new CDM::PersonParticipation();
}

CDM::WorkflowContextState  * Defaults::WorkflowContextState() {
	return new CDM::WorkflowContextState();
}

CDM::WorkflowDetail  * Defaults::WorkflowDetail() {
	return new CDM::WorkflowDetail();
}

CDM::RequestedOrderDetail  * Defaults::RequestedOrderDetail() {
	return new CDM::RequestedOrderDetail();
}

CDM::PerformedOrderDetail  * Defaults::PerformedOrderDetail() {
	return new CDM::PerformedOrderDetail();
}

CDM::OperatorContextDescriptor  * Defaults::OperatorContextDescriptor() {
	return new CDM::OperatorContextDescriptor();
}

CDM::OperatorContextState  * Defaults::OperatorContextState() {
	return new CDM::OperatorContextState();
}

CDM::MeansContextDescriptor  * Defaults::MeansContextDescriptor() {
	return new CDM::MeansContextDescriptor();
}

CDM::MeansContextState  * Defaults::MeansContextState() {
	return new CDM::MeansContextState();
}

CDM::EnsembleContextDescriptor  * Defaults::EnsembleContextDescriptor() {
	return new CDM::EnsembleContextDescriptor();
}

CDM::EnsembleContextState  * Defaults::EnsembleContextState() {
	return new CDM::EnsembleContextState();
}

CDM::ContainmentTree  * Defaults::ContainmentTree() {
	return new CDM::ContainmentTree();
}

CDM::ContainmentTreeEntry  * Defaults::ContainmentTreeEntry() {
	return new CDM::ContainmentTreeEntry();
}

CDM::DicomTransferCapability  * Defaults::DicomTransferCapability() {
	return new CDM::DicomTransferCapability();
}

CDM::DicomNetworkAe  * Defaults::DicomNetworkAe() {
	return new CDM::DicomNetworkAe();
}

CDM::DicomNetworkConnection  * Defaults::DicomNetworkConnection() {
	return new CDM::DicomNetworkConnection();
}

CDM::DicomDeviceDescriptor  * Defaults::DicomDeviceDescriptor() {
	return new CDM::DicomDeviceDescriptor();
}



} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
