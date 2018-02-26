
#include "OSCLib/Data/SDC/MDIB/ActivateOperationDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/SDC/MDIB/ScoDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/SetAlertStateOperationDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/SetContextStateOperationDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/SetStringOperationDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/SetValueOperationDescriptor.h"

#include "osdm.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

template <class WrapperOperationDescriptorType>
void ScoDescriptor::collectOperationDescriptorImpl(std::vector<WrapperOperationDescriptorType> & out) const {
	const CDM::ScoDescriptor & sco(*this->data);
	for (const auto & operation : sco.Operation()) {
		if (const auto foundDescriptor = dynamic_cast<const typename WrapperOperationDescriptorType::WrappedType *>(&operation)) {
			out.push_back(ConvertFromCDM::convert(*foundDescriptor));
		}
	}
}

std::vector<ActivateOperationDescriptor> ScoDescriptor::collectAllActivateOperationDescriptors() const {
	std::vector<ActivateOperationDescriptor> result;
	collectOperationDescriptorImpl<ActivateOperationDescriptor>(result);
	return result;
}

std::vector<SetAlertStateOperationDescriptor> ScoDescriptor::collectAllSetAlertStateOperationDescriptors() const {
	std::vector<SetAlertStateOperationDescriptor> result;
	collectOperationDescriptorImpl<SetAlertStateOperationDescriptor>(result);
	return result;
}

std::vector<SetContextStateOperationDescriptor> ScoDescriptor::collectAllSetContextOperationDescriptors() const {
	std::vector<SetContextStateOperationDescriptor> result;
	collectOperationDescriptorImpl<SetContextStateOperationDescriptor>(result);
	return result;
}

std::vector<SetStringOperationDescriptor> ScoDescriptor::collectAllSetStringOperationDescriptors() const {
	std::vector<SetStringOperationDescriptor> result;
	collectOperationDescriptorImpl<SetStringOperationDescriptor>(result);
	return result;
}

std::vector<SetValueOperationDescriptor> ScoDescriptor::collectAllSetValueOperationDescriptors() const {
	std::vector<SetValueOperationDescriptor> result;
	collectOperationDescriptorImpl<SetValueOperationDescriptor>(result);
	return result;
}

}
}
}
