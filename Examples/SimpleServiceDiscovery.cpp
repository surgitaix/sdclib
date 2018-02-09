
#include "OSCLib/SDCLibrary.h"
#include "OSELib/OSCP/SDCConstants.h"
#include "OSCLib/Data/OSCP/SDCConsumer.h"
#include "OSCLib/Data/OSCP/SDCProvider.h"
#include "OSCLib/Util/DebugOut.h"

#include "OSELib/OSCP/ServiceManager.h"

#include "Poco/Thread.h"

using namespace OSCLib;
using namespace OSCLib::Util;
using namespace OSCLib::Data::SDC;

int main()
{
	const std::string testname("Test SimpleServiceDiscovery");
	DebugOut(DebugOut::Default, "SimpleServiceDiscovery") << std::endl << "Startup: " << testname;
	SDCLibrary::getInstance().startup(OSELib::LogLevel::DEBUG);

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

