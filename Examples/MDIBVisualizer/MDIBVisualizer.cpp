
#include "SDCLib/SDCLibrary.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Util/DebugOut.h"
#include "OSELib/Helper/WithLogger.h"

#include "OSELib/SDC/ServiceManager.h"

#include "DataModel/osdm.hxx"

#include <chrono>

#include <fstream>
#include <sstream>

#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "OSELib/Helper/XercesParserWrapper.h"
#include "OSELib/SDC/DefaultSDCSchemaGrammarProvider.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

std::string stripCharacters(const std::string & input, const std::string & removeChars) {
	std::string str(input);
    str.erase(
        std::remove_if(str.begin(), str.end(), [&](char c){
            return removeChars.find(c) != std::string::npos;
        }),
        str.end()
    );
    return str;
}



template<class Type>
std::string typeAsString(const Type & ) {
	return "Type not yet supported by Visualizer";
}


//
// Metrices
//
template<>
std::string typeAsString(const CDM::NumericMetricDescriptor & ) {
	return "NumericMetricDescriptor";
}

template<>
std::string typeAsString(const CDM::NumericMetricState & ) {
	return "NumericMetricState";
}



template<>
std::string typeAsString(const CDM::StringMetricDescriptor & ) {
	return "StringMetricDescriptor";
}

template<>
std::string typeAsString(const CDM::StringMetricState & ) {
	return "StringMetricState";
}



template<>
std::string typeAsString(const CDM::RealTimeSampleArrayMetricDescriptor & ) {
	return "RealTimeSampleArrayMetricDescriptor";
}

template<>
std::string typeAsString(const CDM::RealTimeSampleArrayMetricState & ) {
	return "RealTimeSampleArrayMetricState";
}



template<>
std::string typeAsString(const CDM::EnumStringMetricDescriptor & ) {
	return "EnumStringMetricDescriptor";
}

template<>
std::string typeAsString(const CDM::EnumStringMetricState & ) {
	return "EnumStringMetricState";
}



template<>
std::string typeAsString(const CDM::DistributionSampleArrayMetricDescriptor & ) {
	return "DistributionSampleArrayMetricDescriptor";
}

template<>
std::string typeAsString(const CDM::DistributionSampleArrayMetricState & ) {
	return "DistributionSampleArrayMetricState";
}



//
// Contexts
//
template<>
std::string typeAsString(const CDM::OperatorContextDescriptor & ) {
	return "OperatorContextDescriptor";
}

template<>
std::string typeAsString(const CDM::OperatorContextState & ) {
	return "OperatorContextState";
}



template<>
std::string typeAsString(const CDM::MeansContextDescriptor & ) {
	return "MeansContextDescriptor";
}

template<>
std::string typeAsString(const CDM::MeansContextState & ) {
	return "MeansContextState";
}



template<>
std::string typeAsString(const CDM::WorkflowContextDescriptor & ) {
	return "WorkflowContextDescriptor";
}

template<>
std::string typeAsString(const CDM::WorkflowContextState & ) {
	return "WorkflowContextState";
}



template<>
std::string typeAsString(const CDM::SystemContextDescriptor & ) {
	return "SystemContextDescriptor";
}

template<>
std::string typeAsString(const CDM::SystemContextState & ) {
	return "SystemContextState";
}


template<>
std::string typeAsString(const CDM::PatientContextDescriptor & ) {
	return "PatientContextDescriptor";
}

template<>
std::string typeAsString(const CDM::PatientContextState & ) {
	return "PatientContextState";
}



template<>
std::string typeAsString(const CDM::LocationContextDescriptor & ) {
	return "LocationContextDescriptor";
}

template<>
std::string typeAsString(const CDM::LocationContextState & ) {
	return "LocationContextState";
}



template<>
std::string typeAsString(const CDM::EnsembleContextDescriptor & ) {
	return "EnsembleContextDescriptor";
}

template<>
std::string typeAsString(const CDM::EnsembleContextState & ) {
	return "EnsembleContextState";
}




//
// Operations
//
template<>
std::string typeAsString(const CDM::SetContextStateOperationDescriptor & ) {
	return "SetContextStateOperationDescriptor";
}

template<>
std::string typeAsString(const CDM::SetContextStateOperationState & ) {
	return "SetContextStateOperationState";
}




template<>
std::string typeAsString(const CDM::SetAlertStateOperationDescriptor & ) {
	return "SetAlertStateOperationDescriptor";
}

template<>
std::string typeAsString(const CDM::SetAlertStateOperationState & ) {
	return "SetAlertStateOperationState";
}



template<>
std::string typeAsString(const CDM::ActivateOperationDescriptor & ) {
	return "ActivateOperationDescriptor";
}

template<>
std::string typeAsString(const CDM::ActivateOperationState & ) {
	return "ActivateOperationState";
}



template<>
std::string typeAsString(const CDM::SetStringOperationDescriptor & ) {
	return "SetStringOperationDescriptor";
}

template<>
std::string typeAsString(const CDM::SetStringOperationState & ) {
	return "SetStringOperationState";
}



template<>
std::string typeAsString(const CDM::SetValueOperationDescriptor & ) {
	return "SetValueOperationDescriptor";
}

template<>
std::string typeAsString(const CDM::SetValueOperationState & ) {
	return "SetValueOperationState";
}



template<>
std::string typeAsString(const CDM::SetComponentStateOperationDescriptor & ) {
	return "SetComponentStateOperationDescriptor";
}

