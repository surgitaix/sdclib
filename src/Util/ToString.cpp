/*
 * ToString.cpp
 *
 *  Created on: 13.10.2014
 *      Author: roehser
 */

#include <sstream>

#include "OSCLib/Util/ToString.h"
#include "osdm.hxx"

namespace CDM {

const xml_schema::Flags xercesFlags(xml_schema::Flags::dont_validate | xml_schema::Flags::no_xml_declaration | xml_schema::Flags::dont_initialize);

const std::string XML_ENCODING("UTF-8");

ToString::ToString() {

}

ToString::~ToString() {

}

std::string ToString::convert(const int i) {
	std::ostringstream result;
	result << i;
	return result.str();
}

std::string ToString::convert(const double d) {
	std::ostringstream result;
	result << d;
	return result.str();
}

std::string ToString::convert(const CDM::WaveformStream & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::WaveformStream_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::Activate & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::Activate_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::ActivateResponse & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::ActivateResponse_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::EpisodicAlertReport & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::EpisodicAlertReport_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::EpisodicContextChangedReport & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::EpisodicContextChangedReport_(result, obj, map, XML_ENCODING, xercesFlags);

	return result.str();
}

std::string ToString::convert(const CDM::EpisodicMetricReport & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::EpisodicMetricReport_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::GetContextStatesResponse & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::GetContextStatesResponse_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::GetMDDescription & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::GetMDDescription_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::GetMDDescriptionResponse & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::GetMDDescriptionResponse_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::GetMDIB & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::GetMDIB_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::GetMDIBResponse & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::GetMDIBResponse_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::GetMDState & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::GetMDState_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::GetMDStateResponse & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::GetMDStateResponse_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::MDIB & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::MDIBContainer(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::MDSCreatedReport & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::MDSCreatedReport_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::MDSDeletedReport & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::MDSDeletedReport_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::ObjectCreatedReport & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::ObjectCreatedReport_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::ObjectDeletedReport & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::ObjectDeletedReport_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::OperationalStateChangedReport & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::OperationalStateChangedReport_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::OperationCreatedReport & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::OperationCreatedReport_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::OperationDeletedReport & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::OperationDeletedReport_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::OperationInvokedReport & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::OperationInvokedReport_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::PeriodicAlertReport & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::PeriodicAlertReport_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::PeriodicContextChangedReport & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::PeriodicContextChangedReport_(result, obj, map, XML_ENCODING, xercesFlags);

	return result.str();
}

std::string ToString::convert(const CDM::PeriodicMetricReport & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::PeriodicMetricReport_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::SetAlertState & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::SetAlertState_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::SetAlertStateResponse & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::SetAlertStateResponse_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::SetContextState & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::SetContextState_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::SetContextStateResponse & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::SetContextStateResponse_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::SetString & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::SetString_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::SetStringResponse & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::SetStringResponse_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::SetValue & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::SetValue_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::SetValueResponse & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::SetValueResponse_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

std::string ToString::convert(const CDM::SystemErrorReport & obj) {
	std::ostringstream result;
	xml_schema::NamespaceInfomap map;
	CDM::SystemErrorReport_(result, obj, map, XML_ENCODING, xercesFlags);
	return result.str();
}

}
