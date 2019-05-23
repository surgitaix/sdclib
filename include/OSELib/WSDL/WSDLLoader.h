/*
 * WSDLLoader.h
 *
 *
 *  Created on: 15.03.2019
 *  @author: buerger
 *  @brief: Class for loading the WSDLs for each service from hard drive
 */

#ifndef INCLUDE_WSDL_H_
#define INCLUDE_WSDL_H_

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
            std::string getContextServiceWSDL() const;
            std::string getStateEventServiceWSDL() const;
            std::string getWaveformServiceWSDL() const;
        };
    }
}

#endif /* INCLUDE_WSDL_H_ */
