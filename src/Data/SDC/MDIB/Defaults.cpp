#include "OSCLib/Data/SDC/MDIB/Mdib.h"
#include "OSCLib/Data/SDC/MDIB/MdDescription.h"
#include "OSCLib/Data/SDC/MDIB/MdState.h"
#include "OSCLib/Data/SDC/MDIB/LocalizedText.h"
#include "OSCLib/Data/SDC/MDIB/CodedValue.h"
#include "OSCLib/Data/SDC/MDIB/Translation.h"
#include "OSCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/SDC/MDIB/Range.h"
#include "OSCLib/Data/SDC/MDIB/Measurement.h"
#include "OSCLib/Data/SDC/MDIB/ApprovedJurisdictions.h"
#include "OSCLib/Data/SDC/MDIB/OperatingJurisdiction.h"
#include "OSCLib/Data/SDC/MDIB/PhysicalConnectorInfo.h"
#include "OSCLib/Data/SDC/MDIB/ProductionSpecification.h"
#include "OSCLib/Data/SDC/MDIB/CalibrationInfo.h"
#include "OSCLib/Data/SDC/MDIB/CalibrationDocumentation.h"
#include "OSCLib/Data/SDC/MDIB/CalibrationResult.h"
#include "OSCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MetaData.h"
#include "OSCLib/Data/SDC/MDIB/Udi.h"
#include "OSCLib/Data/SDC/MDIB/MdsState.h"
#include "OSCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/VmdState.h"
#include "OSCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/ChannelState.h"
#include "OSCLib/Data/SDC/MDIB/SystemSignalActivation.h"
#include "OSCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "OSCLib/Data/SDC/MDIB/CauseInfo.h"
#include "OSCLib/Data/SDC/MDIB/RemedyInfo.h"
#include "OSCLib/Data/SDC/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "OSCLib/Data/SDC/MDIB/LimitAlertConditionDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/SDC/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "OSCLib/Data/SDC/MDIB/MetricQuality.h"
#include "OSCLib/Data/SDC/MDIB/Annotation.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "OSCLib/Data/SDC/MDIB/SampleArrayValue.h"
#include "OSCLib/Data/SDC/MDIB/ApplyAnnotation.h"
#include "OSCLib/Data/SDC/MDIB/Relation.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "OSCLib/Data/SDC/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/StringMetricState.h"
#include "OSCLib/Data/SDC/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/AllowedValue.h"
#include "OSCLib/Data/SDC/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/SDC/MDIB/DistributionSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/DistributionSampleArrayMetricState.h"
#include "OSCLib/Data/SDC/MDIB/ScoDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/ScoState.h"
#include "OSCLib/Data/SDC/MDIB/OperationGroup.h"
#include "OSCLib/Data/SDC/MDIB/SetValueOperationDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/SetValueOperationState.h"
#include "OSCLib/Data/SDC/MDIB/SetStringOperationDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/SetStringOperationState.h"
#include "OSCLib/Data/SDC/MDIB/AllowedValues.h"
#include "OSCLib/Data/SDC/MDIB/ActivateOperationDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/Argument.h"
#include "OSCLib/Data/SDC/MDIB/ActivateOperationState.h"
#include "OSCLib/Data/SDC/MDIB/SetContextStateOperationDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/SetContextStateOperationState.h"
#include "OSCLib/Data/SDC/MDIB/SetMetricStateOperationDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/SetMetricStateOperationState.h"
#include "OSCLib/Data/SDC/MDIB/SetComponentStateOperationDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/SetComponentStateOperationState.h"
#include "OSCLib/Data/SDC/MDIB/SetAlertStateOperationDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/SetAlertStateOperationState.h"
#include "OSCLib/Data/SDC/MDIB/ClockDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/ClockState.h"
#include "OSCLib/Data/SDC/MDIB/BatteryDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/BatteryState.h"
#include "OSCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/SystemContextState.h"
#include "OSCLib/Data/SDC/MDIB/BaseDemographics.h"
#include "OSCLib/Data/SDC/MDIB/PersonReference.h"
#include "OSCLib/Data/SDC/MDIB/LocationDetail.h"
#include "OSCLib/Data/SDC/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/PatientDemographicsCoreData.h"
#include "OSCLib/Data/SDC/MDIB/NeonatalPatientDemographicsCoreData.h"
#include "OSCLib/Data/SDC/MDIB/PatientContextState.h"
#include "OSCLib/Data/SDC/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/LocationContextState.h"
#include "OSCLib/Data/SDC/MDIB/WorkflowContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/ClinicalInfo.h"
#include "OSCLib/Data/SDC/MDIB/RelatedMeasurement.h"
#include "OSCLib/Data/SDC/MDIB/ReferenceRange.h"
#include "OSCLib/Data/SDC/MDIB/ImagingProcedure.h"
#include "OSCLib/Data/SDC/MDIB/LocationReference.h"
#include "OSCLib/Data/SDC/MDIB/OrderDetail.h"
#include "OSCLib/Data/SDC/MDIB/PersonParticipation.h"
#include "OSCLib/Data/SDC/MDIB/WorkflowContextState.h"
#include "OSCLib/Data/SDC/MDIB/WorkflowDetail.h"
#include "OSCLib/Data/SDC/MDIB/RequestedOrderDetail.h"
#include "OSCLib/Data/SDC/MDIB/PerformedOrderDetail.h"
#include "OSCLib/Data/SDC/MDIB/OperatorContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/OperatorContextState.h"
#include "OSCLib/Data/SDC/MDIB/MeansContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MeansContextState.h"
#include "OSCLib/Data/SDC/MDIB/EnsembleContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/EnsembleContextState.h"
#include "OSCLib/Data/SDC/MDIB/ContainmentTree.h"
#include "OSCLib/Data/SDC/MDIB/ContainmentTreeEntry.h"
#include "OSCLib/Data/SDC/MDIB/DicomTransferCapability.h"
#include "OSCLib/Data/SDC/MDIB/DicomNetworkAe.h"
#include "OSCLib/Data/SDC/MDIB/DicomNetworkConnection.h"
#include "OSCLib/Data/SDC/MDIB/DicomDeviceDescriptor.h"


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

