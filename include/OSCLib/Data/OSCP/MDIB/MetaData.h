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
 *  Author: besting, roehser
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
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
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
public:
	MetaData();
	MetaData(const MetaData & object);
	virtual ~MetaData();
    
    void copyFrom(const MetaData & object);
    MetaData & operator=(const MetaData & object);
    
    typedef CDM::MetaData WrappedType;

	MetaData & setModelNumber(const std::string & value);
	std::string getModelNumber() const;
	bool getModelNumber(std::string & out) const;
	bool hasModelNumber() const;

	MetaData & addUdi(const Udi & value);
	std::vector<Udi> getUdiLists() const;
	void clearUdiLists();
	
	MetaData & addManufacturer(const LocalizedText & value);
	std::vector<LocalizedText> getManufacturerLists() const;
	void clearManufacturerLists();
	
	MetaData & addModelName(const LocalizedText & value);
	std::vector<LocalizedText> getModelNameLists() const;
	void clearModelNameLists();
	
	MetaData & addSerialNumber(const std::string & value);
	std::vector<std::string> getSerialNumberLists() const;
	void clearSerialNumberLists();
	
private:
	std::shared_ptr<CDM::MetaData> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* METADATA_H_ */
