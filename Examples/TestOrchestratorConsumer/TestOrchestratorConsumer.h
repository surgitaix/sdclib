/*
 * TestOrchestratorConsumer.h
 *
 *  Created on: Jul 31, 2019
 *      Author: rosenau
 */

#ifndef EXAMPLES_ABSTRACTCONSUMERSIMULATOR_TESTORCHESTRATORCONSUMER_H_
#define EXAMPLES_ABSTRACTCONSUMERSIMULATOR_TESTORCHESTRATORCONSUMER_H_

#include <iostream>
#include "osdm.hxx"
#include "OSELib/DPWS/DPWS11Constants.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/SDCConsumerConnectionLostHandler.h"
#include "SDCLib/Data/SDC/MDIB/custom/MdibContainer.h"
#include "OSELib/SDC/ServiceManager.h"
#include "SDCLib/SDCInstance.h"
#include "../AbstractConsumerSimulator/NamigConvention.h"

namespace SDCLib {
namespace Data {
namespace SDC {
namespace ACS {

class TestOrchestratorConsumer {
public:
	TestOrchestratorConsumer();
	virtual ~TestOrchestratorConsumer();

	//Discovery of DiscoveryProvider
	void discoverDiscoveryProvider();
	void updateAvailableEndpointReferences();

	//Discover DUT
	void setDUTEndpointRef(const std::string& EndpointRef);
	void discoverDUT();

	//Setup MirrorProvider
	void setMirrorProviderEndpointRef(const std::string& EndpointRef);
	void setupMirrorProvider();
	bool discoverMirrorProvider();


	std::string getProviderMDIB();
	void addSetHandler();
	void sendGetRequest(HandleRef& descriptorHandle);
	template <typename TState>
	TState requestState(HandleRef& descriptorHandle);
	template <typename TState>
	void sendSetRequest(HandleRef& descriptorHandle, TState state);
	void sendSubcribeRequest(HandleRef& descriptorHandle);
	void stopMirrorProvider();
	void startMirrorProvider();

private:
	const std::string getStringRepresentationOfMDIB(const MdibContainer MDIB);

	SDCInstance_shared_ptr createDefaultSDCInstance();

	std::string DUTMirrorProviderRef;
	std::string DUTEndpointRef;

	std::vector<std::string> availableEndpointReferences;

	std::unique_ptr<SDCConsumer> consumer;


};
} //ACS
} //SDC
} //Data
} //SDCLib

#endif /* EXAMPLES_ABSTRACTCONSUMERSIMULATOR_TESTORCHESTRATORCONSUMER_H_ */
