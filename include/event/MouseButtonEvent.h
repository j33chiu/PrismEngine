#pragma once

#include "EventUtil.h"
#include "MouseEvent.h"

namespace prism {

struct MouseButtonEvent : MouseEvent {
    MouseButtonEvent(MouseButton buttonId, EventState state, short x, short y) 
        : MouseEvent(x, y), buttonId(buttonId), state(state)
    {}

    MouseButton buttonId;
    EventState state;

    friend std::ostream &operator<<(std::ostream& stream, const MouseButtonEvent& event) {
        switch (event.buttonId) {
            case MouseButton::LEFT:
                stream << "LEFT, ";
                break;
            case MouseButton::MIDDLE:
                stream << "MIDDLE, ";
                break;
            case MouseButton::RIGHT:
                stream << "RIGHT, ";
                break;
            case MouseButton::MB4:
                stream << "MB4, ";
                break;
            case MouseButton::MB5:
                stream << "MB5, ";
                break;
            default:
                stream << "unknown mouse button, ";
                break;
        }
        switch (event.state) {
            case EventState::UP:
                stream << "UP, ";
                break;
            case EventState::DOWN:
                stream << "DOWN, ";
                break;
            default:
                stream << "unknown event state, ";
                break;
        }
        stream << (MouseEvent)event;
        return stream;
    }

};

}