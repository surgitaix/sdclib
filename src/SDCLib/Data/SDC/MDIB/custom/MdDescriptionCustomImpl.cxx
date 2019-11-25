
#include "SDCLib/Data/SDC/MDIB/AlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ClockDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/DicomDeviceDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/EnsembleContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/OperatorContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/PatientContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ActivateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/WorkflowContextDescriptor.h"

#include "DataModel/osdm.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

//// template specialization for API
template std::unique_ptr<AlertConditionDescriptor>  MdDescription::findDescriptor(const std::string & handle) const;
template std::unique_ptr<AlertSignalDescriptor>  MdDescription::findDescriptor(const std::string & handle) const;
template std::unique_ptr<AlertSystemDescriptor>  MdDescription::findDescriptor(const std::string & handle) const;
template std::unique_ptr<ChannelDescriptor>  MdDescription::findDescriptor(const std::string & handle) const;
template std::unique_ptr<ClockDescriptor>  MdDescription::findDescriptor(const std::string & handle) const;
template std::unique_ptr<EnsembleContextDescriptor>  MdDescription::findDescriptor(const std::string & handle) const;
template std::unique_ptr<EnumStringMetricDescriptor>  MdDescription::findDescriptor(const std::string & handle) const;
template std::unique_ptr<MdsDescriptor>  MdDescription::findDescriptor(const std::string & handle) const;
template std::unique_ptr<LimitAlertConditionDescriptor>  MdDescription::findDescriptor(const std::string & handle) const;
template std::unique_ptr<LocationContextDescriptor>  MdDescription::findDescriptor(const std::string & handle) const;
template std::unique_ptr<NumericMetricDescriptor>  MdDescription::findDescriptor(const std::string & handle) const;
template std::unique_ptr<OperatorContextDescriptor>  MdDescription::findDescriptor(const std::string & handle) const;
template std::unique_ptr<PatientContextDescriptor>  MdDescription::findDescriptor(const std::string & handle) const;
template std::unique_ptr<RealTimeSampleArrayMetricDescriptor>  MdDescription::findDescriptor(const std::string & handle) const;
template std::unique_ptr<StringMetricDescriptor>  MdDescription::findDescriptor(const std::string & handle) const;
template std::unique_ptr<VmdDescriptor>  MdDescription::findDescriptor(const std::string & handle) const;
template std::unique_ptr<WorkflowContextDescriptor>  MdDescription::findDescriptor(const std::string & handle) const;

template<class TDescriptor>
std::unique_ptr<TDescriptor> MdDescription::findDescriptor(const std::string & handle) const {
	TDescriptor outState;
	if (findDescriptor(handle, outState)) {
		auto ptr = std::unique_ptr<TDescriptor>(new TDescriptor(outState));
		return std::move(ptr);
	}
	return nullptr;
}

template<class AlertSystemOwner>
bool findAlertConditionDescriptorImpl(const AlertSystemOwner & owner, const std::string & handle, AlertConditionDescriptor & outDescriptor) {
		if (owner.getAlertSystem().present()) {
		const CDM::AlertSystemDescriptor & alertSystem(owner.getAlertSystem().get());
		for (const auto & descriptor : alertSystem.getAlertCondition()) {
			if (dynamic_cast<const LimitAlertConditionDescriptor::WrappedType *>(&descriptor)) {
				continue;
			}
			if (descriptor.getHandle() == handle) {
				outDescriptor = ConvertFromCDM::convert(descriptor);
				return true;
			}
		}
	}
	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, AlertConditionDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		if (findAlertConditionDescriptorImpl(mds, handle, outDescriptor)) {
			return true;
		}
		for (const auto & vmdDescriptor : mds.getVmd()) {
			if (findAlertConditionDescriptorImpl(vmdDescriptor, handle, outDescriptor)) {
				return true;
			}
		}
	}

	return false;
}

