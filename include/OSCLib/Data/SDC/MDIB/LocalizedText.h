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
 *  LocalizedText.h
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

#ifndef LOCALIZEDTEXT_H_
#define LOCALIZEDTEXT_H_

#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class LocalizedText {
private:
	LocalizedText(const CDM::LocalizedText & object);
	operator CDM::LocalizedText() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	LocalizedText(
	); 
	LocalizedText(const LocalizedText & object);
	virtual ~LocalizedText();
    
    void copyFrom(const LocalizedText & object);
    LocalizedText & operator=(const LocalizedText & object);
    
    typedef CDM::LocalizedText WrappedType;

	LocalizedText & setRef(const LocalizedTextRef & value);
	LocalizedTextRef getRef() const;
	bool getRef(LocalizedTextRef & out) const;
	bool hasRef() const;

	LocalizedText & setLang(const xml_schema::Language & value);
	xml_schema::Language getLang() const;
	bool getLang(xml_schema::Language & out) const;
	bool hasLang() const;

	LocalizedText & setVersion(const ReferencedVersion & value);
	ReferencedVersion getVersion() const;
	bool getVersion(ReferencedVersion & out) const;
	bool hasVersion() const;

	LocalizedText & setTextWidth(const LocalizedTextWidth & value);
	LocalizedTextWidth getTextWidth() const;
	bool getTextWidth(LocalizedTextWidth & out) const;
	bool hasTextWidth() const;

private:
	std::shared_ptr<CDM::LocalizedText> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* LOCALIZEDTEXT_H_ */
