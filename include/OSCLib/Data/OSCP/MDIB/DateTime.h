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
 *  DateTime.h
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

#ifndef DATETIME_H_
#define DATETIME_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class DateTime {
private:
	DateTime(const CDM::DateTime & object);
	operator CDM::DateTime() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	DateTime();
	DateTime(const DateTime & object);
	virtual ~DateTime();
    
    void copyFrom(const DateTime & object);
    DateTime & operator=(const DateTime & object);
    
    typedef CDM::DateTime WrappedType;

	DateTime & setyear(const int & value);
	int getyear() const;

	DateTime & setmonth(const unsigned short & value);
	unsigned short getmonth() const;

	DateTime & setday(const unsigned short & value);
	unsigned short getday() const;

	DateTime & sethours(const unsigned short & value);
	unsigned short gethours() const;

	DateTime & setminutes(const unsigned short & value);
	unsigned short getminutes() const;

	DateTime & setseconds(const double & value);
	double getseconds() const;

private:
	std::shared_ptr<CDM::DateTime> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* DATETIME_H_ */
