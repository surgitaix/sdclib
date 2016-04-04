
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/TimeZone.h"

#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

std::string TimeZone::get() const {
	return *data;
}

TimeZone & TimeZone::set(const std::string & value) {
	data->assign(value);
	return *this;
}

}
}
}
