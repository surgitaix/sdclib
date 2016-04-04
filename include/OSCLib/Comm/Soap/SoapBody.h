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
 *  @file SoapBody.h
 *  @project OSCLib
 *  @date 08.07.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#ifndef SOAPBODY_H_
#define SOAPBODY_H_

#include "XMLEntity.h"

namespace OSCLib {
namespace Comm {
namespace Soap {

class SoapBody : public XMLEntity {
public:
	SoapBody(XMLEntity * parent);
    SoapBody(rapidxml::xml_node<>* node) : XMLEntity(node) {};
	virtual ~SoapBody();
};

} /* namespace Soap */
} /* namespace Comm */
} /* namespace OSCLib */
#endif /* SOAPBODY_H_ */