#include "OSCLib/Data/SDC/MDIB/Defaults.h"
#include "Poco/UUIDGenerator.h"
#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/SDC/MDIB/ConvertToCDM.h"

#include "osdm.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

const std::string NOT_ASSIGNED("Invalid. Not assigned!");

Defaults::Defaults() {

}

Defaults::~Defaults() {

}


CDM::Mdib  * Defaults::MdibInit() {
	// todo: real sequence id. maybe as a setting?
	return new CDM::Mdib(xml_schema::Uri("uri:surgitaixplaceholder:123456789"));
}

CDM::MdDescription  * Defaults::MdDescriptionInit() {
	return new CDM::MdDescription();
}

CDM::MdState  * Defaults::MdStateInit() {
	return new CDM::MdState();
}

CDM::LocalizedText  * Defaults::LocalizedTextInit() {
	return new CDM::LocalizedText();
}

CDM::CodedValue  * Defaults::CodedValueInit(CodeIdentifier code) {
	return new CDM::CodedValue(ConvertToCDM::convert(code));
}

CDM::Translation  * Defaults::TranslationInit(CodeIdentifier code) {
	return new CDM::Translation(ConvertToCDM::convert(code));
}

CDM::InstanceIdentifier  * Defaults::InstanceIdentifierInit() {
	return new CDM::InstanceIdentifier();
}

CDM::Range  * Defaults::RangeInit() {
	return new CDM::Range();
}

CDM::Measurement  * Defaults::MeasurementInit(CodedValue measurementunit, double measuredvalue) {
	return new CDM::Measurement(ConvertToCDM::convert(measurementunit), ConvertToCDM::convert(measuredvalue));
}

CDM::ApprovedJurisdictions  * Defaults::ApprovedJurisdictionsInit() {
	return new CDM::ApprovedJurisdictions();
}

