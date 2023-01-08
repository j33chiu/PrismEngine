#include "core/Exception.h"

namespace prism {
    
Exception::Exception(const std::string &message) 
    : std::runtime_error(message), message(message)
{}

}

