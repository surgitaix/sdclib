/*
 * DurationWrapper.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef HELPER_DURATIONWRAPPER_H_
#define HELPER_DURATIONWRAPPER_H_

#include "OSELib/fwd.h"

namespace OSELib {
namespace Helper {

class DurationWrapper : public xml_schema::Duration {
public:
	DurationWrapper(const std::string & value);

	DurationWrapper & operator=(const xml_schema::Duration & source);

	std::string toString();

	Poco::Timestamp toExpirationTimeStamp();
};

} /* namespace Helper */
} /* namespace OSELib */

#endif /* HELPER_DURATIONWRAPPER_H_ */
