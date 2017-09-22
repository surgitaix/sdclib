

InvocationState ConvertFromCDM::convert(const MDM::InvocationState & source) {
	switch (source) {
		case MDM::InvocationState::Wait: return InvocationState::Wait;
		case MDM::InvocationState::Start: return InvocationState::Start;
		case MDM::InvocationState::Cnclld: return InvocationState::Cnclld;
		case MDM::InvocationState::CnclldMan: return InvocationState::CnclldMan;
		case MDM::InvocationState::Fin: return InvocationState::Fin;
		case MDM::InvocationState::FinMod: return InvocationState::FinMod;
		case MDM::InvocationState::Fail: return InvocationState::Fail;
	}
	throw std::runtime_error("Illegal value for InvocationState");
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
