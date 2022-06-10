/*
 * WithLogger.h
 *
 *  Created on: 16.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_HELPER_WITHLOGGER_H_
#define OSELIB_HELPER_WITHLOGGER_H_

#include <functional>

#include <Poco/Logger.h>

namespace OSELib
{
    namespace Log
    {
        /**
 * Declare the names for all used loggers here, so we can get a reference for
 * each logger later. That allows us to reconfigure each part independently.
 * For example we can get the EVENTSOURCE logger and set the log level
 * to maximum output only for log messages, that are related to the
 * event management on the provider side.
 *
 */
        const std::string BASE("SDCLib");
        const std::string RAWMESSAGES(BASE + ".RAW");
        const std::string SCHEMA(RAWMESSAGES + ".SCHEMA");
        const std::string SOAP(RAWMESSAGES + ".SOAP");
        const std::string DISCOVERY(RAWMESSAGES + ".DISCOVERY");
        const std::string SDC(BASE + ".SDC");
        const std::string SDCCONSUMER(SDC + ".CONSUMER");
        const std::string SDCCONSUMERADAPTER(SDC + ".CONSUMERADAPTER");
        const std::string sdcProvider(SDC + ".PROVIDER");
        const std::string SERVICEMANAGER(SDC + ".SERVICEMANAGER");
        const std::string HTTP(BASE + ".HTTP");
        const std::string EVENTING(BASE + ".EVENTING");
        const std::string EVENTSOURCE(EVENTING + ".SOURCE");
        const std::string EVENTSINK(EVENTING + ".SINK");
        const std::string STREAMING(BASE + ".STREAMING");
    }  // namespace Log

    //StF Refactored to avoid collision of ERROR with #def in wingdi.h
    enum class LogLevel
    {
        None,
        Fatal,
        Critical,
        Error,
        Warning,
        Notice,
        Information,
        Debug,
        Trace
    };

    namespace Helper
    {
        class WithLogger
        {
        private:
            Poco::Logger& _logger;

        public:
            WithLogger(const std::string& loggerID);
            virtual ~WithLogger() = default;

            Poco::Logger& getLogger();

            void log_fatal(std::function<std::string()> logmessage) const;
            void log_critical(std::function<std::string()> logmessage) const;
            void log_error(std::function<std::string()> logmessage) const;
            void log_warning(std::function<std::string()> logmessage) const;
            void log_notice(std::function<std::string()> logmessage) const;
            void log_information(std::function<std::string()> logmessage) const;
            void log_debug(std::function<std::string()> logmessage) const;
            void log_trace(std::function<std::string()> logmessage) const;

            void setDebugLevel(LogLevel logLevel);
        };
    }  // namespace Helper
}  // namespace OSELib

#endif
