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
 *  @file Operation.h
 *  @project OSCLib
 *  @date 04.01.2012
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */

#ifndef OPERATION_H_
#define OPERATION_H_

#include "Parameter.h"
#include <string>
#include <vector>

namespace OSCLib {
namespace Dev {
	class Service;
}
namespace Data {

class Operation;

typedef std::vector<std::shared_ptr<Data::Operation>> OperationVector;

class Operation {
public:

	typedef enum {
		DEFAULT,
		EVENT_SOURCE,
		EVENT_SINK
	} InternalType;

	Operation();
	Operation(const std::string & name, const QName & portType);
	virtual ~Operation();

    const std::string & getName() const;
    const QName & getPortType() const;
    void setName(const std::string & name);
    void setPortType(const QName & portType);
    void addInputParameter(const Parameter & p);
    void addOutputParameter(const Parameter & p);
    Dev::Service * getParentService() const;
    void setParentService(Dev::Service * parentService);

    virtual const std::string & getInputAction() const;
    virtual const std::string & getOutputAction() const;

    virtual std::string getDefaultInputAction() const;
    virtual std::string getDefaultOutputAction() const;

    void setInputAction(const std::string & action);
    void setOutputAction(const std::string & action);

    InternalType getInternalType() const;
    void setInternalType(const InternalType & newType);

    const Parameters & getInput() const;
    const Parameters & getOutput() const;

    virtual Parameters invoke(Parameters & p) = 0;

private:
    Parameters input;
	Parameters output;

	Dev::Service * parentService;
    InternalType internalType;
    std::string name;
    std::string inputAction;
    std::string outputAction;
    QName portType;
};

} /* namespace Data */
} /* namespace OSCLib */
#endif /* OPERATION_H_ */
