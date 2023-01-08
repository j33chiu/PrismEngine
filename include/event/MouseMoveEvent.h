#pragma once

#include "EventUtil.h"
#include "MouseEvent.h"

namespace prism {

struct MouseMoveEvent : MouseEvent {
    MouseMoveEvent(short dX, short dY, short x, short y)
        : MouseEvent(x, y), dX(dX), dY(dY)
    {}

    short dX;
    short dY;

    friend std::ostream &operator<<(std::ostream& stream, const MouseMoveEvent& event) {
        stream << "(dX, dY) = ";
        stream << "(";
        stream << std::to_string(event.dX);
        stream << ", ";
        stream << std::to_string(event.dY);
        stream << "), ";
        stream << (MouseEvent)event;
        return stream;
    }

};


}