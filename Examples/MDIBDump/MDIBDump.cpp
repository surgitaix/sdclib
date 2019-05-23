
#include "SDCLib/SDCLibrary.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/custom/MdibContainer.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ClockDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ClockState.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdsState.h"
#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/ScoDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "OSELib/SDC/SDCConstants.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Util/DebugOut.h"

#include "OSELib/SDC/ServiceManager.h"

#include "osdm.hxx"

#include "Poco/Thread.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"

#include <fstream>

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

std::string stripCharacters(const std::string & input, const std::string & removeChars) {
	std::string str(input);
    str.erase(
        std::remove_if(str.begin(), str.end(), [&](char c){
            return removeChars.find(c) != std::string::npos;
        }),
        str.end()
    );
    return str;
}

std::string stateTypeAsString(const AlertConditionState & ) {
	return "AlertConditionState";
}

std::string stateTypeAsString(const AlertSignalState & ) {
	return "AlertSignalState";
}

std::string stateTypeAsString(const AlertSystemState & ) {
	return "AlertSystemState";
}

std::string stateTypeAsString(const ClockState & ) {
	return "ClockState";
}

std::string stateTypeAsString(const EnumStringMetricState & ) {
	return "EnumStringMetricState";
}

std::string stateTypeAsString(const MdsState & ) {
	return "MdsState";
}

std::string stateTypeAsString(const LimitAlertConditionState & ) {
	return "LimitAlertConditionState";
}

std::string stateTypeAsString(const NumericMetricState & ) {
	return "NumericMetricState";
}

std::string stateTypeAsString(const RealTimeSampleArrayMetricState & ) {
	return "RealTimeSampleArrayMetricState";
}

std::string stateTypeAsString(const StringMetricState & ) {
	return "StringMetricState";
}

template<class StateType>
void validateStates(const MdDescription & mdd, const std::vector<StateType> & states, std::vector<std::string> & stateHandles) {
	for (const auto & state : states) {
		stateHandles.push_back(state.getDescriptorHandle());


		typename StateType::DescriptorType descriptor(state.getDescriptorHandle());
		if (!mdd.findDescriptor(state.getDescriptorHandle(), descriptor)) {
			if (state.getDescriptorHandle()) {
				DebugOut(DebugOut::Default, "MDIBDump") << stateTypeAsString(state) << " with descriptor handle " << state.getDescriptorHandle();
			} else {
				DebugOut(DebugOut::Default, "MDIBDump") << stateTypeAsString(state) << " (without own handle) references non existing descriptor " << state.getDescriptorHandle();
			}
		}
	}
}


template<>
void validateStates(const MDDescription & mdd, const std::vector<ComponentState> & states, std::vector<std::string> & stateHandles) {
	for (const auto & state : states) {
		if (state.hasHandle()) {
			stateHandles.push_back(state.getHandle());
		}

		bool match = false;

		{
			for (const auto & hydramds : mdd.collectAllHydraMDSDescriptors()) {
				if (hydramds.getHandle() == state.getDescriptorHandle()) {
					match |= true;
				}
				if (!hydramds.hasSCO()) {
					continue;
				}
				if (hydramds.getSCO().getHandle() == state.getDescriptorHandle()) {
					match |= true;
				}
			}
		}
		{
			VMDDescriptor descriptor;
			if (mdd.findDescriptor(state.getDescriptorHandle(), descriptor)) {
				match |= true;
			}
		}
		{
			ChannelDescriptor descriptor;
			if (mdd.findDescriptor(state.getDescriptorHandle(), descriptor)) {
				match |= true;
			}
		}

		if (match) {
			continue;
		}

		if (state.hasHandle()) {
			DebugOut(DebugOut::Default, "MDIBDump") << stateTypeAsString(state) << " with handle " << state.getHandle() << " references non existing descriptor " << state.getDescriptorHandle();
		} else {
			DebugOut(DebugOut::Default, "MDIBDump") << stateTypeAsString(state) << " (without own handle) references non existing descriptor " << state.getDescriptorHandle();
		}
	}
}

