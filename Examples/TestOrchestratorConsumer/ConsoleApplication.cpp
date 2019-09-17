/*
 * ConsoleApplication.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: rosenau
 */

#include "TestOrchestratorConsumer.h"
#include "CallbackMap.h"
#include "SDCLib/SDCLibrary.h"

#include <fstream>


using namespace SDCLib::Data::SDC::ACS;


int main() {
    SDCLib::SDCLibrary::getInstance().startup(OSELib::LogLevel::None);

	TestOrchestratorConsumer toc;
	CallbackMap cbm;
	cbm.setCallback("discoverDiscoveryProvider", {""}, cbm.defineCallback([&]() { toc.discoverDiscoveryProvider(); }));
	cbm.setCallback("updateAvailableEndpointReferences", {""}, cbm.defineCallback( [&]() { toc.updateAvailableEndpointReferences(); }));
	cbm.setCallback("setDUTEndpointRef", {"[UUIDv5]"}, cbm.defineCallback<std::string>( [&](std::string EndpointRef) { toc.setDUTEndpointRef(EndpointRef);}));
	cbm.setCallback("discoverDUT", {""}, cbm.defineCallback( [&]() {toc.discoverDUT();}));
	cbm.setCallback("setMirrorProviderEndpointRef", {"[EndpointRef]"}, cbm.defineCallback<std::string>( [&](std::string EndpointRef) {toc.setMirrorProviderEndpointRef(EndpointRef);}));
	cbm.setCallback("setupMirrorProvider", {""}, cbm.defineCallback([&]() {toc.setupMirrorProvider();}));
	cbm.setCallback("discoverMirrorProvider", {""}, cbm.defineCallback([&]() {toc.discoverMirrorProvider();}));
	cbm.setCallback("requestDUTMDIB", {""}, cbm.defineCallback( [&] () {toc.requestDUTMDIB();}));
	cbm.setCallback("requestNumericMetricValue", {"[NMSDescriptorHandle]"}, cbm.defineCallback<std::string>( [&] (std::string descriptorHandle) {toc.requestNumericMetricValue(descriptorHandle);}));
	cbm.setCallback("setNumericMetricValue", {"[NMSDescriptorHandle]", "[double]"}, cbm.defineCallback<std::string, double>
	( [&](std::string descriptorHandle, double val) { toc.setNumericMetricValue(descriptorHandle, val); } ));
	cbm.setCallback("setMMBBTestCaseValue", {"[BBMMEnumHandle]", "[allowedTestCaseValue]"}, cbm.defineCallback<std::string, std::string>
	( [&](std::string descriptorHandle, std::string val) {toc.setMMBBTestCaseValue(descriptorHandle, val);}));
	cbm.setCallback("requestStringMetricValue", {"[SMSDescriptorHandle]"}, cbm.defineCallback<std::string>
	( [&] (std::string descriptorHandle) {toc.requestStringMetricValue(descriptorHandle);}));
	cbm.setCallback("setStringMetricValue", {"[SMSDescriptorHandle]", "[string]"}, cbm.defineCallback<std::string, std::string>
	( [&] (std::string descriptorHandle, std::string val) {toc.setStringMetricValue(descriptorHandle, val);}));
	cbm.setCallback("requestMirrorProviderMDIB", {""}, cbm.defineCallback( [&]() {toc.requestMirrorProviderMDIB();}));
	cbm.setCallback("activate", {"[ActivateDescriptorHandle]"}, cbm.defineCallback<std::string>
	([&] (std::string descriptorHandle) {toc.activate(descriptorHandle);}));
	cbm.setCallback("exit", {""}, cbm.defineCallback([&]() { exit(0);}));
	cbm.setCallback("calcUUIDv5", {"string"}, cbm.defineCallback<std::string>( [&](std::string stringEndpointRef) {toc.calcUUIDv5(stringEndpointRef);}));
	cbm.setCallback("subscribeToState", {"string"}, cbm.defineCallback<std::string>( [&](std::string descriptorHandle) {toc.subscribeToState(descriptorHandle);}));
	cbm.setCallback("unsubscribeFromState", {"string"}, cbm.defineCallback<std::string>( [&](std::string descriptorHandle) {toc.unsubscribeFromState(descriptorHandle);}));
	auto help = [&]() {
		std::cout << "Available Methods:" << std::endl;
		for(auto callback : cbm.getCallbacks())
		{
			if((callback.first.functionName == "help") || (callback.first.functionName == "Help"))
			{
				continue;
			}
			std::cout << callback.first.functionName << " ";
			for(auto arg : callback.first.args)
			{
				std::cout << arg << " ";
			}
			std::cout << std::endl;
		}
	};
	cbm.setCallback("help", {""}, cbm.defineCallback(help));
	cbm.setCallback("Help", {""}, cbm.defineCallback(help));

	std::cout << "Welcome to the TestOrchestratorConsumer ConsoleApplication. "
				 "If you are here for the first time use help, to get a list of all available functions. \n";


	std::ofstream log("log.txt");
	if(!log)
	{
		std::cout << "Could not open log file" << std::endl;
	}
	std::string input = "";

	while(input != "exit")
	{
		std::getline (std::cin, input);
		if(input.empty())
		{
			continue;
		}
		if(log)
		{
			log << input << std::endl;
		}
		std::istringstream iss(input);
		std::vector<std::string> command(std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>());
		auto functionName = command.front();
		command.erase(command.begin());
		std::ostringstream oss;
		std::copy(command.begin(), command.end(),
		           std::ostream_iterator<std::string>(oss, " "));
		auto args = oss.str();
		std::cout << "calling " << functionName << " with " << args << std::endl;
		cbm.call(functionName, args);
	}
	log.close();
	return 0;

//	std::function<void(std::string)> func = (std::bind(&TestOrchestratorConsumer::setDUTEndpointRef, &toc, std::placeholders::_1));
//	CallbackMap::defineCallback<std::string>(func);
//			cbm.setCallback("discoverDUT", cbm.defineCallback( [&]() {toc.discoverDUT(); }));

}






