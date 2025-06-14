cmake_minimum_required(VERSION 3.30)
project(torpedo C)


set(CMAKE_C_STANDARD 23)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(lib/external/SDL EXCLUDE_FROM_ALL)
add_subdirectory(lib/internal/Graphics)
add_subdirectory(lib/internal/Table)
add_subdirectory(lib/internal/Generics)
add_subdirectory(lib/internal/UtilMacros)

add_executable(torpedo main.c
        lib/internal/Table/Table.c
        lib/internal/Table/Table.h
        lib/internal/Graphics/Graphics.c
        lib/internal/Graphics/Graphics.h
        lib/internal/Generics/Generics.c
        lib/internal/Generics/Generics.h
        lib/internal/Generics/Array.h
        lib/internal/UtilMacros/UtilMacros.h
)

target_link_libraries(torpedo PRIVATE SDL3::SDL3)
#target_include_directories(torpedo PRIVATE ${SDL3_INCLUDE_DIRS})
