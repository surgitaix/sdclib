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
 *  RequestedOrderDetail.h
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

#ifndef REQUESTEDORDERDETAIL_H_
#define REQUESTEDORDERDETAIL_H_

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "DataModel/osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class RequestedOrderDetail
{
private:
	RequestedOrderDetail(const CDM::RequestedOrderDetail & object);
	operator CDM::RequestedOrderDetail() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	RequestedOrderDetail(
		InstanceIdentifier placerordernumber
	);
private:
	RequestedOrderDetail(){};
public:
	RequestedOrderDetail(const RequestedOrderDetail& object);
	virtual ~RequestedOrderDetail() = default;

    void copyFrom(const RequestedOrderDetail& object);
    RequestedOrderDetail & operator=(const RequestedOrderDetail& object);

    typedef CDM::RequestedOrderDetail WrappedType;

	RequestedOrderDetail & setStart(const xml_schema::DateTime & value);
	xml_schema::DateTime getStart() const;
	bool getStart(xml_schema::DateTime & out) const;
	bool hasStart() const;

	RequestedOrderDetail & setEnd(const xml_schema::DateTime & value);
	xml_schema::DateTime getEnd() const;
	bool getEnd(xml_schema::DateTime & out) const;
	bool hasEnd() const;

	RequestedOrderDetail & addPerformer(const PersonParticipation & value);
	std::vector<PersonParticipation> getPerformerList() const;
	void clearPerformerList();

	RequestedOrderDetail & addService(const CodedValue & value);
	std::vector<CodedValue> getServiceList() const;
	void clearServiceList();

	RequestedOrderDetail & addImagingProcedure(const ImagingProcedure & value);
	std::vector<ImagingProcedure> getImagingProcedureList() const;
	void clearImagingProcedureList();

	RequestedOrderDetail & setReferringPhysician(const PersonReference & value);
	PersonReference getReferringPhysician() const;
	bool getReferringPhysician(PersonReference & out) const;
	bool hasReferringPhysician() const;

	RequestedOrderDetail & setRequestingPhysician(const PersonReference & value);
	PersonReference getRequestingPhysician() const;
	bool getRequestingPhysician(PersonReference & out) const;
	bool hasRequestingPhysician() const;

	RequestedOrderDetail & setPlacerOrderNumber(const InstanceIdentifier & value);
	InstanceIdentifier getPlacerOrderNumber() const;

private:
	std::shared_ptr<CDM::RequestedOrderDetail> data = nullptr;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* REQUESTEDORDERDETAIL_H_ */
