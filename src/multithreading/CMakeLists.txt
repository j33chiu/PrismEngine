set(_INCL "${PROJECT_SOURCE_DIR}/include/multithreading")

target_sources(prism PRIVATE
	${_INCL}/Queue.h
	${_INCL}/Vector.h
)