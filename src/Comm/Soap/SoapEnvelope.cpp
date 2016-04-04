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
 *  @file SoapEnvelope.cpp
 *  @project OSCLib
 *  @date 08.07.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */

#include "OSCLib/Comm/Soap/SoapBody.h"
#include "OSCLib/Comm/Soap/SoapEnvelope.h"
#include "OSCLib/Comm/Soap/SoapHeader.h"
#include "OSCLib/Dev/EndpointReference.h"

namespace OSCLib {
namespace Comm {
namespace Soap {

SoapEnvelope::SoapEnvelope() : header(new SoapHeader(this)), body(new SoapBody(this))
{
	setName("soap:Envelope");
	addNamespace("soap", "http://www.w3.org/2003/05/soap-envelope");
}

SoapEnvelope::SoapEnvelope(const SoapEnvelope& e) : XMLEntity(e) {
    header = new SoapHeader(this->getNode()->first_node("soap:Header"));
    body = new SoapBody(this->getNode()->first_node("soap:Body"));
}

SoapEnvelope::~SoapEnvelope() {
	delete header;
	delete body;
}

SoapBody * SoapEnvelope::getBody() const {
	return body;
}

SoapHeader * SoapEnvelope::getHeader() const {
	return header;
}

} /* namespace Soap */
} /* namespace Comm */
} /* namespace OSCLib */
