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
 *  @project OSCLib
 *  @date 05.07.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#ifndef DEVICEDESCRIPTION_H_
#define DEVICEDESCRIPTION_H_

#include <string>
#include <map>

namespace SDCLib {
namespace Dev {

typedef std::map<std::string, std::string> LocalizedString;

class DeviceCharacteristics {
public:
	DeviceCharacteristics();
	virtual ~DeviceCharacteristics();

	void setManufacturer(const std::string & name);
	void setManufacturerUrl(const std::string & url);

	void addModelName(const std::string & lang, const std::string & name);
	const std::string & getManufacturer() const;
	const std::string & getManufacturerUrl() const;
	std::string getModelName(const std::string & lang) const;

	const LocalizedString & getModelNames() const;

	const std::string & getModelNumber() const;
	const std::string & getModelUrl() const;
	const std::string & getPresentationUrl() const;

    void setModelNumber(const std::string & modelNumber);
    void setModelUrl(const std::string & modelUrl);
    void setPresentationUrl(const std::string & presentationUrl);

	void addFriendlyName(const std::string & lang, const std::string & name);
	std::string getFriendlyName(const std::string & lang) const;

	const LocalizedString & getFriendlyNames() const;

	const std::string & getFirmwareVersion() const;
	const std::string & getSerialNumber() const;
    void setFirmwareVersion(const std::string & firmwareVersion);
    void setSerialNumber(const std::string & serialNumber);

private:
    // ThisModel
    std::string manufacturer;
    std::string manufacturerUrl;
    LocalizedString modelName;
	std::string modelNumber;
	std::string modelUrl;
	std::string presentationUrl;

    // ThisDevice
	LocalizedString friendlyName;
	std::string firmwareVersion;
	std::string serialNumber;
};

}
}

#endif /* DEVICEDESCRIPTION_H_ */
