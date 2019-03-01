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
 * SDCConsumerConnectionLostHandler.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting
 */

#ifndef SDCCONSUMERCONNECTIONLOSTHANDLER_H_
#define SDCCONSUMERCONNECTIONLOSTHANDLER_H_

namespace SDCLib {
namespace Data {
namespace SDC {

class SDCConsumerConnectionLostHandler {
public:
    virtual ~SDCConsumerConnectionLostHandler() = default;

    /**
    * @brief This method will be called if a ping has failed.
    */
    virtual void onConnectionLost() = 0;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

#endif /* SDCCONSUMERCONNECTIONLOSTHANDLER_H_ */
