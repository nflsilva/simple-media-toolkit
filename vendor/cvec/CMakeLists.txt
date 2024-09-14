cmake_minimum_required(VERSION 3.26.4)

project(cvec)

set(CVEC_SOURCES
  source/vec2.c
  source/vec3.c
  source/mat4.c
)

add_library(cvec STATIC ${CVEC_SOURCES})

target_include_directories(cvec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#include(CTest)
#add_subdirectory(tests)