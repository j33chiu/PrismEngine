#pragma once

#include <string>

#include "EventUtil.h"
#include "MouseEvent.h"

namespace prism {

struct MouseScrollEvent : MouseEvent {
    MouseScrollEvent(float wheelDelta, short x, short y)
        : MouseEvent(x, y), state(wheelDelta > 0 ? EventState::UP : EventState::DOWN), wheelDelta(wheelDelta)
    {}

    EventState state;
    float wheelDelta;

    friend std::ostream &operator<<(std::ostream& stream, const MouseScrollEvent& event) {
        switch(event.state) {
            case EventState::UP:
                stream << "UP(";
                break;
            case EventState::DOWN:
                stream << "DOWN(";
                break;
            default:
                stream << "unknown event state(";
                break;
        }
        stream << std::to_string(event.wheelDelta);
        stream << "), ";
        stream << (MouseEvent)event;
        return stream;
    }
};

}