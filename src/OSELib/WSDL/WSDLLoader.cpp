/*
 * WSDLLoader.cpp
 *
 *
 *  Created on: 15.03.2019
 *  @author: buerger
 *  @brief: Class for loading the WSDLs for each service
 */

#include "OSELib/WSDL/WSDLLoader.h"
#include "OSCLib/Data/SDC/WSDL/ContextServiceWSDL.h"
#include "OSCLib/Data/SDC/WSDL/GetServiceWSDL.h"
#include "OSCLib/Data/SDC/WSDL/SetServiceWSDL.h"
#include "OSCLib/Data/SDC/WSDL/WaveformServiceWSDL.h"
#include "OSCLib/Data/SDC/WSDL/StateEventServiceWSDL.h"


using namespace OSELib::WSDL;

std::string WSDLLoader::getGetServiceWSDL() const
{
    return getServiceWsdl;
};

std::string WSDLLoader::getSetServiceWSDL() const
{
    return setServiceWsdl;
};

std::string WSDLLoader::getContextServiceWSDL() const
{
    return contextServiceWsdl;
};

std::string WSDLLoader::getStateEventServiceWSDL() const
{
    return stateEventServiceWsdl;
};

std::string WSDLLoader::getWaveformServiceWSDL() const
{
    return waveformServiceWsdl;
};
