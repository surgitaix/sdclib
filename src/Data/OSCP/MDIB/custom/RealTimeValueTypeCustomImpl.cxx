
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeValueType.h"

#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

std::vector<double> RealTimeValueType ::getValues() const {
	std::vector<double> result(*data);
	return result;
}

RealTimeValueType  & RealTimeValueType ::setValues(const std::vector<double> & values) {
	data->assign(values.begin(), values.end());
	return *this;
}

}
}
}
