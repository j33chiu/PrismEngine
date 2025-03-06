#pragma once

#include <string>
#include <unordered_map>
#include <thread>

#include "event/Event.h"
#include "event/KeyEvent.h"

namespace prism {

/**
 * basic controller class
 * handles user input
*/

class Controller {

public:
    Controller();

    // register/map an event to a game function
    void registerEvent(Event event/*, function*/);

    // automatically load events and functions from a file
    virtual void loadEvents(std::string eventFileName);

protected:

    // execute function mapped to an event
    void run(Event event);  

private:
    //std::unordered_map<Event, /*function*/>;

};

}
