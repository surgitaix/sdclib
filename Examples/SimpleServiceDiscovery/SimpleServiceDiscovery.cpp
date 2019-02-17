
#include "OSCLib/SDCLibrary.h"
#include "OSELib/SDC/SDCConstants.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Util/DebugOut.h"

#include "OSELib/SDC/ServiceManager.h"

#include "Poco/Thread.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

int main()
{
	const std::string testname("Test SimpleServiceDiscovery");
	DebugOut(DebugOut::Default, "SimpleServiceDiscovery") << std::endl << "Startup: " << testname;
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Debug);

	int loopcounter = 0;
	OSELib::SDC::ServiceManager oscpsm;

	while (loopcounter < 5) {
		DebugOut(DebugOut::Default, "simpleservicediscovery") << "Refreshing ..." << std::flush;
		std::vector<std::unique_ptr<SDCConsumer> > results = oscpsm.discoverOSCP();

		DebugOut(DebugOut::Default, "simpleservicediscovery") << "Found devices with these EPRs: ";

		for (auto & it : results) {

			DebugOut(DebugOut::Default, "simpleservicediscovery") << (*it).getEndpointReference();

		}

		for (auto & it : results) {
			(*it).disconnect();
			it.reset();
		}
		results.clear();
		DebugOut(DebugOut::Default, "simpleservicediscovery") << "Done." << std::endl << std::flush;

		++loopcounter;
	}

	Poco::Thread::sleep(2000);

	DebugOut(DebugOut::Default, "SimpleServiceDiscovery") << "Shutdown: " << testname << std::endl;
}

