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
 *  @file SoapHeader.h
 *  @project OSCLib
 *  @date 08.07.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#ifndef SOAPHEADER_H_
#define SOAPHEADER_H_

#include "XMLEntity.h"
#include <string>

namespace OSCLib {

namespace Dev {
	class Device;
}

namespace Comm {
namespace Soap {

class SoapHeader : public XMLEntity {
public:
	SoapHeader(XMLEntity * parent);
    SoapHeader(rapidxml::xml_node<>* node) : XMLEntity(node) {};
	virtual ~SoapHeader();

	XMLEntity * addAction(const std::string & action);
	std::string addMessageID(const std::string & msgId = "");
	XMLEntity * addFrom(const std::string & from);
	XMLEntity * addTo(const std::string & to);
	XMLEntity * addReplyTo(const std::string & reply);
	XMLEntity * addFaultTo(const std::string & fault);
	XMLEntity * addAppSequence(const Dev::Device & device);
	XMLEntity * addRelatesTo(const std::string & to);
};

} /* namespace Soap */
} /* namespace Comm */
} /* namespace OSCLib */
#endif /* SOAPHEADER_H_ */
