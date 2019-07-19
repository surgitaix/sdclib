#include <iostream>
#include "SDCLib/SDCLibrary.h"
#include "SDCLib/SDCInstance.h"
#include "SDCLib/Util/DebugOut.h"

#include "PulseOximeterProvider.h"
#include "SerialConnectionEventHandler.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

int main(int argc, char* argv[])
{

	// Startup
	DebugOut(DebugOut::Default, "ExampleProvider") << "Startup" << std::endl;
    SDCLibrary::getInstance().startup(OSELib::LogLevel::Warning);

    // Create a new SDCInstance (no flag will auto init)
    auto t_SDCInstance = std::make_shared<SDCInstance>();
    // Some restriction
    t_SDCInstance->setIP6enabled(false);
    t_SDCInstance->setIP4enabled(true);
    // Bind it to interface that matches the internal criteria (usually the first enumerated)
    if(!t_SDCInstance->bindToDefaultNetworkInterface()) {
        std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
        return -1;
    }

	PulseOximeterProvider provider(t_SDCInstance);
	provider.startMedicalDevice();
	provider.startup();
	provider.start();

	std::string temp;
	DebugOut(DebugOut::Default, "ExampleProvider") << "Press key to exit program.";
	std::cin >> temp;

	// Shutdown
	DebugOut(DebugOut::Default, "ExampleProvider") << "Shutdown." << std::endl;
	provider.shutdown();
    SDCLibrary::getInstance().shutdown();
}