template<class AlertSystemOwner>
bool findAlertSignalDescriptorImpl(const AlertSystemOwner & owner, const std::string & handle, AlertSignalDescriptor & outDescriptor) {
	if (owner.getAlertSystem().present()) {
		const CDM::AlertSystemDescriptor & alertSystem(owner.getAlertSystem().get());
		for (const auto & descriptor : alertSystem.getAlertSignal()) {
			if (descriptor.getHandle() == handle) {
				outDescriptor = ConvertFromCDM::convert(descriptor);
				return true;
			}
		}
	}
	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, AlertSignalDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		if (findAlertSignalDescriptorImpl(mds, handle, outDescriptor)) {
			return true;
		}
		for (const auto & vmdDescriptor : mds.getVmd()) {
			if (findAlertSignalDescriptorImpl(vmdDescriptor, handle, outDescriptor)) {
				return true;
			}
		}
	}

	return false;
}

template<class AlertSystemOwner>
bool findAlertSystemDescriptorImpl(const AlertSystemOwner & owner, const std::string & handle, AlertSystemDescriptor & outDescriptor) {
	if (owner.getAlertSystem().present()) {
		const CDM::AlertSystemDescriptor & alertSystem(owner.getAlertSystem().get());
		if (alertSystem.getHandle() == handle) {
			outDescriptor = ConvertFromCDM::convert(alertSystem);
			return true;
		}
	}
	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, AlertSystemDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		if (findAlertSystemDescriptorImpl(mds, handle, outDescriptor)) {
			return true;
		}
		for (const auto & vmdDescriptor : mds.getVmd()) {
			if (findAlertSystemDescriptorImpl(vmdDescriptor, handle, outDescriptor)) {
				return true;
			}
		}
	}

	return false;
}

template<class AlertSystemOwner>
bool findLimitAlertConditionDescriptorImpl(const AlertSystemOwner & owner, const std::string & handle, LimitAlertConditionDescriptor & outDescriptor) {
	if (owner.getAlertSystem().present()) {
		const CDM::AlertSystemDescriptor & alertSystem(owner.getAlertSystem().get());
		for (const auto & descriptor : alertSystem.getAlertCondition()) {
			if (descriptor.getHandle() == handle) {
				if (const CDM::LimitAlertConditionDescriptor * match = dynamic_cast<const CDM::LimitAlertConditionDescriptor *>(&descriptor)) {
					outDescriptor = ConvertFromCDM::convert(*match);
					return true;
				}
			}
		}
	}
	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, LimitAlertConditionDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		if (findLimitAlertConditionDescriptorImpl(mds, handle, outDescriptor)) {
			return true;
		}
		for (const auto & vmdDescriptor : mds.getVmd()) {
			if (findLimitAlertConditionDescriptorImpl(vmdDescriptor, handle, outDescriptor)) {
				return true;
			}
		}
	}

	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, ChannelDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		for (const auto & vmdDescriptor : mds.getVmd()) {
			for (const auto & channelDescriptor : vmdDescriptor.getChannel()) {
				if (channelDescriptor.getHandle() == handle) {
					outDescriptor = ConvertFromCDM::convert(channelDescriptor);
					return true;
				}
			}
		}
	}
	return false;
}



