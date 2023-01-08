set(_INCL "${PROJECT_SOURCE_DIR}/include/event")

target_sources(prism PRIVATE
	${_INCL}/Event.h
	${_INCL}/EventUtil.h
	${_INCL}/ExitEvent.h
	${_INCL}/FocusEvent.h
	${_INCL}/KeyEvent.h
	${_INCL}/MouseButtonEvent.h
	${_INCL}/MouseEvent.h
	${_INCL}/MouseScrollEvent.h
	${_INCL}/MouseMoveEvent.h
	Event.cpp
	KeyEvent.cpp
)