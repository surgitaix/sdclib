/*
 * AbstractOSCLibFixture.h
 *
 *  Created on: 23.05.2014
 *      Author: roehser
 */

#ifndef ABSTRACTOSCLIBFIXTURE_H_
#define ABSTRACTOSCLIBFIXTURE_H_

#include <string>

#include "OSCLib/OSCLibrary.h"

#include "OSELib/Helper/WithLogger.h"

namespace OSCLib {
namespace Tests {

struct AbstractOSCLibFixture : public OSELib::WithLogger {
public:
	AbstractOSCLibFixture(const std::string & testname, OSELib::LogLevel debuglevel, int portStart) :
		WithLogger(OSELib::Log::BASE),
		testname(testname)
	{
		log_notice([&]{ return testname + ":  Startup."; });
		OSCLibrary::getInstance().startup(debuglevel);
        OSCLibrary::getInstance().setPortStart(portStart);
	}

	virtual ~AbstractOSCLibFixture() {
		OSCLibrary::getInstance().shutdown();
		log_notice([&]{ return testname + ":  Shutdown."; });
	}

private:
	const std::string testname;
};

}
}

#endif /* ABSTRACTOSCLIBFIXTURE_H_ */
