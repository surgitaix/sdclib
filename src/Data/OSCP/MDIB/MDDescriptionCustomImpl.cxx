
#include "OSCLib/Data/OSCP/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ClockDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/DICOMDeviceDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MDDescription.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/VMDDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextDescriptor.h"

#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

template<class AlertSystemOwner>
bool findAlertConditionDescriptorImpl(const AlertSystemOwner & owner, const std::string & handle, AlertConditionDescriptor & outDescriptor) {
	if (owner.AlertSystem().present()) {
		const CDM::AlertSystemDescriptor & alertSystem(owner.AlertSystem().get());
		for (const auto & descriptor : alertSystem.AlertCondition()) {
			if (dynamic_cast<const LimitAlertConditionDescriptor::WrappedType *>(&descriptor)) {
				continue;
			}
			if (descriptor.Handle() == handle) {
				outDescriptor = ConvertFromCDM::convert(descriptor);
				return true;
			}
		}
	}
	return false;
}

bool MDDescription::findDescriptor(const std::string & handle, AlertConditionDescriptor & outDescriptor) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			if (findAlertConditionDescriptorImpl(*hydraMDS, handle, outDescriptor)) {
				return true;
			}
			for (const auto & vmdDescriptor : hydraMDS->VMD()) {
				if (findAlertConditionDescriptorImpl(vmdDescriptor, handle, outDescriptor)) {
					return true;
				}
				for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
					if (findAlertConditionDescriptorImpl(channelDescriptor, handle, outDescriptor)) {
						return true;
					}
				}
			}
		}
	}

	return false;
}

template<class AlertSystemOwner>
bool findAlertSignalDescriptorImpl(const AlertSystemOwner & owner, const std::string & handle, AlertSignalDescriptor & outDescriptor) {
	if (owner.AlertSystem().present()) {
		const CDM::AlertSystemDescriptor & alertSystem(owner.AlertSystem().get());
		for (const auto & descriptor : alertSystem.AlertSignal()) {
			if (descriptor.Handle() == handle) {
				outDescriptor = ConvertFromCDM::convert(descriptor);
				return true;
			}
		}
	}
	return false;
}

bool MDDescription::findDescriptor(const std::string & handle, AlertSignalDescriptor & outDescriptor) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			if (findAlertSignalDescriptorImpl(*hydraMDS, handle, outDescriptor)) {
				return true;
			}
			for (const auto & vmdDescriptor : hydraMDS->VMD()) {
				if (findAlertSignalDescriptorImpl(vmdDescriptor, handle, outDescriptor)) {
					return true;
				}
				for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
					if (findAlertSignalDescriptorImpl(channelDescriptor, handle, outDescriptor)) {
						return true;
					}
				}
			}
		}
	}

	return false;
}

template<class AlertSystemOwner>
bool findAlertSystemDescriptorImpl(const AlertSystemOwner & owner, const std::string & handle, AlertSystemDescriptor & outDescriptor) {
	if (owner.AlertSystem().present()) {
		const CDM::AlertSystemDescriptor & alertSystem(owner.AlertSystem().get());
		if (alertSystem.Handle() == handle) {
			outDescriptor = ConvertFromCDM::convert(alertSystem);
			return true;
		}
	}
	return false;
}

bool MDDescription::findDescriptor(const std::string & handle, AlertSystemDescriptor & outDescriptor) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			if (findAlertSystemDescriptorImpl(*hydraMDS, handle, outDescriptor)) {
				return true;
			}
			for (const auto & vmdDescriptor : hydraMDS->VMD()) {
				if (findAlertSystemDescriptorImpl(vmdDescriptor, handle, outDescriptor)) {
					return true;
				}
				for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
					if (findAlertSystemDescriptorImpl(channelDescriptor, handle, outDescriptor)) {
						return true;
					}
				}
			}
		}
	}

	return false;
}

