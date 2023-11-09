cmake_minimum_required(VERSION "3.26.4")

set(TARGET_NAME "yavec2")
project(${TARGET_NAME})

include_directories(include)
file(GLOB_RECURSE SRC_FILES "source/*.c")

add_library(${TARGET_NAME} STATIC ${SRC_FILES})
