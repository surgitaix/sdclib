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
 *  @file Operation.cpp
 *  @project OSCLib
 *  @date 04.01.2012
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#include "OSCLib/Data/Operation.h"
#include "OSCLib/Data/OperationHelpers.h"

namespace OSCLib {
namespace Data {

Operation::Operation() :
		parentService(nullptr), internalType(DEFAULT)
{

}

Operation::Operation(const std::string & nameValue, const QName & portTypeValue) :
		parentService(nullptr), internalType(DEFAULT), name(nameValue), portType(portTypeValue)
{

}

Operation::~Operation() {

}

const std::string & Operation::getName() const {
	return name;
}

const QName & Operation::getPortType() const {
	return portType;
}

void Operation::setName(const std::string & newValue) {
	this->name = newValue;
}

void Operation::setPortType(const QName & newValue) {
	this->portType = newValue;
}

void Operation::addInputParameter(const Parameter & p) {
	input.push_back(p);
}

Dev::Service * Operation::getParentService() const {
	return parentService;
}

void Operation::setParentService(Dev::Service * service) {
	this->parentService = service;
}

void Operation::addOutputParameter(const Parameter & p) {
	output.push_back(p);
}

const std::string & Operation::getOutputAction() const {
	return outputAction;
}

std::string Operation::getDefaultInputAction() const {
	return OperationHelpers::getDefaultInputAction(Operation::getName(), Operation::getPortType());
}

std::string Operation::getDefaultOutputAction() const {
    return OperationHelpers::getDefaultOutputAction(getName(), getPortType());
}

const std::string & Operation::getInputAction() const {
	return inputAction;
}

void Operation::setInputAction(const std::string & action) {
	this->inputAction = action;
}

void Operation::setOutputAction(const std::string & action) {
	this->outputAction = action;
}

Operation::InternalType Operation::getInternalType() const {
    return internalType;
}

void Operation::setInternalType(const InternalType & newType) {
	internalType = newType;
}

const Parameters & Operation::getInput() const {
    return input;
}

const Parameters & Operation::getOutput() const {
    return output;
}

} /* namespace Data */
} /* namespace OSCLib */
