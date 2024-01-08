#pragma once

#include <ostream>
#include <optional>
#include <variant>
#include <string>

#include "ExitEvent.h"
#include "FocusEvent.h"
#include "KeyEvent.h"
#include "MouseButtonEvent.h"
#include "MouseEvent.h"
#include "MouseScrollEvent.h"
#include "MouseMoveEvent.h"

#include "util/PrismHash.h"

namespace prism {

class Event {
public:

    // default constructor:
    Event(const EventType type = EventType::NONE);

    // acts as container for other event types
    Event(ExitEvent exitEvent);
    Event(FocusEvent focusEvent);
    Event(KeyEvent keyEvent);
    Event(MouseButtonEvent mouseButtonEvent);
    Event(MouseEvent mouseEvent);
    Event(MouseScrollEvent mouseScrollEvent);
    Event(MouseMoveEvent mouseMoveEvent);

    EventType getEventType() const;

    std::optional<ExitEvent> getExitEvent() const;
    bool isExitEvent() const;

    std::optional<FocusEvent> getFocusEvent() const;
    bool isFocusEvent() const;

    std::optional<KeyEvent> getKeyEvent() const;
    bool isKeyEvent() const;

    std::optional<MouseButtonEvent> getMouseButtonEvent() const;
    bool isMouseButtonEvent() const;

    std::optional<MouseEvent> getMouseEvent() const;
    bool isMouseEvent() const;

    std::optional<MouseScrollEvent> getMouseScrollEvent() const;
    bool isMouseScrollEvent() const;

    std::optional<MouseMoveEvent> getMouseMoveEvent() const;
    bool isMouseMoveEvent() const;

    friend std::ostream &operator<<(std::ostream& stream, const Event& event) {
        switch(event.getEventType()) {
        case EventType::EXIT:
            stream << "triggered EXIT event.";
            break;
        case EventType::FOCUS:
            stream << "triggered FOCUS event.";
            break;
        case EventType::KEY:
            stream << "triggered KEY event.";
            if (event.getKeyEvent().has_value())
                stream << event.getKeyEvent().value();
            break;
        case EventType::MOUSE:
            stream << "triggered MOUSE event.";
            if (event.getMouseEvent().has_value())
                stream << event.getMouseEvent().value();
            break;
        case EventType::MOUSE_BUTTON:
            stream << "triggered MOUSE_BUTTON event: ";
            if (event.getMouseButtonEvent().has_value())
                stream << event.getMouseButtonEvent().value();
            break;
        case EventType::MOUSE_SCROLL:
            stream << "triggered MOUSE_SCROLL event.";
            if (event.getMouseScrollEvent().has_value())
                stream <<  event.getMouseScrollEvent().value();
            break;
        case EventType::MOUSE_MOVE:
            // LOTS of debug messages: commented out
            //stream << "triggered MOUSE_MOVE event.";
            //if (event.getMouseMoveEvent().has_value())
            //    stream << event.getMouseMoveEvent().value();
            break;
        default:
            stream << "triggered UNKNOWN event.";
            break;
        }
        return stream;
    }

private:
    EventType eventType;

    std::variant<ExitEvent, FocusEvent, KeyEvent, MouseButtonEvent, MouseEvent, MouseScrollEvent, MouseMoveEvent> event;

    

};

}

namespace std {

// override hash for prism::Event objects
template<>
struct hash<prism::Event> {
    std::size_t operator()(const prism::Event& event) const {
        std::size_t hashResult;
        switch(event.getEventType()) {
        case prism::EventType::KEY:
            if (event.getKeyEvent().has_value())
                hashResult = prism::hash(event.getEventType(), event.getKeyEvent().value().key, event.getKeyEvent().value().keyState);
            else 
                hashResult = prism::hash(event.getEventType());
            break;
        case prism::EventType::MOUSE_BUTTON:
            if (event.getMouseButtonEvent().has_value())
                hashResult = prism::hash(event.getEventType(), event.getMouseButtonEvent().value().buttonId, event.getMouseButtonEvent().value().state);
            else
                hashResult = prism::hash(event.getEventType());
            break;
        case prism::EventType::MOUSE_SCROLL:
            if (event.getMouseScrollEvent().has_value())
                hashResult = prism::hash(event.getEventType(), event.getMouseScrollEvent().value().state);
            else 
                hashResult = prism::hash(event.getEventType());
            break;
        case prism::EventType::EXIT:
        case prism::EventType::FOCUS:
        case prism::EventType::MOUSE:
        case prism::EventType::MOUSE_MOVE:
        case prism::EventType::NONE:
        default:
            hashResult = prism::hash(event.getEventType());
            break;
        }

        return hashResult;
    }
};

}