#include <iostream>
#include "SerialConnectionEventHandler.h"

using namespace Serial;

int main(int argc, char* argv[])
{
    try {

    	std::shared_ptr<SerialConnectionEventHandler> serial = std::shared_ptr<SerialConnectionEventHandler>(new SerialConnectionEventHandler("/dev/ttyS0", 115200));

    	serial->start();

		std::string hex = "7d81a1808080808080";

		int len = hex.length();
		std::string newString;
		for(int i=0; i< len; i+=2)
		{
		    std::string byte = hex.substr(i,2);
		    char chr = (char) (int)strtol(byte.c_str(), nullptr, 16);
		    newString.push_back(chr);
		}
		serial->send(newString.c_str(), newString.size());
    	while(true)
    	{

    	}
    	serial->stop();

    } catch(std::system_error& e)
    {
        //std::cout<< "Error: "<<e.what()<<endl;
        return 1;
    }
}
