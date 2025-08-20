cmake_minimum_required(VERSION 3.26.4)

project(smt)
add_compile_options(-Wall -Wextra)

file(GLOB_RECURSE SMT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c)
add_library(smt STATIC ${SMT_SOURCES})

set(GLFW_BUILD_EXAMPLES false)
set(GLFW_BUILD_TESTS false)
find_package(OpenGL REQUIRED)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/cutil)
add_subdirectory(vendor/stb)

file(GLOB_RECURSE SHADER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.glsl)

# List to store generated header files
set(GENERATED_SHADER_HEADERS "")

# Loop over each shader and create a rule to generate its header
foreach(SHADER_FILE ${SHADER_SOURCES})
    get_filename_component(SHADER_NAME ${SHADER_FILE} NAME_WE)
    set(OUTPUT_HEADER ${SHADER_NAME}_shader.h)

    add_custom_command(
        OUTPUT ${OUTPUT_HEADER}
        COMMAND xxd -i -n ${SHADER_NAME}_shader ${SHADER_FILE} > ${OUTPUT_HEADER}
        DEPENDS ${SHADER_FILE}
        COMMENT "Embedding ${SHADER_FILE} -> ${OUTPUT_HEADER}"
        VERBATIM
    )

    list(APPEND GENERATED_SHADER_HEADERS ${OUTPUT_HEADER})
endforeach()

set_source_files_properties(${GENERATED_HEADERS} PROPERTIES GENERATED TRUE)

target_sources(smt PRIVATE ${GENERATED_SHADER_HEADERS})
target_include_directories(smt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${OPENGL_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(smt PUBLIC ${OPENGL_LIBRARIES} glad glfw cutil stb)

include(CTest)
add_subdirectory(tests)
