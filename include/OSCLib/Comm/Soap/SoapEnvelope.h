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
 *  @file SoapEnvelope.h
 *  @project OSCLib
 *  @date 08.07.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#ifndef SOAPENVELOPE_H_
#define SOAPENVELOPE_H_

#include "XMLEntity.h"

namespace OSCLib {
namespace Comm {
namespace Soap {

class SoapBody;
class SoapHeader;

class SoapEnvelope : public XMLEntity {
public:
	SoapEnvelope();
    SoapEnvelope(const SoapEnvelope& e);
	virtual ~SoapEnvelope();

    SoapBody * getBody() const;
    SoapHeader * getHeader() const;

private:
	SoapHeader * header;
	SoapBody * body;
};

} /* namespace Soap */
} /* namespace Comm */
} /* namespace OSCLib */

#endif /* SOAPENVELOPE_H_ */
