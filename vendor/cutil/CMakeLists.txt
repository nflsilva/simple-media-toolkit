cmake_minimum_required(VERSION 3.26.4)

project(cutil)

set(CUTIL_SOURCES
  source/hashTable.c
  source/list.c
  source/filesystem.c
  source/math.c
  source/sort.c
  source/vector.c
)

add_library(cutil STATIC ${CUTIL_SOURCES})

target_include_directories(cutil PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(CTest)
add_subdirectory(tests)