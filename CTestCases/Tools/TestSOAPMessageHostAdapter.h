/*
 * TestSOAPMessageHostAdapter.h
 *
 *  Created on: Nov 27, 2018
 *      Author: sebastian
 */

#ifndef CTESTCASES_TOOLS_TESTSOAPMESSAGEHOSTADAPTER_H_
#define CTESTCASES_TOOLS_TESTSOAPMESSAGEHOSTADAPTER_H_

#include <OSELib/DPWS/MDPWSHostAdapter.h>

namespace SDCLib {
namespace Data {
namespace SDC {


class TestSOAPMessageHostAdapter: public OSELib::DPWS::MDPWSHostAdapter {
public:
	TestSOAPMessageHostAdapter();
	virtual ~TestSOAPMessageHostAdapter();
};

}
}
} /* namespace TestTools */

#endif /* CTESTCASES_TOOLS_TESTSOAPMESSAGEHOSTADAPTER_H_ */