CDM::OperatingJurisdiction  * Defaults::OperatingJurisdictionInit() {
	return new CDM::OperatingJurisdiction();
}

CDM::PhysicalConnectorInfo  * Defaults::PhysicalConnectorInfoInit() {
	return new CDM::PhysicalConnectorInfo();
}

CDM::ProductionSpecification  * Defaults::ProductionSpecificationInit(CodedValue spectype, std::string productionspec) {
	return new CDM::ProductionSpecification(ConvertToCDM::convert(spectype), ConvertToCDM::convert(productionspec));
}

CDM::CalibrationInfo  * Defaults::CalibrationInfoInit() {
	return new CDM::CalibrationInfo();
}

CDM::CalibrationDocumentation  * Defaults::CalibrationDocumentationInit() {
	return new CDM::CalibrationDocumentation();
}

CDM::CalibrationResult  * Defaults::CalibrationResultInit(CodedValue code, Measurement value) {
	return new CDM::CalibrationResult(ConvertToCDM::convert(code), ConvertToCDM::convert(value));
}

CDM::MdsDescriptor  * Defaults::MdsDescriptorInit(Handle handle) {
	return new CDM::MdsDescriptor(ConvertToCDM::convert(handle));
}

CDM::MetaData  * Defaults::MetaDataInit() {
	return new CDM::MetaData();
}

CDM::Udi  * Defaults::UdiInit(std::string deviceidentifier, std::string humanreadableform, InstanceIdentifier issuer) {
	return new CDM::Udi(ConvertToCDM::convert(deviceidentifier), ConvertToCDM::convert(humanreadableform), ConvertToCDM::convert(issuer));
}

CDM::MdsState  * Defaults::MdsStateInit(HandleRef descriptorhandle) {
	return new CDM::MdsState(ConvertToCDM::convert(descriptorhandle));
}

CDM::VmdDescriptor  * Defaults::VmdDescriptorInit(Handle handle) {
	return new CDM::VmdDescriptor(ConvertToCDM::convert(handle));
}

CDM::VmdState  * Defaults::VmdStateInit(HandleRef descriptorhandle) {
	return new CDM::VmdState(ConvertToCDM::convert(descriptorhandle));
}

CDM::ChannelDescriptor  * Defaults::ChannelDescriptorInit(Handle handle) {
	return new CDM::ChannelDescriptor(ConvertToCDM::convert(handle));
}

CDM::ChannelState  * Defaults::ChannelStateInit(HandleRef descriptorhandle) {
	return new CDM::ChannelState(ConvertToCDM::convert(descriptorhandle));
}

CDM::SystemSignalActivation  * Defaults::SystemSignalActivationInit(AlertSignalManifestation manifestation, AlertActivation state) {
	return new CDM::SystemSignalActivation(ConvertToCDM::convert(manifestation), ConvertToCDM::convert(state));
}

CDM::AlertSystemDescriptor  * Defaults::AlertSystemDescriptorInit(Handle handle) {
	return new CDM::AlertSystemDescriptor(ConvertToCDM::convert(handle));
}

CDM::AlertSystemState  * Defaults::AlertSystemStateInit(HandleRef descriptorhandle, AlertActivation activationstate) {
	return new CDM::AlertSystemState(ConvertToCDM::convert(descriptorhandle), ConvertToCDM::convert(activationstate));
}

CDM::CauseInfo  * Defaults::CauseInfoInit() {
	return new CDM::CauseInfo();
}

CDM::RemedyInfo  * Defaults::RemedyInfoInit() {
	return new CDM::RemedyInfo();
}

CDM::AlertConditionDescriptor  * Defaults::AlertConditionDescriptorInit(Handle handle, AlertConditionKind kind, AlertConditionPriority priority) {
	return new CDM::AlertConditionDescriptor(ConvertToCDM::convert(handle), ConvertToCDM::convert(kind), ConvertToCDM::convert(priority));
}

CDM::AlertConditionState  * Defaults::AlertConditionStateInit(HandleRef descriptorhandle, AlertActivation activationstate) {
	return new CDM::AlertConditionState(ConvertToCDM::convert(descriptorhandle), ConvertToCDM::convert(activationstate));
}

