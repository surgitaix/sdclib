/*
 * EnumMappings.h
 *
 *  Created on: 11.11.2014
 *      Author: roehser
 */

#ifndef ENUMMAPPINGS_H_
#define ENUMMAPPINGS_H_

#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

enum class AlertActivation
{
	Off,
	On,
	Paused
};


enum class AlertConditionKind
{
	PHYSIOLOGICAL,
	TECHNICAL,
	OTHER
};

enum class AlertConditionMonitoredLimits
{
	None,
	LoOff,
	HiOff,
	All
};


enum class AlertConditionPriority
{
	Low,
	Medium,
	High,
	None
};


enum class AlertSignalManifestation
{
	AUDIBLE,
	VISIBLE,
	TANGIBLE
};

enum class CalibrationState {
	NotCalibrated,
	CalibrationRequired,
	Calibrated
};

enum class CalibrationType {
	Offset,
	Gain,
	TwoPointCalibration,
	Unspecified
};

enum class ComponentActivation
{
	Off,
	On,
	NotReady,
	Standby,
	Shutdown,
	Fail
};

enum class ContextAssociation {
	NO_ASSOCIATION,
	PRE_ASSOCIATION,
	ASSOCIATED,
	DISASSOCIATED
};

enum class DicomTransferRole {
	Scu,
	Scp
};

enum class GenerationMode {
	Real,
	Test,
	Demo
};

enum class InvocationState
{
	FAILED,
	WAITING,
	STARTED,
	CANCELLED,
	CANCELLED_MANUALLY,
	FINISHED
};


enum class MdsOperatingMode
{
	Normal,
	Demo,
	Service,
	Maintenance
};

enum class MetricAvailability
{
	INTERMITTENT,
	CONTINUOUS
};

enum class MetricCategory
{
	UNSPECIFIED,
	MEASUREMENT,
	CALCULATION,
	SETTING,
	PRESETTING,
	RECOMMENDATION
};

enum class MeasurementValidity
{
	Valid,
	ValidatedData,
	Ongoing,
	Questionable,
	CalibrationOngoing,
	Invalid,
	Overflow,
	Underflow,
	NotAvailable
};

enum class MetricRetrievability
{
    GET,
    PERIODIC,
    EPISODIC,
    STREAM
};



enum class OperatingMode {
	Disabled,
	Enabled,
	NotAvailable
};

enum class PatientType
{
	ADULT,
	NEONATAL,
	PEDIATRIC,
	UNSPECIFIED
};

enum class AlertSignalPrimaryLocation
{
	Local,
	Remote
};

enum class SafetyClassification
{
	Inf,
	MedA,
	MedB,
	MedC
};


enum class Sex
{
	UNSPECIFIED,
	MALE,
	FEMALE,
	UNKNOWN
};

enum class AlertSignalPresence
{
	On,
	Off,
	Latched,
	Acknowledged
};

class EnumToString {
public:
	static std::string convert(AlertActivation source);
	static std::string convert(AlertConditionKind source);
	static std::string convert(AlertConditionPriority source);
	static std::string convert(AlertSignalManifestation source);
	static std::string convert(AlertSignalPresence source);
	static std::string convert(AlertSignalPrimaryLocation source);
	static std::string convert(CalibrationState source);
	static std::string convert(CalibrationType source);
	static std::string convert(ComponentActivation source);
	static std::string convert(ContextAssociation source);
	static std::string convert(DicomTransferRole source);
	static std::string convert(GenerationMode source);
	static std::string convert(InvocationState source);
	static std::string convert(MdsOperatingMode source);
	static std::string convert(MetricAvailability source);
	static std::string convert(MetricCategory source);
	static std::string convert(MeasurementValidity source);
	static std::string convert(MetricRetrievability source);
	static std::string convert(AlertConditionMonitoredLimits source);
	static std::string convert(OperatingMode source);
	static std::string convert(PatientType source);
	static std::string convert(SafetyClassification source);
	static std::string convert(Sex source);
};

}
}
}

#endif /* ENUMMAPPINGS_H_ */
