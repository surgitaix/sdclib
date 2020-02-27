/*
 * PulseOximeterProvider.h
 *
 *  Created on: Jun 19, 2019
 *      Author: rosenau
 */

#ifndef EXAMPLES_PULSEOXIMETERPROVIDER_PULSEOXIMETERPROVIDER_H_
#define EXAMPLES_PULSEOXIMETERPROVIDER_PULSEOXIMETERPROVIDER_H_

#include "SerialConnectionEventHandler.h"
#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdState.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"

#include "SDCLib/Util/Task.h"
#include "SDCLib/Data/SDC/MDIB/custom/MdibContainer.h"
#include "SDCLib/SDCInstance.h"

class PulseOximeterFingerOutGetHandler;
class PulseOximeterSatO2GetHandler;
class PulseOximeterPulseRateGetHandler;
class PulseOximeterAlertSystemState;
class SatO2AlertStateHandle;
class PulseOximeterAlarmLimitPulseRateHandler;
class PulseOximeterAlarmLimitSatO2Handler;
class PulseOximeterAlarmFingerOutHandler;



class PulseOximeterProvider : public SDCLib::Util::Task{
public:
	PulseOximeterProvider(std::shared_ptr<SDCLib::SDCInstance> p_SDCInstance, const std::string& p_port);
	~PulseOximeterProvider();

	void setPort(int port);

	void setEndPointReference(std::string p_endPointReference);

	void startMedicalDevice();

	void startup();
	void shutdown();
	void runImpl() override;

	SDCLib::Data::SDC::MdibContainer getMdib();
	SDCLib::Data::SDC::MdDescription getMdDescription();
	SDCLib::Data::SDC::MdState getMdState();

private:

	void addAlertSystem(SDCLib::Data::SDC::VmdDescriptor &vmdDesc);
	void addPulseRateLimitAlertCondition(SDCLib::Data::SDC::AlertSystemDescriptor &p_alertSystemDesc);
	void addSatO2LimitAlertCondition(SDCLib::Data::SDC::AlertSystemDescriptor &p_alertSystemDesc);
	void addFingerOutAlertCondition(SDCLib::Data::SDC::AlertSystemDescriptor &p_alertSystemDesc);

	SDCLib::Data::SDC::SDCProvider sdcProvider;
	const std::string COMport;

	std::shared_ptr<PulseOximeterFingerOutGetHandler> fingerOutStatusHandler;
	std::shared_ptr<PulseOximeterSatO2GetHandler> satO2GetHandler;
	std::shared_ptr<PulseOximeterPulseRateGetHandler> pulseRateGetHandler;
	std::shared_ptr<PulseOximeterAlarmLimitPulseRateHandler> pulseRateAlarmLimitHandler;
	std::shared_ptr<PulseOximeterAlarmLimitSatO2Handler> satO2AlarmLimitHandler;
	std::shared_ptr<PulseOximeterAlarmFingerOutHandler> fingerAlarmHandler;
	SDCLib::Data::SDC::NumericMetricDescriptor satO2Descriptor;
	SDCLib::Data::SDC::NumericMetricDescriptor pulseRateDescriptor;
	SDCLib::Data::SDC::AlertSystemDescriptor pulseOximeterAlertSystemDescriptor;


	std::shared_ptr<Serial::SerialConnectionEventHandler> serial;
};



#endif /* EXAMPLES_PULSEOXIMETERPROVIDER_PULSEOXIMETERPROVIDER_H_ */
