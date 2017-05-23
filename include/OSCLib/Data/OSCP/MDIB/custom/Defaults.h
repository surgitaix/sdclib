/*
 * Defaults.h
 *
 *  Created on: 27.04.2015
 *      Author: roehser
 */

#ifndef DATA_OSCP_MDIB_DEFAULTS_H_
#define DATA_OSCP_MDIB_DEFAULTS_H_

#include "OSCLib/Data/OSCP/MDIB/custom/MDIB-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

extern const std::string NOT_ASSIGNED;

class Defaults {
public:
	Defaults();
	virtual ~Defaults();

	static CDM::ActivateOperationDescriptor * ActivateOperationDescriptor();
	static CDM::AlertConditionDescriptor * AlertConditionDescriptor();
	static CDM::AlertConditionReference * AlertConditionReference();
	static CDM::AlertConditionState * AlertConditionState();
	static CDM::AlertSignalDescriptor * AlertSignalDescriptor();
	static CDM::AlertSignalState * AlertSignalState();
	static CDM::AlertSystemDescriptor * AlertSystemDescriptor();
	static CDM::AlertSystemState * AlertSystemState();
	static CDM::AllowedValue * AllowedValue();
	static CDM::Annotation * Annotation();
	static CDM::ApplyAnnotation * ApplyAnnotation();
	static CDM::Base64Binary * Base64Binary();
	static CDM::BaseDemographics * BaseDemographics();
	static CDM::BatteryDescriptor * BatteryDescriptor();
	static CDM::CauseInfo * CauseInfo();
	static CDM::CalibrationInfo * CalibrationInfo();
	static CDM::ChannelDescriptor * ChannelDescriptor();
	static CDM::ClinicalInfo * ClinicalInfo();
	static CDM::ClockDescriptor * ClockDescriptor();
	static CDM::ClockState * ClockState();
	static CDM::CodedValue * CodedValue();
	static CDM::DateTime * DateTime();
	static CDM::DicomNetworkAe * DicomNetworkAe();
	static CDM::DicomDeviceDescriptor * DicomDeviceDescriptor();
	static CDM::DicomNetworkConnection * DicomNetworkConnection();
	static CDM::DicomTransferCapability * DicomTransferCapability();
	static CDM::Duration * Duration();
	static CDM::EnsembleContextDescriptor * EnsembleContextDescriptor();
	static CDM::EnsembleContextState * EnsembleContextState();
	static CDM::EnumStringMetricDescriptor * EnumStringMetricDescriptor();
	static CDM::EnumStringMetricState * EnumStringMetricState();
	static CDM::MdsDescriptor * MdsDescriptor();
	static CDM::MdsState * MdsState();
	static CDM::ImagingProcedure * ImagingProcedure();
	static CDM::InstanceIdentifier * InstanceIdentifier();
	static CDM::Language * Language();
	static CDM::LimitAlertConditionDescriptor * LimitAlertConditionDescriptor();
	static CDM::LimitAlertConditionState * LimitAlertConditionState();
	static CDM::LocalizedText * LocalizedText();
	static CDM::LocationContextDescriptor * LocationContextDescriptor();
	static CDM::LocationContextState * LocationContextState();
	static CDM::Measurement * Measurement();
	static CDM::MdDescription * MdDescription();
	static CDM::MdState * MdState();
	static CDM::NumericMetricDescriptor * NumericMetricDescriptor();
	static CDM::NumericMetricState * NumericMetricState();
	static CDM::NumericMetricValue * NumericMetricValue();
	static CDM::AbstractOperationState * AbstractOperationState();
	static CDM::OperatorContextDescriptor * OperatorContextDescriptor();
	static CDM::OperatorContextState * OperatorContextState();
	static CDM::PatientContextDescriptor * PatientContextDescriptor();
	static CDM::PatientContextState * PatientContextState();
	static CDM::PatientDemographicsCoreData * PatientDemographicsCoreData();
	static CDM::PersonParticipation * PersonParticipation();
	static CDM::PersonReference * PersonReference();
	static CDM::ProductionSpecification * ProductionSpecification();
	static CDM::Range * Range();
	static CDM::RealTimeSampleArrayMetricDescriptor * RealTimeSampleArrayMetricDescriptor();
	static CDM::RealTimeSampleArrayMetricState * RealTimeSampleArrayMetricState();
	static CDM::SampleArrayValue * SampleArrayValue();
	static CDM::ReferencedVersion * ReferencedVersion();
	static CDM::RemedyInfo * RemedyInfo();
	static CDM::RealTimeValueType * RealTimeValueType();
	static CDM::ScoDescriptor * ScoDescriptor();
	static CDM::SetAlertStateOperationDescriptor * SetAlertStateOperationDescriptor();
	static CDM::SetContextStateOperationDescriptor * SetContextStateOperationDescriptor();
	static CDM::SetStringOperationDescriptor * SetStringOperationDescriptor();
	static CDM::SetValueOperationDescriptor * SetValueOperationDescriptor();
	static CDM::StringMetricDescriptor * StringMetricDescriptor();
	static CDM::StringMetricState * StringMetricState();
	static CDM::StringMetricValue * StringMetricValue();
	static CDM::SystemContextDescriptor * SystemContextDescriptor();
	static CDM::MetaData * MetaData();
	static CDM::Timestamp * Timestamp();
	static CDM::TimeZone * TimeZone();
	static CDM::VersionCounter * VersionCounter();
	static CDM::VmdDescriptor * VmdDescriptor();
	static CDM::WorkflowContextDescriptor * WorkflowContextDescriptor();
	static CDM::WorkflowContextState * WorkflowContextState();
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* DATA_OSCP_MDIB_DEFAULTS_H_ */