template<>
bool MdDescription::findMetricDescriptorImpl(const std::string & handle, StringMetricDescriptor & outMetric) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		for (const auto & vmdDescriptor : mds.getVmd()) {
			for (const auto & channelDescriptor : vmdDescriptor.getChannel()) {
				for (const auto & metricDescriptor : channelDescriptor.getMetric()) {
					if (metricDescriptor.getHandle() != handle) {
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

	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, ClockDescriptor & outDescriptor) const {
	return findMetricDescriptorImpl(handle, outDescriptor);
}

bool MdDescription::findDescriptor(const std::string & handle, EnumStringMetricDescriptor & outDescriptor) const {
	return findMetricDescriptorImpl(handle, outDescriptor);
}

bool MdDescription::findDescriptor(const std::string & handle, NumericMetricDescriptor & outDescriptor) const {
	return findMetricDescriptorImpl(handle, outDescriptor);
}

bool MdDescription::findDescriptor(const std::string & handle, StringMetricDescriptor & outDescriptor) const {
	return findMetricDescriptorImpl(handle, outDescriptor);
}

bool MdDescription::findDescriptor(const std::string & handle, VmdDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		for (const auto & vmdDescriptor : mds.getVmd()) {
			if (vmdDescriptor.getHandle() == handle) {
				outDescriptor = ConvertFromCDM::convert(vmdDescriptor);
				return true;
			}
		}
	}
	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, RealTimeSampleArrayMetricDescriptor & outDescriptor) const {
	return findMetricDescriptorImpl(handle, outDescriptor);
}

bool MdDescription::findDescriptor(const std::string & handle, EnsembleContextDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		if (mds.getSystemContext().present()) {
			if (!mds.getSystemContext().get().getEnsembleContext().empty()) {
				for (const auto & descriptor : mds.getSystemContext().get().getEnsembleContext()) {
					if (descriptor.getHandle() == handle) {
						outDescriptor = ConvertFromCDM::convert(descriptor);
						return true;
					}
				}
			}
		}
	}

	return false;
}


template <class MdsDescriptor>
void MdDescription::addMdsDescriptor(const MdsDescriptor & source) {
	CDM::MdDescription & mddescription(*this->data);
	mddescription.getMds().push_back(ConvertToCDM::convert(source));
}

template void MdDescription::addMdsDescriptor<MdsDescriptor>(const MdsDescriptor & source);

// not abstractMDSDevice in MdDescription, thus no DicomDeviceDescriptor realized
//template void MdDescription::addMdsDescriptor<DicomDeviceDescriptor>(const DicomDeviceDescriptor & source);


template <class MdsDescriptor>
bool MdDescription::removeMdsDescriptor(const MdsDescriptor & object) {
	CDM::MdDescription & mddescription(*this->data);
	for (auto iter = mddescription.getMds().begin(); iter != mddescription.getMds().end(); iter++) {
		if (iter->getHandle() == object.getHandle()) {
			mddescription.getMds().erase(iter);
			return true;
		}
	}
	return false;
}

template bool MdDescription::removeMdsDescriptor<MdsDescriptor>(const MdsDescriptor & source);
template bool MdDescription::removeMdsDescriptor<DicomDeviceDescriptor>(const DicomDeviceDescriptor & source);


bool MdDescription::findDescriptor(const std::string & handle, LocationContextDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		if (mds.getSystemContext().present()) {
			if (mds.getSystemContext().get().getLocationContext().present()) {
				const auto & descriptor(mds.getSystemContext().get().getLocationContext().get());
				if (descriptor.getHandle() == handle) {
					outDescriptor = ConvertFromCDM::convert(descriptor);
					return true;
				}
			}
		}
	}
	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, OperatorContextDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		if (mds.getSystemContext().present()) {
			if (!mds.getSystemContext().get().getOperatorContext().empty()) {
				for (const auto & descriptor : mds.getSystemContext().get().getOperatorContext()) {
					if (descriptor.getHandle() == handle) {
						outDescriptor = ConvertFromCDM::convert(descriptor);
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, PatientContextDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		if (mds.getSystemContext().present()) {
			if (mds.getSystemContext().get().getPatientContext().present()) {
				const auto & descriptor(mds.getSystemContext().get().getPatientContext().get());
				if (descriptor.getHandle() == handle) {
					outDescriptor = ConvertFromCDM::convert(descriptor);
					return true;
				}
			}
		}
	}

	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, WorkflowContextDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		if (mds.getSystemContext().present()) {
			if (!mds.getSystemContext().get().getWorkflowContext().empty()) {
				for (const auto & descriptor : mds.getSystemContext().get().getWorkflowContext()) {
					if (descriptor.getHandle() == handle) {
						outDescriptor = ConvertFromCDM::convert(descriptor);
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool MdDescription::getFirstMdsDescriptor(MdsDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		outDescriptor = ConvertFromCDM::convert(mds);
		return true;
	}
	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, MdsDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		if (mds.getHandle() != handle) {
			continue;
		}
		outDescriptor = ConvertFromCDM::convert(mds);
		return true;
	}
	return false;
}

std::string MdDescription::getOperationTargetForOperationHandle(const std::string & operationHandle) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		if (!mds.getSco().present()) {
			continue;
		}
		for (const auto & operation : mds.getSco().get().getOperation()) {
			if (operation.getHandle() == operationHandle) {
				return operation.getOperationTarget();
			}
		}
		// Check Vmds too
		for(const auto& t_vmd : mds.getVmd())
		{
			if (!t_vmd.getSco().present()) {
				continue;
			}
			for (const auto & t_operation : t_vmd.getSco().get().getOperation()) {
				if (t_operation.getHandle() == operationHandle) {
					return t_operation.getOperationTarget();
				}
			}

		}

	}

	return "";
}

std::string MdDescription::getFirstOperationHandleForOperationTarget(const std::string & operationTarget) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		if (!mds.getSco().present()) {
			continue;
		}
		for (const auto & operation : mds.getSco().get().getOperation()) {
			if (operation.getOperationTarget() == operationTarget) {
				return operation.getHandle();
			}
		}
	}

	return "";
}

std::vector<AlertConditionDescriptor> MdDescription::collectAllAlertConditionDescriptors() const {
	auto impl = [](const CDM::AlertSystemDescriptor & owner, std::vector<AlertConditionDescriptor> & out) {
		for (const auto & descriptor : owner.getAlertCondition()) {
			if (dynamic_cast<const LimitAlertConditionDescriptor *>(&descriptor)) {
				continue;
			}
			out.push_back(ConvertFromCDM::convert(descriptor));
		}
	};

	std::vector<AlertConditionDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		if (mds.getAlertSystem().present()) {
			impl(mds.getAlertSystem().get(), result);
		}
		for (const auto & vmdDescriptor : mds.getVmd()) {
			if (vmdDescriptor.getAlertSystem().present()) {
				impl(vmdDescriptor.getAlertSystem().get(), result);
			}
		}
	}
	return result;
}

std::vector<AlertSignalDescriptor> MdDescription::collectAllAlertSignalDescriptors() const {
	auto impl = [](const CDM::AlertSystemDescriptor & owner, std::vector<AlertSignalDescriptor> & out) {
		for (const auto & descriptor : owner.getAlertSignal()) {
			out.push_back(ConvertFromCDM::convert(descriptor));
		}
	};

	std::vector<AlertSignalDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		if (mds.getAlertSystem().present()) {
			impl(mds.getAlertSystem().get(), result);
		}
		for (const auto & vmdDescriptor : mds.getVmd()) {
			if (vmdDescriptor.getAlertSystem().present()) {
				impl(vmdDescriptor.getAlertSystem().get(), result);
			}
		}
	}
	return result;
}