template<class AlertSystemOwner>
bool findLimitAlertConditionDescriptorImpl(const AlertSystemOwner & owner, const std::string & handle, LimitAlertConditionDescriptor & outDescriptor) {
	if (owner.AlertSystem().present()) {
		const CDM::AlertSystemDescriptor & alertSystem(owner.AlertSystem().get());
		for (const auto & descriptor : alertSystem.AlertCondition()) {
			if (descriptor.Handle() == handle) {
				if (const CDM::LimitAlertConditionDescriptor * match = dynamic_cast<const CDM::LimitAlertConditionDescriptor *>(&descriptor)) {
					outDescriptor = ConvertFromCDM::convert(*match);
					return true;
				}
			}
		}
	}
	return false;
}

bool MDDescription::findDescriptor(const std::string & handle, LimitAlertConditionDescriptor & outDescriptor) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			if (findLimitAlertConditionDescriptorImpl(*hydraMDS, handle, outDescriptor)) {
				return true;
			}
			for (const auto & vmdDescriptor : hydraMDS->VMD()) {
				if (findLimitAlertConditionDescriptorImpl(vmdDescriptor, handle, outDescriptor)) {
					return true;
				}
				for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
					if (findLimitAlertConditionDescriptorImpl(channelDescriptor, handle, outDescriptor)) {
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool MDDescription::findDescriptor(const std::string & handle, ChannelDescriptor & outDescriptor) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			for (const auto & vmdDescriptor : hydraMDS->VMD()) {
				for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
					if (channelDescriptor.Handle() == handle) {
						outDescriptor = ConvertFromCDM::convert(channelDescriptor);
						return true;
					}
				}
			}
		}
	}
	return false;
}

template<class WrapperMetricDescriptorType>
bool MDDescription::findMetricDescriptorImpl(const std::string & handle, WrapperMetricDescriptorType & outMetric) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			for (const auto & vmdDescriptor : hydraMDS->VMD()) {
				for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
					for (const auto & metricDescriptor : channelDescriptor.Metric()) {
						if (metricDescriptor.Handle() != handle) {
							continue;
						}
						if (const typename WrapperMetricDescriptorType::WrappedType * foundMetric = dynamic_cast<const typename WrapperMetricDescriptorType::WrappedType *>(&metricDescriptor)) {
							outMetric = ConvertFromCDM::convert(*foundMetric);
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

template<>
bool MDDescription::findMetricDescriptorImpl(const std::string & handle, StringMetricDescriptor & outMetric) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			for (const auto & vmdDescriptor : hydraMDS->VMD()) {
				for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
					for (const auto & metricDescriptor : channelDescriptor.Metric()) {
						if (metricDescriptor.Handle() != handle) {
							continue;
						}
						if (dynamic_cast<const EnumStringMetricDescriptor::WrappedType *>(&metricDescriptor)) {
							continue;
						}
						if (auto foundMetric = dynamic_cast<const StringMetricDescriptor::WrappedType *>(&metricDescriptor)) {
							outMetric = ConvertFromCDM::convert(*foundMetric);
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

bool MDDescription::findDescriptor(const std::string & handle, ClockDescriptor & outDescriptor) const {
	return findMetricDescriptorImpl(handle, outDescriptor);
}

bool MDDescription::findDescriptor(const std::string & handle, EnumStringMetricDescriptor & outDescriptor) const {
	return findMetricDescriptorImpl(handle, outDescriptor);
}

bool MDDescription::findDescriptor(const std::string & handle, NumericMetricDescriptor & outDescriptor) const {
	return findMetricDescriptorImpl(handle, outDescriptor);
}

bool MDDescription::findDescriptor(const std::string & handle, StringMetricDescriptor & outDescriptor) const {
	return findMetricDescriptorImpl(handle, outDescriptor);
}

bool MDDescription::findDescriptor(const std::string & handle, VMDDescriptor & outDescriptor) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			for (const auto & vmdDescriptor : hydraMDS->VMD()) {
				if (vmdDescriptor.Handle() == handle) {
					outDescriptor = ConvertFromCDM::convert(vmdDescriptor);
					return true;
				}
			}
		}
	}
	return false;
}

bool MDDescription::findDescriptor(const std::string & handle, RealTimeSampleArrayMetricDescriptor & outDescriptor) const {
	return findMetricDescriptorImpl(handle, outDescriptor);
}

bool MDDescription::findDescriptor(const std::string & handle, EnsembleContextDescriptor & outDescriptor) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			if (hydraMDS->Context().EnsembleContext().present()) {
				const auto & descriptor(hydraMDS->Context().EnsembleContext().get());
				if (descriptor.Handle() == handle) {
					outDescriptor = ConvertFromCDM::convert(descriptor);
					return true;
				}
			}
		}
	}

	return false;
}


