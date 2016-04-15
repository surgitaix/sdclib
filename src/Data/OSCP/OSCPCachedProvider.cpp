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

#include <memory>

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/OSCPCachedProvider.h"
#include "OSCLib/Data/OSCP/MDIB/MDDescription.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"

#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "OSELib/Helper/XercesParserWrapper.h"
#include "OSELib/OSCP/DefaultOSCPSchemaGrammarProvider.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPCachedProvider::OSCPCachedProvider() {
}

OSCPCachedProvider::~OSCPCachedProvider() {
}

MDDescription OSCPCachedProvider::getMDDescription() {
	Poco::Mutex::ScopedLock lock(getMutex());
	return *mdDescription;
}

void OSCPCachedProvider::setMDDescription(MDDescription description) {
	Poco::Mutex::ScopedLock lock(getMutex());
	this->mdDescription.reset(new MDDescription(description));
}

void OSCPCachedProvider::setMDDescription(std::string xml) {
	OSELib::OSCP::DefaultOSCPSchemaGrammarProvider grammarProvider;
	auto rawMessage = OSELib::Helper::Message::create(xml);
	auto xercesDocument = OSELib::Helper::XercesDocumentWrapper::create(*rawMessage, grammarProvider);

	std::unique_ptr<CDM::MDIB> result(CDM::MDIBContainer(xercesDocument->getDocument()));

	if (result != nullptr) {
		Poco::Mutex::ScopedLock lock(getMutex());
		this->mdDescription.reset(new MDDescription(ConvertFromCDM::convert(result->MDDescription())));
	} else {
		log_fatal([&] { return " Fatal error, can't create MDIB - schema validation error! Offending MDIB: \n" + xml; });
		std::exit(1);
	}
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
