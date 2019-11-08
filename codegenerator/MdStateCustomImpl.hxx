
	// use this API function to get a copy of the MDIB's internal state
	template<class TState>
	std::unique_ptr<TState> findState(const std::string & handle) const;

	std::vector<ActivateOperationState> findActivateOperationStates() const;
	std::vector<AlertConditionState> findAlertConditionStates() const;
	std::vector<AlertSignalState> findAlertSignalStates() const;
	std::vector<AlertSystemState> findAlertSystemStates() const;
	std::vector<ClockState> findClockStates() const;
	std::vector<EnsembleContextState> findEnsembleContextStates() const;
	std::vector<EnumStringMetricState> findEnumStringMetricStates() const;
	std::vector<MdsState> findMdsStates() const;
	std::vector<LimitAlertConditionState> findLimitAlertConditionStates() const;
	std::vector<LocationContextState> findLocationContextStates() const;
	std::vector<NumericMetricState> findNumericMetricStates() const;
	std::vector<OperatorContextState> findOperatorContextStates() const;
	std::vector<PatientContextState> findPatientContextStates() const;
	std::vector<RealTimeSampleArrayMetricState> findRealTimeSampleArrayMetricStates() const;
	std::vector<StringMetricState> findStringMetricStates() const;
	std::vector<WorkflowContextState> findWorkflowContextStates() const;

    MdState & addState(const AlertConditionState & source);
    MdState & addState(const AlertSignalState & source);
    MdState & addState(const AlertSystemState & source);
    MdState & addState(const ClockState & source);
    MdState & addState(const EnsembleContextState & source);
    MdState & addState(const EnumStringMetricState & source);
    MdState & addState(const LocationContextState & source);
    MdState & addState(const LimitAlertConditionState & source);
    MdState & addState(const MdsState & source);
    MdState & addState(const MeansContextState & source);
    MdState & addState(const NumericMetricState & source);
    MdState & addState(const OperatorContextState & source);
    MdState & addState(const PatientContextState & source);
    MdState & addState(const RealTimeSampleArrayMetricState & source);
    MdState & addState(const DistributionSampleArrayMetricState & source);
    MdState & addState(const StringMetricState & source);
    MdState & addState(const WorkflowContextState & source);
    MdState & addState(const VmdState & source);
    MdState & addState(const ChannelState & source);
    MdState & addState(const ScoState & source);
	MdState & addState(const SystemContextState & source);

private:
    // these classes are for internal finding states in the MDIB
    // the initialize objects which reference is processed
	bool findState(const std::string & handle, ActivateOperationState & outState) const;
	bool findState(const std::string & handle, AlertConditionState & outState) const;
	bool findState(const std::string & handle, AlertSignalState & outState) const;
	bool findState(const std::string & handle, AlertSystemState & outState) const;
	bool findState(const std::string & handle, ClockState & outState) const;
	bool findState(const std::string & handle, EnsembleContextState & outState) const;
	bool findState(const std::string & handle, EnumStringMetricState & outState) const;
    bool findState(const std::string & handle, MdsState & outState) const;
	bool findState(const std::string & handle, LimitAlertConditionState & outState) const;
	bool findState(const std::string & handle, LocationContextState & outState) const;
	bool findState(const std::string & handle, NumericMetricState & outState) const;
	bool findState(const std::string & handle, OperatorContextState & outState) const;
	bool findState(const std::string & handle, PatientContextState & outState) const;
	bool findState(const std::string & handle, RealTimeSampleArrayMetricState & outState) const;
	bool findState(const std::string & handle, StringMetricState & outState) const;
	bool findState(const std::string & handle, WorkflowContextState & outState) const;
	bool findState(const std::string & handle, VmdState & outState) const;
	bool findState(const std::string & handle, ChannelState & outState) const;
	bool findState(const std::string & handle, ScoState & outState) const;
	bool findState(const std::string & handle, SystemContextState & outState) const;

	template <class WrapperStateDescriptorType>
    bool findStateImpl(const std::string & handle, WrapperStateDescriptorType & out) const;

    template <class WrapperStateDescriptorType>
    MdState & addStateImpl(const WrapperStateDescriptorType & source);

    template <class WrapperStateDescriptorType, class ForbiddenType>
    std::vector<WrapperStateDescriptorType> findStatesImpl() const;
    template <class WrapperStateDescriptorType>
    std::vector<WrapperStateDescriptorType> findStatesImpl() const;