template <class MDSDescriptor>
void MDDescription::addMDSDescriptor(const MDSDescriptor & source) {
		CDM::MDDescription & mddescription(*this->data);
		mddescription.MDS().push_back(ConvertToCDM::convert(source));
}

template void MDDescription::addMDSDescriptor<HydraMDSDescriptor>(const HydraMDSDescriptor & source);
template void MDDescription::addMDSDescriptor<DICOMDeviceDescriptor>(const DICOMDeviceDescriptor & source);

bool MDDescription::findDescriptor(const std::string & handle, LocationContextDescriptor & outDescriptor) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			if (hydraMDS->Context().LocationContext().present()){
				const auto & descriptor(hydraMDS->Context().LocationContext().get());
				if (descriptor.Handle() == handle) {
					outDescriptor = ConvertFromCDM::convert(descriptor);
					return true;
				}
			}
		}
	}

	return false;
}

bool MDDescription::findDescriptor(const std::string & handle, OperatorContextDescriptor & outDescriptor) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			if (hydraMDS->Context().OperatorContext().present()){
				const auto & descriptor(hydraMDS->Context().OperatorContext().get());
				if (descriptor.Handle() == handle) {
					outDescriptor = ConvertFromCDM::convert(descriptor);
					return true;
				}
			}
		}
	}

	return false;
}

bool MDDescription::findDescriptor(const std::string & handle, PatientContextDescriptor & outDescriptor) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			if (hydraMDS->Context().PatientContext().present()) {
				const auto & descriptor(hydraMDS->Context().PatientContext().get());
				if (descriptor.Handle() == handle) {
					outDescriptor = ConvertFromCDM::convert(descriptor);
					return true;
				}
			}
		}
	}

	return false;
}

bool MDDescription::findDescriptor(const std::string & handle, WorkflowContextDescriptor & outDescriptor) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			if (hydraMDS->Context().WorkflowContext().present()){
				const auto & descriptor(hydraMDS->Context().WorkflowContext().get());
				if (descriptor.Handle() == handle) {
					outDescriptor = ConvertFromCDM::convert(descriptor);
					return true;
				}
			}
		}
	}

	return false;
}

bool MDDescription::getFirstHydraMDSDescriptor(HydraMDSDescriptor & outDescriptor) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			outDescriptor = ConvertFromCDM::convert(*hydraMDS);
			return true;
		}
	}
	return false;
}

bool MDDescription::findDescriptor(const std::string & handle, HydraMDSDescriptor & outDescriptor) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			if (hydraMDS->Handle() != handle) {
				continue;
			}
			outDescriptor = ConvertFromCDM::convert(*hydraMDS);
			return true;
		}
	}
	return false;
}

std::string MDDescription::getOperationTargetForOperationHandle(const std::string & operationHandle) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			if (!hydraMDS->SCO().present()) {
				continue;
			}
			for (const auto & operation : hydraMDS->SCO().get().Operation()) {
				if (operation.Handle() == operationHandle) {
					return operation.OperationTarget();
				}
			}
		}
	}

	return "";
}

std::string MDDescription::getFirstOperationHandleForOperationTarget(const std::string & operationTarget) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			if (!hydraMDS->SCO().present()) {
				continue;
			}
			for (const auto & operation : hydraMDS->SCO().get().Operation()) {
				if (operation.OperationTarget() == operationTarget) {
					return operation.Handle();
				}
			}
		}
	}

	return "";
}

