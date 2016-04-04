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

/**
 *  @file IPBinding.h
 *  @project OSCLib
 *  @date 24.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#ifndef IPBINDING_H_
#define IPBINDING_H_

#include "AbstractBinding.h"
#include "Poco/Net/SocketAddress.h"

namespace OSCLib {

namespace Comm {

class IPBinding: public OSCLib::Comm::AbstractBinding {
public:
	const std::string PROTOCOL_HTTP;
	const std::string PROTOCOL_UDP;

	IPBinding(const std::string & ip, unsigned int port);
	IPBinding(const IPBinding & source);
	IPBinding(const Poco::Net::SocketAddress sa);
	virtual ~IPBinding();
    const std::string getIp() const;
    unsigned int getPort() const;
    std::string getPortStr() const;
    virtual std::string toString() const ;

    void setSocketAddress(const Poco::Net::SocketAddress sa);

private:
	Poco::Net::SocketAddress socketAddress;
};

} /* namespace Comm */
} /* namespace OSCLib */
#endif /* IPBINDING_H_ */
