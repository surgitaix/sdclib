/*
 * test_ServiceParticipant_PresentAlertConditions_11073_10207_R0133.cpp
 *
 *  Created on: Jan 31, 2019
 *      Author: rosenau
 */
/*
 * Test against Requiremtent 11073-10207-R0133: If pm:AlertConditionState/@Presence is "true" for any physiological alarm condition or technical alarm condition, then the HANDLE of the corresponding ALERT CONDITION SHALL be added to pm:AlertSystemState/@PresentPhysiologicalAlarmConditions or pm:AlertSystem-State/@PresentTechnicalAlarmConditions, respectively.
 */

#include <iostream>

#include "OSCLib/SDCInstance.h"
#include "OSCLib/SDCLibrary.h"


#include "Tools/HelperMethods.h"
#include "Tools/TestProvider.h"
#include "Tools/TestConsumer.h"
#include "Tools/TestProviderHandleNames.h"


int main()
{
	std::cout << "Test against requirement 11073-10207-R0133: If pm:AlertConditionState/@Presence is \"true\" "
			  << "for any physiological alarm condition or technical alarm condition, then the HANDLE of the "
			  << "corresponding ALERT CONDITION SHALL be added to "
			  << "pm:AlertSystemState/@PresentPhysiologicalAlarmConditions or "
			  << "pm:AlertSystem-State/@PresentTechnicalAlarmConditions, respectively."
			  << std::endl;

	//Network settings
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);
	SDCLibrary::getInstance().setPortStart(12000);

	//Provider setup
	TestTools::TestProvider provider;
	provider.setPort(TestTools::getFreePort());
	provider.startup();
	provider.start();

	provider.setAlertConditionPresence(TestTools::HANDLE_TECHNICAL_ALERT_CONDITION, true, OperationInvocationContext::none());
	provider.setAlertConditionPresence(TestTools::HANDLE_PHYSICAL_ALERT_CONDITION, true, OperationInvocationContext::none());

	if(provider.getMdState().findAlertSystemStates().empty())
	{
		std::cout << "Test failed: No alertSystem present!" << std::endl;
	}
	else {
		if(provider.getMdState().findAlertSystemStates().front().hasPresentPhysiologicalAlarmConditions()) {
			auto physicalAlertCondition = provider.getMdState().findAlertSystemStates().front().getPresentTechnicalAlarmConditions().front();
			if (physicalAlertCondition == TestTools::HANDLE_PHYSICAL_ALERT_CONDITION) {
				std::cout << "Present physical alertConditions are listed." << std::endl;
			}
		}
		else
		{
			std::cout << "Test failed: No physicalAlertCodition present." << std::endl;
		}

		if(provider.getMdState().findAlertSystemStates().front().hasPresentTechnicalAlarmConditions()) {
			auto technicalAlertCondition = provider.getMdState().findAlertSystemStates().front().getPresentTechnicalAlarmConditions().front();
			if (technicalAlertCondition == TestTools::HANDLE_TECHNICAL_ALERT_CONDITION) {
				std::cout << "Present technical alertConditions are listed" << std::endl;
			}
		}
		else
		{
			std::cout << "Test failed: No technicalAlertCondition present." << std::endl;
		}
	}

	std::cout << TestTools::getStringRepresentationOfMDIB(provider.getMdib());

	//Clean up
	provider.shutdown();
	SDCLibrary::getInstance().shutdown();
}

