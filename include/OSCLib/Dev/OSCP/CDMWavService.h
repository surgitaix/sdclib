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
 * CDMWavService.h
 *
 *  @Copyright (C) 2016, SurgiTAIX AG
 *  Author: besting, roehser
 */

#ifndef INCLUDE_OSCLIB_DEV_OSCP_CDMWAVSERVICE_H_
#define INCLUDE_OSCLIB_DEV_OSCP_CDMWAVSERVICE_H_

#include "OSCLib/Dev/Service.h"

namespace OSCLib {
namespace Dev {
namespace OSCP {

class CDMWavService : public Service {
public:
	CDMWavService();
	virtual ~CDMWavService();
};

} /* namespace OSCP */
} /* namespace Dev */
} /* namespace OSCLib */

#endif /* INCLUDE_OSCLIB_DEV_OSCP_CDMWAVSERVICE_H_ */