template<>
std::string typeAsString(const CDM::SetComponentStateOperationState & ) {
	return "SetComponentStateOperationDescriptor";
}



template<>
std::string typeAsString(const CDM::SetMetricStateOperationDescriptor & ) {
	return "SetMetricStateOperationDescriptor";
}

template<>
std::string typeAsString(const CDM::SetMetricStateOperationState & ) {
	return "SetMetricStateOperationState";
}


//
// Componentes
//
template<>
std::string typeAsString(const CDM::ChannelDescriptor & ) {
	return "ChannelDescriptor";
}

template<>
std::string typeAsString(const CDM::ChannelState & ) {
	return "ChannelState";
}



template<>
std::string typeAsString(const CDM::ClockDescriptor & ) {
	return "ClockDescriptor";
}

template<>
std::string typeAsString(const CDM::ClockState & ) {
	return "ClockState";
}



template<>
std::string typeAsString(const CDM::BatteryDescriptor & ) {
	return "BatteryDescriptor";
}

template<>
std::string typeAsString(const CDM::BatteryState& ) {
	return "BatteryState";
}




//
// 	ComplexDeviceComponents
//
template<>
std::string typeAsString(const CDM::MdsDescriptor & ) {
	return "MdsDescriptor";
}

template<>
std::string typeAsString(const CDM::MdsState & ) {
	return "MdsState";
}



template<>
std::string typeAsString(const CDM::VmdDescriptor & ) {
	return "VmdDescriptor";
}

template<>
std::string typeAsString(const CDM::VmdState & ) {
	return "VmdState";
}



//
// Alerts
//
template<>
std::string typeAsString(const CDM::AlertConditionDescriptor & ) {
	return "AlertConditionDescriptor";
}

template<>
std::string typeAsString(const CDM::AlertConditionState & ) {
	return "AlertConditionState";
}



template<>
std::string typeAsString(const CDM::AlertSignalDescriptor & ) {
	return "AlertSignalDescriptor";
}

template<>
std::string typeAsString(const CDM::AlertSignalState & ) {
	return "AlertSignalState";
}



template<>
std::string typeAsString(const CDM::AlertSystemDescriptor & ) {
	return "AlertSystemDescriptor";
}

template<>
std::string typeAsString(const CDM::AlertSystemState & ) {
	return "AlertSystemState";
}



template<>
std::string typeAsString(const CDM::LimitAlertConditionDescriptor & ) {
	return "LimitAlertConditionDescriptor";
}

template<>
std::string typeAsString(const CDM::LimitAlertConditionState & ) {
	return "LimitAlertConditionState";
}



//
// other
//
template<>
std::string typeAsString(const CDM::ScoDescriptor & ) {
	return "ScoDescriptor";
}

template<>
std::string typeAsString(const CDM::ScoState & ) {
	return "ScoState";
}





// kick
//
//std::string makeDescription(const CDM::AbstractMetricDescriptor & object) {
//	return makeDefaultDescriptorDescription(object);
//}
//
//std::string makeDescription(const CDM::AbstractOperationDescriptor & object) {
//	return makeDefaultDescriptorDescription(object);
//}
//
//std::string makeDescription(const CDM::AbstractState & object) {
//	std::ostringstream result;
//	result << typeAsString(object) << std::endl;
//	return result.str();
//}



template<class Type>
std::string makeDefaultDescriptorDescription(const Type & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	result << "Handle: " << object.getHandle() << std::endl;
	if (object.getType().present()) {
		result << "Type: " << object.getType().get().getCode() << std::endl;
	}
	return result.str();
}

template<class Type>
std::string makeDefaultStateDescription(const Type & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}



//
// Metrices
//
std::string makeDescription(const CDM::NumericMetricDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::NumericMetricState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	result << "MetricValue:" << (object.getMetricValue().present() ? "Yes" : "No") << std::endl;
	if (object.getMetricValue().present()) {
		result << "MetricValue.getValue:";
		if (object.getMetricValue().get().getValue().present()) {
			result << object.getMetricValue().get().getValue().get() << std::endl;
		} else {
			result << "No" << std::endl;
		}
	}
	return result.str();
}



std::string makeDescription(const CDM::StringMetricDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::StringMetricState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	result << "MetricValue:" << (object.getMetricValue().present() ? "Yes" : "No") << std::endl;
	if (object.getMetricValue().present()) {
		result << "MetricValue.getValue:";
		if (object.getMetricValue().get().getValue().present()) {
			result << object.getMetricValue().get().getValue().get() << std::endl;
		} else {
			result << "---" << std::endl;
		}
	}
	return result.str();
}



std::string makeDescription(const CDM::RealTimeSampleArrayMetricDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::RealTimeSampleArrayMetricState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}



std::string makeDescription(const CDM::EnumStringMetricDescriptor & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	result << "Handle:" << object.getHandle() << std::endl;
	result << "AllowedValues:" << std::endl;
	for (const auto & allowedValue : object.getAllowedValue()) {
		result << allowedValue.getValue() << std::endl;
	}
	return result.str();
}


std::string makeDescription(const CDM::EnumStringMetricState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	result << "MetricValue:" << (object.getMetricValue().present() ? "Yes" : "No") << std::endl;
	if (object.getMetricValue().present()) {
		result << "MetricValue.getValue:";
		if (object.getMetricValue().get().getValue().present()) {
			result << object.getMetricValue().get().getValue().get() << std::endl;
		} else {
			result << "---" << std::endl;
		}
	}
	return result.str();
}


