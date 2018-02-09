/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/*
 * MDIBContainer.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#include "OSCLib/Data/SDC/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/SDC/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/SDC/MDIB/LimitAlertConditionDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MdDescription.h"
#include "OSCLib/Data/SDC/MDIB/custom/MdibContainer.h"
#include "OSCLib/Data/SDC/MDIB/MdState.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "OSCLib/Data/SDC/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/StringMetricState.h"
#include "OSCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"

#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace SDC {

MdibContainer::MdibContainer() :
		mddescription(new MdDescription()),
		mdstate(new MdState()),
		mdibVersion(0) {

}

MdibContainer::~MdibContainer() {

}

void MdibContainer::setMdDescription(const MdDescription & source) {
    *mddescription = source;
}

MdDescription MdibContainer::getMdDescription() const {
    return *mddescription;
}

void MdibContainer::setMdState(const MdState & source) {
    *mdstate = source;
}

MdState MdibContainer::getMdState() const {
    return *mdstate;
}

void MdibContainer::setMdibVersion(const unsigned long long int version) {
	mdibVersion = version;
}
unsigned long long int MdibContainer::getMdibVersion() const {
	return mdibVersion;
}

template<class TDescriptor>
std::unique_ptr<TDescriptor> MdibContainer::findDescriptor(const std::string & handle) const {
	return mddescription->findDescriptor<TDescriptor>(handle);
}

template<class TState>
std::unique_ptr<TState> MdibContainer::findState(const std::string & handle) const {
	return mdstate->findState<TState>(handle);
}



} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */
