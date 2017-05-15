/*
 * MDIB-fwd.h
 *
 *  Created on: 10.02.2015
 *      Author: roehser
 */

#ifndef OSCLIB_DATA_OSCP_MDIB_MDIB_FWD_H_
#define OSCLIB_DATA_OSCP_MDIB_MDIB_FWD_H_

namespace OSCLib {
namespace Data {
namespace OSCP {
	// classes, that are implemented manually
	class MDIBContainer;
	class OperationInvocationContext;

	// classes, that are generated
	class Annotation;
	class ActivateOperationDescriptor;
	class AlertConditionDescriptor;
	class AlertConditionReference;
	class AlertConditionState;
	class AlertSignalDescriptor;
	class AlertSignalState;
	class AlertSystemDescriptor;
	class AlertSystemState;
	class AllowedValue;
	class Base64Binary;
	class BaseDemographics;
	class CauseInfo;
	class CalibrationInfo;
	class ChannelDescriptor;
	class ClinicalInfo;
	class ClockDescriptor;
	class ClockState;
	class CodedValue;
	class ComponentState;
	class DateTime;
	class DicomDeviceDescriptor;
	class DicomNetworkAe;
	class DicomNetworkConnection;
	class DicomTransferCapability;
	class Duration;
	class EnsembleContextDescriptor;
	class EnsembleContextState;
	class EnumStringMetricDescriptor;
	class EnumStringMetricState;
	class InstanceIdentifier;
	class MdsDescriptor;
	class HydraMDSState;
	class ImagingProcedure;
	class Language;
	class LimitAlertConditionDescriptor;
	class LimitAlertConditionState;
	class LocalizedText;
	class LocationContextDescriptor;
	class LocationContextState;
	class MDDescription;
	class MDState;
	class Measure;
	class MeasurementState;
	class NumericMetricDescriptor;
	class NumericMetricState;
	class NumericMetricValue;
	class OperationState;
	class OperatorContextDescriptor;
	class OperatorContextState;
	class Order;
	class OrderDetail;
	class PatientContextDescriptor;
	class PatientContextState;
	class PatientDemographicsCoreData;
	class PersonParticipation;
	class PersonReference;
	class ProductionSpecification;
	class SampleIndex;
	class Range;
	class RealTimeSampleArrayMetricDescriptor;
	class RealTimeSampleArrayMetricState;
	class RealTimeSampleArrayValue;
	class RemedyInfo;
	class ReferencedVersion;
	class RTValueType;
	class SCODescriptor;
	class SetAlertStateOperationDescriptor;
	class SetContextOperationDescriptor;
	class SetRangeOperationDescriptor;
	class SetStringOperationDescriptor;
	class SetValueOperationDescriptor;
	class StringMetricDescriptor;
	class StringMetricState;
	class StringMetricValue;
	class SystemContext;
	class SystemMetaData;
	class Timestamp;
	class TimeZone;
	class VersionCounter;
	class VMDDescriptor;
	class WorkflowContextDescriptor;
	class WorkflowContextState;
}
}
}

#endif /* OSCLIB_DATA_OSCP_MDIB_MDIB_FWD_H_ */