std::string makeDescription(const CDM::DistributionSampleArrayMetricDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::DistributionSampleArrayMetricState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}




//
// Contexts
//
std::string makeDescription(const CDM::EnsembleContextDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::EnsembleContextState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}




std::string makeDescription(const CDM::LocationContextDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::LocationContextState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}




std::string makeDescription(const CDM::OperatorContextDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::OperatorContextState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}



std::string makeDescription(const CDM::PatientContextDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::PatientContextState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}



std::string makeDescription(const CDM::WorkflowContextDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::WorkflowContextState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}



std::string makeDescription(const CDM::SystemContextDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::SystemContextState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}



std::string makeDescription(const CDM::MeansContextDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::MeansContextState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}



//
// Operations
//
std::string makeDescription(const CDM::ActivateOperationDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::ActivateOperationState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}



std::string makeDescription(const CDM::SetAlertStateOperationDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::SetAlertStateOperationState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}



std::string makeDescription(const CDM::SetContextStateOperationDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::SetContextStateOperationState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}



std::string makeDescription(const CDM::SetStringOperationDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::SetStringOperationState& object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}



std::string makeDescription(const CDM::SetValueOperationDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::SetValueOperationState& object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}



std::string makeDescription(const CDM::SetMetricStateOperationDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::SetMetricStateOperationState& object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}



std::string makeDescription(const CDM::SetComponentStateOperationDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::SetComponentStateOperationState& object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}


//
// Components
//
std::string makeDescription(const CDM::ChannelDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::ChannelState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}



std::string makeDescription(const CDM::ClockDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::ClockState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}



std::string makeDescription(const CDM::BatteryDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::BatteryState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}




//
// ComplexDeviceComponentes
//
std::string makeDescription(const CDM::VmdDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::VmdState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}



std::string makeDescription(const CDM::MdsDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::MdsState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}



//
// Alerts
//
std::string makeDescription(const CDM::AlertConditionDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::AlertConditionState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}

std::string makeDescription(const CDM::AlertSignalDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::AlertSignalState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}

std::string makeDescription(const CDM::AlertSystemDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}


std::string makeDescription(const CDM::AlertSystemState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}


std::string makeDescription(const CDM::LimitAlertConditionDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}


std::string makeDescription(const CDM::LimitAlertConditionState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}



//
// other
//
std::string makeDescription(const CDM::ScoDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::ScoState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}




const std::string alertColor("tomato");
const std::string contextColor("gold");
const std::string metricColor("aliceblue");
const std::string structureColor("darkolivegreen1");

template<class Type>
std::string makeAlertFormat(const Type &, unsigned int id) {
	std::ostringstream result;
	result << "n" << id << "[style=\"filled,solid\"; fillcolor=\"" << alertColor <<"\"];" << std::endl;
	return result.str();
}

template<class Type>
std::string makeContextFormat(const Type &, unsigned int id) {
	std::ostringstream result;
		result << "n" << id << "[style=\"filled,solid\"; fillcolor=\"" << contextColor <<"\"];" << std::endl;
		return result.str();
}

template<class Type>
std::string makeMetricFormat(const Type &, unsigned int id) {
	std::ostringstream result;
	result << "n" << id << "[style=\"filled,solid\"; fillcolor=\"" << metricColor <<"\"];" << std::endl;
	return result.str();
}

template<class Type>
std::string makeStructureFormat(const Type &, unsigned int id) {
	std::ostringstream result;
		result << "n" << id << "[style=\"filled,solid\"; fillcolor=\"" << structureColor <<"\"];" << std::endl;
		return result.str();
}

//
// Metrices
//
std::string makeFormat(const CDM::StringMetricDescriptor & object, unsigned int id) {
	return makeMetricFormat(object, id);
}

std::string makeFormat(const CDM::StringMetricState & object, unsigned int id) {
	return makeMetricFormat(object, id);
}


std::string makeFormat(const CDM::NumericMetricDescriptor & object, unsigned int id) {
	return makeMetricFormat(object, id);
}

std::string makeFormat(const CDM::NumericMetricState & object, unsigned int id) {
	return makeMetricFormat(object, id);
}


std::string makeFormat(const CDM::EnumStringMetricDescriptor & object, unsigned int id) {
	return makeMetricFormat(object, id);
}

std::string makeFormat(const CDM::EnumStringMetricState & object, unsigned int id) {
	return makeMetricFormat(object, id);
}


std::string makeFormat(const CDM::RealTimeSampleArrayMetricDescriptor & object, unsigned int id) {
	return makeMetricFormat(object, id);
}

std::string makeFormat(const CDM::RealTimeSampleArrayMetricState & object, unsigned int id) {
	return makeMetricFormat(object, id);
}



std::string makeFormat(const CDM::DistributionSampleArrayMetricDescriptor & object, unsigned int id) {
	return makeMetricFormat(object, id);
}

std::string makeFormat(const CDM::DistributionSampleArrayMetricState & object, unsigned int id) {
	return makeMetricFormat(object, id);
}


//
// Contexts
//
std::string makeFormat(const CDM::EnsembleContextDescriptor & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::EnsembleContextState & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::LocationContextDescriptor & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::LocationContextState & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::WorkflowContextDescriptor & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::WorkflowContextState & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::OperatorContextDescriptor & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::OperatorContextState & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::PatientContextDescriptor & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::PatientContextState & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::SystemContextDescriptor & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::SystemContextState & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::MeansContextDescriptor & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::MeansContextState & object, unsigned int id) {
	return makeContextFormat(object, id);
}




