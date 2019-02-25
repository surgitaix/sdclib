/*
 * AbstractOSCLibFixture.h
 *
 *  Created on: 23.05.2014
 *      Author: roehser
 */

#ifndef ABSTRACTOSCLIBFIXTURE_H_
#define ABSTRACTOSCLIBFIXTURE_H_

#include <string>

#include "OSCLib/SDCLibrary.h"

#include "OSELib/Helper/WithLogger.h"

namespace SDCLib {
namespace Tests {

struct AbstractOSCLibFixture : public OSELib::WithLogger {
public:
	AbstractOSCLibFixture(const std::string & testname, OSELib::LogLevel debuglevel, SDCPort portStart, SDCPort portRange = SDCLib::Config::SDC_DEFAULT_PORT_RANGE, bool p_shufflePorts = true) :
		WithLogger(OSELib::Log::BASE),
		testname(testname)
	{

        assert(portStart != 0);
        assert(portRange != 0);

		log_notice([&]{ return testname + ":  Startup."; });
		SDCLibrary::getInstance().startup(debuglevel);

        // Init SDCInstance
        // Create a new SDCInstance - dont init yet
        log_notice([]{ return "Create SDCInstance..."; });
        m_SDCInstance = std::make_shared<SDCInstance>(false);

        // Give a warning if there is a mismatch
        if(portStart < SDCLib::Config::SDC_ALLOWED_PORT_START) {
            log_notice([&]{ return "WARNING passed Portstart of " +std::to_string(portStart) + " less than preconfigured value of " + std::to_string(SDCLib::Config::SDC_ALLOWED_PORT_START) + ". This can lead to connection problems if your firewall settings does not match these values!"; });
        }
        if(portRange > SDCLib::Config::SDC_ALLOWED_PORT_RANGE) {
            log_notice([&]{ return "WARNING passed PortRange value of " +std::to_string(portRange) + " greater than preconfigured value of " + std::to_string(SDCLib::Config::SDC_ALLOWED_PORT_RANGE) + ". This can lead to connection problems if your firewall settings does not match these values!"; });
        }
        if((portStart > SDCLib::Config::SDC_ALLOWED_PORT_START) && (portRange >= SDCLib::Config::SDC_ALLOWED_PORT_RANGE)) {
            log_notice([&]{ return "WARNING passed PortRange of [" +std::to_string(portStart) + "," + std::to_string(portStart+portRange) + ") might exceed the preconfigured Portrange of [" +std::to_string(SDCLib::Config::SDC_ALLOWED_PORT_START) + "," + std::to_string(SDCLib::Config::SDC_ALLOWED_PORT_START+SDCLib::Config::SDC_ALLOWED_PORT_RANGE) + ")!"; });
        }

        // Note, one more check needed to check the combination of both parameters // TODO

        // Configure Portrange
        log_notice([&]{ return "Configure Portrange [" +std::to_string(portStart) + "," + std::to_string(portStart+portRange) + ")..."; });
        m_SDCInstance->setPortConfig(portStart, portRange, p_shufflePorts);

        // Init
        log_notice([]{ return "Init SDCInstance..."; });
        if(!m_SDCInstance->init()) {
            log_notice([]{ return "CRITICAL: Failed to init SDCInstance"; });
        }
        // Some restriction
        m_SDCInstance->setIP6enabled(false);
        m_SDCInstance->setIP4enabled(true);
        // Bind it to interface that matches the internal criteria (usually the first enumerated)
        if(!m_SDCInstance->bindToDefaultNetworkInterface()) {
            log_notice([]{ return "Failed to bind SDCInstance to default network interface! Exit..."; });
        }

	}

	virtual ~AbstractOSCLibFixture() {
		SDCLibrary::getInstance().shutdown();
		log_notice([&]{ return testname + ":  Shutdown."; });
	}

public:

    SDCInstance_shared_ptr getSDCInstance() const { return m_SDCInstance; }

private:
	const std::string testname;

    SDCInstance_shared_ptr m_SDCInstance = nullptr;
};

}
}

#endif /* ABSTRACTOSCLIBFIXTURE_H_ */
