cmake_minimum_required(VERSION 3.26.4)

set(stb_SOURCES
  include/stb_image.h
)

add_library(stb STATIC ${stb_SOURCES})

set_target_properties(stb PROPERTIES LINKER_LANGUAGE C)
target_include_directories(stb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)