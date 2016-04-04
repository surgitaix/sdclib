/*
 * AbstractOSCLibFixture.h
 *
 *  Created on: 23.05.2014
 *      Author: roehser
 */

#ifndef ABSTRACTOSCLIBFIXTURE_H_
#define ABSTRACTOSCLIBFIXTURE_H_

#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Util/DebugOut.h"
#include <string>

namespace OSCLib {
namespace Tests {

struct AbstractOSCLibFixture {
public:
	AbstractOSCLibFixture(const std::string & testname, OSCLib::Util::DebugOut::LogLevel debuglevel, int portStart)
	: testname(testname)
	{
		Util::DebugOut(Util::DebugOut::Default, testname) << "Startup.";
		OSCLibrary::getInstance()->startup(debuglevel);
        OSCLibrary::getInstance()->setPortStart(portStart);
	}

	virtual ~AbstractOSCLibFixture() {
		OSCLibrary::getInstance()->shutdown();
		Util::DebugOut(Util::DebugOut::Default, testname) << "Shutdown." << std::endl;
	}

private:
	const std::string testname;
};

}
}

#endif /* ABSTRACTOSCLIBFIXTURE_H_ */
