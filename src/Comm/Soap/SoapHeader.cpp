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

/**
 *  @file SoapHeader.cpp
 *  @project OSCLib
 *  @date 08.07.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */

#include "OSCLib/Comm/Soap/SoapHeader.h"
#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Dev/Device.h"
#include "OSCLib/Util/DefaultUUIDGenerator.h"

using namespace rapidxml;

namespace OSCLib {
namespace Comm {
namespace Soap {

SoapHeader::SoapHeader(XMLEntity * parent) : XMLEntity(parent, "soap:Header")
{

}

SoapHeader::~SoapHeader()
{
}

XMLEntity * SoapHeader::addAction(const std::string & action)
{
	appendChild("wsa:Action")->setValue(action);
	return this;
}

std::string SoapHeader::addMessageID(const std::string & msgId)
{
	std::string id;

	if (msgId.length() == 0) {
		id = Util::DefaultUUIDGenerator::getUUID();
	} else {
		id = msgId;
	}

	appendChild("wsa:MessageID")->setValue(id);

	return id;
}

XMLEntity * SoapHeader::addFrom(const std::string & from)
{
	appendChild("wsa:From")->setValue(from);
	return this;
}

XMLEntity * SoapHeader::addTo(const std::string & to)
{
	std::string toAddress;

	if (to.compare("") == 0) {
		toAddress = Comm::DPWS::WS_ADDRESSING_ANONYMOUS;
	} else {
		toAddress = to;
	}

	appendChild("wsa:To")->setValue(toAddress);
	return this;
}

XMLEntity * SoapHeader::addReplyTo(const std::string & reply)
{
	if (reply.compare("") == 0) {
		throw std::runtime_error("ReplyTo address can't be null!");
	}

	appendChild("wsa:ReplyTo")->appendChild("wsa:Address")->setValue(reply);

	return this;
}

XMLEntity * SoapHeader::addFaultTo(const std::string & fault)
{
	appendChild("wsa:FaultTo")->setValue(fault);
	return this;
}

XMLEntity * SoapHeader::addAppSequence(const Dev::Device & device)
{
	XMLEntity* appSeqEntity = appendChild("wsd:AppSequence");
	appSeqEntity->addAttribute("InstanceId", std::to_string(device.getInstanceId()));
	appSeqEntity->addAttribute("MessageNumber", std::to_string(device.getMessageNumber()));
	return this;
}

XMLEntity * SoapHeader::addRelatesTo(const std::string & relatesTo)
{
	appendChild("wsa:RelatesTo")->setValue(relatesTo);
	return this;
}

} /* namespace Soap */
} /* namespace Comm */
} /* namespace OSCLib */
