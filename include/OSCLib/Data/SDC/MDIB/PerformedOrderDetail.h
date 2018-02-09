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
 *  PerformedOrderDetail.h
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

#ifndef PERFORMEDORDERDETAIL_H_
#define PERFORMEDORDERDETAIL_H_

#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace SDC {

class PerformedOrderDetail {
private:
	PerformedOrderDetail(const CDM::PerformedOrderDetail & object);
	operator CDM::PerformedOrderDetail() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	PerformedOrderDetail(
	); 
	PerformedOrderDetail(const PerformedOrderDetail & object);
	virtual ~PerformedOrderDetail();
    
    void copyFrom(const PerformedOrderDetail & object);
    PerformedOrderDetail & operator=(const PerformedOrderDetail & object);
    
    typedef CDM::PerformedOrderDetail WrappedType;

	PerformedOrderDetail & setStart(const xml_schema::DateTime & value);
	xml_schema::DateTime getStart() const;
	bool getStart(xml_schema::DateTime & out) const;
	bool hasStart() const;

	PerformedOrderDetail & setEnd(const xml_schema::DateTime & value);
	xml_schema::DateTime getEnd() const;
	bool getEnd(xml_schema::DateTime & out) const;
	bool hasEnd() const;

	PerformedOrderDetail & addPerformer(const PersonParticipation & value);
	std::vector<PersonParticipation> getPerformerList() const;
	void clearPerformerList();
	
	PerformedOrderDetail & addService(const CodedValue & value);
	std::vector<CodedValue> getServiceList() const;
	void clearServiceList();
	
	PerformedOrderDetail & addImagingProcedure(const ImagingProcedure & value);
	std::vector<ImagingProcedure> getImagingProcedureList() const;
	void clearImagingProcedureList();
	
	PerformedOrderDetail & setFillerOrderNumber(const InstanceIdentifier & value);
	InstanceIdentifier getFillerOrderNumber() const;
	bool getFillerOrderNumber(InstanceIdentifier & out) const;
	bool hasFillerOrderNumber() const;

	PerformedOrderDetail & addResultingClinicalInfo(const ClinicalInfo & value);
	std::vector<ClinicalInfo> getResultingClinicalInfoList() const;
	void clearResultingClinicalInfoList();
	
private:
	std::shared_ptr<CDM::PerformedOrderDetail> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* PERFORMEDORDERDETAIL_H_ */
