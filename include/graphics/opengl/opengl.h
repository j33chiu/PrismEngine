#pragma once

#include <optional>
#include <sstream>
#include <string>
#include <string_view>

#if defined(PRISM_PLATFORM_WIN32)
#include <Windows.h>
#include <gl/gl.h>
#pragma comment(lib, "opengl32.lib")
#elif defined(PRISM_PLATFORM_LINUX)
#include <GL/gl.h>
#include <GL/glx.h>
#else 
#error unsupported platform for opengl
#endif

#define PRISM_OPENGL_MAJOR_VERSION 4
#define PRISM_OPENGL_MINOR_VERSION 5

// by default all gl functions are extern unless specified
#if defined(DONT_MAKE_GL_EXTERN)
#define EXTERN
#else
#define EXTERN extern
#endif
#include "graphics/opengl/openglDef.h"

namespace prism {

void checkGLError();

void checkGLError(std::string baseErrMsg);

}