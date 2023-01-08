cmake_minimum_required(VERSION 3.16)

add_subdirectory("files")

set(_INCL "${PROJECT_SOURCE_DIR}/include/util")

target_sources(prism PRIVATE
	${_INCL}/PrismHash.h
)