CDM::LimitAlertConditionDescriptor  * Defaults::LimitAlertConditionDescriptorInit(Handle handle, AlertConditionKind kind, AlertConditionPriority priority, Range maxlimits) {
	return new CDM::LimitAlertConditionDescriptor(ConvertToCDM::convert(handle), ConvertToCDM::convert(kind), ConvertToCDM::convert(priority), ConvertToCDM::convert(maxlimits));
}

CDM::LimitAlertConditionState  * Defaults::LimitAlertConditionStateInit(HandleRef descriptorhandle, AlertActivation activationstate, Range limits, AlertConditionMonitoredLimits monitoredalertlimits) {
	return new CDM::LimitAlertConditionState(ConvertToCDM::convert(descriptorhandle), ConvertToCDM::convert(activationstate), ConvertToCDM::convert(limits), ConvertToCDM::convert(monitoredalertlimits));
}

CDM::AlertSignalDescriptor  * Defaults::AlertSignalDescriptorInit(Handle handle, AlertSignalManifestation manifestation, bool latching) {
	return new CDM::AlertSignalDescriptor(ConvertToCDM::convert(handle), ConvertToCDM::convert(manifestation), ConvertToCDM::convert(latching));
}

CDM::AlertSignalState  * Defaults::AlertSignalStateInit(HandleRef descriptorhandle, AlertActivation activationstate) {
	return new CDM::AlertSignalState(ConvertToCDM::convert(descriptorhandle), ConvertToCDM::convert(activationstate));
}

CDM::MetricQuality  * Defaults::MetricQualityInit(MeasurementValidity validity) {
	return new CDM::MetricQuality(ConvertToCDM::convert(validity));
}

CDM::Annotation  * Defaults::AnnotationInit(CodedValue type) {
	return new CDM::Annotation(ConvertToCDM::convert(type));
}

CDM::NumericMetricValue  * Defaults::NumericMetricValueInit(MetricQuality metricquality) {
	return new CDM::NumericMetricValue(ConvertToCDM::convert(metricquality));
}

CDM::StringMetricValue  * Defaults::StringMetricValueInit(MetricQuality metricquality) {
	return new CDM::StringMetricValue(ConvertToCDM::convert(metricquality));
}

CDM::SampleArrayValue  * Defaults::SampleArrayValueInit(MetricQuality metricquality) {
	return new CDM::SampleArrayValue(ConvertToCDM::convert(metricquality));
}

CDM::ApplyAnnotation  * Defaults::ApplyAnnotationInit(unsigned int annotationindex, unsigned int sampleindex) {
	return new CDM::ApplyAnnotation(ConvertToCDM::convert(annotationindex), ConvertToCDM::convert(sampleindex));
}

CDM::Relation  * Defaults::RelationInit(Kind kind, EntryRef entries) {
	auto asdf = CDM::EntryRef();
//	return new CDM::Relation(ConvertToCDM::convert(kind), ConvertToCDM::convert(entries));
	return new CDM::Relation(ConvertToCDM::convert(kind), asdf);
}

CDM::NumericMetricDescriptor  * Defaults::NumericMetricDescriptorInit(Handle handle, CodedValue unit, MetricCategory metriccategory, MetricAvailability metricavailability, double resolution) {
	return new CDM::NumericMetricDescriptor(ConvertToCDM::convert(handle), ConvertToCDM::convert(unit), ConvertToCDM::convert(metriccategory), ConvertToCDM::convert(metricavailability), ConvertToCDM::convert(resolution));
}

CDM::NumericMetricState  * Defaults::NumericMetricStateInit(HandleRef descriptorhandle) {
	return new CDM::NumericMetricState(ConvertToCDM::convert(descriptorhandle));
}