std::vector<AlertSystemDescriptor> MdDescription::collectAllAlertSystemDescriptors() const {
	std::vector<AlertSystemDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		if (mds.getAlertSystem().present()) {
			result.push_back(ConvertFromCDM::convert(mds.getAlertSystem().get()));
		}
		for (const auto & vmdDescriptor : mds.getVmd()) {
			if (vmdDescriptor.getAlertSystem().present()) {
				result.push_back(ConvertFromCDM::convert(vmdDescriptor.getAlertSystem().get()));
			}
		}
	}
	return result;
}

std::vector<LimitAlertConditionDescriptor> MdDescription::collectAllLimitAlertConditionDescriptors() const {
	auto impl = [](const CDM::AlertSystemDescriptor & owner, std::vector<LimitAlertConditionDescriptor> & out) {
		for (const auto & descriptor : owner.getAlertCondition()) {
			if (const CDM::LimitAlertConditionDescriptor * casted = dynamic_cast<const CDM::LimitAlertConditionDescriptor *>(&descriptor)) {
				out.push_back(ConvertFromCDM::convert(*casted));
			}
		}
	};

	std::vector<LimitAlertConditionDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		if (mds.getAlertSystem().present()) {
			impl(mds.getAlertSystem().get(), result);
		}
		for (const auto & vmdDescriptor : mds.getVmd()) {
			if (vmdDescriptor.getAlertSystem().present()) {
				impl(vmdDescriptor.getAlertSystem().get(), result);
			}
		}
	}
	return result;
}

std::vector<DicomDeviceDescriptor> MdDescription::collectAllDicomDeviceDescriptors() const {
	std::vector<DicomDeviceDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);

	for (const auto & mds : mddescription.getMds()) {
		if (const CDM::DicomDeviceDescriptor * dicomDeviceDescriptor = dynamic_cast<const CDM::DicomDeviceDescriptor *>(&mds)) {
			result.push_back(ConvertFromCDM::convert(*dicomDeviceDescriptor));
		}
	}

	return result;
}

std::vector<MdsDescriptor> MdDescription::collectAllMdsDescriptors() const {
	std::vector<MdsDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
			result.push_back(ConvertFromCDM::convert(mds));
	}
	return result;
}

