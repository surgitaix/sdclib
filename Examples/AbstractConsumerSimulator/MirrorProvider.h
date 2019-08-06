/*
 * MirrorProvider.h
 *
 *  Created on: Apr 10, 2019
 *      Author: rosenau
 */

#ifndef EXAMPLES_ABSTRACTCONSUMERSIMULATOR_MIRRORPROVIDER_H_
#define EXAMPLES_ABSTRACTCONSUMERSIMULATOR_MIRRORPROVIDER_H_

#include "SDCLib/SDCInstance.h"

#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Data/SDC/MDIB/custom/MdibContainer.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"

#include "SDCLib/Util/Task.h"

namespace SDCLib {
namespace Data {
namespace SDC {
namespace ACS {

class MirrorProvider : public Util::Task {
public:
	MirrorProvider(SDCInstance_shared_ptr p_SDCInstance);
	virtual ~MirrorProvider() = default;

	void setEndpointReference(const std::string & epr);
	const std::string getEndpointReference();

	void setDeviceCharacteristics(const Dev::DeviceCharacteristics devChar);

	template<typename T>
	void createSetOperationForDescriptor(const T& descriptor, MdsDescriptor & ownerMDS)
	{
		sdcProvider.createSetOperationForDescriptor(descriptor, ownerMDS);
	}

    void addActivateOperationForDescriptor(const ActivateOperationDescriptor& descriptor, MdsDescriptor & ownderMDS);

	void startup();
	void shutdown();
	void addMdStateHandler(SDCProviderStateHandler * handler);

	virtual void runImpl() override;

	void setMdDescription(const std::string xml);
	void setMdDescription(MdDescription& description);

    MdDescription getMdDescription() const;



	MdibContainer getMdib();


private:
	SDCProvider sdcProvider;


};
} //ACS
} //SDC
} //Data
} //SDCLib

#endif /* EXAMPLES_ABSTRACTCONSUMERSIMULATOR_MIRRORPROVIDER_H_ */