CDM::StringMetricDescriptor  * Defaults::StringMetricDescriptorInit(Handle handle, CodedValue unit, MetricCategory metriccategory, MetricAvailability metricavailability) {
	return new CDM::StringMetricDescriptor(ConvertToCDM::convert(handle), ConvertToCDM::convert(unit), ConvertToCDM::convert(metriccategory), ConvertToCDM::convert(metricavailability));
}

CDM::StringMetricState  * Defaults::StringMetricStateInit(HandleRef descriptorhandle) {
	return new CDM::StringMetricState(ConvertToCDM::convert(descriptorhandle));
}

CDM::EnumStringMetricDescriptor  * Defaults::EnumStringMetricDescriptorInit(Handle handle, CodedValue unit, MetricCategory metriccategory, MetricAvailability metricavailability) {
	return new CDM::EnumStringMetricDescriptor(ConvertToCDM::convert(handle), ConvertToCDM::convert(unit), ConvertToCDM::convert(metriccategory), ConvertToCDM::convert(metricavailability));
}

CDM::AllowedValue  * Defaults::AllowedValueInit(std::string value) {
	return new CDM::AllowedValue(ConvertToCDM::convert(value));
}

CDM::EnumStringMetricState  * Defaults::EnumStringMetricStateInit(HandleRef descriptorhandle) {
	return new CDM::EnumStringMetricState(ConvertToCDM::convert(descriptorhandle));
}

CDM::RealTimeSampleArrayMetricDescriptor  * Defaults::RealTimeSampleArrayMetricDescriptorInit(Handle handle, CodedValue unit, MetricCategory metriccategory, MetricAvailability metricavailability, double resolution, xml_schema::Duration sampleperiod) {
	return new CDM::RealTimeSampleArrayMetricDescriptor(ConvertToCDM::convert(handle), ConvertToCDM::convert(unit), ConvertToCDM::convert(metriccategory), ConvertToCDM::convert(metricavailability), ConvertToCDM::convert(resolution), ConvertToCDM::convert(sampleperiod));
}

CDM::RealTimeSampleArrayMetricState  * Defaults::RealTimeSampleArrayMetricStateInit(HandleRef descriptorhandle) {
	return new CDM::RealTimeSampleArrayMetricState(ConvertToCDM::convert(descriptorhandle));
}

CDM::DistributionSampleArrayMetricDescriptor  * Defaults::DistributionSampleArrayMetricDescriptorInit(Handle handle, CodedValue unit, MetricCategory metriccategory, MetricAvailability metricavailability, CodedValue domainunit, Range distributionrange, double resolution) {
	return new CDM::DistributionSampleArrayMetricDescriptor(ConvertToCDM::convert(handle), ConvertToCDM::convert(unit), ConvertToCDM::convert(metriccategory), ConvertToCDM::convert(metricavailability), ConvertToCDM::convert(domainunit), ConvertToCDM::convert(distributionrange), ConvertToCDM::convert(resolution));
}

CDM::DistributionSampleArrayMetricState  * Defaults::DistributionSampleArrayMetricStateInit(HandleRef descriptorhandle) {
	return new CDM::DistributionSampleArrayMetricState(ConvertToCDM::convert(descriptorhandle));
}

CDM::ScoDescriptor  * Defaults::ScoDescriptorInit(Handle handle) {
	return new CDM::ScoDescriptor(ConvertToCDM::convert(handle));
}

CDM::ScoState  * Defaults::ScoStateInit(HandleRef descriptorhandle) {
	return new CDM::ScoState(ConvertToCDM::convert(descriptorhandle));
}

CDM::OperationGroup  * Defaults::OperationGroupInit(CodedValue type) {
	return new CDM::OperationGroup(ConvertToCDM::convert(type));
}

CDM::SetValueOperationDescriptor  * Defaults::SetValueOperationDescriptorInit(Handle handle, HandleRef operationtarget) {
	return new CDM::SetValueOperationDescriptor(ConvertToCDM::convert(handle), ConvertToCDM::convert(operationtarget));
}

CDM::SetValueOperationState  * Defaults::SetValueOperationStateInit(HandleRef descriptorhandle, OperatingMode operatingmode) {
	return new CDM::SetValueOperationState(ConvertToCDM::convert(descriptorhandle), ConvertToCDM::convert(operatingmode));
}

