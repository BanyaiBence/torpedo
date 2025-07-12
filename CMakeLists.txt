cmake_minimum_required(VERSION 3.30)
project(torpedo C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(lib/external/SDL EXCLUDE_FROM_ALL)
add_subdirectory(lib/internal/Graphics)
add_subdirectory(lib/internal/Table)


add_executable(torpedo 
        lib/internal/Graphics/Graphics.h
        lib/internal/Graphics/Graphics.c
        lib/internal/Table/Table.h
        lib/internal/Table/Table.c
        lib/internal/Common.h
        main.c
)

target_link_libraries(torpedo PRIVATE SDL3::SDL3)
