
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"
#include "OSCLib/Data/OSCP/MDIB/PersonReference.h"

#include <vector>

#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

PersonReference & PersonReference::addIdentification(const InstanceIdentifier & value) {
	// in case there is a dummy value that was created by the framework to fulfill the
	// 1..infinity schema cardinality requirement, we replace the dummy value by the new one
	if (data->Identification().size() == 1
		&& data->Identification().front().root() == NOT_ASSIGNED) {
		data->Identification().front() = *ConvertToCDM::convert(value);
	} else {
		data->Identification().push_back(ConvertToCDM::convert(value));
	}
	return *this;
}

std::vector<InstanceIdentifier> PersonReference::getIdentifications() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Identification().size());
	for (const auto & value: data->Identification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

}
}
}
