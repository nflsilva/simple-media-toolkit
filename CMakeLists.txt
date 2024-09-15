cmake_minimum_required(VERSION 3.26.4)

project(smt)
add_compile_options(-Wall -Wextra)

file(GLOB_RECURSE SMT_SOURCES "source/*.c")
add_library(smt STATIC ${SMT_SOURCES})

set(GLFW_BUILD_EXAMPLES false)
set(GLFW_BUILD_TESTS false)
find_package(OpenGL REQUIRED)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/cutil)
add_subdirectory(vendor/cvec)
add_subdirectory(vendor/stb)

target_include_directories(smt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${OPENGL_INCLUDE_DIRS})

target_link_libraries(smt PUBLIC ${OPENGL_LIBRARIES} glad glfw cutil cvec stb)

include(CTest)
add_subdirectory(tests)
