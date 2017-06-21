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
 * MDIBContainer.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting
 */

#ifndef MDIBCONTAINER_H_
#define MDIBCONTAINER_H_

#include "MDIB-fwd.h"

#include <string>

namespace OSCLib {
namespace Data {
namespace OSCP {

class MDIBContainer {
public:
    MDIBContainer();
    virtual ~MDIBContainer();

    void setMDDescription(const MdDescription & mdd);
    MdDescription getMDDescription() const;
    void setMDState(const MdState & mds);
    MdState getMDState() const;
    void setMDIBVersion(const unsigned long long int version);
    unsigned long long int getMDIBVersion() const;

    typedef CDM::Mdib WrappedType;

	bool findDescriptor(const std::string & handle, AlertConditionDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, AlertSignalDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, AlertSystemDescriptor & outDescriptor) const;
	bool findDescriptor(const std::string & handle, LimitAlertConditionDescriptor & outDescriptor) const;

    bool findDescriptor(const std::string & handle, EnumStringMetricDescriptor & outDescriptor) const;
    bool findDescriptor(const std::string & handle, NumericMetricDescriptor & outDescriptor) const;
    bool findDescriptor(const std::string & handle, RealTimeSampleArrayMetricDescriptor & outDescriptor) const;
    bool findDescriptor(const std::string & handle, StringMetricDescriptor & outDescriptor) const;

    bool findState(const std::string & handle, EnumStringMetricState & outState) const;
	bool findState(const std::string & handle, NumericMetricState & outState) const;
	bool findState(const std::string & handle, RealTimeSampleArrayMetricState & outState) const;
	bool findState(const std::string & handle, StringMetricState & outState) const;

private:
    std::shared_ptr<MdDescription> mddescription;
    std::shared_ptr<MdState> mdstate;
    unsigned long long int mdibVersion;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* MDIBCONTAINER_H_ */
