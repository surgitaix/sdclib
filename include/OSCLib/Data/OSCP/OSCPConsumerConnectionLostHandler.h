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
 * OSCPConsumerConnectionLostHandler.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting
 */

#ifndef OSCPCONSUMERCONNECTIONLOSTHANDLER_H_
#define OSCPCONSUMERCONNECTIONLOSTHANDLER_H_

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPConsumerConnectionLostHandler {
public:
    virtual ~OSCPConsumerConnectionLostHandler() {
    }

    /**
    * @brief This method will be called if a ping has failed.
    */
    virtual void onConnectionLost() = 0;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* OSCPCONSUMERCONNECTIONLOSTHANDLER_H_ */
