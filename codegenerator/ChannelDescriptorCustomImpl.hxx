
	std::vector<EnumStringMetricDescriptor> getEnumStringMetricDescriptorList() const;
	std::vector<NumericMetricDescriptor> getNumericMetricDescriptorList() const;
	std::vector<StringMetricDescriptor> getStringMetricDescriptorList() const;
	std::vector<RealTimeSampleArrayMetricDescriptor> getRealTimeSampleArrayMetricDescriptorList() const;
	std::vector<DistributionSampleArrayMetricDescriptor> getDistributionSampleArrayMetricDescriptorList() const;

	ChannelDescriptor & addMetric(const EnumStringMetricDescriptor & source);
	ChannelDescriptor & addMetric(const NumericMetricDescriptor & source);
	ChannelDescriptor & addMetric(const StringMetricDescriptor & source);
	ChannelDescriptor & addMetric(const RealTimeSampleArrayMetricDescriptor & source);
	ChannelDescriptor & addMetric(const DistributionSampleArrayMetricDescriptor & source);

private:
	template<class U, class V>
	void getMetricDescriptors(std::vector<U> & result) const;

	template<class T>
	ChannelDescriptor & addMetricImpl(const T & source);
