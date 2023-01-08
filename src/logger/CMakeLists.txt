set(_INCL "${PROJECT_SOURCE_DIR}/include/logger")

target_sources(prism PRIVATE
	${_INCL}/Logger.h
	${_INCL}/LogLevel.h
)