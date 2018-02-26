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
 *  @project OSCLib
 *  @date 05.07.2011
 *  @author besting (H)
 *  @copyright (c) SurgiTAIX AG
 */

#include <stdexcept>

#include "OSCLib/Dev/DeviceCharacteristics.h"

#include "OSELib/DPWS/DPWS11Constants.h"

namespace SDCLib {
namespace Dev {

DeviceCharacteristics::DeviceCharacteristics()
{
}

DeviceCharacteristics::~DeviceCharacteristics()
{
}

const LocalizedString & DeviceCharacteristics::getModelNames() const
{
	return modelName;
}

const LocalizedString & DeviceCharacteristics::getFriendlyNames() const
{
	return friendlyName;
}

void DeviceCharacteristics::setManufacturer(const std::string & name)
{
	if (name.length() > OSELib::MAX_FIELD_SIZE)
		throw std::runtime_error("Name length exceeds MAX_FILE_SIZE");
	this->manufacturer = name;
}

void DeviceCharacteristics::setManufacturerUrl(const std::string & url)
{
	if (url.length() > OSELib::MAX_FIELD_SIZE)
		throw std::runtime_error("Name length exceeds MAX_FILE_SIZE");
	this->manufacturerUrl = url;
}

void DeviceCharacteristics::addModelName(const std::string & lang, const std::string & name)
{
	if (name.length() > OSELib::MAX_FIELD_SIZE)
		throw std::runtime_error("Name length exceeds MAX_FILE_SIZE");
	modelName[lang] = name;
}

const std::string & DeviceCharacteristics::getManufacturer() const
{
	return manufacturer;
}

const std::string & DeviceCharacteristics::getManufacturerUrl() const
{
	return manufacturerUrl;
}

std::string DeviceCharacteristics::getModelName(const std::string & lang) const
{
	std::string name;
	if (modelName.find(lang) == modelName.end())
		return name;
	return modelName.find(lang)->second;
}

const std::string & DeviceCharacteristics::getModelNumber() const
{
    return modelNumber;
}

const std::string & DeviceCharacteristics::getModelUrl() const
{
    return modelUrl;
}

const std::string & DeviceCharacteristics::getPresentationUrl() const
{
    return presentationUrl;
}

void DeviceCharacteristics::setModelNumber(const std::string & modelNumber)
{
	if (modelNumber.length() > OSELib::MAX_FIELD_SIZE)
		throw std::runtime_error("Name length exceeds MAX_FILE_SIZE");
    this->modelNumber = modelNumber;
}

void DeviceCharacteristics::setModelUrl(const std::string & modelUrl)
{
	if (modelUrl.length() > OSELib::MAX_URI_SIZE)
		throw std::runtime_error("Name length exceeds MAX_URI_SIZE");
    this->modelUrl = modelUrl;
}

void DeviceCharacteristics::setPresentationUrl(const std::string & presentationUrl)
{
	if (presentationUrl.length() > OSELib::MAX_URI_SIZE)
		throw std::runtime_error("Name length exceeds MAX_URI_SIZE");
    this->presentationUrl = presentationUrl;
}

void DeviceCharacteristics::addFriendlyName(const std::string & lang, const std::string & name)
{
	if (name.length() > OSELib::MAX_FIELD_SIZE)
		throw std::runtime_error("Name length exceeds MAX_FILE_SIZE");
	friendlyName[lang] = name;
}

std::string DeviceCharacteristics::getFriendlyName(const std::string & lang) const
{
	std::string name;
	if (friendlyName.find(lang) == friendlyName.end())
		return name;
	return friendlyName.find(lang)->second;
}

const std::string & DeviceCharacteristics::getFirmwareVersion() const
{
    return firmwareVersion;
}

const std::string & DeviceCharacteristics::getSerialNumber() const
{
    return serialNumber;
}

void DeviceCharacteristics::setFirmwareVersion(const std::string & firmwareVersion)
{
    this->firmwareVersion = firmwareVersion;
}

void DeviceCharacteristics::setSerialNumber(const std::string & serialNumber)
{
    this->serialNumber = serialNumber;
}

}
}