void validate(const MdibContainer & mdib) {
	std::vector<std::string> descriptorHandles;
	std::vector<std::string> stateHandles;

	const MdDescription mdd(mdib.getMdDescription());
	const MdState mdstate(mdib.getMdState());

	{
		MdsDescriptor mds("");
		if (!mdd.getFirstMdsDescriptor(mds)) {
			DebugOut(DebugOut::Default, "MDIBDump") << "No MDS found!" << std::endl;
			return;
		}
	}

	for (const auto & mds : mdd.collectAllMdsDescriptors()) {
		descriptorHandles.push_back(mds.getHandle());
		if (mds.hasSco()) {
			descriptorHandles.push_back(mds.getSco().getHandle());
		}
	}
	for (const auto & vmd: mdd.collectAllVmdDescriptors()) {
		descriptorHandles.push_back(vmd.getHandle());
	}
	for (const auto & channel : mdd.collectAllChannelDescriptors()) {
		descriptorHandles.push_back(channel.getHandle());
	}
	for (const auto & clockDescriptor : mdd.collectAllClockDescriptors()) {
		descriptorHandles.push_back(clockDescriptor.getHandle());
	}
	for (const auto & metricDescriptor : mdd.collectAllEnumStringMetricDescriptors()) {
		descriptorHandles.push_back(metricDescriptor.getHandle());
	}
	for (const auto & metricDescriptor : mdd.collectAllNumericMetricDescriptors()) {
		descriptorHandles.push_back(metricDescriptor.getHandle());
	}
	for (const auto & metricDescriptor : mdd.collectAllRealTimeSampleArrayMetricDescriptors()) {
		descriptorHandles.push_back(metricDescriptor.getHandle());
	}
	for (const auto & metricDescriptor : mdd.collectAllStringMetricDescriptors()) {
		descriptorHandles.push_back(metricDescriptor.getHandle());
	}

	for (const auto & alertSystem : mdd.collectAllAlertSystemDescriptors()) {
		descriptorHandles.push_back(alertSystem.getHandle());
		for (const auto & alertSignal : alertSystem.getAlertSignalList()) {
			descriptorHandles.push_back(alertSignal.getHandle());
		}
		for (const auto & condition : alertSystem.getAlertConditionList()) {
			descriptorHandles.push_back(condition.getHandle());
		}
		for (const auto & condition : alertSystem.getLimitAlertConditionList()) {
			descriptorHandles.push_back(condition.getHandle());
		}
	}


	{ //verify if all descriptors have a state
		std::vector<std::string> tempDescriptorHandles(descriptorHandles);
		std::sort(tempDescriptorHandles.begin(), tempDescriptorHandles.end());

		CDM::MdState states(*ConvertToCDM::convert(mdstate));
		for (const auto & state : states.State()) {
			const auto iterator(std::find(tempDescriptorHandles.begin(), tempDescriptorHandles.end(), state.DescriptorHandle()));
			if (iterator != tempDescriptorHandles.end()) {
				tempDescriptorHandles.erase(iterator);
			}
		}

		for (const auto & handle : tempDescriptorHandles) {
			DebugOut(DebugOut::Default, "MDIBDump") << "Error: Found descriptor without state. It has handle: " << handle << std::flush;
		}
	}

	validateStates(mdd, mdstate.findAlertSystemStates(), stateHandles);
	validateStates(mdd, mdstate.findAlertSignalStates(), stateHandles);
	validateStates(mdd, mdstate.findAlertConditionStates(), stateHandles);
	validateStates(mdd, mdstate.findClockStates(), stateHandles);
	validateStates(mdd, mdstate.findMdsStates(), stateHandles);
	validateStates(mdd, mdstate.findLimitAlertConditionStates(), stateHandles);
	validateStates(mdd, mdstate.findEnumStringMetricStates(), stateHandles);
	validateStates(mdd, mdstate.findNumericMetricStates(), stateHandles);
	validateStates(mdd, mdstate.findRealTimeSampleArrayMetricStates(), stateHandles);
	validateStates(mdd, mdstate.findStringMetricStates(), stateHandles);

	// check for duplicates
	std::vector<std::string> allHandles;
	allHandles.insert(allHandles.end(), descriptorHandles.begin(), descriptorHandles.end());
	allHandles.insert(allHandles.end(), stateHandles.begin(), stateHandles.end());
	std::sort(allHandles.begin(), allHandles.end());

	if (allHandles.size() > 1) {
		std::vector<std::string>::const_iterator cur_iter(allHandles.begin());
		std::vector<std::string>::const_iterator prev_iter(allHandles.begin());
		++cur_iter;
		while (cur_iter != allHandles.end()) {
			if (*cur_iter == *prev_iter) {
				DebugOut(DebugOut::Default, "MDIBDump") << "Error: Found duplicate handle: " << *cur_iter << std::flush;
			}
			++cur_iter;
			++prev_iter;
		}
	}
	DebugOut(DebugOut::Default, "MDIBDump") << std::flush;
}

int main (int argc, char * argv[])
{
	const std::string testname(argc != 2 ? "Dump MDIBs of all found devices" : "Dump MDIBs of given EPR");
	DebugOut(DebugOut::Default, "MDIBDump") << std::endl << "Startup: " << testname;
	SDCLibrary::getInstance().startup();

	OSELib::SDC::ServiceManager oscpsm;

	while (true) {
		DebugOut(DebugOut::Default, "MDIBDump") << "Refreshing ..." << std::flush;
		Poco::Timestamp refreshStarted;

		std::vector<std::unique_ptr<SDCConsumer> > results;
		if (argc != 2) {
			results = oscpsm.discoverOSCP();
		} else {
			std::unique_ptr<SDCConsumer> result(oscpsm.discoverEndpointReference(std::string(argv[1])));
			if (result != nullptr) {
				results.emplace_back(std::move(result));
			}
		}

		DebugOut(DebugOut::Default, "MDIBDump") << "Found devices with these EPRs: ";

		for (auto & consumer : results) {
			const std::string epr(consumer->getEndpointReference());
			const std::string filename("mdib" + stripCharacters(epr, ".:/\\!?*") + ".xml");

			DebugOut(DebugOut::Default, "MDIBDump") << "Found EPR " << epr << " and dumping to file " << filename;

			try {
				std::ofstream outFile;
				outFile.open(filename, std::ios::trunc);
				Poco::Timestamp dumpStarted;
				outFile << consumer->requestRawMdib();
				DebugOut(DebugOut::Default, "MDIBDump") << "   -> took " << Poco::DateTimeFormatter::format(Poco::Timespan(dumpStarted.elapsed()), "%s:%i") << " s:ms." << std::endl;
				outFile.close();
			} catch (...) {
				DebugOut(DebugOut::Default, "MDIBDump") << "Error writing file." << std::endl;
			}

			const MdibContainer mdib(consumer->getMdib());
			validate(mdib);
		}

		for (auto & consumer : results) {
			consumer->disconnect();
			consumer.reset();
		}
		results.clear();
		DebugOut(DebugOut::Default, "MDIBDump") << "Done after " << Poco::DateTimeFormatter::format(Poco::Timespan(refreshStarted.elapsed()), "%s:%i") << " s:ms." << std::endl << std::flush;

		if (argc != 2) {
			Poco::Thread::sleep(5000);
		}
	}

	Poco::Thread::sleep(2000);

	DebugOut(DebugOut::Default, "MDIBDump") << "Shutdown: " << testname << std::endl;
}

