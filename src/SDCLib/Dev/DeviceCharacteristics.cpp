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

/**
 *  @file DeviceCharacteristics.cpp
 *  @project SDCLib
 *  @date 05.07.2011
 *  @author besting (H)
 *  @copyright (c) SurgiTAIX AG
 *
 *  Modified on: 29.08.2019, baumeister
 */

#include <stdexcept>

#include "SDCLib/Dev/DeviceCharacteristics.h"

#include "OSELib/DPWS/DPWS11Constants.h"

namespace SDCLib
{
namespace Dev
{

LocalizedString DeviceCharacteristics::getModelNames() const
{
	return ml_modelName;
}

LocalizedString DeviceCharacteristics::getFriendlyNames() const
{
	return ml_friendlyName;
}

void DeviceCharacteristics::setManufacturer(const std::string& p_name)
{
	if (p_name.length() > OSELib::MAX_FIELD_SIZE) {
		throw std::runtime_error("Name length exceeds MAX_FILE_SIZE");
	}
	m_manufacturer = p_name;
}

void DeviceCharacteristics::setManufacturerUrl(const std::string& p_url)
{
	if (p_url.length() > OSELib::MAX_FIELD_SIZE) {
		throw std::runtime_error("Name length exceeds MAX_FILE_SIZE");
	}
	m_manufacturerUrl = p_url;
}

void DeviceCharacteristics::addModelName(const std::string& p_lang, const std::string& p_name)
{
	if (p_name.length() > OSELib::MAX_FIELD_SIZE) {
		throw std::runtime_error("Name length exceeds MAX_FILE_SIZE");
	}
	ml_modelName[p_lang] = p_name;
}

std::string DeviceCharacteristics::getManufacturer() const
{
	return m_manufacturer;
}

std::string DeviceCharacteristics::getManufacturerUrl() const
{
	return m_manufacturerUrl;
}

std::string DeviceCharacteristics::getModelName(const std::string& p_lang) const
{
	if (ml_modelName.find(p_lang) == ml_modelName.end()) {
		return std::string();
	}
	return ml_modelName.find(p_lang)->second;
}

std::string DeviceCharacteristics::getModelNumber() const
{
    return m_modelNumber;
}

std::string DeviceCharacteristics::getModelUrl() const
{
    return m_modelUrl;
}

std::string DeviceCharacteristics::getPresentationUrl() const
{
    return m_presentationUrl;
}

void DeviceCharacteristics::setModelNumber(const std::string& p_modelNumber)
{
	if (p_modelNumber.length() > OSELib::MAX_FIELD_SIZE) {
		throw std::runtime_error("Name length exceeds MAX_FILE_SIZE");
	}
    m_modelNumber = p_modelNumber;
}

void DeviceCharacteristics::setModelUrl(const std::string& p_modelUrl)
{
	if (p_modelUrl.length() > OSELib::MAX_URI_SIZE) {
		throw std::runtime_error("Name length exceeds MAX_URI_SIZE");
	}
    m_modelUrl = p_modelUrl;
}

void DeviceCharacteristics::setPresentationUrl(const std::string& p_presentationUrl)
{
	if (p_presentationUrl.length() > OSELib::MAX_URI_SIZE) {
		throw std::runtime_error("Name length exceeds MAX_URI_SIZE");
	}
    m_presentationUrl = p_presentationUrl;
}

void DeviceCharacteristics::addFriendlyName(const std::string& p_lang, const std::string& p_name)
{
	if (p_name.length() > OSELib::MAX_FIELD_SIZE) {
		throw std::runtime_error("Name length exceeds MAX_FILE_SIZE");
	}
	ml_friendlyName[p_lang] = p_name;
}

std::string DeviceCharacteristics::getFriendlyName(const std::string & p_lang) const
{
	if (ml_friendlyName.find(p_lang) == ml_friendlyName.end()) {
		return std::string();
	}
	return ml_friendlyName.find(p_lang)->second;
}

std::string DeviceCharacteristics::getFirmwareVersion() const
{
    return m_firmwareVersion;
}

std::string DeviceCharacteristics::getSerialNumber() const
{
    return m_serialNumber;
}

void DeviceCharacteristics::setFirmwareVersion(const std::string& p_firmwareVersion)
{
    m_firmwareVersion = p_firmwareVersion;
}

void DeviceCharacteristics::setSerialNumber(const std::string& p_serialNumber)
{
    m_serialNumber = p_serialNumber;
}

void DeviceCharacteristics::setEndpointReference(const std::string& p_epr)
{
	m_endpointReference = p_epr;
}
std::string DeviceCharacteristics::getEndpointReference() const
{
	return m_endpointReference;
}


}
}




