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
 *  Author: besting, buerger, roehser
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

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "DataModel/osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class ProductionSpecification {
private:
	ProductionSpecification(const CDM::ProductionSpecification & object);
	operator CDM::ProductionSpecification() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	ProductionSpecification(
		CodedValue spectype
		,
		std::string productionspec
	);
private:
	ProductionSpecification(){};
public:
	ProductionSpecification(const ProductionSpecification & object);
	virtual ~ProductionSpecification();

    void copyFrom(const ProductionSpecification & object);
    ProductionSpecification & operator=(const ProductionSpecification & object);

    typedef CDM::ProductionSpecification WrappedType;

	ProductionSpecification & setSpecType(const CodedValue & value);
	CodedValue getSpecType() const;

	ProductionSpecification & setProductionSpec(const std::string & value);
	std::string getProductionSpec() const;

	ProductionSpecification & setComponentId(const InstanceIdentifier & value);
	InstanceIdentifier getComponentId() const;
	bool getComponentId(InstanceIdentifier & out) const;
	bool hasComponentId() const;

private:
	std::shared_ptr<CDM::ProductionSpecification> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* PRODUCTIONSPECIFICATION_H_ */
