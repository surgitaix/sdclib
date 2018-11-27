/*
 * TestSOAPMessageSocketImpl.h
 *
 *  Created on: Nov 27, 2018
 *      Author: sebastian
 */

#ifndef CTESTCASES_TOOLS_TESTSOAPMESSAGESOCKETIMPL_H_
#define CTESTCASES_TOOLS_TESTSOAPMESSAGESOCKETIMPL_H_

#include <OSELib/DPWS/DPWSHostSocketImpl.h>

namespace SDCLib {
namespace Data {
namespace SDC {
namespace TestTools{

class TestSOAPMessageSocketImpl: public OSELib::DPWS::Impl::DPWSHostSocketImpl {
public:
	TestSOAPMessageSocketImpl();
	virtual ~TestSOAPMessageSocketImpl();

	void addSOAPMessage(std::string);
};

}
}
}
} /* namespace TestTools */

#endif /* CTESTCASES_TOOLS_TESTSOAPMESSAGESOCKETIMPL_H_ */
