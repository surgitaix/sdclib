/*
 * WSDLLoader.h
 *
 *
 *  Created on: 15.03.2019
 *  @author: buerger
 *  @brief: Class for loading the WSDLs for each service
 *  Modified on: 26.09.2019, baumeister
 */

#ifndef OSELIB_WSDL_WSDLLOADER_H_
#define OSELIB_WSDL_WSDLLOADER_H_

#include <string>

namespace OSELib
{
    namespace WSDL
    {
        class WSDLLoader {
        public:
            WSDLLoader() = default;
            ~WSDLLoader() = default;

            std::string getGetServiceWSDL() const;
            std::string getSetServiceWSDL() const;
            std::string getBICEPSServiceWSDL() const;
        };
    }
}

#endif
