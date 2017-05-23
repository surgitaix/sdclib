
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"

#include <vector>

#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

template<class U, class V>
void ChannelDescriptor::getMetricDescriptors(std::vector<U> & result) const {
	for (const auto & metric : data->Metric()) {
		if (const V * m = dynamic_cast<const V *>(&metric)) {
			result.push_back(ConvertFromCDM::convert(*m));
		}
	}
}

std::vector<NumericMetricDescriptor> ChannelDescriptor::getNumericMetricDescriptors() const {
	std::vector<NumericMetricDescriptor> result;
	getMetricDescriptors<NumericMetricDescriptor, CDM::NumericMetricDescriptor>(result);
	return result;
}

std::vector<StringMetricDescriptor> ChannelDescriptor::getStringMetricDescriptors() const {
	std::vector<StringMetricDescriptor> result;
	getMetricDescriptors<StringMetricDescriptor, CDM::StringMetricDescriptor>(result);
	return result;
}

std::vector<EnumStringMetricDescriptor> ChannelDescriptor::getEnumStringMetricDescriptors() const {
	std::vector<EnumStringMetricDescriptor> result;
	getMetricDescriptors<EnumStringMetricDescriptor, CDM::EnumStringMetricDescriptor>(result);
	return result;
}

std::vector<RealTimeSampleArrayMetricDescriptor> ChannelDescriptor::getRealTimeSampleArrayMetricDescriptors() const {
	std::vector<RealTimeSampleArrayMetricDescriptor> result;
	getMetricDescriptors<RealTimeSampleArrayMetricDescriptor, CDM::RealTimeSampleArrayMetricDescriptor>(result);
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

template<class T>
ChannelDescriptor & ChannelDescriptor::addMetricImpl(const T & source) {
	data->Metric().push_back(ConvertToCDM::convert(source));
	return *this;
}

}
}
}
