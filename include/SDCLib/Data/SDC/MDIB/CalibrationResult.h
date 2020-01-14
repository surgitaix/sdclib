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
 *  CalibrationResult.h
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

#ifndef CALIBRATIONRESULT_H_
#define CALIBRATIONRESULT_H_

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "DataModel/osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class CalibrationResult
{
private:
	CalibrationResult(const CDM::CalibrationResult & object);
	operator CDM::CalibrationResult() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	CalibrationResult(
		CodedValue code
		,
		Measurement value
	);
private:
	CalibrationResult(){};
public:
	CalibrationResult(const CalibrationResult& object);
	virtual ~CalibrationResult() = default;

    void copyFrom(const CalibrationResult& object);
    CalibrationResult & operator=(const CalibrationResult& object);

    typedef CDM::CalibrationResult WrappedType;

	CalibrationResult & setCode(const CodedValue & value);
	CodedValue getCode() const;

	CalibrationResult & setValue(const Measurement & value);
	Measurement getValue() const;

private:
	std::shared_ptr<CDM::CalibrationResult> data = nullptr;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* CALIBRATIONRESULT_H_ */
