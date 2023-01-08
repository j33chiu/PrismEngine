# CMakeList.txt : CMake project for Prism_Engine, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.16)

project(Prism_Engine
	VERSION "0.1"
	DESCRIPTION "full game and application engine"
	LANGUAGES C CXX
)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)

# Add source to this project's executable.
#set (SOURCES
#	"include/core/testCmake.h" 
#	"src/core/testCmake.cpp"
#)
#file(GLOB_RECURSE _SRCS_DEVAPP "_sample/devApp/*.[hc]pp")
#add_executable(devApp ${_SRCS_DEVAPP})

#file(GLOB_RECURSE _SRCS_BLOCKGAME "_sample/blockgame/*.[hc]pp")
#add_executable(blockGame ${_SRCS_BLOCKGAME})

#file(GLOB_RECURSE _SRCS_PASSWORDMANAGER "_sample/passwordManager/*.[hc]pp")
#add_executable(passwordManager ${_SRCS_PASSWORDMANAGER})

#target_include_directories(devApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#target_include_directories(blockGame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#target_include_directories(passwordManager PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


add_library(prism STATIC "")


# platform specific setup
# for now, detect current machine platform
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(PRISM_PLATFORM "MACOS")
  if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm64")
    set(PRISM_PLATFORM_ARCH "ARM64")
  else()
    set(PRISM_PLATFORM_ARCH "X86_64")
  endif()
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(PRISM_PLATFORM "WIN32")
  set(PRISM_PLATFORM_ARCH "X86_64")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(PRISM_PLATFORM "LINUX")
  set(PRISM_PLATFORM_ARCH "X86_64")
else()
  message(FATAL_ERROR "Prism doesn't support platform: ${CMAKE_SYSTEM_NAME}")
endif()

if(PRISM_PLATFORM MATCHES "MACOS" OR PRISM_PLATFORM MATCHES "IOS")
  enable_language(OBJC)
  enable_language(OBJCXX)
  enable_language(ASM)
endif()

if(PRISM_PLATFORM MATCHES "LINUX")
  enable_language(ASM)
endif()


add_subdirectory("src")
add_subdirectory("_sample")

target_include_directories(prism PUBLIC ${PROJECT_SOURCE_DIR}/include)

enable_testing()
add_subdirectory("tests")

