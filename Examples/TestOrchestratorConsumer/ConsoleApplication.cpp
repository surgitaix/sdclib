/*
 * ConsoleApplication.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: rosenau
 */

#include "TestOrchestratorConsumer.h"
#include "CallbackMap.h"

using namespace SDCLib::Data::SDC::ACS;


int main() {
	TestOrchestratorConsumer toc;
	CallbackMap cbm;
	cbm.setCallback("discoverDiscoveryProvider", cbm.defineCallback([&]() { toc.discoverDiscoveryProvider(); }));
	cbm.setCallback("updateAvailableEndpointReferences", cbm.defineCallback( [&]() { toc.updateAvailableEndpointReferences(); }));
	std::function<void(std::string&)> func = (std::bind(&TestOrchestratorConsumer::setDUTEndpointRef, &toc, std::placeholders::_1));
    cbm.defineCallback<std::string>(std::bind(&TestOrchestratorConsumer::setDUTEndpointRef, &toc, std::placeholders::_1));
//			cbm.setCallback("discoverDUT", cbm.defineCallback( [&]() {toc.discoverDUT(); }));

	}






