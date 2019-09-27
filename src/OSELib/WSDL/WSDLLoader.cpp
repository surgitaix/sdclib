/*
 * WSDLLoader.cpp
 *
 *
 *  Created on: 15.03.2019
 *  @author: buerger
 *  @brief: Class for loading the WSDLs for each service
 *  Modified on: 26.09.2019, baumeister
 */

#include "OSELib/WSDL/WSDLLoader.h"
#include "OSELib/WSDL/GetServiceWSDL.h"
#include "OSELib/WSDL/SetServiceWSDL.h"
#include "OSELib/WSDL/BICEPSServiceWSDL.h"


namespace OSELib
{
namespace WSDL
{


std::string WSDLLoader::getGetServiceWSDL() const
{
    return getServiceWsdl;
}

std::string WSDLLoader::getSetServiceWSDL() const
{
    return setServiceWsdl;
}
std::string WSDLLoader::getBICEPSServiceWSDL() const
{
    return BICEPSServiceWsdl;
}
}
}
