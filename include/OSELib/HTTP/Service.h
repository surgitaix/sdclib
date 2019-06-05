/*
 * Service.h
 *
 *  Created on: 18.11.2015
 *      Author: matthias
 */

#ifndef SERVICE_H_
#define SERVICE_H_

#include <string>
#include <vector>

#include "OSELib/fwd.h"

namespace OSELib {
namespace HTTP {

class Service {
public:
	Service(FrontController & controller, const std::vector<std::string> & uris);
	virtual ~Service();

	virtual Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest & request, bool p_SSL) = 0;

	const std::vector<std::string> & getUris() const;

private:
	const std::vector<std::string> _uris;
};

}
} /* namespace OSELib */

#endif /* SERVICE_H_ */
