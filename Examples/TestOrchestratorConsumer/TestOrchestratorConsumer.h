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
	void discoverMirrorProvider();

	void requestDUTMDIB();

	void requestNumericMetricValue(HandleRef& descriptorHandle);
	void setNumericMetricValue(HandleRef& descriptorHandle, double val);

	void requestStringMetricValue(HandleRef& descriptorHandle);
	void setStringMetricValue(HandleRef& descriptorHandel, std::string val);

	void activate(std::string descriptorHandle);


	void calcUUIDv5(std::string StringEndpointRef);

	void subscribeToState(std::string descriptorHandle);
	void unsubscribeFromState(std::string descriptorHandle);

	void requestMirrorProviderMDIB();
	const std::string getMirrorProviderMDIB();
	const std::string getDUTMDIB();
	void addSetHandler();
	void sendGetRequest(HandleRef& descriptorHandle);
	template <typename TState>
	std::unique_ptr<TState> requestState(HandleRef& descriptorHandle);
	template <typename TState>
	void sendSetRequest(HandleRef& descriptorHandle, TState state);
	void sendSubcribeRequest(HandleRef& descriptorHandle);
	void stopMirrorProvider();
	void startMirrorProvider();
	const std::vector<std::string> getAvailableEndpointReferences();


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
