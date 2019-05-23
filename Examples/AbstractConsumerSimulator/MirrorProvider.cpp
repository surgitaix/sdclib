/*
 * MirrorProvider.cpp
 *
 *  Created on: Apr 10, 2019
 *      Author: sebastian
 */

#include "MirrorProvider.h"
#include <Poco/Thread.h>

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

MirrorProvider::MirrorProvider(SDCInstance_shared_ptr p_SDCInstance) : sdcProvider(p_SDCInstance) {

}

MirrorProvider::~MirrorProvider() {
}

//forwarding of the startup function
void MirrorProvider::startup() {
	sdcProvider.startup();
}

//forwarding of the shutdown function
void MirrorProvider::shutdown() {
	sdcProvider.shutdown();
}

//forwarding of the addMdStateHandler function
void MirrorProvider::addMdStateHandler(SDCProviderStateHandler *handler) {
	sdcProvider.addMdStateHandler(handler);
}

void MirrorProvider::setMdDescription(std::string xml) {
	sdcProvider.setMdDescription(xml);
}

void MirrorProvider::setEndpointReference(const std::string & epr) {
	sdcProvider.setEndpointReference(epr);
}

void MirrorProvider::setDeviceCharacteristics(Dev::DeviceCharacteristics devChar)
{
	sdcProvider.setDeviceCharacteristics(devChar);
}

void MirrorProvider::runImpl() {
	while(!isInterrupted()) {
		Poco::Thread::sleep(1000);
	}
}

MdibContainer MirrorProvider::getMdib() {
	return sdcProvider.getMdib();
}
