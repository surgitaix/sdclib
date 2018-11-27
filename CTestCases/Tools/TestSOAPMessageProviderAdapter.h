/*
 * TestSOAPMessageProviderAdapter.h
 *
 *  Created on: Nov 27, 2018
 *      Author: sebastian
 */

#ifndef CTESTCASES_TOOLS_TESTSOAPMESSAGEPROVIDERADAPTER_H_
#define CTESTCASES_TOOLS_TESTSOAPMESSAGEPROVIDERADAPTER_H_

#include "OSCLib/Dev/DeviceCharacteristics.h"
#include "OSCLib/Data/SDC/SDCProviderAdapter.h"
#include "TestSOAPMessageProvider.h"

namespace SDCLib {
namespace Data {
namespace SDC {
namespace TestTools{

class TestSOAPMessageProviderAdapter: public SDCProviderAdapter {
public:
	TestSOAPMessageProviderAdapter(TestSOAPMessageProvider & testSOAPMessageProvider);
	virtual ~TestSOAPMessageProviderAdapter();
};
}
}
}
} /* namespace TestTools */

#endif /* CTESTCASES_TOOLS_TESTSOAPMESSAGEPROVIDERADAPTER_H_ */
