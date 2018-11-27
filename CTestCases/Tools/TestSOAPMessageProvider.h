/*
 * TestSOAPMessageProvider.h
 *
 *  Created on: Nov 26, 2018
 *      Author: rosenau
 */

#ifndef CTESTCASES_TOOLS_TESTSOAPMESSAGEPROVIDER_H_
#define CTESTCASES_TOOLS_TESTSOAPMESSAGEPROVIDER_H_

#include "OSCLib/Data/SDC/SDCProvider.h"


namespace SDCLib {
namespace Data {
namespace SDC {
namespace TestTools{

class TestSOAPMessageProvider : public SDCProvider {
public:

	TestSOAPMessageProvider();
	virtual ~TestSOAPMessageProvider();

	void sendMulticastSOAPMessage(std::string message);
	void sendUnicastSOAPMessage(std::string message);



};
}/* namespace TestTools */
}
}
}

#endif /* CTESTCASES_TOOLS_TESTSOAPMESSAGEPROVIDER_H_ */
