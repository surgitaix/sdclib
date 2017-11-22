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
 *  PatientDemographicsCoreData.h
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

#ifndef PATIENTDEMOGRAPHICSCOREDATA_H_
#define PATIENTDEMOGRAPHICSCOREDATA_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class PatientDemographicsCoreData {
private:
	PatientDemographicsCoreData(const CDM::PatientDemographicsCoreData & object);
	operator CDM::PatientDemographicsCoreData() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class OSCPProvider;
	friend class OSCPConsumer;
public:
	PatientDemographicsCoreData(
	); 
	PatientDemographicsCoreData(const PatientDemographicsCoreData & object);
	virtual ~PatientDemographicsCoreData();
    
    void copyFrom(const PatientDemographicsCoreData & object);
    PatientDemographicsCoreData & operator=(const PatientDemographicsCoreData & object);
    
    typedef CDM::PatientDemographicsCoreData WrappedType;

	PatientDemographicsCoreData & setGivenname(const std::string & value);
	std::string getGivenname() const;
	bool getGivenname(std::string & out) const;
	bool hasGivenname() const;

	PatientDemographicsCoreData & setFamilyname(const std::string & value);
	std::string getFamilyname() const;
	bool getFamilyname(std::string & out) const;
	bool hasFamilyname() const;

	PatientDemographicsCoreData & setBirthname(const std::string & value);
	std::string getBirthname() const;
	bool getBirthname(std::string & out) const;
	bool hasBirthname() const;

	PatientDemographicsCoreData & setTitle(const std::string & value);
	std::string getTitle() const;
	bool getTitle(std::string & out) const;
	bool hasTitle() const;

	PatientDemographicsCoreData & addMiddlename(const std::string & value);
	std::vector<std::string> getMiddlenameList() const;
	void clearMiddlenameList();
	
	PatientDemographicsCoreData & setSex(const Sex & value);
	Sex getSex() const;
	bool getSex(Sex & out) const;
	bool hasSex() const;

	PatientDemographicsCoreData & setPatientType(const PatientType & value);
	PatientType getPatientType() const;
	bool getPatientType(PatientType & out) const;
	bool hasPatientType() const;

	PatientDemographicsCoreData & setDateOfBirth(const DateOfBirth & value);
	DateOfBirth getDateOfBirth() const;
	bool getDateOfBirth(DateOfBirth & out) const;
	bool hasDateOfBirth() const;

	PatientDemographicsCoreData & setHeight(const Measurement & value);
	Measurement getHeight() const;
	bool getHeight(Measurement & out) const;
	bool hasHeight() const;

	PatientDemographicsCoreData & setWeight(const Measurement & value);
	Measurement getWeight() const;
	bool getWeight(Measurement & out) const;
	bool hasWeight() const;

	PatientDemographicsCoreData & setRace(const CodedValue & value);
	CodedValue getRace() const;
	bool getRace(CodedValue & out) const;
	bool hasRace() const;

private:
	std::shared_ptr<CDM::PatientDemographicsCoreData> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* PATIENTDEMOGRAPHICSCOREDATA_H_ */
