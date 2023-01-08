#include "event/Event.h"

namespace prism {

Event::Event(const EventType eventType) 
    : eventType(eventType)
{}

Event::Event(ExitEvent exitEvent) 
    : event(exitEvent), eventType(EventType::EXIT)
{}

Event::Event(FocusEvent focusEvent) 
    : event(focusEvent), eventType(EventType::FOCUS)
{}

Event::Event(KeyEvent keyEvent)
    : event(keyEvent), eventType(EventType::KEY)
{}

Event::Event(MouseButtonEvent mouseButtonEvent)
    : event(mouseButtonEvent), eventType(EventType::MOUSE_BUTTON)
{}

Event::Event(MouseEvent mouseEvent)
    : event(mouseEvent), eventType(EventType::MOUSE)
{}

Event::Event(MouseScrollEvent mouseScrollEvent)
    : event(mouseScrollEvent), eventType(EventType::MOUSE_SCROLL)
{}

Event::Event(MouseMoveEvent mouseMoveEvent)
    : event(mouseMoveEvent), eventType(EventType::MOUSE_MOVE)
{}

EventType Event::getEventType() const {
    return eventType;
}

std::optional<ExitEvent> Event::getExitEvent() const {
    if (isExitEvent()) return std::get<ExitEvent>(event);
    return {};
}

bool Event::isExitEvent() const {
    return std::holds_alternative<ExitEvent>(event);
}

std::optional<FocusEvent> Event::getFocusEvent() const {
    if (isFocusEvent()) return std::get<FocusEvent>(event);
    return {};
}

bool Event::isFocusEvent() const {
    return std::holds_alternative<FocusEvent>(event);
}

std::optional<KeyEvent> Event::getKeyEvent() const {
    if (isKeyEvent()) return std::get<KeyEvent>(event);
    return {};
}

bool Event::isKeyEvent() const {
    return std::holds_alternative<KeyEvent>(event);
}

std::optional<MouseButtonEvent> Event::getMouseButtonEvent() const {
    if (isMouseButtonEvent()) return std::get<MouseButtonEvent>(event);
    return {};
}

bool Event::isMouseButtonEvent() const {
    return std::holds_alternative<MouseButtonEvent>(event);
}

std::optional<MouseEvent> Event::getMouseEvent() const {
    if (isMouseEvent()) return std::get<MouseEvent>(event);
    return {};
}

bool Event::isMouseEvent() const {
    return std::holds_alternative<MouseEvent>(event);
}

std::optional<MouseScrollEvent> Event::getMouseScrollEvent() const {
    if (isMouseScrollEvent()) return std::get<MouseScrollEvent>(event);
    return {};
}

bool Event::isMouseScrollEvent() const {
    return std::holds_alternative<MouseScrollEvent>(event);
}

std::optional<MouseMoveEvent> Event::getMouseMoveEvent() const {
    if (isMouseMoveEvent()) return std::get<MouseMoveEvent>(event);
    return {};
}

bool Event::isMouseMoveEvent() const {
    return std::holds_alternative<MouseMoveEvent>(event);
}


}