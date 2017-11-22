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
 *  NeonatalPatientDemographicsCoreData.h
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

#ifndef NEONATALPATIENTDEMOGRAPHICSCOREDATA_H_
#define NEONATALPATIENTDEMOGRAPHICSCOREDATA_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class NeonatalPatientDemographicsCoreData {
private:
	NeonatalPatientDemographicsCoreData(const CDM::NeonatalPatientDemographicsCoreData & object);
	operator CDM::NeonatalPatientDemographicsCoreData() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class OSCPProvider;
	friend class OSCPConsumer;
public:
	NeonatalPatientDemographicsCoreData(
	); 
	NeonatalPatientDemographicsCoreData(const NeonatalPatientDemographicsCoreData & object);
	virtual ~NeonatalPatientDemographicsCoreData();
    
    void copyFrom(const NeonatalPatientDemographicsCoreData & object);
    NeonatalPatientDemographicsCoreData & operator=(const NeonatalPatientDemographicsCoreData & object);
    
    typedef CDM::NeonatalPatientDemographicsCoreData WrappedType;

	NeonatalPatientDemographicsCoreData & setGivenname(const std::string & value);
	std::string getGivenname() const;
	bool getGivenname(std::string & out) const;
	bool hasGivenname() const;

	NeonatalPatientDemographicsCoreData & setFamilyname(const std::string & value);
	std::string getFamilyname() const;
	bool getFamilyname(std::string & out) const;
	bool hasFamilyname() const;

	NeonatalPatientDemographicsCoreData & setBirthname(const std::string & value);
	std::string getBirthname() const;
	bool getBirthname(std::string & out) const;
	bool hasBirthname() const;

	NeonatalPatientDemographicsCoreData & setTitle(const std::string & value);
	std::string getTitle() const;
	bool getTitle(std::string & out) const;
	bool hasTitle() const;

	NeonatalPatientDemographicsCoreData & addMiddlename(const std::string & value);
	std::vector<std::string> getMiddlenameList() const;
	void clearMiddlenameList();
	
	NeonatalPatientDemographicsCoreData & setSex(const Sex & value);
	Sex getSex() const;
	bool getSex(Sex & out) const;
	bool hasSex() const;

	NeonatalPatientDemographicsCoreData & setPatientType(const PatientType & value);
	PatientType getPatientType() const;
	bool getPatientType(PatientType & out) const;
	bool hasPatientType() const;

	NeonatalPatientDemographicsCoreData & setDateOfBirth(const DateOfBirth & value);
	DateOfBirth getDateOfBirth() const;
	bool getDateOfBirth(DateOfBirth & out) const;
	bool hasDateOfBirth() const;

	NeonatalPatientDemographicsCoreData & setHeight(const Measurement & value);
	Measurement getHeight() const;
	bool getHeight(Measurement & out) const;
	bool hasHeight() const;

	NeonatalPatientDemographicsCoreData & setWeight(const Measurement & value);
	Measurement getWeight() const;
	bool getWeight(Measurement & out) const;
	bool hasWeight() const;

	NeonatalPatientDemographicsCoreData & setRace(const CodedValue & value);
	CodedValue getRace() const;
	bool getRace(CodedValue & out) const;
	bool hasRace() const;

	NeonatalPatientDemographicsCoreData & setGestationalAge(const Measurement & value);
	Measurement getGestationalAge() const;
	bool getGestationalAge(Measurement & out) const;
	bool hasGestationalAge() const;

	NeonatalPatientDemographicsCoreData & setBirthLength(const Measurement & value);
	Measurement getBirthLength() const;
	bool getBirthLength(Measurement & out) const;
	bool hasBirthLength() const;

	NeonatalPatientDemographicsCoreData & setBirthWeight(const Measurement & value);
	Measurement getBirthWeight() const;
	bool getBirthWeight(Measurement & out) const;
	bool hasBirthWeight() const;

	NeonatalPatientDemographicsCoreData & setHeadCircumference(const Measurement & value);
	Measurement getHeadCircumference() const;
	bool getHeadCircumference(Measurement & out) const;
	bool hasHeadCircumference() const;

	NeonatalPatientDemographicsCoreData & setMother(const PersonReference & value);
	PersonReference getMother() const;
	bool getMother(PersonReference & out) const;
	bool hasMother() const;

private:
	std::shared_ptr<CDM::NeonatalPatientDemographicsCoreData> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* NEONATALPATIENTDEMOGRAPHICSCOREDATA_H_ */
