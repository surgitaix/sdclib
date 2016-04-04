

#include "OSCLib/Data/OSCP/MDIB/AlertConditionReference.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"

#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

AlertConditionReference & AlertConditionReference::addHandle(const std::string & source) {
	data->push_back(source);
	return *this;
}

std::vector<std::string> AlertConditionReference::getHandles() const {
	std::vector<std::string> result;
	for (const auto & handle : *data) {
			result.push_back(handle);
	}
	return result;
}

}
}
}
