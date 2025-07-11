cmake_minimum_required(VERSION 3.30)
project(Torpedo C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(lib/external/SDL EXCLUDE_FROM_ALL)
add_subdirectory(lib/internal/Graphics)
add_subdirectory(lib/internal/Table)

add_executable(Torpedo main.c
        table.c
        table.h
        lib/internal/Graphics/Graphics.c
        lib/internal/Graphics/Graphics.h
        lib/internal/Common.h
        lib/internal/Table/Table.c
        lib/internal/Table/Table.h
)

target_link_libraries(Torpedo PRIVATE SDL3::SDL3)
