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
 * OSCPCachedProvider.cpp
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, roehser
 */


#include "OSCLib/Data/OSCP/OSCPCachedProvider.h"
#include "OSCLib/Data/OSCP/MDIB/MDDescription.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/FromString.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "osdm.hxx"
#include <memory>

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPCachedProvider::OSCPCachedProvider() {
}

OSCPCachedProvider::~OSCPCachedProvider() {
}

MDDescription OSCPCachedProvider::getMDDescription() {
	Poco::Mutex::ScopedLock lock(mutex);
	return *mdDescription;
}

void OSCPCachedProvider::setMDDescription(MDDescription description) {
	Poco::Mutex::ScopedLock lock(mutex);
	this->mdDescription.reset(new MDDescription(description));
}

void OSCPCachedProvider::setMDDescription(std::string xml) {
	std::unique_ptr<CDM::MDIB> result(CDM::FromString::validateAndConvert<CDM::MDIB>(xml));
	if (result != nullptr) {
		Poco::Mutex::ScopedLock lock(mutex);
		this->mdDescription.reset(new MDDescription(ConvertFromCDM::convert(result->MDDescription())));
	}
	else
	{
		OSCLib::Util::DebugOut(OSCLib::Util::DebugOut::Error, std::cout, "OSCPCachedProvider")
			<< "Fatal error, can't create MDIB - schema validation error! Offending MDIB: "
			<< std::endl << xml << std::endl;
		std::exit(1);
	}
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
