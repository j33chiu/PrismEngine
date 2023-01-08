#pragma once

#include "EventUtil.h"

namespace prism {

struct KeyEvent {
    KeyEvent(KeyId key, EventState keyState)
        : key(key), keyState(keyState)
    {}

    KeyId key;
    EventState keyState;

    static std::vector<std::string> keyList;

    friend std::ostream &operator<<(std::ostream& stream, const KeyEvent& event) {
        switch(event.keyState) {
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
        stream << keyList[(int)event.key];
        stream << ")";

        return stream;
    }

};

}
