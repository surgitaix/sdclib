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
 * DPWS11WaveformStreamActionHandler.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#ifndef DPWS11WAVEFORMSTREAMACTIONHANDLER_H
#define	DPWS11WAVEFORMSTREAMACTIONHANDLER_H

#include "OSCLib/Comm/DPWS/DPWS11ActionHandler.h"

namespace OSCLib {
    
namespace Data {
namespace OSCP {
    class OSCPConsumer;
}
}    
    
namespace Comm {
namespace DPWS {
    
class DPWS11WaveformStreamActionHandler : public DPWS11ActionHandler {
public:
    DPWS11WaveformStreamActionHandler(OSCLib::Data::OSCP::OSCPConsumer & c);
    virtual ~DPWS11WaveformStreamActionHandler();
    
	bool handleAction(DPWS11Message * dpws11msg);
    
    bool isUnicast() {
        return false;
    }
    
private:
    OSCLib::Data::OSCP::OSCPConsumer & consumer;
};

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
#endif	/* DPWS11WAVEFORMSTREAMACTIONHANDLER_H */

