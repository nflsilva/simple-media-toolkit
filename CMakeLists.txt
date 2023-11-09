cmake_minimum_required(VERSION "3.26.4")

set(TARGET_NAME "smt")
project(${TARGET_NAME})

add_compile_options(-Wall -Wextra)
file(GLOB_RECURSE SRC_FILES "source/*.c")
add_library(${TARGET_NAME} ${SRC_FILES})

add_subdirectory("dependencies/yavec2")
include_directories("dependencies/yavec2/include")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(${TARGET_NAME} ${OPENGL_LIBRARIES})

set(GLFW_BUILD_EXAMPLES false)
set(GLFW_BUILD_TESTS false)
add_subdirectory("dependencies/glfw")
include_directories("dependencies/glfw/include")
target_link_libraries(${TARGET_NAME} glfw)

add_subdirectory("dependencies/glad")
include_directories("dependencies/glad/include")
target_link_libraries(${TARGET_NAME} glad)

target_link_libraries(${TARGET_NAME} yavec2)
target_include_directories(${TARGET_NAME} PUBLIC "include")