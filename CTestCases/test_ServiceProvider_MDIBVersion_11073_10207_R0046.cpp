/*
 * test_ServiceProvider_MDIBVersion_11073_10207_R0046.cpp
 *
 *  Created on: Dec 5, 2018
 *      Author: rosenau
 */

#include <iostream>

#include "OSCLib/Data/SDC/MDIB/Range.h"
#include "OSCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "OSCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "OSCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "OSCLib/Data/SDC/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/SDC/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/SDC/SDCProvider.h"

using namespace SDCLib;
using namespace SDCLib::Data::SDC;

const std::string HANDLE_ALERT_CONDITION("handle_alert_condition");
const std::string HANDLE_ALERT_SYSTEM("handle_alert_system");
const std::string HANDLE_ALERT_SIGNAL("handle_alert_signal");
const std::string HANDLE_ENUM_STRING_METRIC("handle_enum_string_metric");
const std::string HANDLE_LIMIT_ALERT_CONDITION("handle_limt_alert_condition");
const std::string HANDLE_NUMERIC_METRIC("handle_numeric_metric");
const std::string HANDLE_String_METRIC("handle_string_metric");


int main ()
{
	AlertConditionState alertConditionState(HANDLE_ALERT_CONDITION, AlertActivation::Off);
	SDCProvider sdcProvider;
	std::cout << sdcProvider.getMdibVersion() << std::endl;
	sdcProvider.updateState(alertConditionState);
	alertConditionState.setStateVersion(0);
	std::cout << "alertVerision" << alertConditionState.getStateVersion() << std::endl;
	std::cout << sdcProvider.getMdibVersion() << std::endl;
	sdcProvider.updateState(alertConditionState);
	std::cout << "alertVerision" << alertConditionState.getStateVersion() << std::endl;
	std::cout << sdcProvider.getMdibVersion() << std::endl;

	AlertSystemState alertSystemState(HANDLE_ALERT_SYSTEM, AlertActivation::Off);
	sdcProvider.updateState(alertSystemState);
	std::cout << sdcProvider.getMdibVersion() << std::endl;

	AlertSignalState alertSignalState(HANDLE_ALERT_SIGNAL, AlertActivation::Off);
	sdcProvider.updateState(alertSignalState);
	std::cout << sdcProvider.getMdibVersion() << std::endl;

	EnumStringMetricState enumStringMetricState(HANDLE_ENUM_STRING_METRIC);
	sdcProvider.updateState(enumStringMetricState);
	std::cout << sdcProvider.getMdibVersion() << std::endl;

	Range range;
	range.setUpper(0.0);
	range.setLower(0.0);
	LimitAlertConditionState limitAlertConditionState(HANDLE_LIMIT_ALERT_CONDITION, AlertActivation::Off, range, AlertConditionMonitoredLimits::All);
	sdcProvider.updateState(limitAlertConditionState);
	std::cout << sdcProvider.getMdibVersion() << std::endl;
//
//	NumericMetricState numericMetricState(HANDLE_NUMERIC_METRIC);
//	sdcProvider.updateState(numericMetricState);
//	std::cout << sdcProvider.getMdibVersion() << std::endl;
//
//	StringMetricState stringMetricState(HANDLE_String_METRIC);
//	sdcProvider.updateState(stringMetricState);
}


