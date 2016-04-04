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
 *  @file Binding.h
 *  @project OSCLib
 *  @date 29.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#ifndef HTTPBINDING_H_
#define HTTPBINDING_H_

#include "IPBinding.h"

namespace OSCLib {
namespace Comm {

class Binding: public OSCLib::Comm::IPBinding {
public:
	Binding(const std::string& ip, unsigned int port, const std::string& path = "");
	Binding(const Binding & source);

	Binding(const std::string& str);
	virtual ~Binding();

    const std::string & getPath() const;
    void setPath(const std::string& path);
    virtual std::string toString() const;

    virtual Binding * clone() const {
    	return new Binding(*this);
    }

private:
	std::string path;
};

} /* namespace Comm */
} /* namespace OSCLib */
#endif /* HTTPBINDING_H_ */
