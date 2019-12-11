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
#include "SDCLib/SDCInstance.h"

#include "OSELib/Helper/WithLogger.h"

namespace SDCLib {
namespace Tests {

struct AbstractSDCLibFixture : public OSELib::Helper::WithLogger
{
public:
	AbstractSDCLibFixture(const std::string & p_testname, OSELib::LogLevel debuglevel)
	: OSELib::Helper::WithLogger(OSELib::Log::BASE),
	  testname(p_testname)
	{
		log_notice([&]{ return std::string(testname + ":  Startup."); });
		SDCLibrary::getInstance().startup(debuglevel);

	}

	virtual ~AbstractSDCLibFixture()
	{
		log_notice([&]{ return  std::string(testname + ":  Shutdown."); });
	}

public:

    SDCLib::SDCInstance_shared_ptr createSDCInstance()
    {
        return SDCInstance::createSDCInstance();
    }

private:
	const std::string testname;
};

}
}

#endif
