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
 *  @file DeviceCharacteristics.h
 *  @project SDCLib
 *  @date 05.07.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 *
 *  Modified on: 29.08.2019, baumeister
 */


#ifndef SDCLIB_DEV_DEVICEDESCRIPTION_H_
#define SDCLIB_DEV_DEVICEDESCRIPTION_H_

#include <string>
#include <map>

namespace SDCLib
{
	namespace Dev
	{
		typedef std::map<std::string, std::string> LocalizedString;
		// FIXME: NOT THREADSAFE!
		class DeviceCharacteristics
		{
		private:

			// ThisModel
			std::string m_manufacturer;
			std::string m_manufacturerUrl;
			LocalizedString ml_modelName;
			std::string m_modelNumber;
			std::string m_modelUrl;
			std::string m_presentationUrl;

			// ThisDevice
			LocalizedString ml_friendlyName;
			std::string m_firmwareVersion;
			std::string m_serialNumber;

			// Host
			std::string m_endpointReference;

		public:
			DeviceCharacteristics() = default;
			DeviceCharacteristics(const DeviceCharacteristics& p_obj) = default;
			DeviceCharacteristics(DeviceCharacteristics&& p_obj) = default;
			DeviceCharacteristics& operator=(const DeviceCharacteristics& p_obj) = default;
			DeviceCharacteristics& operator=(DeviceCharacteristics&& p_obj) = default;
			~DeviceCharacteristics() = default;

			void setManufacturer(const std::string& p_name);
			void setManufacturerUrl(const std::string& p_url);

			void addModelName(const std::string& p_lang, const std::string& p_name);
			std::string getManufacturer() const;
			std::string getManufacturerUrl() const;
			std::string getModelName(const std::string& p_lang) const;

			LocalizedString getModelNames() const;

			std::string getModelNumber() const;
			std::string getModelUrl() const;
			std::string getPresentationUrl() const;

			void setModelNumber(const std::string& p_modelNumber);
			void setModelUrl(const std::string& p_modelUrl);
			void setPresentationUrl(const std::string& p_presentationUrl);

			void addFriendlyName(const std::string& p_lang, const std::string& p_name);
			std::string getFriendlyName(const std::string& p_lang) const;

			LocalizedString getFriendlyNames() const;

			std::string getFirmwareVersion() const;
			std::string getSerialNumber() const;
			void setFirmwareVersion(const std::string& p_firmwareVersion);
			void setSerialNumber(const std::string& p_serialNumber);

			// Host

			// only to be used by SDCProvider
			void setEndpointReference(const std::string& p_epr);
			std::string getEndpointReference() const;
		};
	}
}

#endif
