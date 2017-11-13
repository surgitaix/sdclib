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
 *  AbstractMetricDescriptor.h
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

#ifndef ABSTRACTMETRICDESCRIPTOR_H_
#define ABSTRACTMETRICDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

// inheritance
#include "OSCLib/Data/OSCP/MDIB/AbstractDescriptor.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class AbstractMetricDescriptor : public AbstractDescriptor {
private:
	AbstractMetricDescriptor(const CDM::AbstractMetricDescriptor & object);
	operator CDM::AbstractMetricDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	AbstractMetricDescriptor();
	AbstractMetricDescriptor(const AbstractMetricDescriptor & object);
	virtual ~AbstractMetricDescriptor() = 0;
    
    void copyFrom(const AbstractMetricDescriptor & object);
    AbstractMetricDescriptor & operator=(const AbstractMetricDescriptor & object);
    
    typedef CDM::AbstractMetricDescriptor WrappedType;


	AbstractMetricDescriptor & setUnit(const CodedValue & value);
	CodedValue getUnit() const;

	AbstractMetricDescriptor & setMetricCategory(const MetricCategory & value);
	MetricCategory getMetricCategory() const;

	AbstractMetricDescriptor & setDerivationMethod(const DerivationMethod & value);
	DerivationMethod getDerivationMethod() const;
	bool getDerivationMethod(DerivationMethod & out) const;
	bool hasDerivationMethod() const;

	AbstractMetricDescriptor & setMetricAvailability(const MetricAvailability & value);
	MetricAvailability getMetricAvailability() const;

	AbstractMetricDescriptor & setMaxMeasurementTime(const xml_schema::Duration & value);
	xml_schema::Duration getMaxMeasurementTime() const;
	bool getMaxMeasurementTime(xml_schema::Duration & out) const;
	bool hasMaxMeasurementTime() const;

	AbstractMetricDescriptor & setMaxDelayTime(const xml_schema::Duration & value);
	xml_schema::Duration getMaxDelayTime() const;
	bool getMaxDelayTime(xml_schema::Duration & out) const;
	bool hasMaxDelayTime() const;

	AbstractMetricDescriptor & setDeterminationPeriod(const xml_schema::Duration & value);
	xml_schema::Duration getDeterminationPeriod() const;
	bool getDeterminationPeriod(xml_schema::Duration & out) const;
	bool hasDeterminationPeriod() const;

	AbstractMetricDescriptor & setLifeTimePeriod(const xml_schema::Duration & value);
	xml_schema::Duration getLifeTimePeriod() const;
	bool getLifeTimePeriod(xml_schema::Duration & out) const;
	bool hasLifeTimePeriod() const;

	AbstractMetricDescriptor & setActivationDuration(const xml_schema::Duration & value);
	xml_schema::Duration getActivationDuration() const;
	bool getActivationDuration(xml_schema::Duration & out) const;
	bool hasActivationDuration() const;

	AbstractMetricDescriptor & addBodySite(const CodedValue & value);
	std::vector<CodedValue> getBodySiteList() const;
	void clearBodySiteList();
	
	AbstractMetricDescriptor & addRelation(const Relation & value);
	std::vector<Relation> getRelationList() const;
	void clearRelationList();
	
private:
	std::shared_ptr<CDM::AbstractMetricDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ABSTRACTMETRICDESCRIPTOR_H_ */