std::vector<AlertConditionDescriptor> MDDescription::collectAllAlertConditionDescriptors() const {
	auto impl = [](const CDM::AlertSystemDescriptor & owner, std::vector<AlertConditionDescriptor> & out) {
		for (const auto & descriptor : owner.AlertCondition()) {
			if (dynamic_cast<const LimitAlertConditionDescriptor *>(&descriptor)) {
				continue;
			}
			out.push_back(ConvertFromCDM::convert(descriptor));
		}
	};

	std::vector<AlertConditionDescriptor> result;
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			if (hydraMDS->AlertSystem().present()) {
				impl(hydraMDS->AlertSystem().get(), result);
			}
			for (const auto & vmdDescriptor : hydraMDS->VMD()) {
				if (vmdDescriptor.AlertSystem().present()) {
					impl(vmdDescriptor.AlertSystem().get(), result);
				}
				for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
					if (channelDescriptor.AlertSystem().present()) {
						impl(channelDescriptor.AlertSystem().get(), result);
					}
				}
			}
		}
	}
	return result;
}

std::vector<AlertSignalDescriptor> MDDescription::collectAllAlertSignalDescriptors() const {
	auto impl = [](const CDM::AlertSystemDescriptor & owner, std::vector<AlertSignalDescriptor> & out) {
		for (const auto & descriptor : owner.AlertSignal()) {
			out.push_back(ConvertFromCDM::convert(descriptor));
		}
	};

	std::vector<AlertSignalDescriptor> result;
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			if (hydraMDS->AlertSystem().present()) {
				impl(hydraMDS->AlertSystem().get(), result);
			}
			for (const auto & vmdDescriptor : hydraMDS->VMD()) {
				if (vmdDescriptor.AlertSystem().present()) {
					impl(vmdDescriptor.AlertSystem().get(), result);
				}
				for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
					if (channelDescriptor.AlertSystem().present()) {
						impl(channelDescriptor.AlertSystem().get(), result);
					}
				}
			}
		}
	}
	return result;
}

std::vector<AlertSystemDescriptor> MDDescription::collectAllAlertSystemDescriptors() const {
	std::vector<AlertSystemDescriptor> result;
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			if (hydraMDS->AlertSystem().present()) {
				result.push_back(ConvertFromCDM::convert(hydraMDS->AlertSystem().get()));
			}
			for (const auto & vmdDescriptor : hydraMDS->VMD()) {
				if (vmdDescriptor.AlertSystem().present()) {
					result.push_back(ConvertFromCDM::convert(vmdDescriptor.AlertSystem().get()));
				}
				for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
					if (channelDescriptor.AlertSystem().present()) {
						result.push_back(ConvertFromCDM::convert(channelDescriptor.AlertSystem().get()));
					}
				}
			}
		}
	}
	return result;
}

std::vector<LimitAlertConditionDescriptor> MDDescription::collectAllLimitAlertConditionDescriptors() const {
	auto impl = [](const CDM::AlertSystemDescriptor & owner, std::vector<LimitAlertConditionDescriptor> & out) {
		for (const auto & descriptor : owner.AlertCondition()) {
			if (const CDM::LimitAlertConditionDescriptor * casted = dynamic_cast<const CDM::LimitAlertConditionDescriptor *>(&descriptor)) {
				out.push_back(ConvertFromCDM::convert(*casted));
			}
		}
	};

	std::vector<LimitAlertConditionDescriptor> result;
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			if (hydraMDS->AlertSystem().present()) {
				impl(hydraMDS->AlertSystem().get(), result);
			}
			for (const auto & vmdDescriptor : hydraMDS->VMD()) {
				if (vmdDescriptor.AlertSystem().present()) {
					impl(vmdDescriptor.AlertSystem().get(), result);
				}
				for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
					if (channelDescriptor.AlertSystem().present()) {
						impl(channelDescriptor.AlertSystem().get(), result);
					}
				}
			}
		}
	}
	return result;
}

std::vector<DICOMDeviceDescriptor> MDDescription::collectAllDICOMDeviceDescriptors() const {
	std::vector<DICOMDeviceDescriptor> result;
	const CDM::MDDescription & mddescription(*this->data);

	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::DICOMDeviceDescriptor * dicomDeviceDescriptor = dynamic_cast<const CDM::DICOMDeviceDescriptor *>(&mds)) {
			result.push_back(ConvertFromCDM::convert(*dicomDeviceDescriptor));
		}
	}

	return result;
}

