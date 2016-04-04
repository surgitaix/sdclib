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
 * CDMGetService.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting
 */

#ifndef CDMGETSERVICE_H_
#define CDMGETSERVICE_H_

#include "OSCLib/Dev/Service.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"

namespace OSCLib {
namespace Dev {
namespace OSCP {

class CDMGetService : public Service {
public:
    CDMGetService(OSCLib::Data::OSCP::OSCPProvider & provider);
    virtual ~CDMGetService();
};

} /* namespace OSCP */
} /* namespace Dev */
} /* namespace OSCLib */
#endif /* CDMGETSERVICE_H_ */
