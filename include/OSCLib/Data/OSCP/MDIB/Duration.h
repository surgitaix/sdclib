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
 *  Duration.h
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#ifndef DURATION_H_
#define DURATION_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class Duration {
private:
	Duration(const CDM::Duration & object);
	operator CDM::Duration() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	Duration();
	Duration(const Duration & object);
	virtual ~Duration();
    
    void copyFrom(const Duration & object);
    Duration & operator=(const Duration & object);
    
    typedef CDM::Duration WrappedType;

	Duration & setnegative(const bool & value);
	bool getnegative() const;

	Duration & setyears(const unsigned int & value);
	unsigned int getyears() const;

	Duration & setmonths(const unsigned int & value);
	unsigned int getmonths() const;

	Duration & setdays(const unsigned int & value);
	unsigned int getdays() const;

	Duration & sethours(const unsigned int & value);
	unsigned int gethours() const;

	Duration & setminutes(const unsigned int & value);
	unsigned int getminutes() const;

	Duration & setseconds(const double & value);
	double getseconds() const;

private:
	std::shared_ptr<CDM::Duration> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* DURATION_H_ */
