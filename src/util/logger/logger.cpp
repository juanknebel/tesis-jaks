#include <iostream>
#include <new>
#include <cstdlib>

#include "logger.h"

// Definition (and initialization) of static attributes
Logger* Logger::m_ = 0;

#ifdef LOGGER_MULTITHREAD
pthread_mutex_t Logger::lock_ = PTHREAD_MUTEX_INITIALIZER;
inline void Logger::lock()
{
	pthread_mutex_lock(&lock_);
}

inline void Logger::unlock()
{
	pthread_mutex_unlock(&lock_);
}
#else
void Logger::lock() {}
void Logger::unlock() {}
#endif



/**
 * \brief Constructor.
 * It is a private constructor, called only by getInstance() and only the
 * first time. It is called inside a lock, so lock inside this method
 * is not required.
 * It only initializes the initial time. All configuration is done inside the
 * configure() method.
 */
Logger::Logger(): configured_(false)
{

	gettimeofday(&initialTime_, NULL);
}

/**
 * \brief Method to configure the logger. Called by the DEBUG_CONF() macro.
 * To make implementation easier, the old stream is always closed.
 * Then, in case, it is open again in append mode.
 * @param Name of the file used for logging
 * @param Configuration (i.e., log on file and on screen on or off)
 * @param Verbosity threshold for file
 * @param Verbosity threshold for screen
 */
void Logger::configure (const std::string&	outputFile,
                        const loggerConf	configuration,
                        const int		fileVerbosityLevel,
                        const int		screenVerbosityLevel)
{
	Logger::lock();

	fileVerbosityLevel_ = fileVerbosityLevel;
	screenVerbosityLevel_ = screenVerbosityLevel;

	// Close the old stream, if needed
	if (configuration_&file_on)
		out_.close();

	// Compute a new file name, if needed
	if (outputFile != logFile_) {
		std::ostringstream oss;
		time_t currTime;
		time(&currTime);
		struct tm *currTm = localtime(&currTime);
		oss << outputFile << "_" <<
		    currTm->tm_mday << "_" <<
		    currTm->tm_mon << "_" <<
		    (1900 + currTm->tm_year) << "_" <<
		    currTm->tm_hour << "-" <<
		    currTm->tm_min << "-" <<
		    currTm->tm_sec << ".log";
		logFile_ = oss.str().c_str();
	}

	// Open a new stream, if needed
	if (configuration&file_on)
		out_.open(logFile_.c_str(), std::ios::app);

	configuration_ = configuration;
	configured_ = true;

	Logger::unlock();
}

/**
 * \brief Destructor.
 * It only closes the file, if open, and cleans memory.
 */

Logger::~Logger()
{
	Logger::lock();

	if (configuration_&file_on)
		out_.close();

	delete m_;
	Logger::unlock();

}

/**
 * \brief Method to get a reference to the object (i.e., Singleton)
 * It is a static method.
 * @return Reference to the object.
 */
Logger& Logger::getInstance()
{
	Logger::lock();

	if (m_ == 0)
		m_ = new Logger;

	Logger::unlock();
	return *m_;
}


/**
 * \brief Method used to print messages.
 * Called by the DEBUG() macro.
 * @param Priority of the message
 * @param Source file where the method has been called (set equal to __FILE__
 * 	      by the DEBUG macro)
 * @param Source line where the method has been called (set equal to __LINE__
          by the macro)
 * @param Message
 */
void Logger::print(const unsigned int verbosityLevel,
                   const std::string& file,
                   const int line,
                   const std::string& message)
{
	if (!configured_) {
		//std::cerr << "ERROR: Logger not configured!" << std::endl;
		return;
	}

	struct timeval currentTime;

	gettimeofday(&currentTime, NULL);

	Logger::lock();

	if ((configuration_&file_on) && (verbosityLevel <= fileVerbosityLevel_))
		out_ << "DEBUG [" << file << ":" << line << "] @ " <<
		     (currentTime.tv_sec - initialTime_.tv_sec) <<
		     ":" << message << std::endl;

	if ((configuration_&screen_on) && (verbosityLevel <= screenVerbosityLevel_))
		std::cerr << "DEBUG [" << file << ":" << line << "] @ " <<
		          (currentTime.tv_sec - initialTime_.tv_sec) <<
		          ":" << message << std::endl;

	Logger::unlock();
}

void Logger::printWithNoError(const unsigned int verbosityLevel,
                              const std::string& file,
                              const int line,
                              const std::string& message)
{
	if (!configured_) {
		return;
	}

	struct timeval currentTime;

	gettimeofday(&currentTime, NULL);

	Logger::lock();

	if ((configuration_&file_on) && (verbosityLevel <= fileVerbosityLevel_))
		out_ << "DEBUG [" << file << ":" << line << "] @ " <<
		     (currentTime.tv_sec - initialTime_.tv_sec) <<
		     ":" << message << std::endl;

	if ((configuration_&screen_on) && (verbosityLevel <= screenVerbosityLevel_))
		std::cerr << "DEBUG [" << file << ":" << line << "] @ " <<
		          (currentTime.tv_sec - initialTime_.tv_sec) <<
		          ":" << message << std::endl;

	Logger::unlock();
}