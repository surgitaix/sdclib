/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/*
 * OSCPServiceManager.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting
 */

#ifndef OSCPSERVICEMANAGER_H_
#define OSCPSERVICEMANAGER_H_

#include "OSCLib/Data/OSCP/OSCP-fwd.h"

#include <memory>
#include <vector>

namespace OSCLib {

namespace Cli {
class Client;
class HelloReceivedHandler;
}

namespace Data {
namespace OSCP {

class OSCPHelloReceivedHandler {
public:

    OSCPHelloReceivedHandler() {}
    virtual ~OSCPHelloReceivedHandler() {}

	virtual void helloReceived(const std::string & epr);

};

class OSCPServiceManager {
public:

	OSCPServiceManager();
	virtual ~OSCPServiceManager();

	// Todo replace shared_ptr with unique_ptr
	std::shared_ptr<OSCPConsumer> connect(const std::string & xaddr);
    std::shared_ptr<OSCPConsumer> discoverEndpointReference(const std::string & epr);
    std::vector<std::shared_ptr<OSCPConsumer>> discoverOSCP();

    /**
     * @brief Set a handler to receive arbitrary hello messages
     * @param handler The handler
     */
    void setHelloReceivedHandler(OSCPHelloReceivedHandler * handler);

    void helloReceived(std::string epr);

private:
    std::shared_ptr<OSCPConsumer> executeSearch(std::shared_ptr<Cli::Client> client);
    OSCPHelloReceivedHandler * helloHandler;
    std::shared_ptr<Cli::HelloReceivedHandler> internalHelloHandler;
    std::shared_ptr<Cli::Client> internalClient;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* OSCPSERVICEMANAGER_H_ */