//
// Operations
//
std::string makeFormat(const CDM::SetStringOperationState & object, unsigned int id) {
	return makeMetricFormat(object, id);
}

std::string makeFormat(const CDM::SetContextStateOperationState & object, unsigned int id) {
	return makeMetricFormat(object, id);
}

std::string makeFormat(const CDM::SetAlertStateOperationState & object, unsigned int id) {
	return makeMetricFormat(object, id);
}

std::string makeFormat(const CDM::ActivateOperationState & object, unsigned int id) {
	return makeMetricFormat(object, id);
}

std::string makeFormat(const CDM::SetComponentStateOperationState & object, unsigned int id) {
	return makeMetricFormat(object, id);
}

std::string makeFormat(const CDM::SetMetricStateOperationState & object, unsigned int id) {
	return makeMetricFormat(object, id);
}

std::string makeFormat(const CDM::SetValueOperationState & object, unsigned int id) {
	return makeMetricFormat(object, id);
}




//
// Components
//
std::string makeFormat(const CDM::ChannelDescriptor & object, unsigned int id) {
	return makeStructureFormat(object, id);
}

std::string makeFormat(const CDM::ChannelState & object, unsigned int id) {
	return makeStructureFormat(object, id);
}

std::string makeFormat(const CDM::ClockDescriptor & object, unsigned int id) {
	return makeStructureFormat(object, id);
}

std::string makeFormat(const CDM::ClockState & object, unsigned int id) {
	return makeStructureFormat(object, id);
}

std::string makeFormat(const CDM::BatteryDescriptor & object, unsigned int id) {
	return makeStructureFormat(object, id);
}

std::string makeFormat(const CDM::BatteryState & object, unsigned int id) {
	return makeStructureFormat(object, id);
}


//
// ComplexDeviceComponents
//
std::string makeFormat(const CDM::MdsDescriptor & object, unsigned int id) {
	return makeStructureFormat(object, id);
}

std::string makeFormat(const CDM::MdsState& object, unsigned int id) {
	return makeStructureFormat(object, id);
}



std::string makeFormat(const CDM::VmdDescriptor & object, unsigned int id) {
	return makeStructureFormat(object, id);
}

std::string makeFormat(const CDM::VmdState & object, unsigned int id) {
	return makeStructureFormat(object, id);
}



//
// Alerts
//
std::string makeFormat(const CDM::AlertConditionDescriptor & object, unsigned int id) {
	return makeAlertFormat(object, id);
}

std::string makeFormat(const CDM::AlertConditionState & object, unsigned int id) {
	return makeAlertFormat(object, id);
}

std::string makeFormat(const CDM::AlertSignalDescriptor & object, unsigned int id) {
	return makeAlertFormat(object, id);
}

std::string makeFormat(const CDM::AlertSignalState & object, unsigned int id) {
	return makeAlertFormat(object, id);
}

std::string makeFormat(const CDM::AlertSystemDescriptor & object, unsigned int id) {
	return makeAlertFormat(object, id);
}

std::string makeFormat(const CDM::AlertSystemState & object, unsigned int id) {
	return makeAlertFormat(object, id);
}


std::string makeFormat(const CDM::LimitAlertConditionState & object, unsigned int id) {
	return makeAlertFormat(object, id);
}

std::string makeFormat(const CDM::LimitAlertConditionDescriptor & object, unsigned int id) {
	return makeAlertFormat(object, id);
}




//
// Other
//







