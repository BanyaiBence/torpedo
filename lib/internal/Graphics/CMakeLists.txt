add_library(Graphics STATIC
        Graphics.c
        Graphics.h
)

target_include_directories(Graphics
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}  
)

set_target_properties(Graphics PROPERTIES
        VERSION 1.0.0
        SOVERSION 1
)

target_link_libraries(Graphics PRIVATE SDL3::SDL3)
