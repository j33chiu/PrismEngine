#pragma once

#include "EventUtil.h"

namespace prism {

struct FocusEvent {
    FocusEvent(EventState state)
        : state(state)
    {}

    EventState state;
};

}