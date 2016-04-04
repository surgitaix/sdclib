/*
 * OSCPConsumerContextStateChangedHandler.h
 *
 *  Created on: 01.06.2015
 *      Author: roehser
 */

#ifndef OSCLIB_DATA_OSCP_OSCPCONSUMERCONTEXTSTATECHANGEDHANDLER_H_
#define OSCLIB_DATA_OSCP_OSCPCONSUMERCONTEXTSTATECHANGEDHANDLER_H_

#include <string>

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPConsumerContextStateChangedHandler {
public:
    virtual ~OSCPConsumerContextStateChangedHandler() {
    }

    /**
    * @brief This method will be called if any context state changes.
    */
    virtual void onContextStateChanged(const std::vector<std::string> & handles) = 0;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */




#endif /* OSCLIB_DATA_OSCP_OSCPCONSUMERCONTEXTSTATECHANGEDHANDLER_H_ */
