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
 *  InvocationInfo.h
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

#ifndef INVOCATIONINFO_H_
#define INVOCATIONINFO_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class InvocationInfo {
private:
	InvocationInfo(const CDM::InvocationInfo & object);
	operator CDM::InvocationInfo() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	InvocationInfo();
	InvocationInfo(const InvocationInfo & object);
	virtual ~InvocationInfo();
    
    void copyFrom(const InvocationInfo & object);
    InvocationInfo & operator=(const InvocationInfo & object);
    
    typedef CDM::InvocationInfo WrappedType;

	InvocationInfo & setTransactionId(const TransactionId & value);
	TransactionId getTransactionId() const;

	InvocationInfo & setInvocationState(const InvocationState & value);
	InvocationState getInvocationState() const;

	InvocationInfo & setInvocationError(const InvocationError & value);
	InvocationError getInvocationError() const;
	bool getInvocationError(InvocationError & out) const;
	bool hasInvocationError() const;

	InvocationInfo & addInvocationErrorMessage(const LocalizedText & value);
	std::vector<LocalizedText> getInvocationErrorMessages() const;
	void clearInvocationErrorMessages();
	
private:
	std::shared_ptr<CDM::InvocationInfo> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* INVOCATIONINFO_H_ */
