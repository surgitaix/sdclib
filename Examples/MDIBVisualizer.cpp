
#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/OSCPConstants.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Util/DebugOut.h"

#include "OSELib/OSCP/ServiceManager.h"

#include "osdm.hxx"

#include "Poco/Thread.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"

#include <fstream>
#include <sstream>

#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "OSELib/Helper/XercesParserWrapper.h"
#include "OSELib/OSCP/DefaultOSCPSchemaGrammarProvider.h"

using namespace OSCLib;
using namespace OSCLib::Util;
using namespace OSCLib::Data::OSCP;

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

template<>
std::string typeAsString(const CDM::ActivateOperationDescriptor & ) {
	return "ActivateOperationDescriptor";
}

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
std::string typeAsString(const CDM::ChannelDescriptor & ) {
	return "ChannelDescriptor";
}

template<>
std::string typeAsString(const CDM::ClockState & ) {
	return "ClockState";
}

template<>
std::string typeAsString(const CDM::ComponentState & ) {
	return "ComponentState";
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
std::string typeAsString(const CDM::EnsembleContextDescriptor & ) {
	return "EnsembleContextDescriptor";
}

template<>
std::string typeAsString(const CDM::EnsembleContextState & ) {
	return "EnsembleContextState";
}

template<>
std::string typeAsString(const CDM::HydraMDSDescriptor & ) {
	return "HydraMDSDescriptor";
}

template<>
std::string typeAsString(const CDM::HydraMDSState & ) {
	return "HydraMDSState";
}

template<>
std::string typeAsString(const CDM::LimitAlertConditionDescriptor & ) {
	return "LimitAlertConditionDescriptor";
}

template<>
std::string typeAsString(const CDM::LimitAlertConditionState & ) {
	return "LimitAlertConditionState";
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
std::string typeAsString(const CDM::NumericMetricDescriptor & ) {
	return "NumericMetricDescriptor";
}

template<>
std::string typeAsString(const CDM::NumericMetricState & ) {
	return "NumericMetricState";
}

template<>
std::string typeAsString(const CDM::OperationState & ) {
	return "OperationState";
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
std::string typeAsString(const CDM::RealTimeSampleArrayMetricDescriptor & ) {
	return "RealTimeSampleArrayMetricDescriptor";
}

template<>
std::string typeAsString(const CDM::RealTimeSampleArrayMetricState & ) {
	return "RealTimeSampleArrayMetricState";
}

template<>
std::string typeAsString(const CDM::SCODescriptor & ) {
	return "SCODescriptor";
}

template<>
std::string typeAsString(const CDM::SetAlertStateOperationDescriptor & ) {
	return "SetAlertStateOperationDescriptor";
}

template<>
std::string typeAsString(const CDM::SetContextOperationDescriptor & ) {
	return "SetContextOperationDescriptor";
}

template<>
std::string typeAsString(const CDM::SetRangeOperationDescriptor & ) {
	return "SetRangeOperationDescriptor";
}

template<>
std::string typeAsString(const CDM::SetStringOperationDescriptor & ) {
	return "SetStringOperationDescriptor";
}

template<>
std::string typeAsString(const CDM::SetValueOperationDescriptor & ) {
	return "SetValueOperationDescriptor";
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
std::string typeAsString(const CDM::SystemContext & ) {
	return "SystemContext";
}

template<>
std::string typeAsString(const CDM::VMDDescriptor & ) {
	return "VMDDescriptor";
}

template<>
std::string typeAsString(const CDM::WorkflowContextDescriptor & ) {
	return "WorkflowContextDescriptor";
}

template<>
std::string typeAsString(const CDM::WorkflowContextState & ) {
	return "WorkflowContextState";
}

template<class Type>
std::string makeDefaultDescriptorDescription(const Type & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	result << "Handle: " << object.Handle() << std::endl;
	if (object.Type().present()) {
		result << "Type: " << object.Type().get().CodeId() << std::endl;
	}
	return result.str();
}

template<class Type>
std::string makeDefaultStateDescription(const Type & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}

std::string makeDescription(const CDM::AbstractMetricDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::AbstractOperationDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::AbstractState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}

std::string makeDescription(const CDM::ActivateOperationDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

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

std::string makeDescription(const CDM::ChannelDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::ComponentState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	result << "ComponentActivation:" << (object.ComponentActivationState().present() ? EnumToString::convert(ConvertFromCDM::convert(object.ComponentActivationState().get())) : "") << std::endl;
	return result.str();
}

std::string makeDescription(const CDM::EnsembleContextDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::EnsembleContextState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}

std::string makeDescription(const CDM::EnumStringMetricDescriptor & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	result << "Handle:" << object.Handle() << std::endl;
	result << "AllowedValues:" << std::endl;
	for (const auto & allowedValue : object.AllowedValue()) {
		result << allowedValue << std::endl;
	}
	return result.str();
}

std::string makeDescription(const CDM::HydraMDSDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::LimitAlertConditionDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}


std::string makeDescription(const CDM::LimitAlertConditionState & object) {
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

std::string makeDescription(const CDM::NumericMetricDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::NumericMetricState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	result << "ObservedValue:" << (object.ObservedValue().present() ? "Yes" : "No") << std::endl;
	if (object.ObservedValue().present()) {
		result << "ObservedValue.Value:";
		if (object.ObservedValue().get().Value().present()) {
			result << object.ObservedValue().get().Value().get() << std::endl;
		} else {
			result << "No" << std::endl;
		}
	}
	return result.str();
}

std::string makeDescription(const CDM::OperationState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	result << "OperatingMode:" << (object.OperatingMode() ? EnumToString::convert(ConvertFromCDM::convert(object.OperatingMode())) : "") << std::endl;
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

std::string makeDescription(const CDM::RealTimeSampleArrayMetricDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::RealTimeSampleArrayMetricState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}

std::string makeDescription(const CDM::SCODescriptor & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}

std::string makeDescription(const CDM::SetAlertStateOperationDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::SetContextOperationDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::SetRangeOperationDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::SetStringOperationDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::SetValueOperationDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::StringMetricDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::StringMetricState & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	result << "ObservedValue:" << (object.ObservedValue().present() ? "Yes" : "No") << std::endl;
	if (object.ObservedValue().present()) {
		result << "ObservedValue.Value:";
		if (object.ObservedValue().get().Value().present()) {
			result << object.ObservedValue().get().Value().get() << std::endl;
		} else {
			result << "---" << std::endl;
		}
	}
	return result.str();
}

std::string makeDescription(const CDM::SystemContext & object) {
	std::ostringstream result;
	result << typeAsString(object) << std::endl;
	return result.str();
}

std::string makeDescription(const CDM::VMDDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::WorkflowContextDescriptor & object) {
	return makeDefaultDescriptorDescription(object);
}

std::string makeDescription(const CDM::WorkflowContextState & object) {
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

std::string makeFormat(const CDM::ChannelDescriptor & object, unsigned int id) {
	return makeStructureFormat(object, id);
}

std::string makeFormat(const CDM::ComponentState & object, unsigned int id) {
	return makeStructureFormat(object, id);
}

std::string makeFormat(const CDM::EnsembleContextDescriptor & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::EnsembleContextState & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::EnumStringMetricDescriptor & object, unsigned int id) {
	return makeMetricFormat(object, id);
}

std::string makeFormat(const CDM::HydraMDSDescriptor & object, unsigned int id) {
	return makeStructureFormat(object, id);
}

std::string makeFormat(const CDM::LocationContextDescriptor & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::LocationContextState & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::LimitAlertConditionDescriptor & object, unsigned int id) {
	return makeAlertFormat(object, id);
}

std::string makeFormat(const CDM::LimitAlertConditionState & object, unsigned int id) {
	return makeAlertFormat(object, id);
}

std::string makeFormat(const CDM::NumericMetricDescriptor & object, unsigned int id) {
	return makeMetricFormat(object, id);
}

std::string makeFormat(const CDM::NumericMetricState & object, unsigned int id) {
	return makeMetricFormat(object, id);
}

std::string makeFormat(const CDM::RealTimeSampleArrayMetricDescriptor & object, unsigned int id) {
	return makeMetricFormat(object, id);
}

std::string makeFormat(const CDM::RealTimeSampleArrayMetricState & object, unsigned int id) {
	return makeMetricFormat(object, id);
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

std::string makeFormat(const CDM::SystemContext & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::StringMetricDescriptor & object, unsigned int id) {
	return makeMetricFormat(object, id);
}

std::string makeFormat(const CDM::StringMetricState & object, unsigned int id) {
	return makeMetricFormat(object, id);
}

std::string makeFormat(const CDM::VMDDescriptor & object, unsigned int id) {
	return makeStructureFormat(object, id);
}

std::string makeFormat(const CDM::WorkflowContextDescriptor & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string makeFormat(const CDM::WorkflowContextState & object, unsigned int id) {
	return makeContextFormat(object, id);
}

std::string buildDotGraph(CDM::MDIB & mdib) {

	std::ostringstream result;
	result << "digraph G {" << std::endl;
	result << "rankdir=\"LR\"" << std::endl;

	result << "unassigned;" << std::endl;

	unsigned int lastNode = 0;

	std::map<std::string, unsigned int> handleToNodeMap;
	std::map<unsigned int, std::string> nodeToDescriptionMap;
	std::vector<unsigned int> metricStateNodes;

	auto processAlertSystemDescriptor = [&](const CDM::AlertSystemDescriptor & system, const std::string & ownerHandle) {
		handleToNodeMap[system.Handle()] = ++lastNode;
		result << "n" << handleToNodeMap[ownerHandle] << " -> n" << handleToNodeMap[system.Handle()] << "[];" << std::endl;
		result << makeFormat(system, handleToNodeMap[system.Handle()]);
		nodeToDescriptionMap[handleToNodeMap[system.Handle()]] = makeDescription(system);
			for (const auto & condition : system.AlertCondition()) {
				handleToNodeMap[condition.Handle()] = ++lastNode;
				result << "n" << handleToNodeMap[system.Handle()] << " -> n" << handleToNodeMap[condition.Handle()] << "[weight=100;];" << std::endl;
				if (auto casted = dynamic_cast<const CDM::LimitAlertConditionDescriptor *>(&condition)) {
					nodeToDescriptionMap[handleToNodeMap[condition.Handle()]] = makeDescription(*casted);
					result << makeFormat(*casted, handleToNodeMap[casted->Handle()]);
				} else {
					nodeToDescriptionMap[handleToNodeMap[condition.Handle()]] = makeDescription(condition);
					result << makeFormat(condition, handleToNodeMap[condition.Handle()]);
				}
			}
			for (const auto & signal : system.AlertSignal()) {
				handleToNodeMap[signal.Handle()] = ++lastNode;
				result << "n" << handleToNodeMap[system.Handle()] << " -> n" << handleToNodeMap[signal.Handle()] << "[weight=100;];" << std::endl;
				nodeToDescriptionMap[handleToNodeMap[signal.Handle()]] = makeDescription(signal);
				result << makeFormat(signal, handleToNodeMap[signal.Handle()]);
			}
		};

	const CDM::MDDescription & mddescription(mdib.MDDescription());
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			handleToNodeMap[hydraMDS->Handle()] = ++lastNode;
			nodeToDescriptionMap[handleToNodeMap[hydraMDS->Handle()]] = makeDescription(*hydraMDS);
			result << makeFormat(*hydraMDS, handleToNodeMap[hydraMDS->Handle()]);

			if (hydraMDS->AlertSystem().present()) {
				processAlertSystemDescriptor(hydraMDS->AlertSystem().get(), hydraMDS->Handle());
			}

			if (hydraMDS->SCO().present()) {
				const CDM::SCODescriptor & sco(hydraMDS->SCO().get());
				handleToNodeMap[sco.Handle()] = ++lastNode;
				result << "n" << handleToNodeMap[hydraMDS->Handle()] << " -> n" << handleToNodeMap[sco.Handle()] << "[];" << std::endl;
				nodeToDescriptionMap[handleToNodeMap[sco.Handle()]] = makeDescription(sco);
				for (const auto & operation : sco.Operation()) {
					handleToNodeMap[operation.Handle()] = ++lastNode;
					result << "n" << handleToNodeMap[sco.Handle()] << " -> n" << handleToNodeMap[operation.Handle()] << "[weight=10000;];" << std::endl;

					if (auto casted = dynamic_cast<const CDM::SetStringOperationDescriptor *>(&operation)) {
						nodeToDescriptionMap[handleToNodeMap[operation.Handle()]] = makeDescription(*casted);
					} else if (auto casted = dynamic_cast<const CDM::SetValueOperationDescriptor *>(&operation)) {
						nodeToDescriptionMap[handleToNodeMap[operation.Handle()]] = makeDescription(*casted);
					} else if (auto casted = dynamic_cast<const CDM::SetContextOperationDescriptor *>(&operation)) {
						nodeToDescriptionMap[handleToNodeMap[operation.Handle()]] = makeDescription(*casted);
					} else if (auto casted = dynamic_cast<const CDM::SetAlertStateOperationDescriptor *>(&operation)) {
						nodeToDescriptionMap[handleToNodeMap[operation.Handle()]] = makeDescription(*casted);
					} else if (auto casted = dynamic_cast<const CDM::SetRangeOperationDescriptor *>(&operation)) {
						nodeToDescriptionMap[handleToNodeMap[operation.Handle()]] = makeDescription(*casted);
					} else if (auto casted = dynamic_cast<const CDM::ActivateOperationDescriptor *>(&operation)) {
						nodeToDescriptionMap[handleToNodeMap[operation.Handle()]] = makeDescription(*casted);
					} else {
						nodeToDescriptionMap[handleToNodeMap[operation.Handle()]] = makeDescription(operation);
					}

				}
			}

			const CDM::SystemContext & systemContext(hydraMDS->Context());
			handleToNodeMap[systemContext.Handle()] = ++lastNode;
			result << "n" << handleToNodeMap[hydraMDS->Handle()] << " -> n" << handleToNodeMap[systemContext.Handle()] << "[];" << std::endl;
			result << makeFormat(systemContext, handleToNodeMap[systemContext.Handle()]);
			nodeToDescriptionMap[handleToNodeMap[systemContext.Handle()]] = makeDescription(systemContext);

			if (systemContext.EnsembleContext().present()) {
				const CDM::EnsembleContextDescriptor & context(systemContext.EnsembleContext().get());
				handleToNodeMap[context.Handle()] = ++lastNode;
				result << "n" << handleToNodeMap[systemContext.Handle()] << " -> n" << handleToNodeMap[context.Handle()] << "[weight=100;];" << std::endl;
				result << makeFormat(context, handleToNodeMap[context.Handle()]);
				nodeToDescriptionMap[handleToNodeMap[context.Handle()]] = makeDescription(context);
			}
			if (systemContext.LocationContext().present()) {
				const CDM::LocationContextDescriptor & context(systemContext.LocationContext().get());
				handleToNodeMap[context.Handle()] = ++lastNode;
				result << "n" << handleToNodeMap[systemContext.Handle()] << " -> n" << handleToNodeMap[context.Handle()] << "[weight=100;];" << std::endl;
				result << makeFormat(context, handleToNodeMap[context.Handle()]);
				nodeToDescriptionMap[handleToNodeMap[context.Handle()]] = makeDescription(context);
			}
			if (systemContext.OperatorContext().present()) {
				const CDM::OperatorContextDescriptor & context(systemContext.OperatorContext().get());
				handleToNodeMap[context.Handle()] = ++lastNode;
				result << "n" << handleToNodeMap[systemContext.Handle()] << " -> n" << handleToNodeMap[context.Handle()] << "[weight=100;];" << std::endl;
				result << makeFormat(context, handleToNodeMap[context.Handle()]);
				nodeToDescriptionMap[handleToNodeMap[context.Handle()]] = makeDescription(context);
			}
			if (systemContext.PatientContext().present()) {
				const CDM::PatientContextDescriptor & context(systemContext.PatientContext().get());
				handleToNodeMap[context.Handle()] = ++lastNode;
				result << "n" << handleToNodeMap[systemContext.Handle()] << " -> n" << handleToNodeMap[context.Handle()] << "[weight=100;];" << std::endl;
				result << makeFormat(context, handleToNodeMap[context.Handle()]);
				nodeToDescriptionMap[handleToNodeMap[context.Handle()]] = makeDescription(context);
			}
			if (systemContext.WorkflowContext().present()) {
				const CDM::WorkflowContextDescriptor & context(systemContext.WorkflowContext().get());
				handleToNodeMap[context.Handle()] = ++lastNode;
				result << "n" << handleToNodeMap[systemContext.Handle()] << " -> n" << handleToNodeMap[context.Handle()] << "[weight=100;];" << std::endl;
				result << makeFormat(context, handleToNodeMap[context.Handle()]);
				nodeToDescriptionMap[handleToNodeMap[context.Handle()]] = makeDescription(context);
			}

			for (const auto & vmdDescriptor : hydraMDS->VMD()) {
				handleToNodeMap[vmdDescriptor.Handle()] = ++lastNode;
				result << "n" << handleToNodeMap[hydraMDS->Handle()] << " -> n" << handleToNodeMap[vmdDescriptor.Handle()] << "[];" << std::endl;
				nodeToDescriptionMap[handleToNodeMap[vmdDescriptor.Handle()]] = makeDescription(vmdDescriptor);
				result << "n" << handleToNodeMap[vmdDescriptor.Handle()] << "[style=\"filled,solid\"; fillcolor=\"" << structureColor <<"\"];" << std::endl;
				result << makeFormat(vmdDescriptor, handleToNodeMap[vmdDescriptor.Handle()]);

				if (vmdDescriptor.AlertSystem().present()) {
					processAlertSystemDescriptor(vmdDescriptor.AlertSystem().get(), vmdDescriptor.Handle());
				}

				for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
					handleToNodeMap[channelDescriptor.Handle()] = ++lastNode;
					result << "n" << handleToNodeMap[vmdDescriptor.Handle()] << " -> n" << handleToNodeMap[channelDescriptor.Handle()] << "[];" << std::endl;
					nodeToDescriptionMap[handleToNodeMap[channelDescriptor.Handle()]] = makeDescription(channelDescriptor);
					result << makeFormat(channelDescriptor, handleToNodeMap[channelDescriptor.Handle()]);

					if (channelDescriptor.AlertSystem().present()) {
						processAlertSystemDescriptor(channelDescriptor.AlertSystem().get(), channelDescriptor.Handle());
					}

					for (const auto & metricDescriptor : channelDescriptor.Metric()) {
						handleToNodeMap[metricDescriptor.Handle()] = ++lastNode;
						result << "n" << handleToNodeMap[channelDescriptor.Handle()] << " -> n" << handleToNodeMap[metricDescriptor.Handle()] << "[weight=100;];" << std::endl;

						if (auto casted = dynamic_cast<const CDM::NumericMetricDescriptor *>(&metricDescriptor)) {
							nodeToDescriptionMap[handleToNodeMap[metricDescriptor.Handle()]] = makeDescription(*casted);
							result << makeFormat(*casted, handleToNodeMap[casted->Handle()]);
						} else if (auto casted = dynamic_cast<const CDM::EnumStringMetricDescriptor *>(&metricDescriptor)) {
							nodeToDescriptionMap[handleToNodeMap[metricDescriptor.Handle()]] = makeDescription(*casted);
							result << makeFormat(*casted, handleToNodeMap[casted->Handle()]);
						} else if (auto casted = dynamic_cast<const CDM::StringMetricDescriptor *>(&metricDescriptor)) {
							nodeToDescriptionMap[handleToNodeMap[metricDescriptor.Handle()]] = makeDescription(*casted);
							result << makeFormat(*casted, handleToNodeMap[casted->Handle()]);
						} else if (auto casted = dynamic_cast<const CDM::RealTimeSampleArrayMetricDescriptor *>(&metricDescriptor)) {
							nodeToDescriptionMap[handleToNodeMap[metricDescriptor.Handle()]] = makeDescription(*casted);
							result << makeFormat(*casted, handleToNodeMap[casted->Handle()]);
						} else {
							nodeToDescriptionMap[handleToNodeMap[metricDescriptor.Handle()]] = makeDescription(metricDescriptor);
						}
					}
				}
			}
		}
	}

	// second pass for operation targets
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			if (hydraMDS->SCO().present()) {
				for (const auto & operation : hydraMDS->SCO().get().Operation()) {
					if (handleToNodeMap.find(operation.OperationTarget()) != handleToNodeMap.end()) {
						result << "n" << handleToNodeMap[operation.OperationTarget()] << "[shape=octagon];" << std::endl;
					} else {
						result << "n" << handleToNodeMap[operation.Handle()] << " -> unassigned;" << std::endl;
					}
				}
			}
		}
	}

	for (const auto & state : mdib.MDState().State()) {
		unsigned int currentNode = ++lastNode;

		// connect to descriptor
		if (handleToNodeMap.find(state.DescriptorHandle()) != handleToNodeMap.end()) {
			result << "n" << handleToNodeMap[state.DescriptorHandle()] << " -> n" << currentNode << " [dir=back,style=dashed];" << std::endl;
		} else {
			result << "n" << currentNode << " -> unassigned;" << std::endl;
		}

		if (auto casted = dynamic_cast<const CDM::LimitAlertConditionState *>(&state)) {
			nodeToDescriptionMap[currentNode] = makeDescription(*casted);
			result << makeFormat(*casted, currentNode);
		} else if (auto casted = dynamic_cast<const CDM::AlertConditionState *>(&state)) {
			nodeToDescriptionMap[currentNode] = makeDescription(*casted);
			result << makeFormat(*casted, currentNode);
		} else if (auto casted = dynamic_cast<const CDM::OperationState *>(&state)) {
			nodeToDescriptionMap[currentNode] = makeDescription(*casted);
		} else if (auto casted = dynamic_cast<const CDM::AlertSignalState*>(&state)) {
			nodeToDescriptionMap[currentNode] = makeDescription(*casted);
			result << makeFormat(*casted, currentNode);
		} else if (auto casted = dynamic_cast<const CDM::AlertSystemState *>(&state)) {
			nodeToDescriptionMap[currentNode] = makeDescription(*casted);
			result << makeFormat(*casted, currentNode);
			// force alert system states next to alert system
			if (handleToNodeMap.find(state.DescriptorHandle()) != handleToNodeMap.end()) {
				result << " { rank = same; " ;
				result << "n" << handleToNodeMap[state.DescriptorHandle()] << "; n" << currentNode << ";";
				result << "} " << std::endl ;
			}
		} else if (auto casted = dynamic_cast<const CDM::EnsembleContextState *>(&state)) {
			nodeToDescriptionMap[currentNode] = makeDescription(*casted);
			result << makeFormat(*casted, currentNode);
		} else if (auto casted = dynamic_cast<const CDM::LocationContextState *>(&state)) {
			nodeToDescriptionMap[currentNode] = makeDescription(*casted);
			result << makeFormat(*casted, currentNode);
		} else if (auto casted = dynamic_cast<const CDM::OperatorContextState *>(&state)) {
			nodeToDescriptionMap[currentNode] = makeDescription(*casted);
			result << makeFormat(*casted, currentNode);
		} else if (auto casted = dynamic_cast<const CDM::PatientContextState *>(&state)) {
			nodeToDescriptionMap[currentNode] = makeDescription(*casted);
			result << makeFormat(*casted, currentNode);
		} else if (auto casted = dynamic_cast<const CDM::WorkflowContextState *>(&state)) {
			nodeToDescriptionMap[currentNode] = makeDescription(*casted);
			result << makeFormat(*casted, currentNode);
		} else if (auto casted = dynamic_cast<const CDM::NumericMetricState *>(&state)) {
			metricStateNodes.emplace_back(currentNode);
			nodeToDescriptionMap[currentNode] = makeDescription(*casted);
			result << makeFormat(*casted, currentNode);
		} else if (auto casted = dynamic_cast<const CDM::RealTimeSampleArrayMetricState *>(&state)) {
			metricStateNodes.emplace_back(currentNode);
			nodeToDescriptionMap[currentNode] = makeDescription(*casted);
			result << makeFormat(*casted, currentNode);
		} else if (auto casted = dynamic_cast<const CDM::StringMetricState *>(&state)) {
			metricStateNodes.emplace_back(currentNode);
			nodeToDescriptionMap[currentNode] = makeDescription(*casted);
			result << makeFormat(*casted, currentNode);
		} else if (auto casted = dynamic_cast<const CDM::ComponentState *>(&state)) {
			nodeToDescriptionMap[currentNode] = makeDescription(*casted);
			result << makeFormat(*casted, currentNode);
			// force component states next to component
			if (handleToNodeMap.find(state.DescriptorHandle()) != handleToNodeMap.end()) {
				result << " { rank = same; " ;
				result << "n" << handleToNodeMap[state.DescriptorHandle()] << "; n" << currentNode << ";";
				result << "} " << std::endl ;
			}
		} else {
			nodeToDescriptionMap[currentNode] = makeDescription(state);
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

int main()
{
	const std::string testname("Create graphvis/dot files of all MDIBs of all found devices");
	DebugOut(DebugOut::Default, "MDIBVisualizer") << std::endl << "Startup: " << testname;
	OSCLibrary::getInstance().startup();
	DebugOut(DebugOut::Default, "MDIBVisualizer") << std::endl << "Compile dotfiles with: " << "ls *.dot | xargs -I {} dot -Tpng {} -o {}.png";

	int loopcounter = 0;
	OSELib::OSCP::ServiceManager oscpsm;

	while (true) {
		DebugOut(DebugOut::Default, "MDIBVisualizer") << "Refreshing ..." << std::flush;
		std::vector<std::unique_ptr<OSCPConsumer> > results(oscpsm.discoverOSCP());

		DebugOut(DebugOut::Default, "MDIBVisualizer") << "Found devices with these EPRs: ";

		for (auto & consumer : results) {
			const std::string epr(consumer->getEndpointReference());
			const std::string filename("mdib" + stripCharacters(epr, "./\\!?*") + ".dot");

			DebugOut(DebugOut::Default, "MDIBVisualizer") << "Found EPR " << epr << " and dumping to file " << filename;

			try {
				std::ofstream outFile;
				outFile.open(filename, std::ios::trunc);
				Poco::Timestamp now;

				OSELib::OSCP::DefaultOSCPSchemaGrammarProvider grammarProvider;
				auto rawMessage = OSELib::Helper::Message::create(consumer->requestRawMDIB());
				auto xercesDocument = OSELib::Helper::XercesDocumentWrapper::create(*rawMessage, grammarProvider);

				std::unique_ptr<CDM::MDIB> mdib(CDM::MDIBContainer(xercesDocument->getDocument()));

				if (mdib) {
					outFile << buildDotGraph(*mdib);
				}

				DebugOut(DebugOut::Default, "MDIBVisualizer") << "   -> took " << Poco::DateTimeFormatter::format(Poco::Timespan(now.elapsed()), "%s:%i") << " s:ms." << std::endl;
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

		++loopcounter;
	}

	Poco::Thread::sleep(2000);

	DebugOut(DebugOut::Default, "MDIBVisualizer") << "Shutdown: " << testname << std::endl;
}

