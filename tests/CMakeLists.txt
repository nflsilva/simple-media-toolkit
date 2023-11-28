link_libraries(
    smt
    ${OPENGL_LIBRARIES}
    glad
    glfw
    cutil
)

add_executable(startupTests startup.c)
add_test(NAME StartupTests COMMAND startupTests)