/*
 * WSDLLoader.cpp
 *
 *
 *  Created on: 15.03.2019
 *  @author: buerger
 *  @brief: Class for loading the WSDLs for each service from hard drive
 */

#include "OSELib/WSDL/WSDLLoader.h"
#include <sstream>
#include <fstream>
#include <iostream>


namespace OSELib {
namespace WSDL {

WSDLLoader::WSDLLoader()
{
}

WSDLLoader::~WSDLLoader() {

}

std::string WSDLLoader::loadGetServiceWSDL() {
	std::ifstream t("ressources/wsdl/getservice.wsdl");
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();

};

std::string WSDLLoader::loadSetServiceWSDL() {
	std::ifstream t("ressources/wsdl/setservice.wsdl");
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
};

std::string WSDLLoader::loadContextServiceWSDL() {
	std::ifstream t("ressources/wsdl/contextservice.wsdl");
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
};

std::string WSDLLoader::loadStateEventServiceWSDL() {
	std::ifstream t("ressources/wsdl/stateeventservice.wsdl");
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
};

std::string WSDLLoader::loadWaveformServiceWSDL() {
	std::ifstream t("ressources/wsdl/waveformservice.wsdl");
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
};


}
} /* namespace SDCLib */
