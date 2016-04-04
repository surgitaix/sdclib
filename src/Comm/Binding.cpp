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
 *  @file Binding.cpp
 *  @project OSCLib
 *  @date 29.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */

#include "OSCLib/Comm/Binding.h"
#include "OSCLib/Util/DebugOut.h"

#include "Poco/URI.h"

namespace OSCLib {
namespace Comm {

Binding::Binding(const std::string& ip, unsigned int port, const std::string & newPath) : IPBinding(ip, port), path(newPath)
{
	setType(TCP_HTTP);
}

Binding::Binding(const Binding & source) : IPBinding(source), path(source.path)
{

}

Binding::Binding(const std::string & str) : IPBinding("0.0.0.0", 0)
{
	size_t foundHttp = str.find(PROTOCOL_HTTP);
	size_t foundUdp = str.find(PROTOCOL_UDP);
	if (foundHttp == 0 || foundUdp == 0)
	{
		std::string temp = str;
		if (foundHttp == 0)
			temp.replace(0, std::string(PROTOCOL_HTTP).length(), "");
		if (foundUdp == 0)
			temp.replace(0, std::string(PROTOCOL_UDP).length(), "");
			
		if (foundHttp == 0)
			setType(AbstractBinding::TCP_HTTP);
		else if (foundUdp == 0)
			setType(AbstractBinding::UDP);

		Poco::URI uri(str);
		setSocketAddress(Poco::Net::SocketAddress(uri.getHost(), uri.getPort()));

		std::string newPath = uri.getPathAndQuery();
		if (newPath.find("/") == 0) {
			newPath = newPath.substr(1, newPath.size());
		}
		setPath(newPath);
	}
}

Binding::~Binding() {
}

const std::string & Binding::getPath() const {
	return path;
}

void Binding::setPath(const std::string & newPath) {
	this->path = newPath;
}

std::string Binding::toString() const {
	return IPBinding::toString() + "/" + getPath();
}

} /* namespace Comm */
} /* namespace OSCLib */
