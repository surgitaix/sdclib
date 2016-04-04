/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/**
 *  @file OSCPDevice.h
 *  @project OSCLib
 *  @date 24.01.2014
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */

#ifndef OSCPDEVICE_H_
#define OSCPDEVICE_H_

#include "OSCLib/Dev/Device.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "OSCLib/Data/OSCP/MDIB/MDIB-fwd.h"
#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"

namespace OSCLib {

namespace Comm {
class AbstractBinding;
}

namespace Dev {

class DeviceCharacteristics;

namespace OSCP {

class CDMWavService;

/**
 * @brief An instance of this class represents an OSCP medical device.
 */
class OSCPDevice {
public:
	OSCPDevice(Data::OSCP::OSCPProvider & provider);
	virtual ~OSCPDevice();

	void start();
	void stop();

	void prepareOSCPDevice(const Data::OSCP::OSCPProvider & provider);

    /**
    * @brief Notify all registered consumers about an operation invoked event (fires operation invoked event).
    *
    * @param object The MDIB object
    */

	void notifyEvent(const CDM::WaveformStream & wfs);
	void notifyEvent(const CDM::EpisodicAlertReport & report);
    void notifyEvent(const CDM::EpisodicContextChangedReport & report);
    void notifyEvent(const CDM::EpisodicMetricReport & report);
    void notifyEvent(const CDM::OperationInvokedReport & report);
    void notifyEvent(const CDM::PeriodicAlertReport & report);
    void notifyEvent(const CDM::PeriodicContextChangedReport & report);
    void notifyEvent(const CDM::PeriodicMetricReport & report);

	const Dev::DeviceCharacteristics& getDeviceCharacteristics() const;
	void setDeviceCharacteristics(const Dev::DeviceCharacteristics& deviceCharacteristics);
	void addStreamBinding(std::shared_ptr<OSCLib::Comm::AbstractBinding> bnd, const std::string handle);

private:
	template<class T> T * getEventSource();

	Device device;
	OSCLib::Data::OSCP::OSCPProvider & provider;
	std::shared_ptr<OSCLib::Dev::OSCP::CDMWavService> streamingService;
};

} /* namespace OSCB */
} /* namespace Dev */
} /* namespace OSCLib */
#endif /* OSCBDEVICE_H_ */
