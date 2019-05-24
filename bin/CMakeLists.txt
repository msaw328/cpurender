add_executable(cpurend
        main.c
        cpurend.c
        doublebuf.c
        )

target_link_libraries(cpurend PUBLIC SDL2)
target_link_libraries(cpurend PUBLIC m)
