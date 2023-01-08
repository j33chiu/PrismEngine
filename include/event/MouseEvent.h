#pragma once

#include <string>

#include "EventUtil.h"

namespace prism {

struct MouseEvent {
    MouseEvent(short x, short y)
        : x(x), y(y)
    {}

    short x;
    short y;

    friend std::ostream &operator<<(std::ostream& stream, const MouseEvent& event) {
        stream << "(x, y) = ";
        stream << "(";
        stream << std::to_string(event.x);
        stream << ", ";
        stream << std::to_string(event.y);
        stream << ")";
        return stream;
    }
};

}