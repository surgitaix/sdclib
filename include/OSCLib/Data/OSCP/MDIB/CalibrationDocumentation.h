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
 *  CalibrationDocumentation.h
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

#ifndef CALIBRATIONDOCUMENTATION_H_
#define CALIBRATIONDOCUMENTATION_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class CalibrationDocumentation {
private:
	CalibrationDocumentation(const CDM::CalibrationDocumentation & object);
	operator CDM::CalibrationDocumentation() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	CalibrationDocumentation(
	); 
	CalibrationDocumentation(const CalibrationDocumentation & object);
	virtual ~CalibrationDocumentation();
    
    void copyFrom(const CalibrationDocumentation & object);
    CalibrationDocumentation & operator=(const CalibrationDocumentation & object);
    
    typedef CDM::CalibrationDocumentation WrappedType;

	CalibrationDocumentation & addDocumentation(const LocalizedText & value);
	std::vector<LocalizedText> getDocumentationList() const;
	void clearDocumentationList();
	
	CalibrationDocumentation & addCalibrationResult(const CalibrationResult & value);
	std::vector<CalibrationResult> getCalibrationResultList() const;
	void clearCalibrationResultList();
	
private:
	std::shared_ptr<CDM::CalibrationDocumentation> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* CALIBRATIONDOCUMENTATION_H_ */
