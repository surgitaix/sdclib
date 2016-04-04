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
 *  @file Entity.h
 *  @project OSCLib
 *  @date 03.01.2012
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#ifndef ENTITY_H_
#define ENTITY_H_

#include "EndpointReference.h"
#include "OSCLib/Data/QName.h"
#include "OSCLib/Util/StringVector.h"
#include <memory>
#include <map>

namespace OSCLib {
namespace Comm {
	class AbstractBinding;
	class IPBinding;
}

typedef std::map<std::string, std::vector<std::shared_ptr<Comm::AbstractBinding>>> ProtocolBindingMap;

namespace Dev {

class Entity {
public:
	Entity();
	virtual ~Entity();

	void addType(const Data::QName & type);
	void addTypes(const Data::QVector & types);
    const Data::QVector & getTypes() const;
    virtual void clearTypes();
    virtual const Util::StringVector & getScopes() const = 0;
    virtual void clearScopes() = 0;
	const EndpointReference & getEndpointReference() const;
	void setEndpointReference(const EndpointReference & epr);

	void addBindingStr(const std::string & protocol, const std::string & bndStr);

	void setEPRAddress(const std::string & adr);

    const ProtocolBindingMap & getProtocolBindings() const;
    void addBinding(const std::string & protocol, std::shared_ptr<Comm::AbstractBinding> binding);

    std::string getDefaultTransportAddr(const std::string & protocol, std::shared_ptr<Comm::IPBinding> dispatcherBinding = nullptr) const;

protected:
	EndpointReference endpoint;
	Data::QVector types;
	ProtocolBindingMap protocolBindings;
};

} /* namespace Dev */
} /* namespace OSCLib */
#endif /* ENTITY_H_ */
