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
 *  OrderDetail.h
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

#ifndef ORDERDETAIL_H_
#define ORDERDETAIL_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OrderDetail {
private:
	OrderDetail(const CDM::OrderDetail & object);
	operator CDM::OrderDetail() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class OSCPProvider;
	friend class OSCPConsumer;
	friend class MdState;
public:
	OrderDetail(
	); 
	OrderDetail(const OrderDetail & object);
	virtual ~OrderDetail();
    
    void copyFrom(const OrderDetail & object);
    OrderDetail & operator=(const OrderDetail & object);
    
    typedef CDM::OrderDetail WrappedType;

	OrderDetail & setStart(const xml_schema::DateTime & value);
	xml_schema::DateTime getStart() const;
	bool getStart(xml_schema::DateTime & out) const;
	bool hasStart() const;

	OrderDetail & setEnd(const xml_schema::DateTime & value);
	xml_schema::DateTime getEnd() const;
	bool getEnd(xml_schema::DateTime & out) const;
	bool hasEnd() const;

	OrderDetail & addPerformer(const PersonParticipation & value);
	std::vector<PersonParticipation> getPerformerList() const;
	void clearPerformerList();
	
	OrderDetail & addService(const CodedValue & value);
	std::vector<CodedValue> getServiceList() const;
	void clearServiceList();
	
	OrderDetail & addImagingProcedure(const ImagingProcedure & value);
	std::vector<ImagingProcedure> getImagingProcedureList() const;
	void clearImagingProcedureList();
	
private:
	std::shared_ptr<CDM::OrderDetail> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ORDERDETAIL_H_ */
