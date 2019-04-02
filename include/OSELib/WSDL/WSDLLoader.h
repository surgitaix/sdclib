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

	std::string getGetServiceWSDL();
	std::string getSetServiceWSDL();
	std::string getContextServiceWSDL();
	std::string getStateEventServiceWSDL();
	std::string getWaveformServiceWSDL();

private:

};

}
} /* namespace SDCLib */

#endif /* INCLUDE_WSDL_H_ */
