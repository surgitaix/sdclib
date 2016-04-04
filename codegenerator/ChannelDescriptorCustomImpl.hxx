
	std::vector<EnumStringMetricDescriptor> getEnumStringMetricDescriptors() const;
	std::vector<NumericMetricDescriptor> getNumericMetricDescriptors() const;
	std::vector<StringMetricDescriptor> getStringMetricDescriptors() const;
	std::vector<RealTimeSampleArrayMetricDescriptor> getRealTimeSampleArrayMetricDescriptors() const;

	ChannelDescriptor & addMetric(const EnumStringMetricDescriptor & source);
	ChannelDescriptor & addMetric(const NumericMetricDescriptor & source);
	ChannelDescriptor & addMetric(const StringMetricDescriptor & source);
	ChannelDescriptor & addMetric(const RealTimeSampleArrayMetricDescriptor & source);

private:
	template<class U, class V>
	void getMetricDescriptors(std::vector<U> & result) const;

	template<class T>
	ChannelDescriptor & addMetricImpl(const T & source);
