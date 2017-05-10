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
 *  Order.h
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

#ifndef ORDER_H_
#define ORDER_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class Order {
private:
	Order(const CDM::Order & object);
	operator CDM::Order() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	Order();
	Order(const Order & object);
	virtual ~Order();
    
    void copyFrom(const Order & object);
    Order & operator=(const Order & object);
    
    typedef CDM::Order WrappedType;

	Order & setVisitNumber(const InstanceIdentifier & value);
	InstanceIdentifier getVisitNumber() const;
	bool getVisitNumber(InstanceIdentifier & out) const;
	bool hasVisitNumber() const;

	Order & setPlacerOrderNumber(const InstanceIdentifier & value);
	InstanceIdentifier getPlacerOrderNumber() const;

	Order & setFillerOrderNumber(const InstanceIdentifier & value);
	InstanceIdentifier getFillerOrderNumber() const;
	bool getFillerOrderNumber(InstanceIdentifier & out) const;
	bool hasFillerOrderNumber() const;

	Order & setPatient(const PersonReference & value);
	PersonReference getPatient() const;

	Order & setReferringPhysician(const PersonReference & value);
	PersonReference getReferringPhysician() const;
	bool getReferringPhysician(PersonReference & out) const;
	bool hasReferringPhysician() const;

	Order & setRequestingPhysician(const PersonReference & value);
	PersonReference getRequestingPhysician() const;
	bool getRequestingPhysician(PersonReference & out) const;
	bool hasRequestingPhysician() const;

	Order & setRequestedOrderDetail(const OrderDetail & value);
	OrderDetail getRequestedOrderDetail() const;
	bool getRequestedOrderDetail(OrderDetail & out) const;
	bool hasRequestedOrderDetail() const;

	Order & setPerformedOrderDetail(const OrderDetail & value);
	OrderDetail getPerformedOrderDetail() const;
	bool getPerformedOrderDetail(OrderDetail & out) const;
	bool hasPerformedOrderDetail() const;

	Order & addReason(const ClinicalInfo & value);
	std::vector<ClinicalInfo> getReasons() const;
	void clearReasons();
	
	Order & addDangerCode(const CodedValue & value);
	std::vector<CodedValue> getDangerCodes() const;
	void clearDangerCodes();
	
	Order & addRelevantClinicalInfo(const ClinicalInfo & value);
	std::vector<ClinicalInfo> getRelevantClinicalInfos() const;
	void clearRelevantClinicalInfos();
	
	Order & addImagingProcedure(const ImagingProcedure & value);
	std::vector<ImagingProcedure> getImagingProcedures() const;
	void clearImagingProcedures();
	
private:
	std::shared_ptr<CDM::Order> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ORDER_H_ */
