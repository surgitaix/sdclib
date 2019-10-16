
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/DistributionSampleArrayMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricDescriptor.h"

#include <vector>

#include "DataModel/osdm.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

template<class U, class V>
void ChannelDescriptor::getMetricDescriptors(std::vector<U> & result) const {
	for (const auto & metric : data->Metric()) {
		if (const V * m = dynamic_cast<const V *>(&metric)) {
			result.push_back(ConvertFromCDM::convert(*m));
		}
	}
}

std::vector<NumericMetricDescriptor> ChannelDescriptor::getNumericMetricDescriptorList() const {
	std::vector<NumericMetricDescriptor> result;
	getMetricDescriptors<NumericMetricDescriptor, CDM::NumericMetricDescriptor>(result);
	return result;
}

std::vector<StringMetricDescriptor> ChannelDescriptor::getStringMetricDescriptorList() const {
	std::vector<StringMetricDescriptor> result;
	getMetricDescriptors<StringMetricDescriptor, CDM::StringMetricDescriptor>(result);
	return result;
}

std::vector<EnumStringMetricDescriptor> ChannelDescriptor::getEnumStringMetricDescriptorList() const {
	std::vector<EnumStringMetricDescriptor> result;
	getMetricDescriptors<EnumStringMetricDescriptor, CDM::EnumStringMetricDescriptor>(result);
	return result;
}

std::vector<RealTimeSampleArrayMetricDescriptor> ChannelDescriptor::getRealTimeSampleArrayMetricDescriptorList() const {
	std::vector<RealTimeSampleArrayMetricDescriptor> result;
	getMetricDescriptors<RealTimeSampleArrayMetricDescriptor, CDM::RealTimeSampleArrayMetricDescriptor>(result);
	return result;
}

std::vector<DistributionSampleArrayMetricDescriptor> ChannelDescriptor::getDistributionSampleArrayMetricDescriptorList() const {
	std::vector<DistributionSampleArrayMetricDescriptor> result;
	getMetricDescriptors<DistributionSampleArrayMetricDescriptor, CDM::DistributionSampleArrayMetricDescriptor>(result);
	return result;
}

ChannelDescriptor & ChannelDescriptor::addMetric(const EnumStringMetricDescriptor & source) {
	return addMetricImpl(source);
}

ChannelDescriptor & ChannelDescriptor::addMetric(const NumericMetricDescriptor & source) {
	return addMetricImpl(source);
}

ChannelDescriptor & ChannelDescriptor::addMetric(const StringMetricDescriptor & source) {
	return addMetricImpl(source);
}

ChannelDescriptor & ChannelDescriptor::addMetric(const RealTimeSampleArrayMetricDescriptor & source) {
	return addMetricImpl(source);
}

ChannelDescriptor & ChannelDescriptor::addMetric(const DistributionSampleArrayMetricDescriptor & source) {
	return addMetricImpl(source);
}

template<class T>
ChannelDescriptor & ChannelDescriptor::addMetricImpl(const T & source) {
	data->Metric().push_back(ConvertToCDM::convert(source));
	return *this;
}

}
}
}
