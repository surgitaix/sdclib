
#include "OSCLib/Data/OSCP/MDIB/ActivateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ScoDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetAlertStateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetContextStateOperationDescriptor.h"
//??
#include "OSCLib/Data/OSCP/MDIB/SetRangeOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetStringOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SetValueOperationDescriptor.h"

#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

template <class WrapperOperationDescriptorType>
void SCODescriptor::collectOperationDescriptorImpl(std::vector<WrapperOperationDescriptorType> & out) const {
	const CDM::SCODescriptor & sco(*this->data);
	for (const auto & operation : sco.Operation()) {
		if (const auto foundDescriptor = dynamic_cast<const typename WrapperOperationDescriptorType::WrappedType *>(&operation)) {
			out.push_back(ConvertFromCDM::convert(*foundDescriptor));
		}
	}
}

std::vector<ActivateOperationDescriptor> SCODescriptor::collectAllActivateOperationDescriptors() const {
	std::vector<ActivateOperationDescriptor> result;
	collectOperationDescriptorImpl<ActivateOperationDescriptor>(result);
	return result;
}

std::vector<SetAlertStateOperationDescriptor> SCODescriptor::collectAllSetAlertStateOperationDescriptors() const {
	std::vector<SetAlertStateOperationDescriptor> result;
	collectOperationDescriptorImpl<SetAlertStateOperationDescriptor>(result);
	return result;
}

std::vector<SetContextStateOperationDescriptor> SCODescriptor::collectAllSetContextOperationDescriptors() const {
	std::vector<SetContextStateOperationDescriptor> result;
	collectOperationDescriptorImpl<SetContextStateOperationDescriptor>(result);
	return result;
}

std::vector<SetRangeOperationDescriptor> SCODescriptor::collectAllSetRangeOperationDescriptors() const {
	std::vector<SetRangeOperationDescriptor> result;
	collectOperationDescriptorImpl<SetRangeOperationDescriptor>(result);
	return result;
}

std::vector<SetStringOperationDescriptor> SCODescriptor::collectAllSetStringOperationDescriptors() const {
	std::vector<SetStringOperationDescriptor> result;
	collectOperationDescriptorImpl<SetStringOperationDescriptor>(result);
	return result;
}

std::vector<SetValueOperationDescriptor> SCODescriptor::collectAllSetValueOperationDescriptors() const {
	std::vector<SetValueOperationDescriptor> result;
	collectOperationDescriptorImpl<SetValueOperationDescriptor>(result);
	return result;
}

}
}
}
