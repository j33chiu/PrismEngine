#pragma once

#include <cstdint>
#include <iosfwd>
#include <iostream>

namespace prism {

enum class LogLevel : std::uint8_t {
    DEBUG,
    INFO,
    WARN,
    ERR
};

/**
 * function to write loglevel enum to stream
*/
inline std::ostream &operator<<(std::ostream &stream, const LogLevel logLevel) {
    switch (logLevel) {
        case LogLevel::DEBUG:
            if (stream.rdbuf() == std::cout.rdbuf()) stream << "\033[39m";
            stream << "[DEBUG ] "; 
            break;
        case LogLevel::INFO:
            if (stream.rdbuf() == std::cout.rdbuf()) stream << "\033[32m";
            stream << "[INFO  ] "; 
            break;
        case LogLevel::WARN:
            if (stream.rdbuf() == std::cout.rdbuf()) stream << "\033[33m";
            stream << "[WARN  ] "; 
            break;
        case LogLevel::ERR:
            if (stream.rdbuf() == std::cout.rdbuf()) stream << "\033[31m";
            stream << "[ERROR ] "; 
            break;
        default:
            if (stream.rdbuf() == std::cout.rdbuf()) stream << "\033[39m";
            stream << "[UNKNWN] "; 
            break;
    }
    return stream;
}

}