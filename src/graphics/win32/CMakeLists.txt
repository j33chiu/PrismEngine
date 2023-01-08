set(_INCL "${PROJECT_SOURCE_DIR}/include/graphics/win32")

target_sources(prism PRIVATE
    ${_INCL}/Win32OpenglWindow.h
	${_INCL}/Win32Window.h
    ${_INCL}/Win32WindowManager.h
	Win32OpenglWindow.cpp
    Win32Window.cpp
    Win32WindowManager.cpp
)