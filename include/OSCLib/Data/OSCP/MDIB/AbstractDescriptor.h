/*
 * AbstractDescriptor.h
 *
 *  Created on: Nov 6, 2017
 *      Author: sebastian
 */

#ifndef ABSTRACTDESCRIPTOR_H_
#define ABSTRACTDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class AbstractDescriptor {
private:
	AbstractDescriptor(const CDM::AbstractDescriptor & object); // ??
	operator CDM::AbstractDescriptor() const; // ??
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	AbstractDescriptor(); // später mit required argumenten
	AbstractDescriptor(const AbstractDescriptor & object);
	virtual ~AbstractDescriptor() = 0;

    void copyFrom(const AbstractDescriptor & object);
    AbstractDescriptor & operator=(const AbstractDescriptor & object);

    typedef CDM::AbstractDescriptor WrappedType;

	AbstractDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	AbstractDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	AbstractDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	AbstractDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

private:
	std::shared_ptr<CDM::AbstractDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ABSTRACTDESCRIPTOR_H_ */
