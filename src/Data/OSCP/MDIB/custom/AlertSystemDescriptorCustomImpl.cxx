

#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionDescriptor.h"

#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

AlertSystemDescriptor & AlertSystemDescriptor::addLimitAlertCondition(const LimitAlertConditionDescriptor & source) {
	data->AlertCondition().push_back(ConvertToCDM::convert(source));
	return *this;
}

std::vector<LimitAlertConditionDescriptor> AlertSystemDescriptor::getLimitAlertConditionList() const {
	std::vector<LimitAlertConditionDescriptor> result;
	for (const auto & condition : data->AlertCondition()) {
		if (const CDM::LimitAlertConditionDescriptor * casted = dynamic_cast<const CDM::LimitAlertConditionDescriptor *>(&condition)) {
			result.push_back(ConvertFromCDM::convert(*casted));
		}
	}
	return result;
}

}
}
}
