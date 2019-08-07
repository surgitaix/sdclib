/*
 * ConsoleApplication.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: rosenau
 */

#include "TestOrchestratorConsumer.h"
#include "CallbackMap.h"
#include "SDCLib/SDCLibrary.h"


using namespace SDCLib::Data::SDC::ACS;


int main() {
    SDCLib::SDCLibrary::getInstance().startup(OSELib::LogLevel::None);

	TestOrchestratorConsumer toc;
	CallbackMap cbm;
	cbm.setCallback("discoverDiscoveryProvider", "", cbm.defineCallback([&]() { toc.discoverDiscoveryProvider(); }));
	cbm.setCallback("updateAvailableEndpointReferences", "", cbm.defineCallback( [&]() { toc.updateAvailableEndpointReferences(); }));
	cbm.setCallback("setDUTEndpointRef", "[string]", cbm.defineCallback<std::string>( [&](std::string EndpointRef) { toc.setDUTEndpointRef(EndpointRef);}));
	cbm.setCallback("discoverDUT", "", cbm.defineCallback( [&]() {toc.discoverDUT();}));
	cbm.setCallback("setMirrorProviderEndpointRef", "[string]", cbm.defineCallback<std::string>( [&](std::string EndpointRef) {toc.setMirrorProviderEndpointRef(EndpointRef);}));
	cbm.setCallback("setupMirrorProvider", "", cbm.defineCallback([&]() {toc.setupMirrorProvider();}));
	cbm.setCallback("discoverMirrorProvider", "", cbm.defineCallback([&]() {toc.discoverMirrorProvider();}));
	cbm.setCallback("requestDUTMDIB", "", cbm.defineCallback( [&] () {toc.requestDUTMDIB();}));
	cbm.setCallback("updateNumericMetricValue", "[string]", cbm.defineCallback<std::string>( [&] (std::string descriptorHandle) {toc.updateNumericMetricValue(descriptorHandle);}));
	cbm.setCallback("requestMirrorProviderMDIB", "", cbm.defineCallback( [&]() {toc.requestMirrorProviderMDIB();}));
	cbm.setCallback("exit", "", cbm.defineCallback([&]() { exit(0);}));
	auto help = [&]() {
		std::cout << "Available Methods:" << std::endl;
		for(auto callback : cbm.getCallbacks())
		{
			if((callback.first.functionName == "help") || (callback.first.functionName == "Help"))
			{
				continue;
			}
			std::cout << callback.first.functionName << " " << callback.first.args << std::endl;
		}
	};
	cbm.setCallback("help", "", cbm.defineCallback(help));
	cbm.setCallback("Help", "", cbm.defineCallback(help));

	std::cout << "Welcome to the TestOrchestratorConsumer ConsoleApplication. "
				 "If you are here for the first time use help, to get a list of all available functions. \n";



	while(true)
	{
		std::string input = "";
		std::getline (std::cin, input);
		if(input.empty())
		{
			continue;
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






//	std::function<void(std::string)> func = (std::bind(&TestOrchestratorConsumer::setDUTEndpointRef, &toc, std::placeholders::_1));
//	CallbackMap::defineCallback<std::string>(func);
//			cbm.setCallback("discoverDUT", cbm.defineCallback( [&]() {toc.discoverDUT(); }));

}






