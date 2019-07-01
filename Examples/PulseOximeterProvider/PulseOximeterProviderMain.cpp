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
//	std::shared_ptr<Serial::SerialConnectionEventHandler> serial;
//	serial = std::make_shared<Serial::SerialConnectionEventHandler>("/dev/ttyS0", 115200);
//
//	serial->start();
//
//	std::string hex = "7d81a1808080808080";
//
//	int len = hex.length();
//	std::string newString;
//	for(int i=0; i< len; i+=2)
//	{
//	    std::string byte = hex.substr(i,2);
//	    char chr = (char) (int)strtol(byte.c_str(), nullptr, 16);
//	    newString.push_back(chr);
//	}
//	serial->send(newString.c_str(), newString.size());
//
//
//	std::string temp;
//	DebugOut(DebugOut::Default, "ExampleProvider") << "Press key to exit program.";
//	std::cin >> temp;
//	serial->stop();


	// Startup
	DebugOut(DebugOut::Default, "ExampleProvider") << "Startup" << std::endl;
    SDCLibrary::getInstance().startup(OSELib::LogLevel::Warning);

    // Create a new SDCInstance (no flag will auto init)
    auto t_SDCInstance = std::make_shared<SDCInstance>(Config::SDC_DEFAULT_MDPWS_PORT, true);
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
