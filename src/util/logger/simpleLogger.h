//
// Created by zero on 21/06/15.
//

#ifndef TESIS_JAKS_EXE_SIMPLELOGGER_H
#define TESIS_JAKS_EXE_SIMPLELOGGER_H

#include "logger.h"
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>

namespace logging = boost::log;

class SimpleLogger : public Logger {
private:
	static SimpleLogger* instance_;

	void init(std::string fileName);
	void logTrace(const char* file, int line, const char* function, std::string message);
	void logDebug(const char* file, int line, const char* function, std::string message);
	void logInfo(const char* file, int line, const char* function, std::string message);
	void logWarning(const char* file, int line, const char* function, std::string message);
	void logError(const char* file, int line, const char* function, std::string message);
	void logFatal(const char* file, int line, const char* function, std::string message);

	SimpleLogger() : Logger() {}
	~SimpleLogger() {
		if (this->instance_ != nullptr) {
			delete this->instance_;
		}
	}
public:
	static Logger* getInstance();
	void log(const char* file, int line, const char* function,
	         std::string message, SeverityLog srvLog);
};


#endif //TESIS_JAKS_EXE_SIMPLELOGGER_H
