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


enum class AlertConditionKind
{
	PHYSIOLOGICAL,
	TECHNICAL,
	OTHER
};

enum class AlertConditionPriority
{
	LOW,
	MEDIUM,
	HIGH,
	NONE
};

enum class AlertSignalManifestation
{
	AUDIBLE,
	VISIBLE,
	TANGIBLE
};

enum class CalibrationState {
	NOT_CALIBRATED,
	CALIBRATION_REQUIRED,
	CALIBRATED
};

enum class ComponentActivation
{
	OFF,
	ON,
	NOT_READY,
	STANDBY,
	SHUTDOWN
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

enum class MonitoredAlertLimits
{
	NONE,
	LOW_OFF,
	HIGH_OFF,
	ALL
};

enum class OperatingMode {
	DISABLED,
	ENABLED,
	NOT_AVAILABLE
};

enum class PatientType
{
	ADULT,
	NEONATAL,
	PEDIATRIC,
	UNSPECIFIED
};

enum class PausableActivation
{
	OFF,
	ON,
	PAUSED
};

enum class PrimaryAlertSignalLocation
{
	LOCAL,
	REMOTE
};

enum class Sex
{
	UNSPECIFIED,
	MALE,
	FEMALE,
	UNKNOWN
};

enum class SignalPresence
{
	On,
	Off,
	Latch,
	Ack
};

class EnumToString {
public:
	static std::string convert(AlertConditionKind source);
	static std::string convert(AlertConditionPriority source);
	static std::string convert(AlertSignalManifestation source);
	static std::string convert(CalibrationState source);
	static std::string convert(ComponentActivation source);
	static std::string convert(ContextAssociation source);
	static std::string convert(DicomTransferRole source);
	static std::string convert(GenerationMode source);
	static std::string convert(InvocationState source);
	static std::string convert(MetricAvailability source);
	static std::string convert(MetricCategory source);
	static std::string convert(MeasurementValidity source);
	static std::string convert(MetricRetrievability source);
	static std::string convert(MonitoredAlertLimits source);
	static std::string convert(OperatingMode source);
	static std::string convert(PatientType source);
	static std::string convert(PausableActivation source);
	static std::string convert(PrimaryAlertSignalLocation source);
	static std::string convert(Sex source);
	static std::string convert(SignalPresence source);
};

}
}
}

#endif /* ENUMMAPPINGS_H_ */
