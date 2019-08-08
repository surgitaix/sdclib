/*
 * MirrorProvider.cpp
 *
 *  Created on: Apr 10, 2019
 *      Author: rosenau
 */

#include "MirrorProvider.h"
#include <Poco/Thread.h>

namespace SDCLib {
namespace Data {
namespace SDC {
namespace ACS {

MirrorProvider::MirrorProvider(SDCInstance_shared_ptr p_SDCInstance) : sdcProvider(p_SDCInstance) {

}

const std::string MirrorProvider::getEndpointReference()
{
	return sdcProvider.getEndpointReference();
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

MdDescription MirrorProvider::getMdDescription() const
{
    return sdcProvider.getMdDescription();
}


void MirrorProvider::setMdDescription(MdDescription& description)
{
	sdcProvider.setMdDescription(description);
}

void MirrorProvider::setEndpointReference(const std::string & epr) {
	sdcProvider.setEndpointReferenceByName(epr);
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


void MirrorProvider::addActivateOperationForDescriptor(const ActivateOperationDescriptor &descriptor, MdsDescriptor & ownerMDS)
{
	sdcProvider.addActivateOperationForDescriptor(descriptor, ownerMDS);
}


} //ACS
} //SDC
} //Data
} //SDCLib
