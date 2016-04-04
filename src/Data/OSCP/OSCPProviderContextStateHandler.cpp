/*
 * OSCPProviderContextStateHandler.cpp
 *
 *  Created on: 29.05.2015
 *      Author: roehser
 */

#include "OSCLib/Data/OSCP/MDIB/EnsembleContextState.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextState.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextState.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextState.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextState.h"
#include "OSCLib/Data/OSCP/OSCPProviderContextStateHandler.h"
#include "OSCLib/Util/DefaultUUIDGenerator.h"
#include "OSCLib/Util/DebugOut.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderContextStateHandler::OSCPProviderContextStateHandler() :
	handle(Util::DefaultUUIDGenerator::getUUID())
{

}

OSCPProviderContextStateHandler::~OSCPProviderContextStateHandler() {

}

std::string OSCPProviderContextStateHandler::getDescriptorHandle() {
	return handle;
}

InvocationState OSCPProviderContextStateHandler::onStateChangeRequest(
		const std::vector<EnsembleContextState> &,
		const std::vector<LocationContextState> &,
		const std::vector<OperatorContextState> &,
		const std::vector<PatientContextState> &,
		const std::vector<WorkflowContextState> &,
		const OperationInvocationContext &) {
    Util::DebugOut(Util::DebugOut::Error, "OSCPProviderContextStateHandler") << "Method not overridden: onStateChangeRequest(AlertSignalState)!";
    return InvocationState::FAILED;
}

std::vector<EnsembleContextState> OSCPProviderContextStateHandler::getEnsembleContextStates() {
	return std::vector<EnsembleContextState>();
}

std::vector<LocationContextState> OSCPProviderContextStateHandler::getLocationContextStates() {
	return std::vector<LocationContextState>();
}

std::vector<OperatorContextState> OSCPProviderContextStateHandler::getOperatorContextStates() {
	return std::vector<OperatorContextState>();
}

std::vector<PatientContextState> OSCPProviderContextStateHandler::getPatientContextStates() {
	return std::vector<PatientContextState>();
}

std::vector<WorkflowContextState> OSCPProviderContextStateHandler::getWorkflowContextStates() {
	return std::vector<WorkflowContextState>();
}

void OSCPProviderContextStateHandler::updateState(const OSCLib::Data::OSCP::EnsembleContextState & object) {
	notifyMDIBObjectChangedImpl(object);
}

void OSCPProviderContextStateHandler::updateState(const OSCLib::Data::OSCP::LocationContextState & object) {
	notifyMDIBObjectChangedImpl(object);
}

void OSCPProviderContextStateHandler::updateState(const OSCLib::Data::OSCP::OperatorContextState & object) {
	notifyMDIBObjectChangedImpl(object);
}

void OSCPProviderContextStateHandler::updateState(const OSCLib::Data::OSCP::PatientContextState & object) {
	notifyMDIBObjectChangedImpl(object);
}

void OSCPProviderContextStateHandler::updateState(const OSCLib::Data::OSCP::WorkflowContextState & object) {
	notifyMDIBObjectChangedImpl(object);
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
