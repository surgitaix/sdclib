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
 * OSCPCachedProvider.h
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, roehser
 */

#ifndef INCLUDE_OSCLIB_DATA_OSCP_OSCPCACHEDPROVIDER_H_
#define INCLUDE_OSCLIB_DATA_OSCP_OSCPCACHEDPROVIDER_H_

#include "OSCLib/Data/OSCP/OSCPProvider.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPCachedProvider : public OSCPProvider {
public:
	OSCPCachedProvider();
	virtual ~OSCPCachedProvider();

	MDDescription getMDDescription() final override;

    /**
    * @brief Set or update the MD description.
    *
    * @param object The MDDescription object
    */
	void setMDDescription(MDDescription description);

    /**
    * @brief Set or update the MD description using a raw XML MDIB string
    *
    * @param object The raw XML MDIB string
    */
	void setMDDescription(std::string xml);

private:
	std::shared_ptr<MDDescription> mdDescription;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* INCLUDE_OSCLIB_DATA_OSCP_OSCPCACHEDPROVIDER_H_ */
