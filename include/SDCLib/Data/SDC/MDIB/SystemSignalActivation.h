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
 *  SystemSignalActivation.h
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#ifndef SYSTEMSIGNALACTIVATION_H_
#define SYSTEMSIGNALACTIVATION_H_

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "DataModel/osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class SystemSignalActivation
{
private:
	SystemSignalActivation(const CDM::SystemSignalActivation & object);
	operator CDM::SystemSignalActivation() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	SystemSignalActivation(
		AlertSignalManifestation manifestation
		,
		AlertActivation state
	);
private:
	SystemSignalActivation(){};
public:
	SystemSignalActivation(const SystemSignalActivation& object);
	virtual ~SystemSignalActivation() = default;

    void copyFrom(const SystemSignalActivation& object);
    SystemSignalActivation & operator=(const SystemSignalActivation& object);

    typedef CDM::SystemSignalActivation WrappedType;

	SystemSignalActivation & setManifestation(const AlertSignalManifestation & value);
	AlertSignalManifestation getManifestation() const;

	SystemSignalActivation & setState(const AlertActivation & value);
	AlertActivation getState() const;

private:
	std::shared_ptr<CDM::SystemSignalActivation> data = nullptr;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* SYSTEMSIGNALACTIVATION_H_ */
