add_subdirectory("math")

set(_INCL "${PROJECT_SOURCE_DIR}/include/core")


target_sources(prism PRIVATE
	${_INCL}/AutoResource.h
	${_INCL}/Camera.h
	${_INCL}/Controller.h
	${_INCL}/Exception.h
	${_INCL}/PrismInit.h
	${_INCL}/PrismRoot.h
	${_INCL}/Platform.h
	${_INCL}/PrismId.h
	Controller.cpp
	Exception.cpp
	PrismInit.cpp
	PrismRoot.cpp
	Camera.cpp
	PrismId.cpp
)