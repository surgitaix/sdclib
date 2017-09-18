
	std::vector<ActivateOperationDescriptor> collectAllActivateOperationDescriptors() const;
	std::vector<SetAlertStateOperationDescriptor> collectAllSetAlertStateOperationDescriptors() const;
	std::vector<SetContextStateOperationDescriptor> collectAllSetContextOperationDescriptors() const;
	std::vector<SetRangeOperationDescriptor> collectAllSetRangeOperationDescriptors() const;
	std::vector<SetStringOperationDescriptor> collectAllSetStringOperationDescriptors() const;
	std::vector<SetValueOperationDescriptor> collectAllSetValueOperationDescriptors() const;

private:
	template <class WrapperOperationDescriptorType>
	void collectOperationDescriptorImpl(std::vector<WrapperOperationDescriptorType> & out) const;
