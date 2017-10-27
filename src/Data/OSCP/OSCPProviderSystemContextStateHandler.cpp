/*
 * OSCPProviderContextStateHandler.cpp
 *
 *  Created on: 29.05.2015
 *      Author: roehser
 */

#include "Poco/UUIDGenerator.h"

#include "OSCLib/Data/OSCP/MDIB/EnsembleContextState.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextState.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextState.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextState.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextState.h"
#include "OSCLib/Data/OSCP/OSCPProviderSystemContextStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderSystemContextStateHandler::OSCPProviderSystemContextStateHandler() :
	handle(Poco::UUIDGenerator::defaultGenerator().create().toString())
{

}

OSCPProviderSystemContextStateHandler::~OSCPProviderSystemContextStateHandler() {

}

std::string OSCPProviderSystemContextStateHandler::getDescriptorHandle() {
	return handle;
}

InvocationState OSCPProviderSystemContextStateHandler::onStateChangeRequest(
		const std::vector<EnsembleContextState> &,
		const std::vector<LocationContextState> &,
		const std::vector<OperatorContextState> &,
		const std::vector<PatientContextState> &,
		const std::vector<WorkflowContextState> &,
		const OperationInvocationContext &) {
	log_error([] { return "Method not overridden: onStateChangeRequest(AlertSignalState)!"; });
    return InvocationState::Fail;
}

std::vector<EnsembleContextState> OSCPProviderSystemContextStateHandler::getEnsembleContextStates() {
	return std::vector<EnsembleContextState>();
}

std::vector<LocationContextState> OSCPProviderSystemContextStateHandler::getLocationContextStates() {
	return std::vector<LocationContextState>();
}

std::vector<OperatorContextState> OSCPProviderSystemContextStateHandler::getOperatorContextStates() {
	return std::vector<OperatorContextState>();
}

std::vector<PatientContextState> OSCPProviderSystemContextStateHandler::getPatientContextStates() {
	return std::vector<PatientContextState>();
}

std::vector<WorkflowContextState> OSCPProviderSystemContextStateHandler::getWorkflowContextStates() {
	return std::vector<WorkflowContextState>();
}

void OSCPProviderSystemContextStateHandler::updateState(const OSCLib::Data::OSCP::EnsembleContextState & object) {
	notifyMDIBObjectChangedImpl(object);
}

void OSCPProviderSystemContextStateHandler::updateState(const OSCLib::Data::OSCP::LocationContextState & object) {
	notifyMDIBObjectChangedImpl(object);
}

void OSCPProviderSystemContextStateHandler::updateState(const OSCLib::Data::OSCP::OperatorContextState & object) {
	notifyMDIBObjectChangedImpl(object);
}

void OSCPProviderSystemContextStateHandler::updateState(const OSCLib::Data::OSCP::PatientContextState & object) {
	notifyMDIBObjectChangedImpl(object);
}

void OSCPProviderSystemContextStateHandler::updateState(const OSCLib::Data::OSCP::WorkflowContextState & object) {
	notifyMDIBObjectChangedImpl(object);
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
