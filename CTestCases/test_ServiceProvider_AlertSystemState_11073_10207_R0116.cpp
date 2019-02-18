/*
 * test_ServiceProvider_AlertSystemState_11073_10207_R0116.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: rosenau
 */

#include <iostream>

#include "OSCLib/SDCInstance.h"

#include "OSCLib/SDCLibrary.h"
#include "OSCLib/Util/Task.h"
#include "OSCLib/Data/SDC/MDPWSTransportLayerConfiguration.h"
#include "OSCLib/Util/DebugOut.h"

#include "OSELib/SDC/ServiceManager.h"

#include "Tools/TestProvider.h"
#include "Tools/HelperMethods.h"

using namespace SDCLib;
using namespace SDCLib::Data;
using namespace SDCLib::Data::SDC;

template< typename Expected, typename Actual >
void CheckEqual(Expected const& expected, Actual const& actual, const std::string &handle, bool &testResult)
{
    if (!(expected == actual))
    {
    	std::cout << "Test failed: " <<	handle <<  " Activation state is "  << TestTools::as_integer(actual) << " while the superiordinated AlertSystem ActiavtionState is " << TestTools::as_integer(expected) << std::endl;
    	testResult = false;
    }
};

void checkActivationState(TestTools::TestProvider &provider, bool &testResult)
{
	for (auto alertSystemDesc : provider.getMdDscription().collectAllAlertSystemDescriptors()) {
		Handle alertSystemHandle = alertSystemDesc.getHandle();
		unique_ptr<AlertSystemState> alertSystemState = provider.getMdState().findState<AlertSystemState>(alertSystemHandle);
		auto alertSystemActivationState = alertSystemState->getActivationState();
		for (auto alertConditionDesc : alertSystemDesc.getAlertConditionList()) {
			Handle alertConditionHandle = alertConditionDesc.getHandle();
			unique_ptr<AlertConditionState> alertConditionState = provider.getMdState().findState<AlertConditionState>(alertConditionHandle);
			auto alertConditionActivationState = alertConditionState->getActivationState();
			CheckEqual(alertSystemActivationState, alertConditionActivationState, alertConditionHandle, testResult);
		}
		for (auto alertSignalDesc : alertSystemDesc.getAlertSignalList()) {
			Handle alertSignalHandle = alertSignalDesc.getHandle();
			unique_ptr<AlertSignalState> alertSignalState = provider.getMdState().findState<AlertSignalState>(alertSignalHandle);
			auto alertSignalActivationState = alertSignalState->getActivationState();
			CheckEqual(alertSystemActivationState, alertSignalActivationState, alertSignalHandle, testResult);
		}
	}
};


int main()
{
	std::cout << "Test against requirement R0116 from IEEE 11073-10207-R0116: "
			  << "The activation state of pm:AlertSystemState SHALL result in "
			  << "an activation state of pm:AlertConditionState and "
			  << "pm:AlertSignalState according to Table 8: Relationship "
			  << "between alert activation states."
			  << std::endl;
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);
	SDCLibrary::getInstance().setPortStart(12000);

	TestTools::TestProvider provider;
	provider.setPort(TestTools::getFreePort());
	provider.startup();
	provider.start();

	bool passed = true;

	provider.setAlertSystemActivationState(AlertActivation::Off);
	checkActivationState(provider, passed);

	provider.setAlertSystemActivationState(AlertActivation::Psd);
	checkActivationState(provider, passed);
	if(passed) {
		std::cout << "Test passed";
	}

	provider.shutdown();
	SDCLibrary::getInstance().shutdown();
	Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Shutdown." << std::endl;
}
