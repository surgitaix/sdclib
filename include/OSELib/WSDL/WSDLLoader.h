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

namespace OSELib {
namespace WSDL {

class WSDLLoader {
public:
	WSDLLoader();
	virtual ~WSDLLoader();

	std::string loadGetServiceWSDL();
	std::string loadSetServiceWSDL();
	std::string loadContextServiceWSDL();
	std::string loadStateEventServiceWSDL();
	std::string loadWaveformServiceWSDL();

private:

};

}
} /* namespace SDCLib */

#endif /* INCLUDE_WSDL_H_ */
