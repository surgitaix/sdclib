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
 *  BaseDemographics.h
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

#ifndef BASEDEMOGRAPHICS_H_
#define BASEDEMOGRAPHICS_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class BaseDemographics {
private:
	BaseDemographics(const CDM::BaseDemographics & object);
	operator CDM::BaseDemographics() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	BaseDemographics(
	); 
	BaseDemographics(const BaseDemographics & object);
	virtual ~BaseDemographics();
    
    void copyFrom(const BaseDemographics & object);
    BaseDemographics & operator=(const BaseDemographics & object);
    
    typedef CDM::BaseDemographics WrappedType;

	BaseDemographics & setGivenname(const std::string & value);
	std::string getGivenname() const;
	bool getGivenname(std::string & out) const;
	bool hasGivenname() const;

	BaseDemographics & setFamilyname(const std::string & value);
	std::string getFamilyname() const;
	bool getFamilyname(std::string & out) const;
	bool hasFamilyname() const;

	BaseDemographics & setBirthname(const std::string & value);
	std::string getBirthname() const;
	bool getBirthname(std::string & out) const;
	bool hasBirthname() const;

	BaseDemographics & setTitle(const std::string & value);
	std::string getTitle() const;
	bool getTitle(std::string & out) const;
	bool hasTitle() const;

	BaseDemographics & addMiddlename(const std::string & value);
	std::vector<std::string> getMiddlenameList() const;
	void clearMiddlenameList();
	
private:
	std::shared_ptr<CDM::BaseDemographics> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* BASEDEMOGRAPHICS_H_ */
