/*
 * Task.h
 *
 *  Created on: 27.01.2015
 *      Author: roehser
 */

#ifndef UTIL_TASK_H_
#define UTIL_TASK_H_

#include "Poco/Runnable.h"
#include "Poco/Thread.h"

#include <atomic>

namespace OSCLib {
namespace Util {

class Task : public Poco::Runnable {
public:
	Task();
	virtual ~Task();

	virtual void run();
	virtual void runImpl() = 0;

	void start();
	void interrupt();
	bool isInterrupted();

private:
	void setIsRunning(bool value);

	std::atomic<bool> isRunning;
	Poco::Thread thread;
};

} /* namespace Util */
} /* namespace OSCLib */

#endif /* UTIL_TASK_H_ */
