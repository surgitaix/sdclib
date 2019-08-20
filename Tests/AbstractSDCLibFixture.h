/*
 * AbstractSDCLibFixture.h
 *
 *  Created on: 23.05.2014
 *      Author: roehser
 */

#ifndef ABSTRACTSDCLIBFIXTURE_H_
#define ABSTRACTSDCLIBFIXTURE_H_

#include <string>

#include "SDCLib/SDCLibrary.h"

#include "OSELib/Helper/WithLogger.h"

namespace SDCLib {
namespace Tests {

struct AbstractSDCLibFixture : public OSELib::Helper::WithLogger
{
public:
	AbstractSDCLibFixture(const std::string & testname, OSELib::LogLevel debuglevel) :
		OSELib::Helper::WithLogger(OSELib::Log::BASE),
		testname(testname)
	{
		log_notice([&]{ return std::string(testname + ":  Startup."); });
		SDCLibrary::getInstance().startup(debuglevel);

	}

	virtual ~AbstractSDCLibFixture() {
		SDCLibrary::getInstance().shutdown();
		log_notice([&]{ return  std::string(testname + ":  Shutdown."); });
	}

public:

    SDCLib::SDCInstance_shared_ptr createSDCInstance()
    {
        // Init SDCInstance
        // Create a new SDCInstance (dont init yet) - give it a new port (just increment)
        auto t_SDCInstance = std::make_shared<SDCInstance>(false);
        // Init
        if(!t_SDCInstance->init()) {
            log_notice([]{ return "Failed to init SDCInstance"; });
            return nullptr;
        }
        // Some restriction
        t_SDCInstance->setIP6enabled(false);
        t_SDCInstance->setIP4enabled(true);
        // Bind it to interface that matches the internal criteria (usually the first enumerated)
        if(!t_SDCInstance->bindToDefaultNetworkInterface()) {
            log_notice([]{ return "Failed to bind SDCInstance to default network interface! Exit..."; });
            return nullptr;
        }
        return t_SDCInstance;
    }

private:
	const std::string testname;
};

}
}

#endif
