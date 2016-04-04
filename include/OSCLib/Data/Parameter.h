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
 *  @file Parameter.h
 *  @project OSCLib
 *  @date 04.01.2012
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#ifndef ELEMENT_H_
#define ELEMENT_H_

#include "QName.h"
#include "OSCLib/Dependencies/rapidxml/rapidxml.hpp"

#include <string>
#include <vector>
#include <memory>

namespace OSCLib {
namespace Comm {
namespace Soap {
	class XMLEntity;
}
}

namespace Data {

class Parameter;
typedef std::vector<Parameter> Parameters;

class Parameter {

public:
	enum class Type {
		STRING,
		BASE64,
		LONG,
		UNSIGNED_LONG,
		INT,
		UNSIGNED_INT,
		SHORT,
		UNSIGNED_SHORT,
		BYTE,
		UNSIGNED_BYTE,
		DECIMAL,
		FLOAT,
		DOUBLE,
		BOOLEAN,
		DURATION,
		DATETIME,
		DATE,
		TIME,
		COMPLEX,
		ANY,
        CDM,
		ERR
	};

	enum class Compositor {
		ALL,
		SEQUENCE,
		CHOICE
	};

	Parameter(const std::string & name);
	Parameter(const QName & name);
	Parameter(const std::string & name, Type type);
	Parameter(const QName & name, Type type);
	Parameter(const std::string & name, Type type, const std::string & value);
	Parameter(const QName & name, Type type, const std::string & value);
	Parameter(const std::string & name, const QName & customType);
	Parameter(const QName & name, const QName & customType);
	~Parameter();

	/**
	 * @brief Get the parameter name.
	 *
	 * @return The name
	 */
	const std::string & getName() const;

	/**
	 * @brief Get the (simple / primitive) parameter type.
	 *
	 * @return The type
	 */
	Type getType() const;

    /**
     * @brief Set the (simple / primitive) parameter type.
     *
     * @param type The type
     * @return This parameter
     */
    Parameter & setType(Type type);

    /**
     * @brief Get the parameter value.
     *
     * @return The value
     */
    const std::string & getValue() const;

    /**
     * @brief Set the parameter value.
     *
     * @param value The value
     * @return This parameter
     */
    Parameter & setValue(const std::string & value);

    /**
     * @brief Get the parameter compositor.
     *
     * @return The compositor
     */
    Compositor getCompositor() const;

    std::string getCompositorAsString() const;

    /**
     * @brief Set the parameter compositor.
     *
     * @param compositor The compositor
     * @return This parameter
     */
    Parameter & setCompositor(Compositor compositor);

    bool hasChildren() const;
    bool hasSiblings() const;
    size_t getChildCount() const;
    size_t getSiblingCount() const;

    /**
     * @brief Set the qualified parameter name.
     *
     * @param name The qualified name
     */
    Parameter & setQualifiedName(const QName & name);

    /**
     * @brief Get the qualified parameter name.
     *
     * @return The qualified parameter name
     */
    const QName & getQualifiedName() const;

    /**
     * @brief Set the custom type name.
     *
     * @param customType The custom type
     */
    Parameter & setCustomTypeName(const std::string & customType);

    /**
     * @brief Set the custom type.
     *
     * @param customType The custom type
     */
    Parameter & setCustomType(const QName & customType);

    /**
     * @brief Get the custom type.
     *
     * @return The custom type
	 */
	const std::string & getCustomTypeName() const;

    /**
     * @brief Get the complex / custom type.
     *
     * @return The custom type
	 */
	const QName & getCustomType() const;

    /**
     * @brief Get the simple / primitive type name.
     *
     * @return The type name.
     */
    std::string getSimpleTypeName() const;

    /**
     * @brief Generate the parameter's simple or complex qualified type name, adjusting namespaces as needed
     *
     * @return The qualified type name
     */
    QName getFinalQualifiedParameterTypeName(const QName& operationPortType) const;

    /**
     * @brief Generate the parameter's qualified name, adjusting namespaces as needed
     *
     * @return The qualified type name
     */
    QName getFinalQualifiedParameterName(const QName& operationPortType) const;

    std::vector<Parameter> getCopyChildren() const;
    void addToNode(Comm::Soap::XMLEntity * node, const QName & qBaseName) const;
    void createFromNode(rapidxml::xml_node<>* node);

    /**
     * @brief Add a copy of a parameter object as child parameter to this parameter.
     *
     * @param childParam The parameter to add
     */
    void addChild(const Parameter& childParam);

    /**
     * @brief Create or access a child or sibling parameter using a path string.
     * Use dots for children and indices within brackets for siblings.
     * Example: p["abc.def(0)"] returns 1st sibling of child named "def" of child
     * named "abc" of parameter p.
     *
     * @param path The path string
     * @return The (newly created or retrieved) parameter.
     */
    Parameter & operator[](const std::string & path);

    /**
     * @brief Get maximum cardinality.
     *
     * @return The cardinality
     */
    int getMaxOccurs() const;

    /**
     * @brief Get minimum cardinality.
     *
     * @return The cardinality
     */
    int getMinOccurs() const;

    /**
     * @brief Set maximum cardinality.
     *
     * @param maxOccurs The cardinality
     * @return This parameter
     */
    Parameter & setMaxOccurs(int maxOccurs);

    /**
     * @brief Set minimum cardinality.
     *
     * @param minOccurs The cardinality
     * @return This parameter
     */
    Parameter & setMinOccurs(int minOccurs);

    /**
     * @brief Check if parameter value has been set.
     *
     * @return True, if value set
     */
    bool isValueSet() const;

    /**
     * @brief Set the value set state.
     *
     * @param valueSet True to mark as value set
     */
    void setValueSet(bool valueSet);

    /**
     * @brief Check if parameter has a value.
     *
     * @return True if this parameter has a value.
	 */
	bool hasValue() const;

private:
    Parameter();
    QName name;
	QName customType;
    Type type;
    std::string value;
    Compositor compositor;
    int minOccurs;
    int maxOccurs;
    bool valueSet;
    std::vector<std::shared_ptr<Parameter>> children;
    std::vector<std::shared_ptr<Parameter>> siblings;
    void init();
    std::shared_ptr<Parameter> getChild(const std::string & name);
	QName updateParameterNameNamespaceIfNeededFrom(const QName & name) const;
	QName updateParameterTypeNamespaceIfNeededFrom(const QName & name) const;
    void addToNodeSelf(Comm::Soap::XMLEntity * node, const QName & qBaseName) const;
    void addToNodeChildren(Comm::Soap::XMLEntity * node, const QName & qBaseName) const;
    void addToNodeSiblings(Comm::Soap::XMLEntity * node, const QName & qBaseName) const;
};

} /* namespace Data */
} /* namespace OSCLib */
#endif /* ELEMENT_H_ */
