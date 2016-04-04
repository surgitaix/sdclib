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
 * CDMEventSink.h
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, roehser
 */

#ifndef INCLUDE_OSCLIB_DATA_OSCP_CDMEVENTSINK_H_
#define INCLUDE_OSCLIB_DATA_OSCP_CDMEVENTSINK_H_

#include "OSCLib/Data/EventSink.h"
#include "OSCLib/Data/OSCP/OSCPSubscriptionManager.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "OSCLib/Util/FromString.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

template<class Traits>
class CDMEventSink : public EventSink {
public:
	typedef Traits TypeTraits;

	CDMEventSink(OSCPSubscriptionManager & manager) : manager(manager) {

	}
	virtual ~CDMEventSink() {

	}

    Parameters eventReceived(Parameters & p) {
        if (p.empty()) {
        	return Parameters();
        }

        // Last parameter contains body raw content
        const Parameter & rawParam = p.back();
    	if (rawParam.getType() != Parameter::Type::CDM) {
    		Parameters returnParams;
    		return returnParams;
    	}

    	std::unique_ptr<typename Traits::ReportType> report(CDM::FromString::validateAndConvert<typename Traits::ReportType>(rawParam.getValue()));
    	manager.dispatch(std::move(report));

        Parameters returnParams;
        return returnParams;
    }

private:
    OSCPSubscriptionManager & manager;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* INCLUDE_OSCLIB_DATA_OSCP_CDMEVENTSINK_H_ */
