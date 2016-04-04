/*
 * HelloReceivedHandler.h
 *
 *  Created on: 07.10.2015
 *      Author: osclib
 */

#ifndef INCLUDE_OSCLIB_CLI_HELLORECEIVEDHANDLER_H_
#define INCLUDE_OSCLIB_CLI_HELLORECEIVEDHANDLER_H_

namespace OSCLib {
namespace Cli {

class HelloReceivedHandler {
public:

	HelloReceivedHandler() {}
	virtual ~HelloReceivedHandler() {}

	virtual void helloReceived(const std::string & epr) = 0;
};

}
}

#endif /* INCLUDE_OSCLIB_CLI_HELLORECEIVEDHANDLER_H_ */
