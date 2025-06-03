cmake_minimum_required(VERSION 3.30)
project(torpedo C)


set(CMAKE_C_STANDARD 23)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_VULKAN OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/external/SDL)
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

target_link_libraries(torpedo PRIVATE SDL3-static)
target_include_directories(torpedo PRIVATE ${SDL3_INCLUDE_DIRS})