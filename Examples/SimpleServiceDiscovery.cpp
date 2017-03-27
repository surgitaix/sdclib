
#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPConstants.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Util/DebugOut.h"

#include "OSELib/OSCP/ServiceManager.h"

#include "Poco/Thread.h"

using namespace OSCLib;
using namespace OSCLib::Util;
using namespace OSCLib::Data::OSCP;

int main()
{
	const std::string testname("Test SimpleServiceDiscovery");
	DebugOut(DebugOut::Default, "SimpleServiceDiscovery") << std::endl << "Startup: " << testname;
	OSCLibrary::getInstance().startup(OSELib::LogLevel::DEBUG);

	int loopcounter = 0;
	OSELib::OSCP::ServiceManager oscpsm;

	while (loopcounter < 5) {
		DebugOut(DebugOut::Default, "simpleservicediscovery") << "Refreshing ..." << std::flush;
		std::vector<std::unique_ptr<OSCPConsumer> > results = oscpsm.discoverOSCP();

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

