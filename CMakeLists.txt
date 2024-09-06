cmake_minimum_required(VERSION 3.26.4)

set(TARGET_NAME smt)
project(${TARGET_NAME})
add_compile_options(-Wall -Wextra)

file(GLOB_RECURSE SMT_SOURCES source/*.c)
add_library(${TARGET_NAME} STATIC ${SMT_SOURCES})

set(GLFW_BUILD_EXAMPLES false)
set(GLFW_BUILD_TESTS false)
find_package(OpenGL REQUIRED)

set(
    SMT_INCLUDE_DIRS
    include
    ${OPENGL_INCLUDE_DIRS}
)

set(
    SMT_LIBRARIES
    ${OPENGL_LIBRARIES}
    glad
    glfw
    cutil
    cvec
)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/cutil)
add_subdirectory(vendor/cvec)

target_include_directories(${TARGET_NAME} PUBLIC ${SMT_INCLUDE_DIRS})
target_link_libraries(${TARGET_NAME} PUBLIC ${SMT_LIBRARIES})

include(CTest)
add_subdirectory(tests)
