/*
 * MirrorProvider.h
 *
 *  Created on: Apr 10, 2019
 *      Author: sebastian
 */

#ifndef EXAMPLES_ABSTRACTCONSUMERSIMULATOR_MIRRORPROVIDER_H_
#define EXAMPLES_ABSTRACTCONSUMERSIMULATOR_MIRRORPROVIDER_H_


#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/MDIB/custom/MdibContainer.h"

#include "OSCLib/Util/Task.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

class MirrorProvider : public Util::Task {
public:
	MirrorProvider();
	virtual ~MirrorProvider();

	void setEndpointReference(const std::string & epr);
	void setDeviceCharacteristics(const Dev::DeviceCharacteristics devChar);

	void startup();
	void shutdown();
	void addMdStateHandler(SDCProviderStateHandler * handler);

	virtual void runImpl() override;

	void setMdDescription(const std::string xml);

	MdibContainer getMdib();


private:
	SDCProvider sdcProvider;


};


#endif /* EXAMPLES_ABSTRACTCONSUMERSIMULATOR_MIRRORPROVIDER_H_ */