std::string buildDotGraph(CDM::Mdib& mdib) {

	std::ostringstream result;
	result << "digraph G {" << std::endl;
	result << "rankdir=\"LR\"" << std::endl;

	unsigned int lastNode = 0;

	std::map<std::string, unsigned int> handleToNodeMap;
	std::map<unsigned int, std::string> nodeToDescriptionMap;
	std::vector<unsigned int> metricStateNodes;


	//
	// Alerts handling
	//
	auto processAlertSystemDescriptor = [&](const CDM::AlertSystemDescriptor & system, const std::string & ownerHandle) {
		handleToNodeMap[system.getHandle()] = ++lastNode;
		result << "n" << handleToNodeMap[ownerHandle] << " -> n" << handleToNodeMap[system.getHandle()] << "[];" << std::endl;
		result << makeFormat(system, handleToNodeMap[system.getHandle()]);
		nodeToDescriptionMap[handleToNodeMap[system.getHandle()]] = makeDescription(system);
		for (const auto & condition : system.getAlertCondition()) {
			handleToNodeMap[condition.getHandle()] = ++lastNode;
			result << "n" << handleToNodeMap[system.getHandle()] << " -> n" << handleToNodeMap[condition.getHandle()] << "[weight=100;];" << std::endl;
			if (auto casted = dynamic_cast<const CDM::LimitAlertConditionDescriptor *>(&condition)) {
				nodeToDescriptionMap[handleToNodeMap[condition.getHandle()]] = makeDescription(*casted);
				result << makeFormat(*casted, handleToNodeMap[casted->getHandle()]);
			} else {
				nodeToDescriptionMap[handleToNodeMap[condition.getHandle()]] = makeDescription(condition);
				result << makeFormat(condition, handleToNodeMap[condition.getHandle()]);
			}
		}
		for (const auto & signal : system.getAlertSignal()) {
			handleToNodeMap[signal.getHandle()] = ++lastNode;
			result << "n" << handleToNodeMap[system.getHandle()] << " -> n" << handleToNodeMap[signal.getHandle()] << "[weight=100;];" << std::endl;
			nodeToDescriptionMap[handleToNodeMap[signal.getHandle()]] = makeDescription(signal);
			result << makeFormat(signal, handleToNodeMap[signal.getHandle()]);
		}
	};

	// walk through mdib
	if (mdib.getMdDescription().present()) {
		const CDM::MdDescription & mddescription(mdib.getMdDescription().get());
		for (const auto & mds : mddescription.getMds()) {
			//if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			handleToNodeMap[mds.getHandle()] = ++lastNode;
			nodeToDescriptionMap[handleToNodeMap[mds.getHandle()]] = makeDescription(mds);
			result << makeFormat(mds, handleToNodeMap[mds.getHandle()]);

			if (mds.getAlertSystem().present()) {
				processAlertSystemDescriptor(mds.getAlertSystem().get(), mds.getHandle());
			}

			if (mds.getSco().present()) {
				const CDM::ScoDescriptor & sco(mds.getSco().get());
				handleToNodeMap[sco.getHandle()] = ++lastNode;
				result << "n" << handleToNodeMap[mds.getHandle()] << " -> n" << handleToNodeMap[sco.getHandle()] << "[];" << std::endl;
				nodeToDescriptionMap[handleToNodeMap[sco.getHandle()]] = makeDescription(sco);
				for (const auto & operation : sco.getOperation()) {
					handleToNodeMap[operation.getHandle()] = ++lastNode;
					result << "n" << handleToNodeMap[sco.getHandle()] << " -> n" << handleToNodeMap[operation.getHandle()] << "[weight=10000;];" << std::endl;

					if (const auto t_desc_String = dynamic_cast<const CDM::SetStringOperationDescriptor *>(std::addressof(operation)))
					{
						nodeToDescriptionMap[handleToNodeMap[operation.getHandle()]] = makeDescription(*t_desc_String);
					}
					else if (const auto t_desc_Value = dynamic_cast<const CDM::SetValueOperationDescriptor *>(std::addressof(operation)))
					{
						nodeToDescriptionMap[handleToNodeMap[operation.getHandle()]] = makeDescription(*t_desc_Value);
					}
					else if (const auto t_desc_Context = dynamic_cast<const CDM::SetContextStateOperationDescriptor*>(std::addressof(operation)))
					{
						nodeToDescriptionMap[handleToNodeMap[operation.getHandle()]] = makeDescription(*t_desc_Context);
					}
					else if (const auto t_desc_Alert = dynamic_cast<const CDM::SetAlertStateOperationDescriptor *>(std::addressof(operation)))
					{
						nodeToDescriptionMap[handleToNodeMap[operation.getHandle()]] = makeDescription(*t_desc_Alert);
					}
					else if (const auto t_desc_Activate = dynamic_cast<const CDM::ActivateOperationDescriptor *>(&operation))
					{
						nodeToDescriptionMap[handleToNodeMap[operation.getHandle()]] = makeDescription(*t_desc_Activate);
					}
					else if (const auto t_desc_Component = dynamic_cast<const CDM::SetComponentStateOperationDescriptor *>(std::addressof(operation)))
					{
						nodeToDescriptionMap[handleToNodeMap[operation.getHandle()]] = makeDescription(*t_desc_Component);
					}
					else if (const auto t_desc_Metric = dynamic_cast<const CDM::SetMetricStateOperationDescriptor *>(std::addressof(operation)))
					{
						nodeToDescriptionMap[handleToNodeMap[operation.getHandle()]] = makeDescription(*t_desc_Metric);
					}
				}
			}

			if (mds.getSystemContext().present())
			{
				const CDM::SystemContextDescriptor & systemContext(mds.getSystemContext().get());
				handleToNodeMap[systemContext.getHandle()] = ++lastNode;
				result << "n" << handleToNodeMap[mds.getHandle()] << " -> n" << handleToNodeMap[systemContext.getHandle()] << "[];" << std::endl;
				result << makeFormat(systemContext, handleToNodeMap[systemContext.getHandle()]);
				nodeToDescriptionMap[handleToNodeMap[systemContext.getHandle()]] = makeDescription(systemContext);

				// todo: find a good way to draw multiple EnsembleContexts and OperatorContexts
//				if (systemContext.EnsembleContext().present()) {
//					const CDM::EnsembleContextDescriptor & context(systemContext.EnsembleContext().get());
//					handleToNodeMap[context.getHandle()] = ++lastNode;
//					result << "n" << handleToNodeMap[systemContext.getHandle()] << " -> n" << handleToNodeMap[context.getHandle()] << "[weight=100;];" << std::endl;
//					result << makeFormat(context, handleToNodeMap[context.getHandle()]);
//					nodeToDescriptionMap[handleToNodeMap[context.getHandle()]] = makeDescription(context);
//				}
				if (systemContext.getLocationContext().present()) {
					const CDM::LocationContextDescriptor & context(systemContext.getLocationContext().get());
					handleToNodeMap[context.getHandle()] = ++lastNode;
					result << "n" << handleToNodeMap[systemContext.getHandle()] << " -> n" << handleToNodeMap[context.getHandle()] << "[weight=100;];" << std::endl;
					result << makeFormat(context, handleToNodeMap[context.getHandle()]);
					nodeToDescriptionMap[handleToNodeMap[context.getHandle()]] = makeDescription(context);
				}
//				if (systemContext.OperatorContext().present()) {
//					const CDM::OperatorContextDescriptor & context(systemContext.OperatorContext().get());
//					handleToNodeMap[context.getHandle()] = ++lastNode;
//					result << "n" << handleToNodeMap[systemContext.getHandle()] << " -> n" << handleToNodeMap[context.getHandle()] << "[weight=100;];" << std::endl;
//					result << makeFormat(context, handleToNodeMap[context.getHandle()]);
//					nodeToDescriptionMap[handleToNodeMap[context.getHandle()]] = makeDescription(context);
//				}
				if (systemContext.getPatientContext().present()) {
					const CDM::PatientContextDescriptor & context(systemContext.getPatientContext().get());
					handleToNodeMap[context.getHandle()] = ++lastNode;
					result << "n" << handleToNodeMap[systemContext.getHandle()] << " -> n" << handleToNodeMap[context.getHandle()] << "[weight=100;];" << std::endl;
					result << makeFormat(context, handleToNodeMap[context.getHandle()]);
					nodeToDescriptionMap[handleToNodeMap[context.getHandle()]] = makeDescription(context);
				}
//				if (systemContext.WorkflowContext().present()) {
//					const CDM::WorkflowContextDescriptor & context(systemContext.WorkflowContext().get());
//					handleToNodeMap[context.getHandle()] = ++lastNode;
//					result << "n" << handleToNodeMap[systemContext.getHandle()] << " -> n" << handleToNodeMap[context.getHandle()] << "[weight=100;];" << std::endl;
//					result << makeFormat(context, handleToNodeMap[context.getHandle()]);
//					nodeToDescriptionMap[handleToNodeMap[context.getHandle()]] = makeDescription(context);
//				}
			}


			for (const auto & vmdDescriptor : mds.getVmd()) {
				handleToNodeMap[vmdDescriptor.getHandle()] = ++lastNode;
				result << "n" << handleToNodeMap[mds.getHandle()] << " -> n" << handleToNodeMap[vmdDescriptor.getHandle()] << "[];" << std::endl;
				nodeToDescriptionMap[handleToNodeMap[vmdDescriptor.getHandle()]] = makeDescription(vmdDescriptor);
				result << "n" << handleToNodeMap[vmdDescriptor.getHandle()] << "[style=\"filled,solid\"; fillcolor=\"" << structureColor <<"\"];" << std::endl;
				result << makeFormat(vmdDescriptor, handleToNodeMap[vmdDescriptor.getHandle()]);

				if (vmdDescriptor.getAlertSystem().present()) {
					processAlertSystemDescriptor(vmdDescriptor.getAlertSystem().get(), vmdDescriptor.getHandle());
				}

				for (const auto & channelDescriptor : vmdDescriptor.getChannel()) {
					handleToNodeMap[channelDescriptor.getHandle()] = ++lastNode;
					result << "n" << handleToNodeMap[vmdDescriptor.getHandle()] << " -> n" << handleToNodeMap[channelDescriptor.getHandle()] << "[];" << std::endl;
					nodeToDescriptionMap[handleToNodeMap[channelDescriptor.getHandle()]] = makeDescription(channelDescriptor);
					result << makeFormat(channelDescriptor, handleToNodeMap[channelDescriptor.getHandle()]);


					for (const auto & metricDescriptor : channelDescriptor.getMetric()) {
						handleToNodeMap[metricDescriptor.getHandle()] = ++lastNode;
						result << "n" << handleToNodeMap[channelDescriptor.getHandle()] << " -> n" << handleToNodeMap[metricDescriptor.getHandle()] << "[weight=100;];" << std::endl;

						if (const auto t_desc_numeric = dynamic_cast<const CDM::NumericMetricDescriptor *>(&metricDescriptor))
						{
							nodeToDescriptionMap[handleToNodeMap[metricDescriptor.getHandle()]] = makeDescription(*t_desc_numeric);
							result << makeFormat(*t_desc_numeric, handleToNodeMap[t_desc_numeric->getHandle()]);
						}
						else if (const auto t_desc_enumString = dynamic_cast<const CDM::EnumStringMetricDescriptor *>(&metricDescriptor))
						{
							nodeToDescriptionMap[handleToNodeMap[metricDescriptor.getHandle()]] = makeDescription(*t_desc_enumString);
							result << makeFormat(*t_desc_enumString, handleToNodeMap[t_desc_enumString->getHandle()]);
						}
						else if (const auto t_desc_string = dynamic_cast<const CDM::StringMetricDescriptor *>(&metricDescriptor))
						{
							nodeToDescriptionMap[handleToNodeMap[metricDescriptor.getHandle()]] = makeDescription(*t_desc_string);
							result << makeFormat(*t_desc_string, handleToNodeMap[t_desc_string->getHandle()]);
						}
						else if (const auto t_desc_rtsa = dynamic_cast<const CDM::RealTimeSampleArrayMetricDescriptor *>(&metricDescriptor))
						{
							nodeToDescriptionMap[handleToNodeMap[metricDescriptor.getHandle()]] = makeDescription(*t_desc_rtsa);
							result << makeFormat(*t_desc_rtsa, handleToNodeMap[t_desc_rtsa->getHandle()]);
						}
						else if (const auto t_desc_dsam = dynamic_cast<const CDM::DistributionSampleArrayMetricDescriptor *>(&metricDescriptor))
						{
							nodeToDescriptionMap[handleToNodeMap[metricDescriptor.getHandle()]] = makeDescription(*t_desc_dsam);
							result << makeFormat(*t_desc_dsam, handleToNodeMap[t_desc_dsam->getHandle()]);
						}
					}
				}
			}
		}

		// second pass for operation targets
		for (const auto & mds : mddescription.getMds())
		{
			if (mds.getSco().present())
			{
				for (const auto & operation : mds.getSco().get().getOperation())
				{
					if (handleToNodeMap.find(operation.getOperationTarget()) != handleToNodeMap.end()) {
						result << "n" << handleToNodeMap[operation.getOperationTarget()] << "[shape=octagon];" << std::endl;
					} else {
						result << "n" << handleToNodeMap[operation.getHandle()] << " -> unassigned;" << std::endl;
					}
				}
			}
		}

		// states
		if (mdib.getMdState().present()) {
			for (const auto & state : mdib.getMdState().get().getState()) {
				unsigned int currentNode = ++lastNode;

				// connect to descriptor
				if (handleToNodeMap.find(state.getDescriptorHandle()) != handleToNodeMap.end()) {
					result << "n" << handleToNodeMap[state.getDescriptorHandle()] << " -> n" << currentNode << " [dir=back,style=dashed];" << std::endl;
				} else {
					result << "n" << currentNode << " -> unassigned;" << std::endl;
				}

				if (const auto& t_state_limitAlertCondition = dynamic_cast<const CDM::LimitAlertConditionState *>(&state))
				{
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_limitAlertCondition);
					result << makeFormat(*t_state_limitAlertCondition, currentNode);
				}
				else if (const auto& t_state_alertCondition = dynamic_cast<const CDM::AlertConditionState *>(&state))
				{
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_alertCondition);
					result << makeFormat(*t_state_alertCondition, currentNode);
				}
				else if (const auto& t_state_alertSignal = dynamic_cast<const CDM::AlertSignalState*>(&state))
				{
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_alertSignal);
					result << makeFormat(*t_state_alertSignal, currentNode);
				}
				else if (const auto& t_state_alertSystem = dynamic_cast<const CDM::AlertSystemState *>(&state))
				{
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_alertSystem);
					result << makeFormat(*t_state_alertSystem, currentNode);
					// force alert system states next to alert system
					if (handleToNodeMap.find(state.getDescriptorHandle()) != handleToNodeMap.end()) {
						result << " { rank = same; " ;
						result << "n" << handleToNodeMap[state.getDescriptorHandle()] << "; n" << currentNode << ";";
						result << "} " << std::endl ;
					}
				}
				else if (const auto& t_state_ensembleContext = dynamic_cast<const CDM::EnsembleContextState *>(std::addressof(state)))
				{
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_ensembleContext);
					result << makeFormat(*t_state_ensembleContext, currentNode);
				}
				else if (const auto& t_state_locationContext = dynamic_cast<const CDM::LocationContextState *>(std::addressof(state)))
				{
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_locationContext);
					result << makeFormat(*t_state_locationContext, currentNode);
				}
				else if (const auto& t_state_operatorContext = dynamic_cast<const CDM::OperatorContextState *>(std::addressof(state)))
				{
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_operatorContext);
					result << makeFormat(*t_state_operatorContext, currentNode);
				}
				else if (const auto& t_state_patientContext = dynamic_cast<const CDM::PatientContextState *>(std::addressof(state)))
				{
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_patientContext);
					result << makeFormat(*t_state_patientContext, currentNode);
				}
				else if (const auto& t_state_workflowContext = dynamic_cast<const CDM::WorkflowContextState *>(std::addressof(state)))
				{
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_workflowContext);
					result << makeFormat(*t_state_workflowContext, currentNode);
				}
				else if (const auto& t_state_numericMetricState = dynamic_cast<const CDM::NumericMetricState *>(std::addressof(state)))
				{
					metricStateNodes.push_back(currentNode);
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_numericMetricState);
					result << makeFormat(*t_state_numericMetricState, currentNode);
				}
				else if (const auto& t_state_rtsa = dynamic_cast<const CDM::RealTimeSampleArrayMetricState *>(std::addressof(state)))
				{
					metricStateNodes.push_back(currentNode);
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_rtsa);
					result << makeFormat(*t_state_rtsa, currentNode);
				}
				else if (const auto& t_state_stringMetricState = dynamic_cast<const CDM::StringMetricState *>(std::addressof(state)))
				{
					metricStateNodes.push_back(currentNode);
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_stringMetricState);
					result << makeFormat(*t_state_stringMetricState, currentNode);
				}
				else if (const auto& t_state_dsam = dynamic_cast<const CDM::DistributionSampleArrayMetricState *>(std::addressof(state)))
				{
					metricStateNodes.push_back(currentNode);
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_dsam);
					result << makeFormat(*t_state_dsam, currentNode);
				}
				else if (const auto& t_state_setValueOperation = dynamic_cast<const CDM::SetValueOperationState *>(std::addressof(state)))
				{
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_setValueOperation);
					result << makeFormat(*t_state_setValueOperation, currentNode);
				}
				else if (const auto& t_state_setStringOperation = dynamic_cast<const CDM::SetStringOperationState *>(std::addressof(state)))
				{
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_setStringOperation);
					result << makeFormat(*t_state_setStringOperation, currentNode);
				}
				else if (const auto& t_state_setContextStateOperation = dynamic_cast<const CDM::SetContextStateOperationState *>(std::addressof(state)))
				{
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_setContextStateOperation);
					result << makeFormat(*t_state_setContextStateOperation, currentNode);
				}
				else if (auto t_state_setAlertStateOperation = dynamic_cast<const CDM::SetAlertStateOperationState *>(std::addressof(state)))
				{
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_setAlertStateOperation);
					result << makeFormat(*t_state_setAlertStateOperation, currentNode);
				}
				else if (const auto& t_state_activateOperation = dynamic_cast<const CDM::ActivateOperationState *>(std::addressof(state)))
				{
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_activateOperation);
					result << makeFormat(*t_state_activateOperation, currentNode);
				}
				else if (const auto& t_state_setComponentStateOperation = dynamic_cast<const CDM::SetComponentStateOperationState *>(std::addressof(state)))
				{
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_setComponentStateOperation);
					result << makeFormat(*t_state_setComponentStateOperation, currentNode);
				}
				else if (const auto& t_state_setMetricStateOperation = dynamic_cast<const CDM::SetMetricStateOperationState *>(std::addressof(state)))
				{
					nodeToDescriptionMap[currentNode] = makeDescription(*t_state_setMetricStateOperation);
					result << makeFormat(*t_state_setMetricStateOperation, currentNode);
				}
			}
		}


		for (const auto & element : nodeToDescriptionMap) {
			result << "n" << element.first << " [label=\"" << element.second <<"\"];" << std::endl;
		}

		{ // force metric states to bottom of graph
			result << " { rank = same; " ;
			for (const auto & node : metricStateNodes) {
				result << "n" << node << "; ";
			}
			result << "} " << std::endl ;
		}

		result << "}" << std::endl;
		return result.str();
	}
	//FIXME: Empty string is an error?
	return std::string();
}

