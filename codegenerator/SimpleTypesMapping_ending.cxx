
// non-auto generated here
std::string EnumToString::convert(InvocationState source) {
	switch (source) {
		case InvocationState::Wait: return "Wait";
		case InvocationState::Start: return "Start";
		case InvocationState::Cnclld: return "Cnclld";
		case InvocationState::CnclldMan: return "CnclldMan";
		case InvocationState::Fin: return "Fin";
		case InvocationState::FinMod: return "FinMod";
		case InvocationState::Fail: return "Fail";
	}
	throw std::runtime_error("Illegal value for InvocationState");
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
