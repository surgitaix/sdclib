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

/*
 * DPWS11ActionHandler.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#ifndef DPWS11ACTIONHANDLER_H_
#define DPWS11ACTIONHANDLER_H_

namespace OSCLib {
namespace Comm {
namespace DPWS {

class DPWS11Message;    
    
class DPWS11ActionHandler {
public:
	DPWS11ActionHandler() {

	}

	virtual ~DPWS11ActionHandler() {

	}

	virtual bool handleAction(DPWS11Message * dpws11msg) = 0;
    
    virtual bool isUnicast() {
        return true;
    }

};

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
#endif /* DPWS11ACTIONHANDLER_H_ */
