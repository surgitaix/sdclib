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
 *  @file XMLEntity.h
 *  @project OSCLib
 *  @date 08.07.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#ifndef SoapEntity_H_
#define SoapEntity_H_

#include "OSCLib/Dependencies/rapidxml/rapidxml.hpp"
#include "Poco/Buffer.h"

#include <string>
#include <memory>
#include <vector>

namespace OSCLib {
namespace Data {
	class QName;
}

namespace Comm {
namespace Soap {

class XMLEntity {
public:

	// Constructor document root
	XMLEntity();
    XMLEntity(const XMLEntity & e);
	XMLEntity(rapidxml::xml_node<>* node);

	// Constructor arbitrary child element
	XMLEntity(XMLEntity * parent, const std::string & nodeName = "", bool addLater = false);

	virtual ~XMLEntity();
	void addNode();

	virtual rapidxml::xml_node<> * getNode() const;
	XMLEntity * getParent() const;
	rapidxml::xml_document<> * getDoc() const;

	std::string toString(int flags = 0) const;
	std::string stripNsPrefix(const std::string & input) const;

	std::string getQualifiedInvariantAttributeValue(const std::string & key);
	XMLEntity * addAttribute(const std::string & key, const std::string & value);
	XMLEntity * addQualifiedAttribute(const std::string & key, const OSCLib::Data::QName & val, XMLEntity * nsTarget = nullptr);
	XMLEntity * addQualifiedAttribute(const OSCLib::Data::QName & key, const std::string & val, XMLEntity * nsTarget = nullptr);
	XMLEntity * addQualifiedAttribute(const OSCLib::Data::QName & key, const OSCLib::Data::QName & val, XMLEntity * nsTarget = nullptr);
	XMLEntity * setName(const std::string & name);
	XMLEntity * setValue(const std::string & value);
	XMLEntity * addTextNode(const std::string & name, const std::string & text = "");

	XMLEntity * addNamespace(const std::string & prefix, const std::string & nameSpace);

	XMLEntity * appendChild(const std::string & childName, bool addLater = false);

private:
    void initDoc(rapidxml::xml_node<> * node) const;
    Poco::Buffer<char> xmlParseBuf;

    bool docOwner;
	mutable rapidxml::xml_document<> * doc;
	rapidxml::xml_node<> * node;
	std::vector<std::shared_ptr<XMLEntity>> refs;

	XMLEntity * parent;
};

} /* namespace Soap */
} /* namespace Comm */
} /* namespace OSCLib */
#endif /* SoapEntity_H_ */
