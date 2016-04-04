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
 *  @file EndpointReference.cpp
 *  @project OSCLib
 *  @date 16.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#include "OSCLib/Dev/EndpointReference.h"

namespace OSCLib {
namespace Dev {

EndpointReference::EndpointReference() : eprAdr("N/A")
{

}

EndpointReference::~EndpointReference()
{
}

const std::string & EndpointReference::getMetaData() const
{
	return metaData;
}

const std::string & EndpointReference::getReferenceParameters() const
{
	return referenceParameters;
}

const std::string & EndpointReference::getAddress() const
{
	return eprAdr;
}

void EndpointReference::setAddress(const std::string & adr)
{
	this->eprAdr = adr;
}

void EndpointReference::setMetaData(const std::string & metaData)
{
	this->metaData = metaData;
}

void EndpointReference::setReferenceParameters(const std::string & referenceParameters)
{
	this->referenceParameters = referenceParameters;
}

} /* namespace Device */
} /* namespace OSCLib */