CDM::SetStringOperationDescriptor  * Defaults::SetStringOperationDescriptorInit(Handle handle, HandleRef operationtarget) {
	return new CDM::SetStringOperationDescriptor(ConvertToCDM::convert(handle), ConvertToCDM::convert(operationtarget));
}

CDM::SetStringOperationState  * Defaults::SetStringOperationStateInit(HandleRef descriptorhandle, OperatingMode operatingmode) {
	return new CDM::SetStringOperationState(ConvertToCDM::convert(descriptorhandle), ConvertToCDM::convert(operatingmode));
}

CDM::AllowedValues  * Defaults::AllowedValuesInit() {
	return new CDM::AllowedValues();
}

CDM::ActivateOperationDescriptor  * Defaults::ActivateOperationDescriptorInit(Handle handle, HandleRef operationtarget) {
	return new CDM::ActivateOperationDescriptor(ConvertToCDM::convert(handle), ConvertToCDM::convert(operationtarget));
}

CDM::Argument  * Defaults::ArgumentInit(CodedValue argname, xml_schema::Qname arg) {
	return new CDM::Argument(ConvertToCDM::convert(argname), ConvertToCDM::convert(arg));
}

CDM::ActivateOperationState  * Defaults::ActivateOperationStateInit(HandleRef descriptorhandle, OperatingMode operatingmode) {
	return new CDM::ActivateOperationState(ConvertToCDM::convert(descriptorhandle), ConvertToCDM::convert(operatingmode));
}

CDM::SetContextStateOperationDescriptor  * Defaults::SetContextStateOperationDescriptorInit(Handle handle, HandleRef operationtarget) {
	return new CDM::SetContextStateOperationDescriptor(ConvertToCDM::convert(handle), ConvertToCDM::convert(operationtarget));
}

CDM::SetContextStateOperationState  * Defaults::SetContextStateOperationStateInit(HandleRef descriptorhandle, OperatingMode operatingmode) {
	return new CDM::SetContextStateOperationState(ConvertToCDM::convert(descriptorhandle), ConvertToCDM::convert(operatingmode));
}

CDM::SetMetricStateOperationDescriptor  * Defaults::SetMetricStateOperationDescriptorInit(Handle handle, HandleRef operationtarget) {
	return new CDM::SetMetricStateOperationDescriptor(ConvertToCDM::convert(handle), ConvertToCDM::convert(operationtarget));
}

CDM::SetMetricStateOperationState  * Defaults::SetMetricStateOperationStateInit(HandleRef descriptorhandle, OperatingMode operatingmode) {
	return new CDM::SetMetricStateOperationState(ConvertToCDM::convert(descriptorhandle), ConvertToCDM::convert(operatingmode));
}

CDM::SetComponentStateOperationDescriptor  * Defaults::SetComponentStateOperationDescriptorInit(Handle handle, HandleRef operationtarget) {
	return new CDM::SetComponentStateOperationDescriptor(ConvertToCDM::convert(handle), ConvertToCDM::convert(operationtarget));
}

CDM::SetComponentStateOperationState  * Defaults::SetComponentStateOperationStateInit(HandleRef descriptorhandle, OperatingMode operatingmode) {
	return new CDM::SetComponentStateOperationState(ConvertToCDM::convert(descriptorhandle), ConvertToCDM::convert(operatingmode));
}

CDM::SetAlertStateOperationDescriptor  * Defaults::SetAlertStateOperationDescriptorInit(Handle handle, HandleRef operationtarget) {
	return new CDM::SetAlertStateOperationDescriptor(ConvertToCDM::convert(handle), ConvertToCDM::convert(operationtarget));
}

CDM::SetAlertStateOperationState  * Defaults::SetAlertStateOperationStateInit(HandleRef descriptorhandle, OperatingMode operatingmode) {
	return new CDM::SetAlertStateOperationState(ConvertToCDM::convert(descriptorhandle), ConvertToCDM::convert(operatingmode));
}