std::vector<VmdDescriptor> MdDescription::collectAllVmdDescriptors() const {
	std::vector<VmdDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		for (const auto & vmdDescriptor : mds.getVmd()) {
			result.push_back(ConvertFromCDM::convert(vmdDescriptor));
		}
	}
	return result;
}

std::vector<ChannelDescriptor> MdDescription::collectAllChannelDescriptors() const {
	std::vector<ChannelDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		for (const auto & vmdDescriptor : mds.getVmd()) {
			for (const auto & channelDescriptor : vmdDescriptor.getChannel()) {
				result.push_back(ConvertFromCDM::convert(channelDescriptor));
			}
		}
	}
	return result;
}


template<class WrapperMetricDescriptorType>
bool MdDescription::findMetricDescriptorImpl(const std::string & handle, WrapperMetricDescriptorType & outMetric) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		for (const auto & vmdDescriptor : mds.getVmd()) {
			for (const auto & channelDescriptor : vmdDescriptor.getChannel()) {
				for (const auto & metricDescriptor : channelDescriptor.getMetric()) {
					if (metricDescriptor.getHandle() != handle) {
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
	return false;
}

template <class WrapperMetricDescriptorType>
void MdDescription::collectMetricDescriptorImpl(std::vector<WrapperMetricDescriptorType> & out) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		for (const auto & vmdDescriptor : mds.getVmd()) {
			for (const auto & channelDescriptor : vmdDescriptor.getChannel()) {
				for (const auto & metricDescriptor : channelDescriptor.getMetric()) {
					if (const typename WrapperMetricDescriptorType::WrappedType * foundMetric = dynamic_cast<const typename WrapperMetricDescriptorType::WrappedType *>(&metricDescriptor)) {
						out.push_back(ConvertFromCDM::convert(*foundMetric));
					}
				}
			}
		}
	}
}

template <class WrapperMetricDescriptorType, class ForbiddenType>
void MdDescription::collectMetricDescriptorImpl(std::vector<WrapperMetricDescriptorType> & out) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		for (const auto & vmdDescriptor : mds.getVmd()) {
			for (const auto & channelDescriptor : vmdDescriptor.getChannel()) {
				for (const auto & metricDescriptor : channelDescriptor.getMetric()) {
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

std::vector<ClockDescriptor> MdDescription::collectAllClockDescriptors() const {
	std::vector<ClockDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
			if (mds.getClock().present()) {
				result.push_back(ConvertFromCDM::convert(mds.getClock().get()));
			}
	}
	return result;
}

std::vector<EnumStringMetricDescriptor> MdDescription::collectAllEnumStringMetricDescriptors() const {
	std::vector<EnumStringMetricDescriptor> result;
	collectMetricDescriptorImpl(result);
	return result;
}

std::vector<NumericMetricDescriptor> MdDescription::collectAllNumericMetricDescriptors() const {
	std::vector<NumericMetricDescriptor> result;
	collectMetricDescriptorImpl(result);
	return result;
}

std::vector<RealTimeSampleArrayMetricDescriptor> MdDescription::collectAllRealTimeSampleArrayMetricDescriptors() const {
	std::vector<RealTimeSampleArrayMetricDescriptor> result;
	collectMetricDescriptorImpl(result);
	return result;
}

std::vector<StringMetricDescriptor> MdDescription::collectAllStringMetricDescriptors() const {
	std::vector<StringMetricDescriptor> result;
	collectMetricDescriptorImpl<StringMetricDescriptor, EnumStringMetricDescriptor>(result);
	return result;
}


std::vector<ActivateOperationDescriptor> MdDescription::collectAllActivateOperationDescriptors() const {
	std::vector<ActivateOperationDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.getMds()) {
		if (mds.getSco().present()) {
			const CDM::ScoDescriptor & sco(mds.getSco().get());
			for (const auto & operation : sco.getOperation()) {
				const typename CDM::ActivateOperationDescriptor *desc = dynamic_cast<const typename CDM::ActivateOperationDescriptor*>(&operation);
				if (desc != nullptr)
					result.push_back(ConvertFromCDM::convert(*desc));
			}
		}
	}
	return result;
}


}
}
}
