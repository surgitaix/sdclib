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
 *  MetaData.h
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

#ifndef METADATA_H_
#define METADATA_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class MetaData {
private:
	MetaData(const CDM::MetaData & object);
	operator CDM::MetaData() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	MetaData(
	); 
	MetaData(const MetaData & object);
	virtual ~MetaData();
    
    void copyFrom(const MetaData & object);
    MetaData & operator=(const MetaData & object);
    
    typedef CDM::MetaData WrappedType;

	MetaData & setLotNumber(const std::string & value);
	std::string getLotNumber() const;
	bool getLotNumber(std::string & out) const;
	bool hasLotNumber() const;

	MetaData & setManufactureDate(const xml_schema::DateTime & value);
	xml_schema::DateTime getManufactureDate() const;
	bool getManufactureDate(xml_schema::DateTime & out) const;
	bool hasManufactureDate() const;

	MetaData & setExpirationDate(const xml_schema::DateTime & value);
	xml_schema::DateTime getExpirationDate() const;
	bool getExpirationDate(xml_schema::DateTime & out) const;
	bool hasExpirationDate() const;

	MetaData & setModelNumber(const std::string & value);
	std::string getModelNumber() const;
	bool getModelNumber(std::string & out) const;
	bool hasModelNumber() const;

	MetaData & addUdi(const Udi & value);
	std::vector<Udi> getUdiList() const;
	void clearUdiList();
	
	MetaData & addManufacturer(const LocalizedText & value);
	std::vector<LocalizedText> getManufacturerList() const;
	void clearManufacturerList();
	
	MetaData & addModelName(const LocalizedText & value);
	std::vector<LocalizedText> getModelNameList() const;
	void clearModelNameList();
	
	MetaData & addSerialNumber(const std::string & value);
	std::vector<std::string> getSerialNumberList() const;
	void clearSerialNumberList();
	
private:
	std::shared_ptr<CDM::MetaData> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* METADATA_H_ */