CDM::ClockDescriptor  * Defaults::ClockDescriptorInit(Handle handle) {
	return new CDM::ClockDescriptor(ConvertToCDM::convert(handle));
}

CDM::ClockState  * Defaults::ClockStateInit(HandleRef descriptorhandle, bool remotesync) {
	return new CDM::ClockState(ConvertToCDM::convert(descriptorhandle), ConvertToCDM::convert(remotesync));
}

CDM::BatteryDescriptor  * Defaults::BatteryDescriptorInit(Handle handle) {
	return new CDM::BatteryDescriptor(ConvertToCDM::convert(handle));
}

CDM::BatteryState  * Defaults::BatteryStateInit(HandleRef descriptorhandle) {
	return new CDM::BatteryState(ConvertToCDM::convert(descriptorhandle));
}

CDM::SystemContextDescriptor  * Defaults::SystemContextDescriptorInit(Handle handle) {
	return new CDM::SystemContextDescriptor(ConvertToCDM::convert(handle));
}

CDM::SystemContextState  * Defaults::SystemContextStateInit(HandleRef descriptorhandle) {
	return new CDM::SystemContextState(ConvertToCDM::convert(descriptorhandle));
}

CDM::BaseDemographics  * Defaults::BaseDemographicsInit() {
	return new CDM::BaseDemographics();
}

CDM::PersonReference  * Defaults::PersonReferenceInit() {
	return new CDM::PersonReference();
}

CDM::LocationDetail  * Defaults::LocationDetailInit() {
	return new CDM::LocationDetail();
}

CDM::PatientContextDescriptor  * Defaults::PatientContextDescriptorInit(Handle handle) {
	return new CDM::PatientContextDescriptor(ConvertToCDM::convert(handle));
}

CDM::PatientDemographicsCoreData  * Defaults::PatientDemographicsCoreDataInit() {
	return new CDM::PatientDemographicsCoreData();
}

CDM::NeonatalPatientDemographicsCoreData  * Defaults::NeonatalPatientDemographicsCoreDataInit() {
	return new CDM::NeonatalPatientDemographicsCoreData();
}

CDM::PatientContextState  * Defaults::PatientContextStateInit(HandleRef descriptorhandle, Handle handle) {
	return new CDM::PatientContextState(ConvertToCDM::convert(descriptorhandle), ConvertToCDM::convert(handle));
}

CDM::LocationContextDescriptor  * Defaults::LocationContextDescriptorInit(Handle handle) {
	return new CDM::LocationContextDescriptor(ConvertToCDM::convert(handle));
}

CDM::LocationContextState  * Defaults::LocationContextStateInit(HandleRef descriptorhandle, Handle handle) {
	return new CDM::LocationContextState(ConvertToCDM::convert(descriptorhandle), ConvertToCDM::convert(handle));
}

CDM::WorkflowContextDescriptor  * Defaults::WorkflowContextDescriptorInit(Handle handle) {
	return new CDM::WorkflowContextDescriptor(ConvertToCDM::convert(handle));
}

CDM::ClinicalInfo  * Defaults::ClinicalInfoInit() {
	return new CDM::ClinicalInfo();
}

CDM::RelatedMeasurement  * Defaults::RelatedMeasurementInit(Measurement value) {
	return new CDM::RelatedMeasurement(ConvertToCDM::convert(value));
}

CDM::ReferenceRange  * Defaults::ReferenceRangeInit(Range range) {
	return new CDM::ReferenceRange(ConvertToCDM::convert(range));
}

CDM::ImagingProcedure  * Defaults::ImagingProcedureInit(InstanceIdentifier accessionidentifier, InstanceIdentifier requestedprocedureid, InstanceIdentifier studyinstanceuid, InstanceIdentifier scheduledprocedurestepid) {
	return new CDM::ImagingProcedure(ConvertToCDM::convert(accessionidentifier), ConvertToCDM::convert(requestedprocedureid), ConvertToCDM::convert(studyinstanceuid), ConvertToCDM::convert(scheduledprocedurestepid));
}

