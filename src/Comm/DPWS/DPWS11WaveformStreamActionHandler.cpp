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
 * DPWS11WaveformStreamActionHandler.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#include "OSCLib/Comm/DPWS/DPWS11Message.h"
#include "OSCLib/Comm/DPWS/DPWS11WaveformStreamActionHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/FromString.h"
#include "osdm.hxx"

namespace OSCLib {
namespace Comm {
namespace DPWS {
    
DPWS11WaveformStreamActionHandler::DPWS11WaveformStreamActionHandler(OSCLib::Data::OSCP::OSCPConsumer & c)
	: consumer(c)
{
}

DPWS11WaveformStreamActionHandler::~DPWS11WaveformStreamActionHandler() {
}

bool DPWS11WaveformStreamActionHandler::handleAction(DPWS11Message * dpws11msg) {
    try {
    	std::unique_ptr<CDM::WaveformStream> wfs(CDM::FromString::validateAndConvert<CDM::WaveformStream>(dpws11msg->bodyRawContent));
        for (const auto & sampleArray : wfs->RealTimeSampleArray()) {
            if (consumer.isValid()) {
                const auto & rtssams = dynamic_cast<const CDM::RealTimeSampleArrayMetricState &>(sampleArray);
                consumer.onStateChanged(Data::OSCP::ConvertFromCDM::convert(rtssams));
            }
        }
        return true;
    } catch (const xml_schema::Exception & e) {
       Util::DebugOut(Util::DebugOut::Error, "DPWS11WaveformStreamActionHandler") << "Schema parse exception " << e << std::endl;
    }
    return false;
}

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */

