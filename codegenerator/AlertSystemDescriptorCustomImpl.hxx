	AlertSystemDescriptor & addAlertCondition(const AlertConditionDescriptor & value);
	std::vector<AlertConditionDescriptor> getAlertConditions() const;

	AlertSystemDescriptor & addLimitAlertCondition(const LimitAlertConditionDescriptor & source);
	std::vector<LimitAlertConditionDescriptor> getLimitAlertConditions() const;
