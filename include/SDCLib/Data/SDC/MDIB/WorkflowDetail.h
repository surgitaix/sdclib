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
 *  WorkflowDetail.h
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

#ifndef WORKFLOWDETAIL_H_
#define WORKFLOWDETAIL_H_

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "DataModel/osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class WorkflowDetail {
private:
	WorkflowDetail(const CDM::WorkflowDetail & object);
	operator CDM::WorkflowDetail() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	WorkflowDetail(
		PersonReference patient
	);
private:
	WorkflowDetail(){};
public:
	WorkflowDetail(const WorkflowDetail & object);
	virtual ~WorkflowDetail();

    void copyFrom(const WorkflowDetail & object);
    WorkflowDetail & operator=(const WorkflowDetail & object);

    typedef CDM::WorkflowDetail WrappedType;

	WorkflowDetail & setPatient(const PersonReference & value);
	PersonReference getPatient() const;

	WorkflowDetail & setAssignedLocation(const LocationReference & value);
	LocationReference getAssignedLocation() const;
	bool getAssignedLocation(LocationReference & out) const;
	bool hasAssignedLocation() const;

	WorkflowDetail & setVisitNumber(const InstanceIdentifier & value);
	InstanceIdentifier getVisitNumber() const;
	bool getVisitNumber(InstanceIdentifier & out) const;
	bool hasVisitNumber() const;

	WorkflowDetail & setRequestedOrderDetail(const RequestedOrderDetail & value);
	RequestedOrderDetail getRequestedOrderDetail() const;
	bool getRequestedOrderDetail(RequestedOrderDetail & out) const;
	bool hasRequestedOrderDetail() const;

	WorkflowDetail & setPerformedOrderDetail(const PerformedOrderDetail & value);
	PerformedOrderDetail getPerformedOrderDetail() const;
	bool getPerformedOrderDetail(PerformedOrderDetail & out) const;
	bool hasPerformedOrderDetail() const;

	WorkflowDetail & addDangerCode(const CodedValue & value);
	std::vector<CodedValue> getDangerCodeList() const;
	void clearDangerCodeList();

	WorkflowDetail & addRelevantClinicalInfo(const ClinicalInfo & value);
	std::vector<ClinicalInfo> getRelevantClinicalInfoList() const;
	void clearRelevantClinicalInfoList();

private:
	std::shared_ptr<CDM::WorkflowDetail> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* WORKFLOWDETAIL_H_ */
