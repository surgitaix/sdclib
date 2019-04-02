/*
 * WSDLLoader.cpp
 *
 *
 *  Created on: 15.03.2019
 *  @author: buerger
 *  @brief: Class for loading the WSDLs for each service from hard drive
 */

#include "OSELib/WSDL/WSDLLoader.h"
#include "OSCLib/Data/SDC/WSDL/ContextServiceWSDL.h"
#include "OSCLib/Data/SDC/WSDL/GetServiceWSDL.h"
#include "OSCLib/Data/SDC/WSDL/SetServiceWSDL.h"
#include "OSCLib/Data/SDC/WSDL/WaveformServiceWSDL.h"
#include "OSCLib/Data/SDC/WSDL/StateEventServiceWSDL.h"
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

std::string WSDLLoader::getGetServiceWSDL() {
	return getServiceWsdl;

};

std::string WSDLLoader::getSetServiceWSDL() {
	return setServiceWsdl;
};

std::string WSDLLoader::getContextServiceWSDL() {
	return contextServiceWsdl;
};

std::string WSDLLoader::getStateEventServiceWSDL() {
	return stateEventServiceWsdl;
};

std::string WSDLLoader::getWaveformServiceWSDL() {
	return waveformServiceWsdl;
};


}
} /* namespace SDCLib */
