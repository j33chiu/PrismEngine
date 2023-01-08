#pragma once

#include <mutex>
#include <ctime>

#include "LogLevel.h"

namespace prism {


/**
 * Logger class, contains a global instance for global logging (thread-safe)
 * public static methods to allow implicit access to the instance
 * public static methods to turn on/off logging etc
 * public static methods to set log location (console, file etc)
 */
class Logger {
public:

    static void turnOn() {
        instance().turnOnImpl();
    }

    static void turnOff() {
        instance().turnOffImpl();
    }

    static void setLogOutputLocation(std::string logFileName) {
        instance().setLogOutputLocationImpl(logFileName);
    }

    static void setMinLogLevel(LogLevel minLogLevel) {
        instance().setMinLogLevelImpl(minLogLevel);
    }

    template <typename T>
    static void log(const LogLevel logLevel, const T &obj) {
        instance().logImpl(logLevel, obj);
    }

    template <typename T>
    static void log(const LogLevel logLevel, std::string className, const T &obj) {
        instance().logImpl(logLevel, className, obj);
    }

    template <typename T>
    static void debug(const T &obj) {
        instance().logImpl(LogLevel::DEBUG, obj);
    }

    template <typename T>
    static void debug(std::string className, const T &obj) {
        instance().logImpl(LogLevel::DEBUG, className, obj);
    }

    template <typename T>
    static void info(const T &obj) {
        instance().logImpl(LogLevel::INFO, obj);
    }

    template <typename T>
    static void info(std::string className, const T &obj) {
        instance().logImpl(LogLevel::INFO, className, obj);
    }


    template <typename T>
    static void warn(const T &obj) {
        instance().logImpl(LogLevel::WARN, obj);
    }

    template <typename T>
    static void warn(std::string className, const T &obj) {
        instance().logImpl(LogLevel::WARN, className, obj);
    }


    template <typename T>
    static void error(const T &obj) {
        instance().logImpl(LogLevel::ERR, obj);
    }

    template <typename T>
    static void error(std::string className, const T &obj) {
        instance().logImpl(LogLevel::ERR, className, obj);
    }

private:
    Logger() : 
        outputStream(std::cout.rdbuf()),
        shouldLog(false),
        logFileName(""),
        minLogLevel(LogLevel::DEBUG),
        logMutex()
    {}

    static Logger &instance() {
        static Logger logger{};
        return logger;
    }

    void turnOnImpl() {
        shouldLog = true;
    }

    void turnOffImpl() {
        shouldLog = false;
    }

    void setLogOutputLocationImpl(std::string logFileName) {
        this->logFileName = logFileName;
        if (logFileName.empty()) {
            outputStream.rdbuf(std::cout.rdbuf());
        } else {
            // TODO: create log file using logFileName
        }
    }

    void setMinLogLevelImpl(LogLevel minLogLevel) {
        this->minLogLevel = minLogLevel;
    }

    template<typename T>
    void logImpl(const LogLevel logLevel, const T &obj) {
        if (!shouldLog) return;
        if (logLevel >= minLogLevel) {
            std::unique_lock<std::mutex> lock(logMutex);
            outputStream << logLevel;
            outputStream << "[" << getCurrentTime() << "] ";
            outputStream << obj;
            outputStream << std::endl;
            if (outputStream.rdbuf() == std::cout.rdbuf()) outputStream << "\033[39m"; // return to default colour
        }
    }

    template<typename T>
    void logImpl(const LogLevel logLevel, std::string className, const T &obj) {
        if (!shouldLog) return;
        if (logLevel >= minLogLevel) {
            std::unique_lock<std::mutex> lock(logMutex);
            outputStream << logLevel;
            // format className to [className ...], 30 characters long
            std::string formattedClassName(30, '.');
            formattedClassName.replace(0, 
                className.length() < 27 ? className.length() : 27, 
                className.length() < 27 ? className : className.substr(0, 27));
            outputStream << "[" << formattedClassName << "] ";
            outputStream << "[" << getCurrentTime() << "] ";
            outputStream << obj;
            outputStream << std::endl;
            if (outputStream.rdbuf() == std::cout.rdbuf()) outputStream << "\033[39m"; // return to default colour
        }
    }

    std::string getCurrentTime() {
        struct tm timeInfo;
        time_t now = time(0);
        localtime_s(&timeInfo, &now);
        
        char buffer[80];
        strftime(buffer,sizeof(buffer),"%H:%M:%S",&timeInfo);
        std::string str(buffer);

        return str;
    }

    std::ostream outputStream;
    bool shouldLog;
    std::string logFileName;
    LogLevel minLogLevel;
    std::mutex logMutex;

};

}