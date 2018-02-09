
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

} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */
