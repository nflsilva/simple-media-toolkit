cmake_minimum_required(VERSION 3.26.4)

set(TARGET_NAME smt)
project(${TARGET_NAME})
add_compile_options(-Wall -Wextra)

file(GLOB_RECURSE SMT_SOURCES source/*.c)
add_library(${TARGET_NAME} STATIC ${SMT_SOURCES})

set(GLFW_BUILD_EXAMPLES false)
set(GLFW_BUILD_TESTS false)
find_package(OpenGL REQUIRED)

add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/cutil)
add_subdirectory(dependencies/cvec)

set(
    SMT_INCLUDE_DIRS
    include
    ${OPENGL_INCLUDE_DIRS}
    dependencies/glad/include
    dependencies/glfw/include
    dependencies/cutil/include
    dependencies/cvec/include
)

set(
    SMT_LIBRARIES
    ${OPENGL_LIBRARIES}
    glad
    glfw
    cutil
    cvec
)

include_directories(${SMT_INCLUDE_DIRS})
link_libraries(${SMT_LIBRARIES})

include(CTest)
add_subdirectory(tests)