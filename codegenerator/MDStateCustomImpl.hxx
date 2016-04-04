
	bool findState(const std::string & handle, AlertConditionState & outState) const;
	bool findState(const std::string & handle, AlertSignalState & outState) const;
	bool findState(const std::string & handle, AlertSystemState & outState) const;
	bool findState(const std::string & handle, ClockState & outState) const;
	bool findState(const std::string & handle, ComponentState & outState) const;
	bool findState(const std::string & handle, EnsembleContextState & outState) const;
	bool findState(const std::string & handle, EnumStringMetricState & outState) const;
    bool findState(const std::string & handle, HydraMDSState & outState) const;
	bool findState(const std::string & handle, LimitAlertConditionState & outState) const;
	bool findState(const std::string & handle, LocationContextState & outState) const;
	bool findState(const std::string & handle, NumericMetricState & outState) const;
	bool findState(const std::string & handle, OperatorContextState & outState) const;
	bool findState(const std::string & handle, PatientContextState & outState) const;
	bool findState(const std::string & handle, RealTimeSampleArrayMetricState & outState) const;
	bool findState(const std::string & handle, StringMetricState & outState) const;
	bool findState(const std::string & handle, WorkflowContextState & outState) const;

	std::vector<AlertConditionState> findAlertConditionStates() const;
	std::vector<AlertSignalState> findAlertSignalStates() const;
	std::vector<AlertSystemState> findAlertSystemStates() const;
	std::vector<ClockState> findClockStates() const;
	std::vector<ComponentState> findComponentStates() const;
	std::vector<EnsembleContextState> findEnsembleContextStates() const;
	std::vector<EnumStringMetricState> findEnumStringMetricStates() const;
	std::vector<HydraMDSState> findHydraMDSStates() const;
	std::vector<LimitAlertConditionState> findLimitAlertConditionStates() const;
	std::vector<LocationContextState> findLocationContextStates() const;
	std::vector<NumericMetricState> findNumericMetricStates() const;
	std::vector<OperatorContextState> findOperatorContextStates() const;
	std::vector<PatientContextState> findPatientContextStates() const;
	std::vector<RealTimeSampleArrayMetricState> findRealTimeSampleArrayMetricStates() const;
	std::vector<StringMetricState> findStringMetricStates() const;
	std::vector<WorkflowContextState> findWorkflowContextStates() const;

    MDState & addState(const AlertConditionState & source);
    MDState & addState(const AlertSignalState & source);
    MDState & addState(const AlertSystemState & source);
    MDState & addState(const ClockState & source);
    MDState & addState(const ComponentState & source);
    MDState & addState(const EnsembleContextState & source);
    MDState & addState(const EnumStringMetricState & source);
    MDState & addState(const LocationContextState & source);
    MDState & addState(const LimitAlertConditionState & source);
    MDState & addState(const HydraMDSState & source);
    MDState & addState(const NumericMetricState & source);
    MDState & addState(const OperationState & source);
    MDState & addState(const OperatorContextState & source);
    MDState & addState(const PatientContextState & source);
    MDState & addState(const RealTimeSampleArrayMetricState & source);
    MDState & addState(const StringMetricState & source);
    MDState & addState(const WorkflowContextState & source);

private:
    template <class WrapperStateDescriptorType>
    bool findStateImpl(const std::string & handle, WrapperStateDescriptorType & out) const;

    template <class WrapperStateDescriptorType>
    MDState & addStateImpl(const WrapperStateDescriptorType & source);

    template <class WrapperStateDescriptorType, class ForbiddenType>
    std::vector<WrapperStateDescriptorType> findStatesImpl() const;
    template <class WrapperStateDescriptorType>
    std::vector<WrapperStateDescriptorType> findStatesImpl() const;
