/*
 * OSCPProviderContextStateHandler.h
 *
 *  Created on: 29.05.2015
 *      Author: roehser
 */

#ifndef DATA_OSCP_OSCPPROVIDERCONTEXTSTATEHANDLER_H_
#define DATA_OSCP_OSCPPROVIDERCONTEXTSTATEHANDLER_H_

#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "OSCLib/Data/OSCP/OSCPProviderMDStateHandler.h"
#include<vector>

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProviderContextStateHandler : public OSCPProviderMDStateHandler {
public:
	OSCPProviderContextStateHandler();
	virtual ~OSCPProviderContextStateHandler();

    /**
    * @brief Called on incoming consumer request for a state change
    *
    * Notes:
    * - The consumer will NOT wait for this method to complete.
    *
    * @param pcStates PatientContextState states
    * @param lcStates LocationContextState states
    * @param ecStates EnsembleContextState states
    * @param ocStates OperatorContextState states
    * @param wcStates WorkflowContextState states
    *
    * @return invocation state
    */
    virtual InvocationState onStateChangeRequest(
			const std::vector<EnsembleContextState> & ecStates,
    		const std::vector<LocationContextState> & lcStates,
			const std::vector<OperatorContextState> & ocStates,
			const std::vector<PatientContextState> & pcStates,
			const std::vector<WorkflowContextState> & wcStates,
    		const OperationInvocationContext & oic);

	virtual std::vector<EnsembleContextState> getEnsembleContextStates();
	virtual std::vector<LocationContextState> getLocationContextStates();
	virtual std::vector<OperatorContextState> getOperatorContextStates();
	virtual std::vector<PatientContextState> getPatientContextStates();
	virtual std::vector<WorkflowContextState> getWorkflowContextStates();

	void updateState(const OSCLib::Data::OSCP::EnsembleContextState & object);
	void updateState(const OSCLib::Data::OSCP::LocationContextState & object);
	void updateState(const OSCLib::Data::OSCP::OperatorContextState & object);
	void updateState(const OSCLib::Data::OSCP::PatientContextState & object);
	void updateState(const OSCLib::Data::OSCP::WorkflowContextState & object);

	/* This should be private, but swig needs this method to be public.
	 * Otherwise it creates malfunctioning wrapper code.
	 * */
	std::string getDescriptorHandle();
private:
	 const std::string handle;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* DATA_OSCP_OSCPPROVIDERCONTEXTSTATEHANDLER_H_ */
