#pragma once

#include <functional>

#include "Platform.h"


namespace prism {

void init(int argc, char **argv, std::function<void(int, char**)> func, Platform platformInfo);

void initDebug(int argc, char **argv, std::function<void(int, char**)> func, Platform platformInfo);

}