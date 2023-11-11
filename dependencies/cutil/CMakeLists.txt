cmake_minimum_required(VERSION "3.26.4")

set(TARGET_NAME "cutils")
project(${TARGET_NAME})

include(CTest)
include_directories(include)
file(GLOB_RECURSE SRC_FILES source/*.c)

add_subdirectory(tests)

add_library(${TARGET_NAME} STATIC ${SRC_FILES})