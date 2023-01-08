cmake_minimum_required(VERSION 3.16)

set(_INCL "${PROJECT_SOURCE_DIR}/include/util/files")

target_sources(prism PRIVATE
	${_INCL}/FileManager.h
    FileManager.cpp
)