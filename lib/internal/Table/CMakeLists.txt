
add_library(Table
        Table.c
        Table.h
)

# Link SDL3 (static)
target_link_libraries(Table PRIVATE Graphics)


target_include_directories(Table
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)


set_target_properties(Table PROPERTIES
        VERSION 1.0.0
        SOVERSION 1
)

