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
 *  ProductionSpecification.h
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

#ifndef PRODUCTIONSPECIFICATION_H_
#define PRODUCTIONSPECIFICATION_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class ProductionSpecification {
private:
	ProductionSpecification(const CDM::ProductionSpecification & object);
	operator CDM::ProductionSpecification() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	ProductionSpecification();
	ProductionSpecification(const ProductionSpecification & object);
	virtual ~ProductionSpecification();
    
    void copyFrom(const ProductionSpecification & object);
    ProductionSpecification & operator=(const ProductionSpecification & object);
    
    typedef CDM::ProductionSpecification WrappedType;

	ProductionSpecification & setspecType(const CodedValue & value);
	CodedValue getspecType() const;

	ProductionSpecification & setproductionSpec(const std::string & value);
	std::string getproductionSpec() const;

	ProductionSpecification & setcomponentId(const InstanceIdentifier & value);
	InstanceIdentifier getcomponentId() const;
	bool getcomponentId(InstanceIdentifier & out) const;
	bool hascomponentId() const;

private:
	std::shared_ptr<CDM::ProductionSpecification> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* PRODUCTIONSPECIFICATION_H_ */
