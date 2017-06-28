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
 *  LocationDetail.h
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

#ifndef LOCATIONDETAIL_H_
#define LOCATIONDETAIL_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class LocationDetail {
private:
	LocationDetail(const CDM::LocationDetail & object);
	operator CDM::LocationDetail() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	LocationDetail();
	LocationDetail(const LocationDetail & object);
	virtual ~LocationDetail();
    
    void copyFrom(const LocationDetail & object);
    LocationDetail & operator=(const LocationDetail & object);
    
    typedef CDM::LocationDetail WrappedType;

	LocationDetail & setPoC(const string & value);
	string getPoC() const;
	bool getPoC(string & out) const;
	bool hasPoC() const;

	LocationDetail & setRoom(const string & value);
	string getRoom() const;
	bool getRoom(string & out) const;
	bool hasRoom() const;

	LocationDetail & setBed(const string & value);
	string getBed() const;
	bool getBed(string & out) const;
	bool hasBed() const;

	LocationDetail & setFacility(const string & value);
	string getFacility() const;
	bool getFacility(string & out) const;
	bool hasFacility() const;

	LocationDetail & setBuilding(const string & value);
	string getBuilding() const;
	bool getBuilding(string & out) const;
	bool hasBuilding() const;

	LocationDetail & setFloor(const string & value);
	string getFloor() const;
	bool getFloor(string & out) const;
	bool hasFloor() const;

private:
	std::shared_ptr<CDM::LocationDetail> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* LOCATIONDETAIL_H_ */
