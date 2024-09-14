#pragma once

#include <ostream>
#include <string>

namespace prism {

struct SizeEvent {
    SizeEvent(unsigned int newWidth, unsigned int newHeight)
        : newWidth(newWidth), newHeight(newHeight)
    {}

    unsigned int newWidth;
    unsigned int newHeight;

    friend std::ostream &operator<<(std::ostream& stream, const SizeEvent& event) {
        stream << "(width, height) = (";
        stream << std::to_string(event.newWidth);
        stream << ", ";
        stream << std::to_string(event.newHeight);
        stream << ")";
        return stream;
    }
};

}