std::vector<HydraMDSDescriptor> MDDescription::collectAllHydraMDSDescriptors() const {
	std::vector<HydraMDSDescriptor> result;
	const CDM::MDDescription & mddescription(*this->data);

	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			result.push_back(ConvertFromCDM::convert(*hydraMDS));
		}
	}

	return result;
}

std::vector<VMDDescriptor> MDDescription::collectAllVMDDescriptors() const {
	std::vector<VMDDescriptor> result;
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			for (const auto & vmdDescriptor : hydraMDS->VMD()) {
				result.push_back(ConvertFromCDM::convert(vmdDescriptor));
			}
		}
	}
	return result;
}

std::vector<ChannelDescriptor> MDDescription::collectAllChannelDescriptors() const {
	std::vector<ChannelDescriptor> result;
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			for (const auto & vmdDescriptor : hydraMDS->VMD()) {
				for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
					result.push_back(ConvertFromCDM::convert(channelDescriptor));
				}
			}
		}
	}
	return result;
}

template <class WrapperMetricDescriptorType>
void MDDescription::collectMetricDescriptorImpl(std::vector<WrapperMetricDescriptorType> & out) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			for (const auto & vmdDescriptor : hydraMDS->VMD()) {
				for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
					for (const auto & metricDescriptor : channelDescriptor.Metric()) {
						if (const typename WrapperMetricDescriptorType::WrappedType * foundMetric = dynamic_cast<const typename WrapperMetricDescriptorType::WrappedType *>(&metricDescriptor)) {
							out.push_back(ConvertFromCDM::convert(*foundMetric));
						}
					}
				}
			}
		}
	}
}

template <class WrapperMetricDescriptorType, class ForbiddenType>
void MDDescription::collectMetricDescriptorImpl(std::vector<WrapperMetricDescriptorType> & out) const {
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			for (const auto & vmdDescriptor : hydraMDS->VMD()) {
				for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
					for (const auto & metricDescriptor : channelDescriptor.Metric()) {
						if (dynamic_cast<const typename ForbiddenType::WrappedType *>(&metricDescriptor)) {
							continue;
						}
						if (const typename WrapperMetricDescriptorType::WrappedType * foundMetric = dynamic_cast<const typename WrapperMetricDescriptorType::WrappedType *>(&metricDescriptor)) {
							out.push_back(ConvertFromCDM::convert(*foundMetric));
						}
					}
				}
			}
		}
	}
}

std::vector<ClockDescriptor> MDDescription::collectAllClockDescriptors() const {
	std::vector<ClockDescriptor> result;
	const CDM::MDDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.MDS()) {
		if (const CDM::HydraMDSDescriptor * hydraMDS = dynamic_cast<const CDM::HydraMDSDescriptor *>(&mds)) {
			if (hydraMDS->Clock().present()) {
				result.push_back(ConvertFromCDM::convert(hydraMDS->Clock().get()));
			}
		}
	}
	return result;
}

std::vector<EnumStringMetricDescriptor> MDDescription::collectAllEnumStringMetricDescriptors() const {
	std::vector<EnumStringMetricDescriptor> result;
	collectMetricDescriptorImpl(result);
	return result;
}

std::vector<NumericMetricDescriptor> MDDescription::collectAllNumericMetricDescriptors() const {
	std::vector<NumericMetricDescriptor> result;
	collectMetricDescriptorImpl(result);
	return result;
}

std::vector<RealTimeSampleArrayMetricDescriptor> MDDescription::collectAllRealTimeSampleArrayMetricDescriptors() const {
	std::vector<RealTimeSampleArrayMetricDescriptor> result;
	collectMetricDescriptorImpl(result);
	return result;
}

std::vector<StringMetricDescriptor> MDDescription::collectAllStringMetricDescriptors() const {
	std::vector<StringMetricDescriptor> result;
	collectMetricDescriptorImpl<StringMetricDescriptor, EnumStringMetricDescriptor>(result);
	return result;
}

}
}
}
