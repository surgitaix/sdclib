
// non-auto generated: invocation state from message model -> transform to MDM
MDM::InvocationState ConvertToCDM::convert(const InvocationState & source) {
	switch (source) {
		case InvocationState::Wait: return MDM::InvocationState::Wait;
		case InvocationState::Start: return MDM::InvocationState::Start;
		case InvocationState::Cnclld: return MDM::InvocationState::Cnclld;
		case InvocationState::CnclldMan: return MDM::InvocationState::CnclldMan;
		case InvocationState::Fin: return MDM::InvocationState::Fin;
		case InvocationState::FinMod: return MDM::InvocationState::FinMod;
		case InvocationState::Fail: return MDM::InvocationState::Fail;
	}
	throw std::runtime_error("Illegal value for InvocationState");
}

template <>
std::unique_ptr<typename MdibContainer::WrappedType> ConvertToCDM::convert(const MdibContainer & source) {
	// todo: replace sequence id
	std::unique_ptr<typename MdibContainer::WrappedType> mdibContainer = std::unique_ptr<typename MdibContainer::WrappedType>(new MdibContainer::WrappedType(xml_schema::Uri("0")));
	mdibContainer->MdDescription(convert(source.getMdDescription()));
	mdibContainer->MdState(convert(source.getMdState()));
	mdibContainer->MdibVersion(source.getMdibVersion());
	return mdibContainer;
}

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
