
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/RTValueType.h"

#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

std::vector<double> RTValueType::getValues() const {
	std::vector<double> result(*data);
	return result;
}

RTValueType & RTValueType::setValues(const std::vector<double> & values) {
	data->assign(values.begin(), values.end());
	return *this;
}

}
}
}
