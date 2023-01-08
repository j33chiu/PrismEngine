#pragma once

#include <stdexcept>
#include <string>

namespace prism {

class Exception : public std::runtime_error {
public:
    explicit Exception(const std::string &message);

    std::string message;
};

}