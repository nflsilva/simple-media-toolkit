cmake_minimum_required(VERSION 3.26.4)

set(GLAD_SOURCES
  src/glad.c
)

add_library(glad STATIC ${GLAD_SOURCES})

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)