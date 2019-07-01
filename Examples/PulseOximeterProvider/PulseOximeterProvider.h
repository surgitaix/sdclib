/*
 * PulseOximeterProvider.h
 *
 *  Created on: Jun 19, 2019
 *      Author: sebastian
 */

#ifndef EXAMPLES_PULSEOXIMETERPROVIDER_PULSEOXIMETERPROVIDER_H_
#define EXAMPLES_PULSEOXIMETERPROVIDER_PULSEOXIMETERPROVIDER_H_

#include "SerialConnectionEventHandler.h"
#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/MdState.h"

#include "SDCLib/Util/Task.h"
#include "SDCLib/Data/SDC/MDIB/custom/MdibContainer.h"
#include "SDCLib/SDCInstance.h"


class PulseOximeterSatO2GetHandler;
class PulseOximeterPulseRateGetHandler;
class PulseOximeterSetLowerAlarmLimitPulseRateHandler;
class PulseOximeterSetUpperAlarmLimitPulseRateHandler;
class PulseOximeterSetLowerAlarmLimitSatO2Handler;
class PulseOximeterSetUpperAlarmLimitSatO2Handler;

class PulseOximeterProvider : public SDCLib::Util::Task{
public:
	PulseOximeterProvider(std::shared_ptr<SDCLib::SDCInstance> p_SDCInstance);
	virtual ~PulseOximeterProvider();

	void setPort(int port);

	void setEndPointReference(std::string endPointReference);

	void startMedicalDevice();

	void startup();
	void shutdown();
	virtual void runImpl() override;

	SDCLib::Data::SDC::MdibContainer getMdib();
	SDCLib::Data::SDC::MdDescription getMdDescription();
	SDCLib::Data::SDC::MdState getMdState();

private:

	SDCLib::Data::SDC::SDCProvider sdcProvider;

	std::shared_ptr<PulseOximeterSatO2GetHandler> satO2GetHandler;
	std::shared_ptr<PulseOximeterPulseRateGetHandler> pulseRateGetHandler;
	std::shared_ptr<PulseOximeterSetLowerAlarmLimitPulseRateHandler> pulseRateLowerAlarmLimitSetHandler;
	std::shared_ptr<PulseOximeterSetUpperAlarmLimitPulseRateHandler> pulseRateUpperAlarmLimitSetHandler;
	std::shared_ptr<PulseOximeterSetUpperAlarmLimitSatO2Handler> satO2UpperAlarmLimitSetHandler;
	std::shared_ptr<PulseOximeterSetLowerAlarmLimitSatO2Handler> satO2LowerAlarmLimitSetHandler;
	SDCLib::Data::SDC::NumericMetricDescriptor satO2Descriptor;
	SDCLib::Data::SDC::NumericMetricDescriptor pulseRateDescriptor;
	SDCLib::Data::SDC::NumericMetricDescriptor pulseRateUpperAlarmLimitDescriptor;
	SDCLib::Data::SDC::NumericMetricDescriptor pulseRateLowerAlarmLimitDescriptor;
	SDCLib::Data::SDC::NumericMetricDescriptor satO2LowerAlarmLimitDescriptor;
	SDCLib::Data::SDC::NumericMetricDescriptor satO2UpperAlarmLimitDescriptor;

	std::shared_ptr<Serial::SerialConnectionEventHandler> serial;
};



#endif /* EXAMPLES_PULSEOXIMETERPROVIDER_PULSEOXIMETERPROVIDER_H_ */
