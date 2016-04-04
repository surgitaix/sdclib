/*
 * Task.cpp
 *
 *  Created on: 27.01.2015
 *      Author: roehser
 */

#include "OSCLib/Util/Task.h"

namespace OSCLib {
namespace Util {

Task::Task() : isRunning(false) {

}

Task::~Task() {

}

void Task::run() {
	while (true) {
		if (isInterrupted()) {
			break;
		} else {
			runImpl();
		}
	}
}

void Task::start() {
	setIsRunning(true);
	thread.start(*this);
}

void Task::interrupt() {
	if (!isInterrupted()) {
		setIsRunning(false);
		thread.join();
	}
}

bool Task::isInterrupted() {
	return !isRunning;
}

void Task::setIsRunning(bool value) {
	isRunning = value;
}

} /* namespace Util */
} /* namespace OSCLib */
