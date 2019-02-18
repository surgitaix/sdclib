/*
 * TestProviderHandleNames.h
 *
 *  Created on: Feb 1, 2019
 *      Author: rosenau
 */

#ifndef CTESTCASES_TOOLS_TESTPROVIDERHANDLENAMES_H_
#define CTESTCASES_TOOLS_TESTPROVIDERHANDLENAMES_H_

#include <string>

namespace TestTools{
	const std::string DEFAULT_TEST_DEVICE_EPR("TestProvider");
	const std::string CHANNEL_DESCRIPTOR_HANDLE("channel_descriptor_handle");
	const std::string VMD_DESCRIPTOR_HANDLE("vmd_descriptor_handle");
	const std::string MDS_DESCRIPTOR_HANDLE("mds_descriptor_handle");
	const std::string HANDLE_GET_NUMERIC_METRIC("handle_get_numeric_metric");
	const std::string HANDLE_SET_NUMERIC_METRIC("handle_set_numeric_metric");
	const std::string HANDLE_PHYSICAL_ALERT_CONDITION("handle_physical_alert_condition");
	const std::string HANDLE_PHYSICAL_ALERT_SIGNAL("handle_physical_alert_signal");
	const std::string HANDLE_TECHNICAL_ALERT_CONDITION("handle_technical_alert_condition");
	const std::string HANDLE_TECHNICAL_ALERT_SIGNAL("handle_technical_alert_signal");
	const std::string HANDLE_SYSTEM_ALERT_STATE("handle_system_alert_state");
	const std::string HANDLE_ALERT_SYSTEM("handle_alert_system");
}


#endif /* CTESTCASES_TOOLS_TESTPROVIDERHANDLENAMES_H_ */
