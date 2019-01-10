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
 *  Udi.h
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

#ifndef UDI_H_
#define UDI_H_

#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class Udi {
private:
	Udi(const CDM::Udi & object);
	operator CDM::Udi() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	Udi(
		std::string deviceidentifier
		,
		std::string humanreadableform
		,
		InstanceIdentifier issuer
	);
private:
	Udi(){};
public:
	Udi(const Udi & object);
	virtual ~Udi();

    void copyFrom(const Udi & object);
    Udi & operator=(const Udi & object);

    typedef CDM::Udi WrappedType;

	Udi & setDeviceIdentifier(const std::string & value);
	std::string getDeviceIdentifier() const;

	Udi & setHumanReadableForm(const std::string & value);
	std::string getHumanReadableForm() const;

	Udi & setIssuer(const InstanceIdentifier & value);
	InstanceIdentifier getIssuer() const;

	Udi & setJurisdiction(const InstanceIdentifier & value);
	InstanceIdentifier getJurisdiction() const;
	bool getJurisdiction(InstanceIdentifier & out) const;
	bool hasJurisdiction() const;

private:
	std::shared_ptr<CDM::Udi> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* UDI_H_ */
