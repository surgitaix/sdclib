/*
 * WithLogger.cpp
 *
 *  Created on: 16.12.2015
 *      Author: matthias
 */

#include <OSELib/Helper/WithLogger.h>

namespace OSELib {

WithLogger::WithLogger(const std::string & loggerID) :
	_logger(Poco::Logger::get(loggerID))
{
}

WithLogger::~WithLogger() {

}

Poco::Logger & WithLogger::getLogger() {
	return _logger;
}

void WithLogger::log_fatal(std::function<std::string()> logmessage) const {
	if (_logger.fatal()) {
		_logger.fatal(logmessage());
	}
}

void WithLogger::log_critical(std::function<std::string()> logmessage) const {
	if (_logger.critical()) {
		_logger.critical(logmessage());
	}
}

void WithLogger::log_error(std::function<std::string()> logmessage) const {
	if (_logger.error()) {
		_logger.error(logmessage());
	}
}

void WithLogger::log_warning(std::function<std::string()> logmessage) const {
	if (_logger.warning()) {
		_logger.warning(logmessage());
	}
}

void WithLogger::log_notice(std::function<std::string()> logmessage) const {
	if (_logger.notice()) {
		_logger.notice(logmessage());
	}
}

void WithLogger::log_information(std::function<std::string()> logmessage) const {
	if (_logger.information()) {
		_logger.information(logmessage());
	}
}

void WithLogger::log_debug(std::function<std::string()> logmessage) const {
	if (_logger.debug()) {
		_logger.debug(logmessage());
	}
}

void WithLogger::log_trace(std::function<std::string()> logmessage) const {
	if (_logger.trace()) {
		_logger.trace(logmessage());
	}
}

void WithLogger::setDebugLevel(LogLevel logLevel) {
	switch(logLevel) {
		case LogLevel::NONE: _logger.setLevel(0); break;
		case LogLevel::FATAL: _logger.setLevel(Poco::Message::Priority::PRIO_FATAL); break;
		case LogLevel::CRITICAL: _logger.setLevel(Poco::Message::Priority::PRIO_CRITICAL); break;
		case LogLevel::ERROR: _logger.setLevel(Poco::Message::Priority::PRIO_ERROR); break;
		case LogLevel::WARNING: _logger.setLevel(Poco::Message::Priority::PRIO_WARNING); break;
		case LogLevel::NOTICE: _logger.setLevel(Poco::Message::Priority::PRIO_NOTICE); break;
		case LogLevel::INFORMATION: _logger.setLevel(Poco::Message::Priority::PRIO_INFORMATION); break;
		case LogLevel::DEBUG: _logger.setLevel(Poco::Message::Priority::PRIO_DEBUG); break;
		case LogLevel::TRACE: _logger.setLevel(Poco::Message::Priority::PRIO_TRACE); break;
	}
}

} /* namespace OSELib */