CDM::LocationReference  * Defaults::LocationReferenceInit() {
	return new CDM::LocationReference();
}

CDM::OrderDetail  * Defaults::OrderDetailInit() {
	return new CDM::OrderDetail();
}

CDM::PersonParticipation  * Defaults::PersonParticipationInit() {
	return new CDM::PersonParticipation();
}

CDM::WorkflowContextState  * Defaults::WorkflowContextStateInit(HandleRef descriptorhandle, Handle handle) {
	return new CDM::WorkflowContextState(ConvertToCDM::convert(descriptorhandle), ConvertToCDM::convert(handle));
}

CDM::WorkflowDetail  * Defaults::WorkflowDetailInit(PersonReference patient) {
	return new CDM::WorkflowDetail(ConvertToCDM::convert(patient));
}

CDM::RequestedOrderDetail  * Defaults::RequestedOrderDetailInit(InstanceIdentifier placerordernumber) {
	return new CDM::RequestedOrderDetail(ConvertToCDM::convert(placerordernumber));
}

CDM::PerformedOrderDetail  * Defaults::PerformedOrderDetailInit() {
	return new CDM::PerformedOrderDetail();
}

CDM::OperatorContextDescriptor  * Defaults::OperatorContextDescriptorInit(Handle handle) {
	return new CDM::OperatorContextDescriptor(ConvertToCDM::convert(handle));
}

CDM::OperatorContextState  * Defaults::OperatorContextStateInit(HandleRef descriptorhandle, Handle handle) {
	return new CDM::OperatorContextState(ConvertToCDM::convert(descriptorhandle), ConvertToCDM::convert(handle));
}

CDM::MeansContextDescriptor  * Defaults::MeansContextDescriptorInit(Handle handle) {
	return new CDM::MeansContextDescriptor(ConvertToCDM::convert(handle));
}

CDM::MeansContextState  * Defaults::MeansContextStateInit(HandleRef descriptorhandle, Handle handle) {
	return new CDM::MeansContextState(ConvertToCDM::convert(descriptorhandle), ConvertToCDM::convert(handle));
}

CDM::EnsembleContextDescriptor  * Defaults::EnsembleContextDescriptorInit(Handle handle) {
	return new CDM::EnsembleContextDescriptor(ConvertToCDM::convert(handle));
}

CDM::EnsembleContextState  * Defaults::EnsembleContextStateInit(HandleRef descriptorhandle, Handle handle) {
	return new CDM::EnsembleContextState(ConvertToCDM::convert(descriptorhandle), ConvertToCDM::convert(handle));
}

CDM::ContainmentTree  * Defaults::ContainmentTreeInit() {
	return new CDM::ContainmentTree();
}

CDM::ContainmentTreeEntry  * Defaults::ContainmentTreeEntryInit() {
	return new CDM::ContainmentTreeEntry();
}

CDM::DicomTransferCapability  * Defaults::DicomTransferCapabilityInit(std::string sopclass, DicomTransferRole transferrole) {
	return new CDM::DicomTransferCapability(ConvertToCDM::convert(sopclass), ConvertToCDM::convert(transferrole));
}

CDM::DicomNetworkAe  * Defaults::DicomNetworkAeInit(std::string aetitle, xml_schema::Idrefs networkconnectionreference, bool associationinitiator, bool associationacceptor) {
	return new CDM::DicomNetworkAe(ConvertToCDM::convert(aetitle), ConvertToCDM::convert(networkconnectionreference), ConvertToCDM::convert(associationinitiator), ConvertToCDM::convert(associationacceptor));
}

CDM::DicomNetworkConnection  * Defaults::DicomNetworkConnectionInit(xml_schema::Id id, std::string hostname) {
	return new CDM::DicomNetworkConnection(ConvertToCDM::convert(id), ConvertToCDM::convert(hostname));
}

CDM::DicomDeviceDescriptor  * Defaults::DicomDeviceDescriptorInit(Handle handle) {
	return new CDM::DicomDeviceDescriptor(ConvertToCDM::convert(handle));
}



} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
