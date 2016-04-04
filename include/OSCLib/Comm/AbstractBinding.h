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
 *  @file AbstractBinding.h
 *  @project OSCLib
 *  @date 14.07.2011
 *  @author Besting
 *  @copyright (c) SurgiTAIX AG
 *
 */

#ifndef BINDING_H_
#define BINDING_H_

#include <string>

namespace OSCLib {
namespace Comm {

class AbstractBinding {
public:

	typedef enum
	{
		UDP_MULTICAST,
		TCP_HTTP,
		UDP
	} BindingType;


	AbstractBinding();
	AbstractBinding(BindingType bType);
	AbstractBinding(const AbstractBinding & source);
	virtual ~AbstractBinding();
    BindingType getType() const;
    void setType(BindingType type);
    virtual std::string toString() const = 0;

private:
	BindingType type;
};

} /* namespace Comm */
} /* namespace OSCLib */
#endif /* BINDING_H_ */
