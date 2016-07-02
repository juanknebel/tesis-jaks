//
// Created by zero on 21/06/15.
//

#include "simpleLogger.h"

SimpleLogger* SimpleLogger::instance_ = nullptr;

void SimpleLogger::init(std::string fileName)
{
	logging::add_file_log(fileName);

	// logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::trace);
}

void SimpleLogger::log(const char* file, int line, const char* function,
                       std::string message, SeverityLog srvLog)
{
	switch(srvLog) {
	case Logger::SeverityLog::trace:
		this->logTrace(file, line, function, message);
		break;

	case Logger::SeverityLog::debug:
		this->logDebug(file, line, function, message);
		break;

	case Logger::SeverityLog::info:
		this->logInfo(file, line, function, message);
		break;

	case Logger::SeverityLog::warning:
		this->logWarning(file, line, function, message);
		break;

	case Logger::SeverityLog::error:
		this->logError(file, line, function, message);
		break;

	case Logger::SeverityLog::fatal:
		this->logFatal(file, line, function, message);
		break;
	}
}

Logger *SimpleLogger::getInstance()
{
	if (instance_ == nullptr) {
		instance_ = new SimpleLogger();
		instance_->init("sample.log");
	}

	return instance_;
}

void SimpleLogger::logTrace(const char* file, int line, const char* function, std::string message)
{
	BOOST_LOG_TRIVIAL(trace) << "{fileName: \"" << file <<
	                         "\", lineNumber: " << line <<
	                         ", functionName: \"" << function <<
	                         "\", message: \"" << message << "\"}";
}

void SimpleLogger::logDebug(const char* file, int line, const char* function, std::string message)
{
	BOOST_LOG_TRIVIAL(debug) << "{fileName: \"" << file <<
	                         "\", lineNumber: " << line <<
	                         ", functionName: \"" << function <<
	                         "\", message: \"" << message << "\"}";
}

void SimpleLogger::logInfo(const char* file, int line, const char* function, std::string message)
{
	BOOST_LOG_TRIVIAL(info) << "{fileName: \"" << file <<
	                        "\", lineNumber: " << line <<
	                        ", functionName: \"" << function <<
	                        "\", message: \"" << message << "\"}";
}

void SimpleLogger::logWarning(const char* file, int line, const char* function, std::string message)
{
	BOOST_LOG_TRIVIAL(warning) << "{fileName: \"" << file <<
	                           "\", lineNumber: " << line <<
	                           ", functionName: \"" << function <<
	                           "\", message: \"" << message << "\"}";
}

void SimpleLogger::logError(const char* file, int line, const char* function, std::string message)
{
	BOOST_LOG_TRIVIAL(error) << "{fileName: \"" << file <<
	                         "\", lineNumber: " << line <<
	                         ", functionName: \"" << function <<
	                         "\", message: \"" << message << "\"}";
}

void SimpleLogger::logFatal(const char* file, int line, const char* function, std::string message)
{
	BOOST_LOG_TRIVIAL(fatal) << "{fileName: \"" << file <<
	                         "\", lineNumber: " << line <<
	                         ", functionName: \"" << function <<
	                         "\", message: \"" << message << "\"}";
}

