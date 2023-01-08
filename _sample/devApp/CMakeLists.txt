cmake_minimum_required (VERSION 3.16)

# sample application
file(GLOB_RECURSE _SRCS_DEVAPP "*.[hc]pp")
add_executable(devApp ${_SRCS_DEVAPP})

target_include_directories(devApp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/_sample/devApp")
target_link_libraries(devApp prism)

