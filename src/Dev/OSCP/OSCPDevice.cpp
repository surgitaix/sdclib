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
 *  @file OSCPDevice.cpp
 *  @project OSCLib
 *  @date 24.01.2014
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */

#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Comm/CommunicationManager.h"
#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Data/OSCP/OSCPConstants.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/Operations/CDMEventSource.h"
#include "OSCLib/Dev/DeviceCharacteristics.h"
#include "OSCLib/Dev/OSCP/CDMContextService.h"
#include "OSCLib/Dev/OSCP/CDMEvtService.h"
#include "OSCLib/Dev/OSCP/CDMGetService.h"
#include "OSCLib/Dev/OSCP/CDMSetService.h"
#include "OSCLib/Dev/OSCP/CDMWavService.h"
#include "OSCLib/Dev/OSCP/OSCPDevice.h"

#include <memory>

namespace OSCLib {
namespace Dev {
namespace OSCP {

OSCPDevice::OSCPDevice(OSCLib::Data::OSCP::OSCPProvider & provider) : provider(provider) {
	device.addService(std::shared_ptr<OSCLib::Dev::OSCP::CDMContextService>(new OSCLib::Dev::OSCP::CDMContextService(provider)));
	device.addService(std::shared_ptr<OSCLib::Dev::OSCP::CDMEvtService>(new OSCLib::Dev::OSCP::CDMEvtService()));
	device.addService(std::shared_ptr<OSCLib::Dev::OSCP::CDMGetService>(new OSCLib::Dev::OSCP::CDMGetService(provider)));
	device.addService(std::shared_ptr<OSCLib::Dev::OSCP::CDMSetService>(new OSCLib::Dev::OSCP::CDMSetService(provider)));
	streamingService = std::shared_ptr<OSCLib::Dev::OSCP::CDMWavService>(new OSCLib::Dev::OSCP::CDMWavService());
	device.addService(streamingService);
}

OSCPDevice::~OSCPDevice() {
    OSCLibrary * lib = OSCLibrary::getInstance();
    if (lib->isInitialized() && device.isRunning()) {
        const Comm::CommunicationManager * cm = device.getDefaultCommunicationManager(Comm::DPWS::DPWS11);
        if (cm != nullptr && lib->getNetInterface()->isValidUnicastCallback(cm))
        {
        	provider.shutdown();
            Util::DebugOut(Util::DebugOut::Error, "OSCPProvider") << "OSCPProvider deleted before shutdown!";
        }
    }
}

void OSCPDevice::start() {
	device.start();
}

void OSCPDevice::stop() {
	device.stop();
}

void OSCPDevice::prepareOSCPDevice(const Data::OSCP::OSCPProvider & provider) {
    device.addType(Data::QName("MedicalDevice", Data::OSCP::NS_MESSAGE_MODEL));
    device.addType(Data::QName("MedicalDevice", "http://www.draeger.com/projects/DSC/CMDM/2012/05"));

    if (provider.getEndpointReference() == "") {
    	throw std::runtime_error("Provider needs an endpoint reference!");
    }

    device.setEPRAddress(provider.getEndpointReference());

    // TODO Map contexts to scopes
}

template<class T> T * OSCPDevice::getEventSource() {
    Poco::Mutex::ScopedLock lockDevice(device.getServicesMutex());
    size_t sSize = device.getServiceCount();
    for (size_t i = 0; i < sSize; ++i) {
        auto & nextService = device.getService(i);
        for (const auto &operation : nextService->getOperations()) {
            if (T * pointer = dynamic_cast<T *>(operation.get())) {
                return pointer;
            }
        }
    }
	return nullptr;
}

void OSCPDevice::notifyEvent(const CDM::WaveformStream & wfs) {
	Data::OSCP::CDMWaveformStreamSource * wss = getEventSource<Data::OSCP::CDMWaveformStreamSource>();
	if (wss != nullptr) {
		for (const auto & nextState : wfs.RealTimeSampleArray()) {
			wss->notifyAll(wfs, nextState.DescriptorHandle());
		}
		return;
	}
}


void OSCPDevice::notifyEvent(const CDM::EpisodicAlertReport & report) {
	Data::OSCP::CDMEpisodicAlertEventSource * ear = getEventSource<Data::OSCP::CDMEpisodicAlertEventSource>();
	if (ear != nullptr) {
		ear->notify(report);
		return;
	}
}

void OSCPDevice::notifyEvent(const CDM::EpisodicContextChangedReport & object) {
	Data::OSCP::CDMEpisodicContextChangedEventSource * source = getEventSource<Data::OSCP::CDMEpisodicContextChangedEventSource>();
	if (source != nullptr) {
		source->notify(object);
		return;
	}
}

void OSCPDevice::notifyEvent(const CDM::EpisodicMetricReport & object) {
	Data::OSCP::CDMEpisodicMetricEventSource * emr = getEventSource<Data::OSCP::CDMEpisodicMetricEventSource>();
	if (emr != nullptr) {
		emr->notify(object);
		return;
	}
}

void OSCPDevice::notifyEvent(const CDM::OperationInvokedReport & report) {
	Data::OSCP::CDMOperationInvokedReportSource * op = getEventSource<Data::OSCP::CDMOperationInvokedReportSource>();
	if (op != nullptr) {
		op->notify(report);
	}
}

void OSCPDevice::notifyEvent(const CDM::PeriodicAlertReport & report) {
	Data::OSCP::CDMPeriodicAlertEventSource * op = getEventSource<Data::OSCP::CDMPeriodicAlertEventSource>();
	if (op != nullptr) {
		op->notify(report);
	}
}


void OSCPDevice::notifyEvent(const CDM::PeriodicContextChangedReport & report) {
	Data::OSCP::CDMPeriodicContextChangedEventSource * op = getEventSource<Data::OSCP::CDMPeriodicContextChangedEventSource>();
	if (op != nullptr) {
		op->notify(report);
	}
}

void OSCPDevice::notifyEvent(const CDM::PeriodicMetricReport & report) {
	Data::OSCP::CDMPeriodicMetricEventSource * op = getEventSource<Data::OSCP::CDMPeriodicMetricEventSource>();
	if (op != nullptr) {
		op->notify(report);
	}
}

const Dev::DeviceCharacteristics& OSCPDevice::getDeviceCharacteristics() const {
	return device.getDeviceCharacteristics();
}

void OSCPDevice::setDeviceCharacteristics(const Dev::DeviceCharacteristics& deviceCharacteristics) {
	device.setDeviceCharacteristics(deviceCharacteristics);
}

void OSCPDevice::addStreamBinding(std::shared_ptr<OSCLib::Comm::AbstractBinding> bnd, const std::string handle) {
	// Add to device's MDPWS protocol
	device.addBinding(OSCLib::Comm::DPWS::MDPWS, bnd);
	// Add to streaming service 'handle' protocol
	streamingService->addBinding(handle, bnd);
}

} /* namespace OSCP */
} /* namespace Dev */
} /* namespace OSCLib */
