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
 * OSCPConsumerContextStateHandler.h
 *
 *  @Copyright (C) 2017, SurgiTAIX AG
 *  Author: buerger
 */


#ifndef INCLUDE_OSCLIB_DATA_OSCP_OSCPCONSUMERCONTEXTSTATEHANDLER_H_
#define INCLUDE_OSCLIB_DATA_OSCP_OSCPCONSUMERCONTEXTSTATEHANDLER_H_


namespace OSCLib {
namespace Data {
namespace OSCP {

template<typename ContextStateClass>
class OSCPConsumerContextStateHandler {
public:
	virtual ~OSCPConsumerContextStateHandler() {
	}

	/**
	* @brief This method will be called if any context state changes.
	*/
	virtual void onContextStateChanged(const std::vector<ContextStateClass> & contextStateClassList) = 0;

};


}
}
}





#endif /* INCLUDE_OSCLIB_DATA_OSCP_OSCPCONSUMERCONTEXTSTATEHANDLER_H_ */
