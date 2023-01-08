#include "event/KeyEvent.h"

namespace prism {

std::vector<std::string> KeyEvent::keyList = {
    "NONE",
    "UNKNWN",
    "NUM0", "NUM1", "NUM2", "NUM3", "NUM4", "NUM5", "NUM6", "NUM7", "NUM8", "NUM9",
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
    "ESC", "FUNC", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24",
    "GRAVE", "MINUS", "EQ", "L_SQ_BRACK", "R_SQ_BRACK", "BACKSLASH", "SEMICOLON", "QUOTE", "COMMA", "PERIOD", "SLASH",
    "SPACE", "BACKSPACE", "TAB", "CAPS", "RETURN", "L_SHIFT", "R_SHIFT", "L_CTRL", "R_CTRL", "L_CODE", "R_CODE", "L_ALT", "R_ALT", "SYS",
    "INS", "DEL", "HELP", "HOME", "END", "PG_UP", "PG_DN", "ARR_UP", "ARR_L", "ARR_DN", "ARR_R", 
    "VOL_UP", "VOL_DN", "MUTE", 
    "NP_DECIMAL", "NP_MULT", "NP_DIV", "NP_PLUS", "NP_MINUS", "NP_CLEAR", "NP_ENTER", "NP_EQ", "NP0", "NP1", "NP2", "NP3", "NP4", "NP5", "NP6", "NP7", "NP8", "NP9"
};

}