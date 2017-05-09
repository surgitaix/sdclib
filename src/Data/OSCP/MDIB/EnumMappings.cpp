/*
 * EnumMappings.cpp
 *
 *  Created on: 11.11.2014
 *      Author: roehser
 */

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "osdm.hxx"

#include <stdexcept>

namespace OSCLib {
namespace Data {
namespace OSCP {

std::string EnumToString::convert(AlertConditionKind source) {
	switch (source) {
		case AlertConditionKind::PHYSIOLOGICAL: return "Physiological";
		case AlertConditionKind::TECHNICAL: return "Technical";
		case AlertConditionKind::OTHER: return "Other";
	}
	throw std::runtime_error("Illegal value for AlertConditionKind");
}

std::string EnumToString::convert(AlertConditionPriority source) {
	switch (source) {
		case AlertConditionPriority::LOW: return "Low";
		case AlertConditionPriority::MEDIUM: return "Medium";
		case AlertConditionPriority::HIGH: return "High";
		case AlertConditionPriority::NONE: return "None";
	}
	throw std::runtime_error("Illegal value for AlertConditionPriority");
}

std::string EnumToString::convert(AlertSignalManifestation source) {
	switch (source) {
		case AlertSignalManifestation::AUDIBLE: return "Audible";
		case AlertSignalManifestation::VISIBLE: return "Visible";
		case AlertSignalManifestation::TANGIBLE: return "Tangible";
	}
	throw std::runtime_error("Illegal value for AlertSignalManifestation");
}

std::string EnumToString::convert(CalibrationState source) {
	switch (source) {
		case CalibrationState::Calibrated: return "Calibrated";
		case CalibrationState::CalibrationRequired: return "Calibration required";
		case CalibrationState::NotCalibrated: return "Not calibrated";
	}
	throw std::runtime_error("Illegal value for CalibrationState");
}

std::string EnumToString::convert(CalibrationType source) {
	switch (source) {
		case CalibrationType::Offset: return "Offset";
		case CalibrationType::Gain: return "Gain calibration";
		case CalibrationType::TwoPointCalibration: return "Two point calibration";
		case CalibrationType::Unspecified: return "Unspecified";
	}
	throw std::runtime_error("Illegal value for CalibrationType");
}

std::string EnumToString::convert(ComponentActivation source) {
	switch (source) {
		case ComponentActivation::Off: return "Off";
		case ComponentActivation::On: return "On";
		case ComponentActivation::NotReady: return "Not ready";
		case ComponentActivation::Standby: return "Standby";
		case ComponentActivation::Shutdown: return "Shutdown";
		case ComponentActivation::Fail: return "Fail";
	}
	throw std::runtime_error("Illegal value for ComponentActivation");
}

std::string EnumToString::convert(ContextAssociation source) {
	switch (source) {
		case ContextAssociation::ASSOCIATED: return "Associated";
		case ContextAssociation::DISASSOCIATED: return "Disassociated";
		case ContextAssociation::NO_ASSOCIATION: return "No association";
		case ContextAssociation::PRE_ASSOCIATION: return "Pre association";
	}
	throw std::runtime_error("Illegal value for ContextAssociation");
}

std::string EnumToString::convert(DicomTransferRole source) {
	switch (source) {
		case DicomTransferRole::Scu: return "Scu";
		case DicomTransferRole::Scp: return "Scp";
	}
	throw std::runtime_error("Illegal value for DICOMTransferRole");
}

std::string EnumToString::convert(GenerationMode source) {
	switch (source) {
		case GenerationMode::DEMO_DATA: return "Demo data";
		case GenerationMode::REAL_DATA: return "Real data";
		case GenerationMode::TEST_DATA: return "Test data";
	}
	throw std::runtime_error("Illegal value for GenerationMode");
}

std::string EnumToString::convert(InvocationState source) {
	switch (source) {
		case InvocationState::FAILED: return "Failed";
		case InvocationState::WAITING: return "Waiting";
		case InvocationState::STARTED: return "Started";
		case InvocationState::CANCELLED: return "Cancelled";
		case InvocationState::CANCELLED_MANUALLY: return "Cancelled_Manually";
		case InvocationState::FINISHED: return "Finished";
	}
	throw std::runtime_error("Illegal value for InvocationState");
}

std::string EnumToString::convert(MetricAvailability source) {
	switch (source) {
		case MetricAvailability::INTERMITTENT: return "Intermittent";
		case MetricAvailability::CONTINUOUS: return "Continuous";
	}
	throw std::runtime_error("Illegal value for MetricAvailability");
}

std::string EnumToString::convert(MetricCategory source) {
	switch (source) {
		case MetricCategory::UNSPECIFIED: return "Unspecified";
		case MetricCategory::MEASUREMENT: return "Measurement";
		case MetricCategory::CALCULATION: return "Calculation";
		case MetricCategory::SETTING: return "Setting";
		case MetricCategory::PRESETTING: return "Presetting";
		case MetricCategory::RECOMMENDATION: return "Recommendation";
	}
	throw std::runtime_error("Illegal value for MetricCategory");
}

std::string EnumToString::convert(MeasurementValidity source) {
	switch (source) {
		case MeasurementValidity::Valid: return "Valid";
		case MeasurementValidity::ValidatedData: return "Validated data";
		case MeasurementValidity::Ongoing: return "Ongoing";
		case MeasurementValidity::Questionable: return "Questionable";
		case MeasurementValidity::CalibrationOngoing: return "Calibration ongoing";
		case MeasurementValidity::Invalid: return "Invalid";
		case MeasurementValidity::Overflow: return "Overflow";
		case MeasurementValidity::Underflow: return "Underflow";
		case MeasurementValidity::NotAvailable: return "Not available";
	}
	throw std::runtime_error("Illegal value for MetricMeasurementValidity");
}

std::string EnumToString::convert(MetricRetrievability source) {
	switch (source) {
		case MetricRetrievability::GET: return "Get";
		case MetricRetrievability::PERIODIC: return "Periodic";
		case MetricRetrievability::EPISODIC: return "Episodic";
		case MetricRetrievability::STREAM: return "Stream";
	}
	throw std::runtime_error("Illegal value for MetricRetrievability");
}

std::string EnumToString::convert(AlertConditionMonitoredLimits source) {
	switch (source) {
		case AlertConditionMonitoredLimits::None: return "None";
		case AlertConditionMonitoredLimits::LoOff: return "Low off";
		case AlertConditionMonitoredLimits::HiOff: return "High off";
		case AlertConditionMonitoredLimits::All: return "All";
	}
	throw std::runtime_error("Illegal value for MonitoredAlertLimits");
}

std::string EnumToString::convert(OperatingMode source) {
	switch (source) {
		case OperatingMode::DISABLED: return "Disabled";
		case OperatingMode::ENABLED: return "Enabled";
		case OperatingMode::NOT_AVAILABLE: return "Not available";
	}
	throw std::runtime_error("Illegal value for OperatingMode");
}

std::string EnumToString::convert(PatientType source) {
	switch (source) {
		case PatientType::ADULT: return "Adult";
		case PatientType::PEDIATRIC: return "Pediatric";
		case PatientType::NEONATAL: return "Neonatal";
		case PatientType::UNSPECIFIED: return "Unspecified";
	}
	throw std::runtime_error("Illegal value for PatientType");
}

std::string EnumToString::convert(AlertActivation source) {
	switch (source) {
		case AlertActivation::Off: return "Off";
		case AlertActivation::On: return "On";
		case AlertActivation::Paused: return "Paused";
	}
	throw std::runtime_error("Illegal value for AlertActivation");
}

std::string EnumToString::convert(AlertSignalPrimaryLocation source) {
	switch (source) {
		case AlertSignalPrimaryLocation::Local: return "Local";
		case AlertSignalPrimaryLocation::Remote: return "Remote";
	}
	throw std::runtime_error("Illegal value for PrimaryAlertSignalLocation");
}

std::string EnumToString::convert(Sex source) {
	switch (source) {
		case Sex::UNSPECIFIED: return "Unspecified";
		case Sex::MALE: return "Male";
		case Sex::FEMALE: return "Female";
		case Sex::UNKNOWN: return "Unknown";
	}
	throw std::runtime_error("Illegal value for Sex");
}

std::string EnumToString::convert(AlertSignalPresence source) {
	switch (source) {
		case AlertSignalPresence::On: return "On";
		case AlertSignalPresence::Off: return "Off";
		case AlertSignalPresence::Acknowledged: return "Acknowledged";
		case AlertSignalPresence::Latched: return "Latched";
	}
	throw std::runtime_error("Illegal value for AlertSignalPresence");
}

}
}
}