int main() {
	DebugOut::DEBUG_LEVEL = DebugOut::Full;
	const std::string testname("Create graphvis/dot files of all MDIBs of all found devices");
	DebugOut(DebugOut::Default, "MDIBVisualizer") << std::endl << "Startup: " << testname;
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Debug);
	DebugOut(DebugOut::Default, "MDIBVisualizer") << std::endl << "Compile dotfiles with: " << "ls *.dot | xargs -I {} dot -Tpdf {} -o {}.pdf";

    // Create a new SDCInstance (no flag will auto init)
    auto t_SDCInstance = std::make_shared<SDCInstance>(true);

    // Some restriction
    t_SDCInstance->setIP6enabled(false);
    t_SDCInstance->setIP4enabled(true);
    // Bind it to interface that matches the internal criteria (usually the first enumerated)
    if(!t_SDCInstance->bindToDefaultNetworkInterface()) {
        DebugOut(DebugOut::Default, "ReferenceProviderSSL") << "Failed to bind to default network interface! Exit..." << std::endl;
        return -1;
    }

	OSELib::SDC::ServiceManager t_serviceManager(t_SDCInstance);


	//int loopcounter = 0;
	//while (true) {

		DebugOut(DebugOut::Default, "MDIBVisualizer") << "Refreshing ..." << std::flush;
		//const std::string deviceEPR("UDI-1234567890");
		//std::shared_ptr<SDCConsumer> consumer(t_serviceManager.discoverEndpointReference(deviceEPR));
		std::vector<std::unique_ptr<SDCLib::Data::SDC::SDCConsumer>> results(t_serviceManager.discover());

		DebugOut(DebugOut::Default, "MDIBVisualizer") << "Found devices with these EPRs: " << std::endl;

		for (auto & consumer : results) {
			const std::string epr(consumer->getEndpointReference());
			const std::string filename("mdib" + stripCharacters(epr, "./\\!?*") + ".dot");

			DebugOut(DebugOut::Default, "MDIBVisualizer") << "Found EPR " << epr << " and dumping to file " << filename << std::endl;

			try {
				std::ofstream outFile;
				outFile.open(filename, std::ios::trunc);

                std::chrono::time_point<std::chrono::system_clock> t_start = std::chrono::system_clock::now();

				OSELib::SDC::DefaultSDCSchemaGrammarProvider grammarProvider;
				auto rawMessage = OSELib::Helper::Message::create(consumer->requestRawMdib());
				auto xercesDocument = OSELib::Helper::XercesDocumentWrapper::create(*rawMessage, grammarProvider);

				std::unique_ptr<CDM::Mdib> mdib(CDM::parseMdibContainer(xercesDocument->getDocument()));

				if (mdib) {
					outFile << buildDotGraph(*mdib);
				}
                std::chrono::time_point<std::chrono::system_clock> t_end = std::chrono::system_clock::now();
                auto t_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
				DebugOut(DebugOut::Default, "MDIBVisualizer") << "   -> took " << t_ms << " ms." << std::endl;
				outFile.close();
			} catch (...) {
				DebugOut(DebugOut::Default, "MDIBVisualizer") << "Error writing file." << std::endl;
			}
		}

		for (auto & consumer : results) {
			consumer->disconnect();
			consumer.reset();
		}
		results.clear();
		DebugOut(DebugOut::Default, "MDIBVisualizer") << "Done." << std::endl << std::flush;

//		++loopcounter;
//	}

	DebugOut(DebugOut::Default, "MDIBVisualizer") << "Shutdown: " << testname << std::endl;
}

